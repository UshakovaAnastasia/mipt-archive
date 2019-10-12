

#include <deque>
#include <future>
#include <memory>
#include <functional>
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <type_traits>
#include <numeric>

template<typename T>
class threadsafe_queue
{
private:
    mutable std::mutex mut;
    std::queue<std::shared_ptr<T> > data_queue;
    std::condition_variable data_cond;
public:
    threadsafe_queue()
    {}
    
    void wait_and_pop(T& value)
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] {return !data_queue.empty(); });
        value = std::move(*data_queue.front());
        data_queue.pop();
    }
    
    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return false;
        value = std::move(*data_queue.front());
        data_queue.pop();
        return true;
    }
    
    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk, [this] {return !data_queue.empty(); });
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }
    
    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if (data_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res = data_queue.front();
        data_queue.pop();
        return res;
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }
    
    void push(T new_value)
    {
        std::shared_ptr<T> data(
                                std::make_shared<T>(std::move(new_value)));
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(data);
        data_cond.notify_one();
    }
};


class join_threads
{
    std::vector<std::thread>& m_threads;
public:
    explicit join_threads(std::vector<std::thread>& t) :
    m_threads(t){}
    
    ~join_threads()
    {
        for(long i=0; i<m_threads.size(); ++i){
            if(m_threads[i].joinable()){
                m_threads[i].join();
            }
        }
    }
};

class wrapper{
    struct impl_base
    {
        virtual void call()=0;
        virtual ~impl_base() {}
    };
    
    template<typename F>
    
    struct impl_type : impl_base
    {
        F m_f;
        impl_type(F && f) :
        m_f(std::move(f))
        {}
        void call(){m_f();}
    };
    
    std::unique_ptr<impl_base> impl;
    
public:
    wrapper()=default;
    template < typename F >
    wrapper(F && f) :
    impl(new impl_type<F>(std::move(f)))
    {}
    void operator()() {impl->call();}
    
    wrapper(wrapper && other) :
    impl(std::move(other.impl))
    {}
    
    wrapper & operator= (wrapper && other){
        impl=std::move(other.impl);
        return *this;
    }
    wrapper (const wrapper&)=delete;
    wrapper& operator=(const wrapper&)=delete;
};

class work_stealing_queue
{
private:
    typedef wrapper data_type;
    std::deque<data_type> the_queue;
    mutable std::mutex the_mutex;
    
public:
    work_stealing_queue()
    {}
    
    work_stealing_queue(const work_stealing_queue& other) = delete;
    work_stealing_queue& operator=(
                                   const work_stealing_queue& other) = delete;
    
    void push(data_type data)
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        the_queue.push_front(std::move(data));
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        return the_queue.empty();
    }
    
    bool try_pop(data_type& res)
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        if (the_queue.empty())
        {
            return false;
        }
        
        res = std::move(the_queue.front());
        the_queue.pop_front();
        return true;
    }
    
    bool try_steal(data_type& res)
    {
        std::lock_guard<std::mutex> lock(the_mutex);
        if (the_queue.empty())
        {
            return false;
        }
        
        res = std::move(the_queue.back());
        the_queue.pop_back();
        return true;
    }
};

class thread_pool
{
public:
    using task_type = wrapper;
    
private:
    std::atomic_bool flag;
    threadsafe_queue < task_type > common_queue;
    std::vector < std::unique_ptr < work_stealing_queue > > local_queues;
    std::vector<std::thread> threads;
    join_threads joiner;
    
    static thread_local work_stealing_queue * local_queue;
    static thread_local std::uint64_t local_index;
    
    void worker_thread(std::uint64_t index)
    {
        local_index = index;
        local_queue = local_queues[local_index].get();
        
        while(!flag)
        {
            run();
        }
    }
    
    bool pop_task_from_local_queue(task_type & task)
    {
        return local_queue && local_queue->try_pop(task);
    }
    
    bool pop_task_from_common_queue(task_type & task)
    {
        return common_queue.try_pop(task);
    }
    
    bool pop_task_from_other_local_queue(task_type & task)
    {
        for(std::size_t i = 0; i < local_queues.size(); ++i)
        {
            const std::uint64_t index = (local_index + i + 1) % local_queues.size();
            
            if(local_queues[index]->try_steal(task))
            {
                return true;
            }
        }
        return false;
    }
    
public:
    thread_pool():
    joiner(threads), flag(false)
    {
        const std::size_t thread_count = std::thread::hardware_concurrency();
        
        try
        {
            for(std::size_t i = 0; i < thread_count; ++i)
            {
                local_queues.push_back(std::unique_ptr < work_stealing_queue > (new work_stealing_queue));
                threads.push_back(std::thread(&thread_pool::worker_thread, this, i));
            }
        }
        catch(...)
        {
            flag = true;
            throw;
        }
    }
    
    ~thread_pool()
    {
        flag = true;
    }
    
    template < typename Function_Type >
    std::future < typename std::result_of < Function_Type() > ::type > submit(Function_Type f)
    {
        using result_type = typename std::result_of < Function_Type() > ::type;
        
        std::packaged_task < result_type() > task(f);
        std::future < result_type > result(task.get_future());
        if(local_queue)
        {
            local_queue->push(std::move(task));
        }
        else
        {
            common_queue.push(std::move(task));
        }
        return result;
    }
    
    void run()
    {
        task_type task;
        
        if(pop_task_from_local_queue(task) || pop_task_from_common_queue(task) || pop_task_from_other_local_queue(task))
        {
            task();
        }
        else
        {
            std::this_thread::yield();
        }
    }
};

thread_local work_stealing_queue * thread_pool::local_queue = nullptr;

thread_local std::uint64_t thread_pool::local_index = 0;
template<typename Iterator, typename T>
struct accumulate_block{
    accumulate_block(Iterator first, Iterator last) :
    m_first(first), m_last(last)
    {}
    T operator()(){
        T result = 0;
        return std::accumulate(m_first, m_last, result);
    }
    Iterator m_first, m_last;
};


template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init){
    long length=std::distance(first, last);
    if(!length){
        return init;
    }
    long block_size=25;
    long num_blocks=(length+block_size - 1)/block_size;
    std::vector<std::future<T>> futures(num_blocks-1);
    thread_pool pool;
    Iterator block_start = first;
    
    for (std::size_t index = 0; index < (num_blocks - 1); ++index)
    {
        Iterator block_end = block_start;
        
        std::advance(block_end, block_size);
        futures[index]=pool.submit(accumulate_block < Iterator, T > (block_start, block_end));
        
        block_start = block_end;
    }
    T last_result=0;
    last_result=std::accumulate(block_start, last, last_result);
    T result = init;
    for (std::size_t index = 0; index < (num_blocks - 1); ++index)
    {
        result+=futures[index].get();
    }
    result+=last_result;
    return result;
}

int main(int argc, char ** argv)
{
    std::vector<int> v;
    for (int i=0; i<566; ++i){
        v.push_back(1);
    }
    int result=0;
    
    std::cout<<parallel_accumulate(v.begin(), v.end(), result)<<std::endl;
    return 0;
}


#include<iostream>
#include<memory>
#include<mutex>
#include <thread>
#include <queue>
#include <condition_variable>

/*std::mutex m;
std::queue<int> data_q;
std::condition_variable data_c;*/

template<typename T>
class threadsafe_queue {
private:
    std::mutex mutex;
    std::queue<T> data_queue;
    std::condition_variable data_c;


public:
    threadsafe_queue() {};

    threadsafe_queue& operator=(threadsafe_queue const  &)= delete;

    threadsafe_queue(const threadsafe_queue &obj) {
        std::lock_guard<std::mutex> lk(mutex);
        data_queue = obj.data_queue;
    }

    void push(T new_value) {
        std::lock_guard<std::mutex> lk(mutex);
        data_queue.push(new_value);
        std::cout<<new_value<<" is in"<<std::endl;
        data_c.notify_one();
        
    }

    void wait_and_pop(T &value) {
        std::unique_lock<std::mutex> lk(mutex);
        std::cout<<"waiting..."<<std::endl;
        data_c.wait(lk, [this] { return !data_queue.empty(); });
        
        value = data_queue.front();
        data_queue.pop();
        std::cout<<value<<" is out"<<std::endl;
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lk(mutex);
        data_c.wait(lk, [this] { return !data_queue.empty(); });
        T t = data_queue.front();
        std::shared_ptr<T> a = std::make_shared<T>(t);
        data_queue.pop();
        return a;

    }

    bool try_pop(T &value) {
        std::unique_lock<std::mutex> lk(mutex);
        if (!data_queue.empty()) {
            value = data_queue.front();
            data_queue.pop();
            return true;
        }
        return false;
    }

    std::shared_ptr<T> try_pop() {
        std::unique_lock<std::mutex> lk(mutex);
        if (!data_queue.empty()) {
            T t = data_queue.front();
            std::shared_ptr<T> a = std::make_shared<T>(t);
            data_queue.pop();
            return a;
        }
        return nullptr;
    }

    bool empty() {
        std::lock_guard<std::mutex> lk(mutex);
        if (data_queue.empty()) {
            return true;
        }
        return false;
    }

    int size() {
        std::lock_guard<std::mutex> lk(mutex);
        return data_queue.size();
    }


};

threadsafe_queue<int> t;


std::vector<int> prepare_data() {
    std::vector<int> a;
    for (int i=0; i<10; i++){
        a.push_back(i);
    }
    return a;
}

void data_preparation() {
    std::vector<int> data = prepare_data();
    for (int i=0; i<10; i++){
        t.push(data[i]);
    }


}

void data_processing() {
    for (int i=0; i<10; i++){
        int value;
        t.wait_and_pop(value);
    }

}

int main(int argc, char **argv) {
    std::thread t1(data_preparation);
    std::thread t2(data_processing);
    t1.join();
    t2.join();
    std::cout << std::endl;
    std::cout <<"It is "<< std::boolalpha << t.empty() <<" that the queue is empty."<< std::endl;
    std::cout<<"Its size is "<<t.size()<<"."<<std::endl;
    return 0;
}
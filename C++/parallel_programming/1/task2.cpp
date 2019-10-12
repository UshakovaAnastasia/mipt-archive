#include <ctime>
#include <cstdlib>
#include <mutex>
#include <list>
#include <algorithm>
#include <iostream>
#include <deque>
#include <thread>
#include <random>


long n_square;
long n_circle;
std::mutex some_mutex;

double rand(double _max, double _min) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> urd(_min, _max);
    return urd(gen);
}

class Rpoint {
private:
    double x;
    double y;
public:
    Rpoint(double min, double max) {
        x = rand(min, max);
        y = rand(min, max);
    }

    bool in_circle() {
        if ((x - 1) * (x - 1) + (y - 1) * (y - 1) <= 1) {
            return true;
        }
        return false;
    }

    void print() {
        std::cout << x << ' ' << y << std::endl;
    }
};

void incr(long n) {

    for (long i = 0; i < n; ++i) {
        Rpoint r(0, 2);
        if (r.in_circle()) {
            std::lock_guard<std::mutex> guard(some_mutex);
            n_circle += 1;
        }
    }
}

void parallel_incr(int num_threads) {
    long n = n_square / num_threads;
    std::vector<std::thread> threads(num_threads);
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread(incr, n);

    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

}


int main() {
    n_square = 10000000;
    n_circle = 0;
    int num_threads = 10;
    parallel_incr(num_threads);
    double c = n_circle;
    double s = n_square;
    std::cout << 4 * c / s << std::endl;

    return 0;
}




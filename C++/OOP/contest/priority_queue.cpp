#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <sstream>

class MinSumCalculator {
    std::priority_queue<int, std::vector<int>, std::greater<int>> queue;
public:
    MinSumCalculator(){}
    void add_number(int x) {
        queue.push(x);
    }
    double calc_min_sum() {
        double result = 0;
        while (queue.size() > 2) {
            int x = queue.top();
            queue.pop();
            x += queue.top();
            queue.pop();
            queue.push(x);
            result += 0.05 * x;
        }
        int x = queue.top();
        queue.pop();
        x += queue.top();
        queue.pop();
        result += 0.05 * x;
        return result;
    }
};

int main() {
    MinSumCalculator calc;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        calc.add_number(x);
    }
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);
    std::cout.precision(2);
    std::cout << calc.calc_min_sum() << "\n";
    return 0;
}







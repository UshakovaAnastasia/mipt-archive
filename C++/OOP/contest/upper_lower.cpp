#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> color;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        color.push_back(x);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        std::cout << std::upper_bound(color.begin(), color.end(), x) - std::lower_bound(color.begin(), color.end(), x) << "\n";
    }
    
    return 0;
}

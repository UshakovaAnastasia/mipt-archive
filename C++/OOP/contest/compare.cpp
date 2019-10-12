#include <iostream>
#include <vector>
#include <algorithm>

struct Team {
    int team_number;
    int solved_problems;
    int time;
};

bool Compare (const Team& first, const Team& second) {
    if (first.solved_problems < second.solved_problems) {
        return false;
    }
    if (first.solved_problems > second.solved_problems) {
        return true;
    }
    if (first.time > second.time) {
        return false;
    }
    if (first.time < second.time) {
        return true;
    }
    return first.team_number < second.team_number;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Team> table(n);
    for (int i = 0; i < n; ++i) {
        int prob;
        int t;
        std::cin >> prob >> t;
        table[i].team_number = i + 1;
        table[i].solved_problems = prob;
        table[i].time = t;
    }
    std::sort(table.begin(), table.end(), Compare);
    for (int i = 0; i < n; ++i) {
        std::cout << table[i].team_number << " ";
    }
    std::cout << "\n";
    return 0;
}

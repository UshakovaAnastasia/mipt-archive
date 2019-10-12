#include <iostream>
#include <vector>
#include <exception>
#include <cstring>
#include <utility>

class Graph {
    std::vector<std::vector<int>> adjacency_list;
public:
    Graph() {};
    Graph(size_t numVertices) {
        adjacency_list.resize(numVertices);
    }
    void AddEdge (const int& u, const int& v) {
        adjacency_list[u - 1].push_back(v - 1);
        adjacency_list[v - 1].push_back(u - 1);
    }
    const std::vector<int>& Vertex(const int& u) {
        return adjacency_list[u - 1];
    }
    
};

int main() {
    int n;
    std::cin >> n;
    int k;
    std::cin >> k;
    Graph g(n);
    for (int i = 0; i < k; ++i) {
        char command[5];
        std::cin >> command;
        if (!std::strcmp(command, "1")) {
            int x;
            int y;
            std::cin >> x >> y;
            g.AddEdge(x, y);
        } else {
            int x;
            std::cin >> x;
            const std::vector<int>& edges = g.Vertex(x);
            for (int i = 0; i < edges.size(); ++i) {
                std::cout << edges[i] + 1 << " ";
            }
            std::cout << "\n";
        }
    }
    return 0;
}




// graph.cpp : This file contains the 'main' function. Program execution begins
// and ends there.
//

#include <iostream>
#include <vector>

constexpr int INF = -1;

class Graph {
 public:
  class RowReadProxy {
   public:
    RowReadProxy(const Graph* graph, int start_index)
        : graph_(graph), start_index_(start_index) {}

    const int& operator[](int column) const {
      return graph_->items_[start_index_ + column];
    }

   private:
    const Graph* graph_;
    int start_index_;
  };

  class RowWriteProxy {
   public:
    RowWriteProxy(Graph* graph, int start_index)
        : graph_(graph), start_index_(start_index) {}

    int& operator[](int column) const {
      return graph_->items_[start_index_ + column];
    }

   private:
    Graph* graph_;
    int start_index_;
  };

  explicit Graph(int num_vertices)
      : num_vertices_(num_vertices), items_(num_vertices * num_vertices, INF) {
    for (int i = 0; i < num_vertices_; ++i) {
      (*this)[i][i] = 0;
    }
  }

  RowReadProxy operator[](int row) const { return {this, row * num_vertices_}; }

  RowWriteProxy operator[](int row) { return {this, row * num_vertices_}; }

  int GetNumVertices() const { return num_vertices_; }

 private:
  int num_vertices_;
  std::vector<int> items_;
};

void PrintGraph(const Graph& graph) {
  for (int row = 0; row < graph.GetNumVertices(); ++row) {
    for (int column = 0; column < graph.GetNumVertices(); ++column) {
      std::cout << graph[row][column] << " ";
    }
    std::cout << "\n";
  }
}

bool IsInfinite(int a) { return a == INF; }

int AddWeights(int a, int b) {
  if (IsInfinite(a) || IsInfinite(b)) {
    return INF;
  }
  return a + b;
}

int MinWeight(int a, int b) {
  if (IsInfinite(a)) {
    return b;
  }
  if (IsInfinite(b)) {
    return a;
  }
  return std::min(a, b);
}

void Floyd(Graph& graph) {
  for (int i = 0; i < graph.GetNumVertices(); ++i) {
    for (int u = 0; u < graph.GetNumVertices(); ++u) {
      for (int v = 0; v < graph.GetNumVertices(); ++v) {
        graph[u][v] =
            MinWeight(graph[u][v], AddWeights(graph[u][i], graph[i][v]));
      }
    }
  }
}
int FindMaxShortestDistance(const Graph& graph) {
  int max_shortest_distance = 0;
  for (int row = 0; row < graph.GetNumVertices(); ++row) {
    for (int column = 0; column < graph.GetNumVertices(); ++column) {
      max_shortest_distance =
          std::max(max_shortest_distance, graph[row][column]);
    }
  }
  return max_shortest_distance;
}

Graph ReadGraph(int num_vertices) {
  Graph g(num_vertices);
  for (int row = 0; row < num_vertices; ++row) {
    for (int column = 0; column < num_vertices; ++column) {
      std::cin >> g[row][column];
    }
  }
  return g;
}

int main() {
#if 0
  Graph g(4);
  g[0][1] = 1;
  g[0][2] = 6;
  g[1][2] = 4;
  g[1][3] = 1;
  g[3][2] = 1;
  PrintGraph(g);
  std::cout << std::endl;
  Floyd(g);
#else
#if 0
  Graph g(6);
  g[0][1] = 6;
  g[0][2] = 8;
  g[1][0] = 5;
  g[1][2] = 5;
  g[2][0] = 1;
  g[2][1] = 7;
  g[3][4] = 6;
  g[4][5] = 3;
  g[5][3] = 2;
  PrintGraph(g);
  std::cout << std::endl;
  Floyd(g);
  std::cout << FindMaxShortestDistance(g) << std::endl;
#endif

#endif
  int num_vertices;
  std::cin >> num_vertices;
  Graph g = ReadGraph(num_vertices);
  Floyd(g);
  std::cout << FindMaxShortestDistance(g) << std::endl;
}

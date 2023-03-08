// checkers.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <array>
#include <iostream>
#include <numeric>

using WayGraph = std::array<std::array<int, 8>, 8>;

void PrintGraph(const WayGraph& graph) {
  for (int row = 0; row < graph.size(); row++) {
    for (int column = 0; column < graph[0].size(); column++) {
      if ((row ^ column) & 1) {
        std::cout << graph[row][column];
      } else {
        std::cout << ' ';
      }
      std::cout << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "\n\n";
}

int GetValue(const WayGraph& graph, int row, int col) {
  if (row < graph.size() && row >= 0 && col < graph[0].size() && col >= 0) {
    return graph[row][col];
  }
  return 0;
}

void RecalculateGraph(WayGraph& graph) {
  for (int row = graph.size() - 2; row >= 0; row--) {
    for (int column = 0; column < graph[0].size(); column++) {
      graph[row][column] += GetValue(graph, row + 1, column - 1) +
                            GetValue(graph, row + 1, column + 1);
    }
  }
}

int GetFirstRowItemsSum(const WayGraph& graph) {
  return std::accumulate(graph[0].begin(), graph[0].end(), 0);
}

int main() {
  WayGraph way_graph{};
  int row = 0, col = 0;
  std::cin >> row >> col;
  way_graph[row][col] = 1;
  PrintGraph(way_graph);
  RecalculateGraph(way_graph);
  PrintGraph(way_graph);
  std::cout << GetFirstRowItemsSum(way_graph) << "\n";
}

// checkers.cpp : This file contains the 'main' function. Program execution
// begins and ends there.
//

#include <array>
#include <iostream>

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
}

int GetValue(const WayGraph& graph, int row, int column) {

}

void RecalculateGraph(WayGraph& graph) {

}

int main() {
  WayGraph way_graph{};
  way_graph[7][2] = 1;
  PrintGraph(way_graph);
}

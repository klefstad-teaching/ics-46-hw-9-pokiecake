#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(Dijkstra, large) {
  const string test_file = "src/large.txt";
  Graph g;
  cout << "printing " << test_file << endl;
  file_to_graph(test_file, g);

  vector<int> previous(g.numVertices, 0);
  vector<int> distances = dijkstra_shortest_path(g, 0, previous);
  vector<int> distances_solution = {0, 7, 15, 5, 14, 11, 12};

  for (int i = 0; i < g.numVertices; ++i)
    EXPECT_EQ(distances[i], distances_solution[i]) << "distance to vertex " << i << " does not match" << endl;

  vector<vector<int>> shortestPaths;
  for (int i = 0; i < g.numVertices; ++i) {
    vector<int> shortest = extract_shortest_path(distances, previous, i);
    shortestPaths.push_back(shortest);
  }
  vector<vector<int>> solutions = {
    {0},
    {0, 1},
    {0, 1, 2},
    {0, 3},
    {0, 1, 4},
    {0, 3, 5},
    {0, 3, 5, 6},
  };

  for (int i = 0; i < g.numVertices; ++i) {
    EXPECT_EQ(shortestPaths[i], solutions[i]) << "path to " << i << " does not match" << endl;
  }
}
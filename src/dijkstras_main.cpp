#include "dijkstras.cpp"
#include <string>

int main() {
    const string test_file = "medium.txt";
    Graph g;
    cout << "printing " << test_file << endl;
    file_to_graph(test_file, g);

    vector<int> previous(g.numVertices, 0);
    vector<int> distances = dijkstra_shortest_path(g, 0, previous);

    vector<int> shortestTo4 = extract_shortest_path(distances, previous, 4);

    cout << "Shortest path to 4: ";
    print_path(shortestTo4, g.numVertices);
    cout << endl;
    return 0;
}
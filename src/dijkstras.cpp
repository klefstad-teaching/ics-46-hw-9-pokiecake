#ifndef DIJKSTRA_CPP
#define DIJKSTRA_CPP

#include "dijkstras.h"
using namespace std;
using pairII = pair<int, int>;

void error(string msg) {
    cerr << msg;
}

struct compare_distance {
    bool operator()(const pair<int,int> p1, const pair<int, int> p2) {
        return p1.second > p2.second;
        //greater, so pq orders "largest" from left to right
        //pq gets elements from right to left
    }
};

// bool compare_distance(const pair<int,int> p1, const pair<int, int> p2) {
//    return p1.second < p2.second;
// }

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);
    // bool (* compare) (pair<int, int> p1, pair<int, int> p2);
    
    //compare = compare_distance;
    priority_queue<pairII, vector<pairII>, compare_distance> pq;

    pq.push(pair(source, 0));
    distances[source] = 0;
    previous[source] = -1;

    while (!pq.empty()) {
        pair<int, int> vertex_weight = pq.top();
        pq.pop();
        int src = vertex_weight.first;
        int distance = vertex_weight.second;
        if (visited[src])
            continue;
        visited[src] = true;

        EdgeList edges = G[src];
        for (Edge e : edges) {
            int dst = e.dst, weight = e.weight;
            if (distance + weight < distances[dst]) {
                distances[dst] = distance + weight;
                pq.push(pair(dst, distances[dst]));
                previous[dst] = src;
            }
        }
    }
    return distances;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    int cur = destination;
    vector<int> path;

    while (cur != -1) {
        path.insert(path.begin(), cur);
        cur = previous[cur];
    }

    return path;
}

void print_path(const vector<int>& v, int total) {
    for (auto n : v)
        cout << n << " ";
    cout << endl << "Total cost is " << total << endl;
}
#endif
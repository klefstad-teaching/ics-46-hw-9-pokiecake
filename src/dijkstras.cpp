#ifndef DIJKSTRA_CPP
#define DIJKSTRA_CPP

#include "dijkstras.h"
using namespace std;
using pairII = pair<int, int>;

struct compare_distance {
    bool operator()(const pair<int,int> p1, const pair<int, int> p2) {
        return p1.second < p2.second;
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
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    int cur = destination;
    vector<int> path = cur;

    while (cur != -1) {
        path.insert(cur, 0);
        cur = previous[cur];
    }

    return path;
}

#endif
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int node;
    int weight;
    Edge(int n, int w) : node(n), weight(w) {}
};

struct ExcelData {
    vector<int> node1;
    vector<int> node2;
    vector<int> weight;
};

void readCSVData(const string& filename, ExcelData& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Skip the first line (header row)
    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string node1, node2, weight;
        if (!(getline(iss, node1, ',') && getline(iss, node2, ',') && getline(iss, weight))) {
            cerr << "Error reading line: " << line << endl;
            continue;
        }
        data.node1.push_back(stoi(node1));
        data.node2.push_back(stoi(node2));
        data.weight.push_back(stoi(weight));
    }

    if (data.node1.empty() || data.node2.empty() || data.weight.empty()) {
        cerr << "Empty data vectors. No data read from file." << endl;
        return;
    }
    file.close();
}


void createAdjacencyList(const ExcelData& data, unordered_map<int, vector<Edge>>& graph) {
    for (size_t i = 0; i < data.node1.size(); ++i) {
        int n1 = data.node1[i];
        int n2 = data.node2[i];
        int w = data.weight[i];

        graph[n1].push_back(Edge(n2, w));
        graph[n2].push_back(Edge(n1, w));
    }
}

void dijkstra(const unordered_map<int, vector<Edge>>& graph, int src, int dest) {
    unordered_map<int, int> dist;
    unordered_map<int, int> parent;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (const auto& kvp : graph) {
        int node = kvp.first;
        dist[node] = INT_MAX;
        parent[node] = -1;
    }

    dist[src] = 0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();
        int node = top.second;
        int distance = top.first;

        if (distance > dist[node]) {
            continue;
        }

        for (const Edge& edge : graph.at(node)) {
            int neighbor = edge.node;
            int newDist = distance + edge.weight;

            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                parent[neighbor] = node;
                pq.push(make_pair(newDist, neighbor));
            }
        }
    }



    if (parent[dest] == -1) {
        cout << "No path found from source to destination." << endl;
        return;
    }

    int curr = dest;
    vector<int> path;
    while (curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());

    cout << "Distance: " << dist[dest] << endl;
}

void shortDistance() {
    int src_index, dest_index;
    cout << "Enter the source index: ";
    cin >> src_index;
    cout << "Enter the destination index: ";
    cin >> dest_index;
    if (src_index == -1 || dest_index == -1) {
        cout << "Invalid source or destination name." << endl;
        return;
    }
    ExcelData data;
    string filename = "C:\\Users\\nithy\\Downloads\\file_name.csv";
    unordered_map<int, vector<Edge>> adjacencyList;

    readCSVData(filename, data);
    createAdjacencyList(data, adjacencyList);

    dijkstra(adjacencyList, src_index, dest_index);
}

int main() {
    shortDistance();
    return 0;
}

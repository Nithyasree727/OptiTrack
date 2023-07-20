#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int node;
    double weight;
    Edge(int n, double w) : node(n), weight(w) {}
};

struct ExcelData {
    vector<int> node1;
    vector<int> node2;
    vector<double> weight;
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
            cerr << line << endl;
            continue;
        }
        data.node1.push_back(stoi(node1));
        data.node2.push_back(stoi(node2));
        data.weight.push_back(stod(weight));
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
        double w = data.weight[i];

        graph[n1].push_back(Edge(n2, w));
        graph[n2].push_back(Edge(n1, w));
    }
}

void dijkstra(const unordered_map<int, vector<Edge>>& graph, int src, int dest) {
    unordered_map<int, double> dist;
    unordered_map<int, double> parent;
    priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> pq;

    for (const auto& kvp : graph) {
        int node = kvp.first;
        dist[node] = INT_MAX;
        parent[node] = -1;
    }

    dist[src] = 0.0;
    pq.push(make_pair(0, src));

    while (!pq.empty()) {
        pair<int, double> top = pq.top();
        pq.pop();
        int node = top.second;
        double distance = top.first;

        if (distance > dist[node]) {
            continue;
        }

        for (const Edge& edge : graph.at(node)) {
            int neighbor = edge.node;
            double newDist = distance + edge.weight;

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

int getStationIndex(const vector<string>& names, const string& stationName) {
    auto it = find(names.begin(), names.end(), stationName);
    if (it != names.end()) {
        return distance(names.begin(), it)+1;
    }
    return -1; // Return -1 if stationName is not found in the names vector
}

void shortDistance() {
    vector<string> names = {
        "Miyapur",
        "JNTU",
        "KPHB",
        "Kukatpally",
        "Balanagar",
        "Moosapet",
        "Bharat Nagar",
        "Erragadda",
        "ESI",
        "S.R.Nagar",
        "Ameerpet",
        "Punjagutta",
        "Irrum Manzil",
        "Khairatabad",
        "Lakdi-ka-pul",
        "Assembly",
        "Nampally",
        "Gandhi Bhavan",
        "OMC",
        "MG Bus Stand",
        "Malakpet",
        "New Market",
        "Musarambagh",
        "Dilsukhnagar",
        "Chaitanyapuri",
        "Victoria Memorial",
        "LBN",
        "Jubliee Bus Station",
        "Parade Ground",
        "Secunderabad West",
        "Gandhi Hospital",
        "Musheerabad",
        "RTC X Road",
        "Chikkadpally",
        "Narayanaguda",
        "Sultan Bazaar",
        "Salarjung Museum",
        "Charminar",
        "Shalibanda",
        "Shamshergunj",
        "Falaknuma",
        "Raidurg",
        "Cyber Gateway",
        "Hitec City",
        "Durgam Cheruvu",
        "Madhapur",
        "Peddamma Temple",
        "Jubliee Hills Check Post",
        "Jubliee Hills Road No.5",
        "Yusufguda",
        "Madhura Nagar",
        "Begumpet",
        "Prakash Nagar",
        "Rasoolpura",
        "Paradise",
        "Secunderabad East",
        "Mettuguda",
        "Tarnaka",
        "Habsiguda",
        "NGRI",
        "Stadium",
        "Uppal",
        "Nagole"
    };
    // Display the station names
    cout << "List of station names:" << endl;
    for (const string& station : names) {
        cout << station << endl;
    }
    string src_name, dest_name;
    cout << "Enter the source name: ";
    cin >> src_name;
    cout << "Enter the destination name: ";
    cin >> dest_name;

    int src_index = getStationIndex(names, src_name);
    int dest_index = getStationIndex(names, dest_name);
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

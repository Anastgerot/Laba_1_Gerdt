#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set> 
#include <functional>
#include <stack>
#include "truba.h"
#include "CS.h"
#include "Utils.h"
using namespace std;
struct Connection {
    int inputStation;
    int pipe;
    int outputStation;

    bool operator==(const Connection& other) const {
        return inputStation == other.inputStation && pipe == other.pipe && outputStation == other.outputStation;
    }
};
class addition
{
public:
    void Addpipe(unordered_map<int, truba>& pipe);
    void Addcs(unordered_map<int, CS>& ks);
    void Filter(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks, vector<vector<Connection>>& graph);
    void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    void Save_objects(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    void Load_Download(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    int Add_newpipe_connect(unordered_map<int, truba>& pipe, int diameter);

    bool IsConnectedToTwoCompressorStations(const vector<vector<Connection>>& graph, int stationId);
    void Connect_CS_and_Pipe(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks, vector<vector<Connection>>& graph);
    void Remove_Edge_And_Unused_Vertices(int pipeId, vector<vector<Connection>>& graph);
    void Remove_Vertex(int vertex, vector<vector<Connection>>& graph);
    void Remove_Connection(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks, vector<vector<Connection>>& graph);

    bool DFS(int v, const vector<vector<Connection>>& graph, vector<bool>& visited, vector<int>& result, unordered_set<int>& currentPath);
    void Topological_sort(vector<vector<Connection>>& graph);
    void Dikstra(unordered_map<int, truba>& pipe, const vector<vector<Connection>>& graph, unordered_map<int, CS>& ks);
    double CalculateCapacity(const truba& pipe);
    double FordFulkerson(vector<vector<Connection>>& graph, unordered_map<int, truba>& pipe, int source, int sink);
    void FindAndPrintMaxFlow(vector<vector<Connection>>& graph, unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    void FindAndPrintCapacities(vector<vector<Connection>>& graph, unordered_map<int, truba>& pipe);

    void Operations_with_graph(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks, vector<vector<Connection>>& graph);


};


#pragma once
#include <iostream>
#include <unordered_map>
#include <set> 
#include "truba.h"
#include "CS.h"
#include "Utils.h"
using namespace std;
class addition
{
public:
    static void Addpipe(unordered_map<int, truba>& pipe);
    static void Addcs(unordered_map<int, CS>& ks);
    static void Filter(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    static vector<int> ParseIds(const string& input);
    static void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    static void Save_objects(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    static void Connect_CS_and_Pipe(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks, vector<vector<int>>& graph);
    static void Load_Download(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
    static int Add_newpipe_connect(unordered_map<int, truba>& pipe, int diameter);
};


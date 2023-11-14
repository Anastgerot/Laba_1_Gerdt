#pragma once
#include <iostream>
#include <unordered_map>
#include <set> 
#include "truba.h"
#include "CS.h"
#include "Utils.h"
using namespace std;
using namespace std;
class addition
{
public:
    friend void Addpipe(unordered_map<int, truba>& pipe);
    friend void Addcs(unordered_map<int, CS>& ks);
    friend void ClearLogFile();
    friend void Filter(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);
    friend vector<int> ParseIds(const string& input);
    friend void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);
    friend void Save_objects(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);
    friend void Load_Download(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);

};


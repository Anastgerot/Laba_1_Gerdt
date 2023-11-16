#pragma once
#include <iostream>
#include <fstream> 
#include <string>
#include <unordered_map>
using namespace std;
class redirect_output_wrapper
{
    ostream& stream;
    streambuf* const old_buf;
public:
    redirect_output_wrapper(ostream& src)
        :old_buf(src.rdbuf()), stream(src)
    {
    }

    ~redirect_output_wrapper() {
        stream.rdbuf(old_buf);
    }
    void redirect(ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};
template <typename T>
T GetCorrectNumber(T min, T max)
{
	T a;
	while ((cin >> a).fail() || a < min || a > max || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Type number (" "from" << " " << min << " " << "to" << " " << max << "): ";
	}
    cerr << a << endl;
    return a;
}
template <typename T>
bool Find_under_repair(const T& obj, bool underRepair) {
    return obj.under_repair == underRepair;
}

template <typename T>
bool Find_procent(const T& obj, const string& percentage) {
    int procent;
    try {
        procent = round(stof(percentage));
    }
    catch (const invalid_argument& e) {
        cerr << "Invalid input for percentage: " << e.what() << endl;
        return false;
    }
    return abs(round((obj.workshop - obj.workshop_on) * 100.0 / obj.workshop) - procent) <= 1;
}

template <typename T>
vector<int> Find_cs(const unordered_map<int, T>& objects, const string& filterValue, bool (*FilterFunction)(const T&, const string&)) {
    vector<int> matching_ids;
    for (const auto& object_entry : objects) {
        const T& obj = object_entry.second;
        if (FilterFunction(obj, filterValue)) {
            matching_ids.push_back(object_entry.first);
        }
    }
    return matching_ids;
}
template <typename T>
vector<int> Find_pipe(const unordered_map<int, T>& objects, bool filterValue, bool (*FilterFunction2)(const T&, bool)) {
    vector<int> matching_ids;
    for (const auto& object_entry : objects) {
        const T& obj = object_entry.second;
        if (FilterFunction2(obj, filterValue)) {
            matching_ids.push_back(object_entry.first);
        }
    }
    return matching_ids;
}
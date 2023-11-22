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
bool Find_procent(const T& obj, int percentage, const string& comparison_type) {
    int obj_percentage = round((obj.workshop - obj.workshop_on) * 100.0 / obj.workshop);

    if (comparison_type == "equal") {
        return abs(obj_percentage - percentage) <= 1;
    }
    else if (comparison_type == "greater") {
        return obj_percentage > (percentage);
    }
    else if (comparison_type == "less") {
        return obj_percentage < (percentage);
    }
    else {
        cerr << "Invalid comparison type" << endl;
        return false;
    }
}

template <typename T, typename U>
vector<int> Find_cs(const unordered_map<int, T>& data, const U& value, const string& comparison_type, bool (*comparison_func)(const T&, U, const string&)) {
    vector<int> matching_ids;
    for (const auto& entry : data) {
        if (comparison_func(entry.second, value, comparison_type)) {
            matching_ids.push_back(entry.first);
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
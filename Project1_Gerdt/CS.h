#pragma once
#include <iostream>
#include <vector>
using namespace std;
class CS
{
private:
	int idcs = 0;
	char efficiency = 'A';
public:
	string name = "";
	int workshop = 0;
	int workshop_on = 0;
	static int max_id_cs;
	friend istream& operator >> (istream& in, CS& cs);
	friend ostream& operator << (ostream& out, const CS& cs);
	friend void Save_CS(ofstream& fout, const CS& cs);
	friend CS& Download_CS(ifstream& fin, CS& cs);
	CS();
	int get_idc() { return idcs; };

};
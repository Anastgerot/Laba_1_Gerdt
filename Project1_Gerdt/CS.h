#pragma once
#include <iostream>
using namespace std;
class CS
{
private:
	int idcs;
	string name;
	int workshop;
	int workshop_on;
	char efficiency;
public:
	static int max_id_cs;
	friend istream& operator >> (istream& in, CS& cs);
	friend ostream& operator << (ostream& out, const CS& cs);
	friend void Edit_CS(CS& cs);
	friend void Save_CS(ofstream& fout, const CS& cs);
	friend CS& Download_CS(ifstream& fin, CS& cs);
	CS();
	int get_idc() { return idcs; };
};


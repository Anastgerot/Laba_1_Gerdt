#pragma once
#include <iostream>
using namespace std;
class truba
{
public:
	int idpipe = 0;
	double length = 0;
	string name = "";
	bool under_repair = false;
	int diameter = 0;
	static int max_id_truba;
	friend ostream& operator << (ostream& out, const truba& tr);
	friend istream& operator >> (istream& in, truba& tr);
	friend void Save_truba(ofstream& fout, const truba& tr);
	friend truba& Download_truba(ifstream& fin, truba& tr);
	truba();
	int get_idp() { return idpipe; };
	void set_diameter(int new_diameter) {
		diameter = new_diameter;
	}
};
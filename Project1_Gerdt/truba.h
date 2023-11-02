#pragma once
#include <iostream>
using namespace std;
class truba
{
private:
	int idpipe;
	string name;
	double length;
	int diameter;
	bool under_repair;
public:
	static int max_id_truba;
	friend ostream& operator << (ostream& out, const truba& tr);
	friend istream& operator >> (istream& in, truba& tr);
	friend void Edit_truba(truba& tr);
	friend void Save_truba(ofstream& fout, const truba& tr);
	friend truba& Download_truba(ifstream& fin, truba& tr);
	truba();
	int get_idp() { return idpipe; };
};


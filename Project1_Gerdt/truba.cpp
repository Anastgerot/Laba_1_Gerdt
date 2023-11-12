#include "truba.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int truba::max_id_truba = 0;
truba::truba()
{
	idpipe = max_id_truba++;
}
istream& operator >> (istream& in, truba& tr)
{
	cout << "Type name: ";
	in >> ws;
	getline(in, tr.name);
	cout << "Type length: ";
	tr.length = GetCorrectNumber(0.0, 1000000.0);
	cout << "Type diameter: ";
	tr.diameter = GetCorrectNumber(0, 1000000);
	cout << "Under repair? (1 - Yes, 0 - No): ";
	tr.under_repair = GetCorrectNumber(0, 1);
	return in;
}
ostream& operator << (ostream& out, const truba& tr)
{
	if (tr.name.empty())
	{
		out << "You don't have the pipe.\n";
	}
	else
	{
		out << "Pipe:\n";
		out << "Id Pipe: " << tr.idpipe << endl
			<< "Name: " << tr.name << endl
			<< "Length: " << tr.length << endl
			<< "Diameter: " << tr.diameter << endl
			<< "Under repair? (1 - Yes, 0 - No): " << tr.under_repair << endl
			<< "Max_id: " << truba::max_id_truba << endl;
		return out;
	}
}
void Save_truba(ofstream& fout, const truba& tr)
{
	if (tr.name.empty())
	{
		Log("You don't have the pipe to save");
	}
	else
	{
		fout << "Pipe:" << endl;
		fout << tr.name << endl << tr.length << endl << tr.diameter << endl << tr.under_repair << endl;
	}
}
truba& Download_truba(ifstream& fin, truba& tr)
{
	string line;
	while (getline(fin, line))
	{
		if (line == "Pipe:")
		{
			getline(fin, tr.name);
			fin >> tr.length >> tr.diameter >> tr.under_repair;
			return tr;
		}
	}
}
void Addpipe(unordered_map<int, truba>& pipe)
{
	truba tr1;
	cin >> tr1;
	pipe.insert({ tr1.get_idp(), tr1 });
}

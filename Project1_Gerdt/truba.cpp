#include <iostream>
#include <fstream>
#include <string>
#include "truba.h"
#include "Utils.h"
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
	tr.diameter = GetCorrectNumber(500, 1400);
	while (!(tr.diameter == 500 || tr.diameter == 700 || tr.diameter == 1000 || tr.diameter == 1400))
	{
		cout << "The diameter can only be 500, 700, 1000 or 1400. Please try again: ";
		tr.diameter = GetCorrectNumber(500, 1400);
	}
	cout << "Under repair? (1 - Yes, 0 - No): ";
	tr.under_repair = GetCorrectNumber(0, 1);
	cout << "Your pipe successfully entered" << endl;
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
			<< "Under repair? (1 - Yes, 0 - No): " << tr.under_repair << endl;
		return out;
	}
}
void Save_truba(ofstream& fout, const truba& tr)
{
	if (tr.name.empty())
	{
		cout << "You don't have the pipe to save" << endl;
	}
	else
	{
		fout << "Pipe:" << endl;
		fout << tr.idpipe << endl;
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
			fin >> tr.idpipe;
			fin.ignore();
			getline(fin, tr.name);
			fin >> tr.length >> tr.diameter >> tr.under_repair;
			return tr;
		}
	}
}

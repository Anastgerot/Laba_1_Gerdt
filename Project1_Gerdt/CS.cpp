#include "CS.h"
#include "Utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
int CS::max_id_cs = 0;
CS::CS()
{
	idcs = max_id_cs++;
}
istream& operator >> (istream& in, CS& cs)
{
	cout << "Type name: ";
	in >> ws;
	getline(in, cs.name);
	cout << "Type the number of workshops: ";
	cs.workshop = GetCorrectNumber(1, 1000000);
	cout << "Type the number of workshops in operation: ";
	cs.workshop_on = GetCorrectNumber(1, cs.workshop);
	while (cs.workshop < cs.workshop_on)
	{
		cout << "The number of workshops can't be less then the number of workshops in operation.\n";
		cout << "Please, try again: ";
		cs.workshop_on = GetCorrectNumber(1, cs.workshop);
	}
	cout << "Type efficiency (From A to D): ";
	cs.efficiency = GetCorrectNumber('A', 'D');
	Log("Your compressor station successfully entered");
	return in;
}
ostream& operator << (ostream& out, const CS& cs)
{
	if (cs.name.empty())
	{
		out << "You don't have the compressor station.\n";
	}
	else
	{
		out << "Compressor station:\n";
		out << "Id CS: " << cs.idcs << endl
			<< "Name: " << cs.name << endl
			<< "The number of workshops: " << cs.workshop << endl
			<< "The number of workshops in operation: " << cs.workshop_on << endl
			<< "Efficiency: " << cs.efficiency << endl
			<< "Max_id: " << CS::max_id_cs << endl;
	}
	return out;
}
void Save_CS(ofstream& fout, const CS& cs)
{
	if (cs.name.empty())
	{
		cout << "You don't have the compressor station to save.\n";
	}
	else
	{
		fout << "Compressor station:" << endl;
		fout << cs.name << endl << cs.workshop << endl << cs.workshop_on << endl << cs.efficiency << endl;
	}
}
CS& Download_CS(ifstream& fin, CS& cs)
{
	string line;
	while (getline(fin, line))
	{
		if (line == "Compressor station:")
		{
			getline(fin, cs.name);
			fin >> cs.workshop >> cs.workshop_on >> cs.efficiency;
			return cs;
		}
	}
}
void Addcs(unordered_map<int, CS>& ks)
{
	CS cs1;
	cin >> cs1;
	ks.insert({ cs1.get_idc(), cs1 });
}

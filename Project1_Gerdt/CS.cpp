#include "CS.h"
#include "Utils.h"
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


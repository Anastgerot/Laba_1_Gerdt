#include "truba.h"
#include "Utils.h"
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
			<< "Under repair? (1 - Yes, 0 - No): " << tr.under_repair << endl;
		return out;
	}
}

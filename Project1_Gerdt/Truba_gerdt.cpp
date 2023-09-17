#include <iostream>
#include <vector>
using namespace std;
struct truba {
	string otmetka;
	double dlina;
	int diametr;
	bool sostoyanie;
};
struct CS {
	string name;
	int just_cekh;
	int rabota_cekh;
	char efficiency;
};
truba Input_truba()
{
	truba tr;
	cout << "Type otmetky: ";
	cin >> tr.otmetka;
	cout << "Type dliny: ";
	cin >> tr.dlina;
	cout << "Type diametr: ";
	cin >> tr.diametr;
	cout << "Type sostoyanie: ";
	cin >> tr.sostoyanie;
	return tr;
}
void Print_truba(truba tr)
{
	cout << "Otmetka: " << tr.otmetka << endl
		<< "Dlina: " << tr.dlina << endl
		<< "Diametr: " << tr.diametr << endl
		<< "Sostoyanie: " << tr.sostoyanie << endl;
}
CS Input_CS()
{
	CS cs;
	cout << "Type name: ";
	cin >> cs.name;
	cout << "Type kolichestvo cekhov: ";
	cin >> cs.just_cekh;
	cout << "Type kolichestvo cekhov v rabote: ";
	cin >> cs.rabota_cekh;
	cout << "Type effectivnost: ";
	cin >> cs.efficiency;
	return cs;
}
void Print_CS(CS cs)
{
	cout << "Name: " << cs.name << endl
		<< "Kolichestvo cekhov: " << cs.just_cekh << endl
		<< "Kolichestvo cekhov v rabote: " << cs.rabota_cekh << endl
		<< "Effectivnost: " << cs.efficiency << endl;
}
int main()
{
	vector <truba> properties_truba;
	vector <CS> properties_CS;
	//Труба
	size_t t = 1;
	properties_truba.resize(t);
	truba tr1 = Input_truba();
	Print_truba(tr1);
	//КС
	size_t c = 1;
	properties_CS.resize(c);
	CS cs1 = Input_CS();
	Print_CS(cs1);
	return 0;
}

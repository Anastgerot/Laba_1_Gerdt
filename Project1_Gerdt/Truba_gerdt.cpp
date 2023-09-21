#include <iostream>
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
void Print_truba(const truba& tr)
{
	cout << "Otmetka: " << tr.otmetka << endl
		<< "Dlina: " << tr.dlina << endl
		<< "Diametr: " << tr.diametr << endl
		<< "Sostoyanie: " << tr.sostoyanie << endl;
}
void Edittruba(truba& tr)
{
	tr.sostoyanie;
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
void Print_CS(const CS& cs)
{
	cout << "Name: " << cs.name << endl
		<< "Kolichestvo cekhov: " << cs.just_cekh << endl
		<< "Kolichestvo cekhov v rabote: " << cs.rabota_cekh << endl
		<< "Effectivnost: " << cs.efficiency << endl;
}
int main()
{
	//Труба
	truba tr1;
	CS cs1;

	int input;

	cout << "Viborite cifru:\n";
	cout << "1. Dobavte trubu\n";
	cout << "2. Dobavte KC\n";
	cout << "3. Prosmotr vsex obectov\n";
	cout << "4. Redactirovat trubu\n";
	cout << "5. Redactirovat KC\n";
	cout << "6. Coxranit\n";
	cout << "7. Zagruzit\n";
	cout << "0. Vixod\n";
	cout << "Selection: ";
	cin >> input;
	switch (input) {
		case 1:
			tr1 = Input_truba();
			break;
		case 2:
			cs1 = Input_CS();
			break;
		case 3:
			cout << "Truba:\n";
			Print_truba(tr1);
			cout << "KC:\n";
			Print_CS(cs1);
			break;
		case 4:
			Edittruba(tr1);
			break;
		case 5:
			;
			break;
		case 6:
			;
			break;
		case 7:
			;
			break;
		case 0:
			break;
		default:
			cout << "Error, bad input, quitting\n";
			break;
	}

	return 0;
}

#include <iostream>
using namespace std;
struct truba {
	string name;
	double length;
	int diameter;
	bool under_repair;
};
struct CS {
	string name;
	int workshop;
	int workshop_on;
	char efficiency;
};
void Checking_exit(int& a)
{
	cin >> a;
	while (!cin || a < 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please, try again: ";
		cin >> a;
	}
};
void Checking_int(int& a)
{
	cin >> a;
	while (!cin || a<= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please, try again: ";
		cin >> a;
	}
};
void Checking_double(double& a)
{
	cin >> a;
	while (!cin || a <= 0)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please, try again: ";
		cin >> a;
	}
};
void Checking_bool(bool&a)
{
	cin >> a;
	while (!cin || !(a==0 || a==1))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please, try again: ";
		cin >> a;
	}
};
truba Input_truba()
{
	truba tr;
	cout << "Type name: ";
	cin >>tr.name; 
	cout << "Type length: ";
	Checking_double(tr.length);
	cout << "Type diameter: ";
	Checking_int(tr.diameter);
	cout << "Under repair? (1 - Yes, 0 - No): ";
	Checking_bool(tr.under_repair);
	return tr;
}
void Print_truba(const truba& tr)
{
	cout << "Name: " << tr.name << endl
		<< "Length: " << tr.length << endl
		<< "Diameter: " << tr.diameter << endl
		<< "Under repair? (1 - Yes, 0 - No): " << tr.under_repair << endl;
}
void Edit_truba(truba& tr)
{
	tr.under_repair = !tr.under_repair;
	cout << "The status has been successfully changed "<< endl;
}
CS Input_CS()
{
	CS cs;
	cout << "Type name: ";
	cin >> cs.name;
	cout << "Type the number of workshops: ";
	Checking_int(cs.workshop);
	cout << "Type the number of workshops in operation: ";
	Checking_int(cs.workshop_on);
	while (cs.workshop < cs.workshop_on)
	{
		cout << "The number of workshops v can't be less then the number of workshops in operation\n";
		cout << "Please, try again: ";
		Checking_int(cs.workshop_on);
	}
	cout << "Type efficiency (From A to D): ";
	cin >> cs.efficiency;
	while (!(cs.efficiency == 'A' || cs.efficiency == 'B' || cs.efficiency == 'C' || cs.efficiency == 'D'))
	{
		cout << "Please, enter available indicator (From A to D): ";
		cin >> cs.efficiency;
	}
	return cs;
}
void Print_CS(const CS& cs)
{
	cout << "Name: " << cs.name << endl
		<< "The number of workshops: " << cs.workshop << endl
		<< "The number of workshops in operation: " << cs.workshop_on << endl
		<< "Efficiency: " << cs.efficiency << endl;
}
void Edit_CS(CS& cs)
{
	cout << "Type name: ";
	cin >> cs.name;
	cout << "Type the number of workshops: ";
	Checking_int(cs.workshop);
	cout << "Type the number of workshops in operation: ";
	Checking_int(cs.workshop_on);
	while (cs.workshop < cs.workshop_on)
	{
		cout << "The number of workshops v can't be less then the number of workshops in operation\n";
		cout << "Please, try again: ";
		Checking_int(cs.workshop_on);
	}
	cout << "Type efficiency (From A to D): ";
	cin >> cs.efficiency;
	while (!(cs.efficiency == 'A' || cs.efficiency == 'B' || cs.efficiency == 'C' || cs.efficiency == 'D'))
	{
		cout << "Please, enter available indicator (From A to D): ";
		cin >> cs.efficiency;
	}
}
int main()
{
	truba tr1;
	CS cs1;
	int check_case1;
	int check_case2;
	check_case1 = 0;
	check_case2 = 0;
	while (true) {

		cout << "Choose the number:\n";
		cout << "1. Add the pipe\n";
		cout << "2. Add the compressor station\n";
		cout << "3. View all objects\n";
		cout << "4. Edit the status 'under repair'\n";
		cout << "5. Edit the compressor station\n";
		cout << "6. Save\n";
		cout << "7. Download\n";
		cout << "0. Exit\n";
		cout << "Selection: ";
		int input;
		Checking_exit(input);
		switch (input) {
		case 1:
			tr1 = Input_truba();
			check_case1 = 1;
			break;
		case 2:
			cs1 = Input_CS();
			check_case2 = 1;
			break;
		case 3:
			if (check_case1 == 0 && check_case2 == 0)
			{
				cout << "You don't have any objects" << endl << "Please, enter your data and try again later!" << endl;
			}
			else if (check_case1 == 1 && check_case2 == 0)
			{
				cout << "Pipe:\n";
				Print_truba(tr1);
				cout << "You don't have the compressor station\n";
			}
			else if (check_case1 == 0 && check_case2 == 1)
			{
				cout << "Compressor station:\n";
				Print_CS(cs1);
				cout << "You don't have the pipe\n";
			}
			else if (check_case1 == 1 && check_case2 == 1)
			{
				cout << "Pipe:\n";
				Print_truba(tr1);
				cout << "Compressor station:\n";
				Print_CS(cs1);
			}
			break;
		case 4:
			if (check_case1 == 0)
			{
				cout << "You have no status to change it" << endl << "Please, enter your data and try again later!" << endl;
			}
			else
			{
			Edit_truba(tr1);
			}
			break;
		case 5:
			if (check_case2 == 0)
			{
				cout << "You have no status to change it" << endl << "Please, enter your data and try again later!" << endl;
			}
			else
			{
				Edit_CS(cs1);
			}
			break;
		case 6:
			;
			break;
		case 7:
			;
			break;
		case 0:
			return 0;
			break;
		default:
			cout << "Error, bad input, try again!\n";
			break;
		}
	
	}

}

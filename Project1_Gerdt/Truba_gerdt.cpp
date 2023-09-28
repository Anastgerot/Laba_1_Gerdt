#include <iostream>
#include <fstream>
#include <cstdio>   
#include <string>
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
	while (!cin || a < 0 || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');//Разобраться с син игнор
		cout << "Please, try again: ";
		cin >> a;
	}
};
void Checking_int(int& a)
{
	cin >> a;
	while (!cin || a<= 0 || cin.peek() != '\n')
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
	while (!cin || a <= 0 || cin.peek() != '\n')
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
	while (!cin || !(a==0 || a==1) || cin.peek() != '\n')
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
	cin.ignore();//Прочитать документацию
	getline(cin, tr.name);
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
	cout << "The status has been successfully changed. "<< endl;
}
void Save_truba(const truba& tr)
{
	ofstream fout;
	fout.open("both.txt", ios::app);
	if (fout.is_open())
	{
		fout << "Pipe:" << endl;
		fout << tr.name << endl << tr.length << endl << tr.diameter << endl << tr.under_repair << endl;
		fout.close();
	}
}
truba Download_truba()
{
	truba tr;
	ifstream fin;
	string line;
	fin.open("both.txt", ios::in);
	if (fin.is_open())
	{
		while (getline(fin, line))
		{
			if (line == "Pipe:")
			{
				getline(fin, tr.name);
				fin >> tr.length >> tr.diameter >> tr.under_repair;
			}
		}
		fin.close();
	}
	return tr;
}

CS Input_CS()
{
	CS cs;
	cout << "Type name: ";
	cin.ignore();
	getline(cin, cs.name);
	cout << "Type the number of workshops: ";
	Checking_int(cs.workshop);
	cout << "Type the number of workshops in operation: ";
	Checking_int(cs.workshop_on);
	while (cs.workshop < cs.workshop_on)
	{
		cout << "The number of workshops can't be less then the number of workshops in operation.\n";
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
	if (cs.name.empty())
	{
		cout << "You don't have data about your compressor station " << endl;
	}
	else
	{
		cout << "The number of workshops: " << " " << cs.workshop << endl;
		cout << "Type the new number of workshops in operation: ";
		Checking_int(cs.workshop_on);
		cout << "Your new data has been successfully modified";
		while (cs.workshop < cs.workshop_on)
		{
			cout << "The number of workshops can't be less then the number of workshops in operation.\n";
			cout << "Please, try again: ";
			Checking_int(cs.workshop_on);//template шаблон функции проверки (одной для всех типов данных)
		}
	}
}
void Save_CS(const CS& cs)
{
	ofstream fout;
	fout.open("both.txt", ios::app);
	if (fout.is_open())
	{
		fout << "Compressor station:" << endl;
		fout << cs.name << endl << cs.workshop << endl << cs.workshop_on << endl << cs.efficiency << endl;
		fout.close();
	}

}
void ClearFile(const string& filename)
{
	ofstream file("both.txt", ios::out | ios::trunc);
	if (file.is_open())
	{
		file.close();
	}
}
CS Download_CS()
{
	CS cs;
	ifstream fin;
	string line;
	fin.open("both.txt", ios::in);
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
		{
			if (line == "Compressor station:")
			{
				getline(fin, cs.name);
				fin  >> cs.workshop >> cs.workshop_on >> cs.efficiency;
			}
		}
		fin.close();
	}
	return cs;
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
		fstream both_file("both.txt");
		string filename = "both.txt";
		switch (input) {
		case 1:
			tr1 = Input_truba();
			check_case1 = 1;
			break;
		case 2:
			cs1 = Input_CS();
			check_case2 = 1;
			break;
		case 3://выполнять проверку внутри функции вывода
			if (check_case1 == 0 && check_case2 == 0)
			{
				cout << "You don't have any objects." << endl << "Please, enter your data and try again later!" << endl;
			}
			else if (check_case1 == 1 && check_case2 == 0)
			{
				cout << "Pipe:\n";
				Print_truba(tr1);
				cout << "You don't have the compressor station.\n";
			}
			else if (check_case1 == 0 && check_case2 == 1)
			{
				cout << "Compressor station:\n";
				Print_CS(cs1);
				cout << "You don't have the pipe.\n";
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
				cout << "You have no status to change it." << endl << "Please, enter your data and try again later!" << endl;
			}
			else
			{
				Edit_truba(tr1);
			}
			break;
		case 5:
			if (check_case2 == 0)
			{
				cout << "You have no compressor station to change it." << endl << "Please, enter your data and try again later!" << endl;
			}
			else
			{
				Edit_CS(cs1);
			}
			break;
		case 6:
			ClearFile(filename);
			if (check_case1 == 0 && check_case2 == 0)
			{
				cout << "You don't have any objects to save." << endl << "Please, enter your data and try again later!" << endl;
			}
			else if (check_case1 == 1 && check_case2 == 0)
			{
				cout << "Pipe successfully saved!" << " " << "Please, check your file." << endl;
				Save_truba(tr1);
				cout << "You don't have the compressor station to save.\n";
			}
			else if (check_case1 == 0 && check_case2 == 1)
			{
				cout << "Compressor station successfully saved!" << " " << "Please, check your file." << endl;
				Save_CS(cs1);
				cout << "You don't have the pipe to save\n";
			}
			else if (check_case1 == 1 && check_case2 == 1)
			{
				Save_truba(tr1);
				Save_CS(cs1);
			}
			break;
		case 7:
			if (both_file.peek() == EOF)
			{
				cout << "File is empty!" << " " << "Please, check your data about your objects!!!" << endl;
				both_file.close();
			}
			else
			{
				if (both_file.is_open()) 
				{
					string line;
					while (getline(both_file, line))
					{
						if (line == "Pipe:")
						{
							cout << "Your pipe data has been successfully download!" << " " << " Press 3 to check your objects. " << endl;
							tr1 = Download_truba();
							check_case1 = 1;
						}
						else if (line == "Compressor station:")
						{
							cout << "Your compressor station data has been successfully download!" << " " << " Press 3 to check your objects. " << endl;
							cs1 = Download_CS();
							check_case2 = 1;
						}
					}
					both_file.close();
	
				}
			}
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

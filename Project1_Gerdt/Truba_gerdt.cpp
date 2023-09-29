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
		cin.ignore(1000, '\n');
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
void Input_truba(truba& tr)
{
	cout << "Type name: ";
	cin >> ws;
	getline(cin, tr.name);
	cout << "Type length: ";
	Checking_double(tr.length);
	cout << "Type diameter: ";
	Checking_int(tr.diameter);
	cout << "Under repair? (1 - Yes, 0 - No): ";
	Checking_bool(tr.under_repair);
}
void Print_truba(const truba& tr)
{
	if (tr.name.empty())
	{
		cout << "You don't have the pipe.\n";
	}
	else
	{
		cout << "Pipe:\n";
		cout << "Name: " << tr.name << endl
			<< "Length: " << tr.length << endl
			<< "Diameter: " << tr.diameter << endl
			<< "Under repair? (1 - Yes, 0 - No): " << tr.under_repair << endl;
	}
}
void Edit_truba(truba& tr)
{
	if (!tr.name.empty())
	{
		tr.under_repair = !tr.under_repair;
		cout << "The status has been successfully changed. " << endl;
	}
	else 
	{
		cout << "You have no status to change it." << endl << "Please, enter your data and try again later!" << endl;
	}
}
void Save_truba(const truba& tr)
{
	if (tr.name.empty())
	{
		cout << "You don't have the pipe to save\n";
	}
	else
	{
		ofstream fout;
		fout.open("both.txt", ios::app);
		if (fout.is_open())
		{
			fout << "Pipe:" << endl;
			fout << tr.name << endl << tr.length << endl << tr.diameter << endl << tr.under_repair << endl;
		}
		fout.close();
		cout << "Pipe successfully saved!" << " " << "Please, check your file." << endl;
	}
}
void Download_truba(truba& tr)
{
	bool replace_data;
	replace_data = 1;
	if (!tr.name.empty())
	{
		cout << "You already have data about your pipe!" << endl;
		cout << "If you are sure you want to replace them with data from the file, then press 1, otherwise 0: ";
		Checking_bool(replace_data);
	}
	if (replace_data == 1)
	{
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
			if (tr.name.empty())
			{
				cout << "You don't have data about the pipe to download\n";
			}
			else
			{
				cout << "Your pipe data has been successfully download!" << " " << " Press 3 to check your objects. " << endl;
			}
		}
	}
}

void Input_CS(CS& cs)
{
	cout << "Type name: ";
	cin >> ws;
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
}
void Print_CS(const CS& cs)
{
	if (cs.name.empty())
	{
		cout << "You don't have the compressor station.\n";
	}
	else
	{
		cout << "Compressor station:\n";
		cout << "Name: " << cs.name << endl
			<< "The number of workshops: " << cs.workshop << endl
			<< "The number of workshops in operation: " << cs.workshop_on << endl
			<< "Efficiency: " << cs.efficiency << endl;
	}
}
void Edit_CS(CS& cs)
{
	if (cs.name.empty())
	{
		cout << "You have no compressor station to change it." << endl << "Please, enter your data and try again later!" << endl;
	}
	else
	{
		cout << "The number of workshops: " << " " << cs.workshop << endl;
		cout << "Type the new number of workshops in operation: ";
		Checking_int(cs.workshop_on);
		while (cs.workshop < cs.workshop_on)
		{
			cout << "The number of workshops can't be less then the number of workshops in operation.\n";
			cout << "Please, try again: ";
			Checking_int(cs.workshop_on);
		}
		cout << "Your new data has been successfully modified.\n";
	}
}
void Save_CS(const CS& cs)
{
	if (cs.name.empty())
	{
		cout << "You don't have the compressor station to save.\n";
	}
	else
	{
		ofstream fout;
		fout.open("both.txt", ios::app);
		if (fout.is_open())
		{
			fout << "Compressor station:" << endl;
			fout << cs.name << endl << cs.workshop << endl << cs.workshop_on << endl << cs.efficiency << endl;
		}
		fout.close();
		cout << "Compressor station successfully saved!" << " " << "Please, check your file." << endl;
	}
}
void ClearFile()
{
	ofstream file("both.txt", ios::out | ios::trunc);
	if (file.is_open())
	{
		file.close();
	}
}
void Download_CS(CS& cs)
{
	bool replace_data;
	replace_data = 1;
	if (!cs.name.empty())
	{
		cout << "You already have data about your compressor station!" << endl;
		cout << "If you are sure you want to replace them with data from the file, then press 1, otherwise 0: ";
		Checking_bool(replace_data);
	}
	if (replace_data == 1)
	{
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
					fin >> cs.workshop >> cs.workshop_on >> cs.efficiency;
				}
			}
			fin.close();
			if (cs.name.empty())
			{
				cout << "You don't have data about the compressor station to download.\n";
			}
			else
			{
				cout << "Your compressor station data has been successfully download!" << " " << " Press 3 to check your objects. " << endl;
			}
		}
	}
}
int main()
{
	truba tr1;
	CS cs1;
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
		switch (input) {
		case 1:
			Input_truba(tr1);
			break;
		case 2:
			Input_CS(cs1);
			break;
		case 3:
			Print_truba(tr1);
			Print_CS(cs1);
			break;
		case 4:
			Edit_truba(tr1);
			break;
		case 5:
			Edit_CS(cs1);
			break;
		case 6:
			ClearFile();
			Save_truba(tr1);
			Save_CS(cs1);
			break;
		case 7:
			if (both_file.peek() == EOF)
			{
				cout << "File is empty!" << " " << "Please, check your data about your objects!!!" << endl;
				both_file.close();
			}
			else
			{
				Download_truba(tr1);
				Download_CS(cs1);
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
//Закрывать после (про cin.close()) +
//Выполнять проверку внутри функции (на введенные данные) +
//Разобраться с син игнор +
//cin.ignore();//Прочитать документацию +
//Сделать проверку если данные введены, тогда нужно вывести сообщение о том, хочет ли пользователь заново их скачать из файла +
//template шаблон функции проверки (одной для всех типов данных) (для 2 лабы, не нужно на повышение балла)
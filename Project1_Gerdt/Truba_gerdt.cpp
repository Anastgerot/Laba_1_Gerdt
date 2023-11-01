#include <iostream>
#include <fstream>
#include <cstdio>   
#include <string>
#include <unordered_map>
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
template <typename T>
T GetCorrectNumber(T min, T max)
{
	T a;
	while ((cin >> a).fail() || a < min || a > max || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Type number (" "from" << " " << min << " " << "to" << " " << max << "): ";
	}
	return a;
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
	tr.under_repair = GetCorrectNumber(0,1);
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
		out << "Name: " << tr.name << endl
			<< "Length: " << tr.length << endl
			<< "Diameter: " << tr.diameter << endl
			<< "Under repair? (1 - Yes, 0 - No): " << tr.under_repair << endl;
		return out;
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
void Save_truba (ofstream& fout, const truba& tr)
{
	if (tr.name.empty())
	{
		cout << "You don't have the pipe to save\n";
	}
	else
	{
		fout << "Pipe:" << endl;
		fout << tr.name << endl << tr.length << endl << tr.diameter << endl << tr.under_repair << endl;
		cout << "Pipe successfully saved!" << " " << "Please, check your file." << endl;
	}
}
void Download_truba(ifstream& fin, truba& tr)
{
	string line;
	while (getline(fin, line))
	{
		if (line == "Pipe:")
		{
			getline(fin, tr.name);
			fin >> tr.length >> tr.diameter >> tr.under_repair;
		}
	}
	if (tr.name.empty())
	{
		cout << "You don't have data about the pipe to download\n";
	}
	else
	{
		cout << "Your pipe data has been successfully download!" << " " << " Press 3 to check your objects. " << endl;
	}
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
		out << "Name: " << cs.name << endl
			<< "The number of workshops: " << cs.workshop << endl
			<< "The number of workshops in operation: " << cs.workshop_on << endl
			<< "Efficiency: " << cs.efficiency << endl;
	}
	return out;
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
		cs.workshop_on = GetCorrectNumber(1, cs.workshop);
		while (cs.workshop < cs.workshop_on)
		{
			cout << "The number of workshops can't be less then the number of workshops in operation.\n";
			cout << "Please, try again: ";
			cs.workshop_on = GetCorrectNumber(1, cs.workshop);
		}
		cout << "Your new data has been successfully modified.\n";
	}
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
void Download_CS(ifstream& fin, CS& cs)
{
		string line;
		while (getline(fin, line))
		{
			if (line == "Compressor station:")
			{
				getline(fin, cs.name);
				fin >> cs.workshop >> cs.workshop_on >> cs.efficiency;
			}
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
truba& SelectTruba (unordered_map<int, truba>& p) 
{
	cout << "Enter index for your pipe: ";
	unsigned int index = GetCorrectNumber(0u, unsigned int(p.size() - 1));
	return p[index];
}
CS& SelectCS(unordered_map<int, CS>& c)
{
	cout << "Enter index for your compressor station: ";
	unsigned int index = GetCorrectNumber(0u, unsigned int(c.size()-1));
	return c[index];
}
int main()
{
	truba tr1;
	CS cs1;
	int max_id_cs = 0;
	int max_id_truba = 0;
	unordered_map<int, truba> pipe;
	unordered_map<int, CS> ks;
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
		ofstream fout;
		ifstream fin;
		fstream both_file("both.txt");
		switch (GetCorrectNumber(0,7)) {
		case 1:
			cin >> tr1;
			pipe.insert({max_id_truba++, tr1});
			break;
		case 2:
			cin >> cs1;
			ks.insert({max_id_cs++, cs1});
			break;
		case 3:
			cout << "You have" << " " << max_id_truba <<  " " << "pipes!" << endl;;
			cout << SelectTruba(pipe) << endl;
			cout << "You have" << " " << max_id_cs << " " << "compressor stations!" << endl;
			cout << SelectCS(ks) << endl;
			break;
		case 4:
			//Edit_truba(tr1);
			break;
		case 5:
			//Edit_CS(cs1);
			break;
		case 6:
			ClearFile();
			fout.open("both.txt", ios::app);
			if (fout.is_open())
			{
				for (const auto& tr : pipe)
					Save_truba(fout, tr.second);
				for (const auto& cs : ks)
					Save_CS(fout, cs.second);
				fout.close();
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
				fin.open("both.txt", ios::in);
				if (fin.is_open())
				{
					//1 вариант
					//pipe.insert({max_id_truba++ , Download_truba(fin, tr1)});
					//ks.insert({max_id_cs++ , Download_CS(fin, cs1)})
					//2 вариант
					/*if (Download_truba(fin, tr1))
					{
						pipe[max_id_truba++] = tr1;
					}
					if (Download_CS(fin, cs1))
					{
						ks[max_id_cs++] = cs1;
					}
					*/
					fin.close();
					fin.close();
				}
			//Download_truba(tr1);
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

//template шаблон функции проверки (одной для всех типов данных) 
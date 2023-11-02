#include <iostream>
#include <fstream>
#include <cstdio>   
#include <string>
#include <unordered_map>
#include "truba.h"
#include "CS.h"
#include "Utils.h"
using namespace std;
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
		fout << tr.idpipe << endl;
		fout << tr.name << endl << tr.length << endl << tr.diameter << endl << tr.under_repair << endl;
		cout << "Pipe successfully saved!" << " " << "Please, check your file." << endl;
	}
}
truba& Download_truba(ifstream& fin, truba& tr)
{
	string line;
	bool dataloaded = false;
	while (getline(fin, line))
	{
		if (line == "Pipe:")
		{
			fin >> tr.idpipe;
			fin.ignore();
			getline(fin, tr.name);
			fin >> tr.length >> tr.diameter >> tr.under_repair;
			if (dataloaded == false)
			{
				cout << "Your pipe data has been successfully download!" << " " << " Press 3 to check your objects. " << endl;
				dataloaded = true;
			}
			return tr;
		}
	}
	if (tr.name.empty())
	{
		cout << "You don't have data about the pipe to download\n";
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
		fout << cs.idcs << endl;
		fout << cs.name << endl << cs.workshop << endl << cs.workshop_on << endl << cs.efficiency << endl;
		cout << "Compressor station successfully saved!" << " " << "Please, check your file." << endl;
	}
}
CS& Download_CS(ifstream& fin, CS& cs)
{
	string line;
	bool dataloaded = false;
	while (getline(fin, line))
	{
		if (line == "Compressor station:")
		{
			fin >> cs.idcs;
			fin.ignore();
			getline(fin, cs.name);
			fin >> cs.workshop >> cs.workshop_on >> cs.efficiency;
			if (dataloaded == false)
			{
				cout << "Your compressor station data has been successfully download!" << " " << " Press 3 to check your objects. " << endl;
				dataloaded = true;
			}
			return cs;
		}
	}
	if (cs.name.empty())
	{
		cout << "You don't have data about the compressor station to download.\n";
	}
}
void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks) {
	for (auto& pipe : pipe) {
		cout << pipe.second << endl;
	}
	for (auto& cs : ks) {
		cout << cs.second << endl;
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
int main()
{
	truba tr1;
	CS cs1;
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
			pipe.insert({tr1.get_idp(), tr1});
			break;
		case 2:
			cin >> cs1;
			ks.insert({cs1.get_idc(), cs1});
			break;
		case 3:
			Viewall(pipe, ks);
			break;
		case 4:
			Edit_truba(tr1);
			break;
		case 5:
			Edit_CS(cs1);
			break;
		case 6:
			ClearFile();
			fout.open("both.txt", ios::app);
			if (fout.is_open())
			{
				fout << pipe.size() << " " << ks.size() << endl;
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
					int count_pipe, count_cs;
					fin >> count_pipe >> count_cs;
					while (count_pipe--)
						pipe.insert({tr1.get_idp(), Download_truba(fin, tr1)});
						if (truba::max_id_truba < tr1.get_idp())
							truba::max_id_truba = tr1.get_idp();
					while (count_cs--)
						ks.insert({cs1.get_idc(), Download_CS(fin, cs1)});
						if (CS::max_id_cs < cs1.get_idc())
							CS::max_id_cs = cs1.get_idc();
					fin.close();
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
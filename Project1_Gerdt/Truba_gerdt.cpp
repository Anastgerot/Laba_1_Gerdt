#include <iostream>
#include <fstream>
#include <cstdio>   
#include <string>
#include <unordered_map>
#include "truba.h"
#include "CS.h"
#include "Utils.h"
using namespace std;
unordered_map<int, truba> pipe;
unordered_map<int, CS> ks;
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
truba& Download_truba(ifstream& fin, truba& tr)
{
	string line;
	bool dataloaded = false;
	while (getline(fin, line))
	{
		if (line == "Pipe:")
		{
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
	//if (tr.name.empty())
	//{
	//	cout << "You don't have data about the pipe to download\n";
	//}
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
CS& Download_CS(ifstream& fin, CS& cs)
{
	string line;
	bool dataloaded = false;
	while (getline(fin, line))
	{
		if (line == "Compressor station:")
		{
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
	//if (cs.name.empty())
	//{
	//	cout << "You don't have data about the compressor station to download.\n";
	//}
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
void Addpipe()
{
	truba tr1;
	cin >> tr1;
	pipe.insert({ tr1.get_idp(), tr1 });
}
void Addcs()
{
	CS cs1;
	cin >> cs1;
	ks.insert({ cs1.get_idc(), cs1 });
}
void Save_objects()
{
	ofstream fout;
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
}
void Load_Download()
{
	int count_pipe, count_cs;
	ifstream fin;
	fin.open("both.txt", ios::in);
	if (fin.is_open())
	{
		pipe.clear();
		ks.clear();
		fin >> count_pipe >> count_cs;
		for (int i = 0; i < count_pipe; i++) {
			truba tr1;
			pipe.insert({ tr1.get_idp(), Download_truba(fin, tr1) });
		}
		for (int i = 0; i < count_cs; i++) {
			CS cs1;
			ks.insert({ cs1.get_idc(), Download_CS(fin, cs1) });
		}
		fin.close();
	}
}
int Find_under_repair_pipe(bool pipe_under_repair) 
{
	for (const auto& pipe_entry : pipe) 
	{
		const truba& tr = pipe_entry.second;
		if (tr.under_repair == pipe_under_repair) 
		{
			return pipe_entry.first;
		}
	}
	return -1;
}
int Find_name_pipe(const string& pipe_name) {
	for (const auto& pipe_entry : pipe) 
	{
		const truba& tr = pipe_entry.second;
		if (tr.name.find(pipe_name) != string::npos) 
		{
			return pipe_entry.first;
		}
	}
	return -1;
}
int Find_name_cs(const string& cs_name) {
	for (const auto& cs_entry : ks)
	{
		const CS& cs = cs_entry.second;
		if (cs.name.find(cs_name) != string::npos)
		{
			return cs_entry.first;
		}
	}
	return -1;
}
int Find_procent_cs(const string& cs_procent) {
	for (const auto& cs_entry : ks)
	{
		const CS& cs = cs_entry.second;
		int procent;
		try {
			procent = stoi(cs_procent); 
		}
		catch (const invalid_argument& e) {
			cerr << "Invalid input for percentage: " << e.what() << endl;
			return -1; 
		}
		if ((cs.workshop_on * 100 / cs.workshop) == procent)
		{
			return cs_entry.first;
		}
	}
	return -1;
}
void Filter_pipe()
{
	string filter;
	int pipe_id;
	cout << "Write the filter (name or under_repair): ";
	cin >> filter;
	if (filter == "name")
	{
		string pipe_name;
		cout << "Enter the name of the pipe to find: ";
		cin.ignore(); 
		getline(cin, pipe_name); 
		pipe_id = Find_name_pipe(pipe_name);
		if (pipe_id != -1)
		{
			cout << "Pipe found with ID: " << pipe_id << endl;
		}
		else
		{
			cout << "Pipe with the specified name not found." << endl;
		}
	}
	else if (filter == "under_repair")
	{
		bool isUnderRepair;
		cout << "Enter the status 'under_repair' (1 for true, 0 for false): ";
		cin >> isUnderRepair;
		pipe_id = Find_under_repair_pipe(isUnderRepair);
		if (pipe_id != -1)
		{
			cout << "Pipe found with ID: " << pipe_id << endl;
		}
		else
		{
			cout << "No pipe with the specified 'under_repair' status found." << endl;
		}
	}
	else
	{
		cout << "Invalid filter entered, press 8 and try again" << endl;
	}
}
void Filter_cs()
{
	string filter;
	int cs_id;
	cout << "Write the filter (name or procent): ";
	if (filter == "name")
	{
		string cs_name;
		cout << "Enter the name of the compressor station to find: ";
		cin.ignore();
		getline(cin, cs_name); 
		cs_id = Find_name_cs(cs_name);
		if (cs_id != -1)
		{
			cout << "Compressor station found with ID: " << cs_id << endl;
		}
		else
		{
			cout << "Compressor station with the specified name not found." << endl;
		}
	}
	else if (filter == "procent") 
	{
		{
			cout << "Enter the percentage to find: ";
			string cs_procent;
			cin >> cs_procent;
			int cs_id = Find_procent_cs(cs_procent);
			if (cs_id != -1)
			{
				cout << "Compressor station found with ID: " << cs_id << endl;
			}
			else
			{
				cout << "Compressor station with the specified percentage not found." << endl;
			}
		}

	}
	else
	{
		cout << "Invalid filter entered, press 9 and try again" << endl;
	}
}

int main()
{
	while (true) {
		cout << "Choose the number:\n";
		cout << "1. Add the pipe\n";
		cout << "2. Add the compressor station\n";
		cout << "3. View all objects\n";
		cout << "4. Edit the status 'under repair'\n";
		cout << "5. Edit the compressor station\n";
		cout << "6. Save\n";
		cout << "7. Download\n";
		cout << "8. Choose pipe with the filter\n";
		cout << "9. Choose compressor station with the filter\n";
		cout << "0. Exit\n";
		cout << "Selection: ";
		fstream both_file("both.txt");
		switch (GetCorrectNumber(0,9)) {
		case 1:
			Addpipe();
			break;
		case 2:
			Addcs();
			break;
		case 3:
			Viewall(pipe, ks);
			break;
		case 4:;
			//Edit_truba(tr1);
			break;
		case 5:
			//Edit_CS(cs1);
			break;
		case 6:
			Save_objects();
			break;
		case 7:
			if (both_file.peek() == EOF)
			{
				cout << "File is empty!" << " " << "Please, check your data about your objects!!!" << endl;
				both_file.close();
			}
			else
			{
				Load_Download();
			}
			break;
		case 8:
			Filter_pipe();
			break;
		case 9:
			Filter_cs();
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
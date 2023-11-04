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
void Edit_truba()
{
	int number_pipes;
	int pipe_size = pipe.size();
	if (pipe_size == 0)
	{
		cout << "You don't have any pipes" << endl;
	}
	else
	{
		cout << "Enter the number of pipes you want to edit: ";
		number_pipes = GetCorrectNumber(0, pipe_size);
		if (number_pipes == pipe_size)
		{
			for (int i = 0; i < number_pipes; i++)
			{
				truba& tr = pipe[i];
				tr.under_repair = !tr.under_repair;

			}
			cout << "The status of all your pipes has been successfully changed." << endl;
		}
		else
		{
			for (int i = 0; i < number_pipes; i++)
			{
				int choose_pipe;
				cout << "Enter the ID of the pipe you want to change: ";
				cin >> choose_pipe;
				if (choose_pipe >= 0 && choose_pipe < pipe_size)
				{
					truba& tr = pipe[choose_pipe];
					tr.under_repair = !tr.under_repair;
					cout << "The status of pipe " << choose_pipe << " has been successfully changed." << endl;
				}
				else
				{
					cout << "Invalid pipe ID for pipe " << choose_pipe << ". Please enter a valid ID." << endl;
				}
			}
		}
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
}
void Edit_CS()
{
	int number_cs;
	int cs_size = ks.size();
	if (cs_size == 0)
	{
		cout << "You don't have any compressor stations" << endl;
	}
	else
	{
		cout << "Enter the number of compressor stations you want to edit: ";
		number_cs = GetCorrectNumber(0, cs_size);
		if (number_cs == cs_size)
		{
			for (int i = 0; i < number_cs; i++)
			{
				CS& cs = ks[i];
				cout << "The number of workshops: " << " " << cs.workshop << endl;
				cout << "Type the new number of workshops in operation: ";
				cs.workshop_on = GetCorrectNumber(1, cs.workshop);
				while (cs.workshop < cs.workshop_on)
				{
					cout << "The number of workshops can't be less then the number of workshops in operation.\n";
					cout << "Please, try again: ";
					cs.workshop_on = GetCorrectNumber(1, cs.workshop);
				}
				cout << "Your new data for all of your compressor stations has been successfully modified.\n";

			}
		}
		else
		{
			for (int i = 0; i < number_cs; i++)
			{
				int choose_cs;
				cout << "Enter the ID of the compressor stations you want to change: ";
				cin >> choose_cs;
				if (choose_cs >= 0 && choose_cs < cs_size)
				{
					CS& cs = ks[choose_cs];
					cout << "The number of workshops: " << " " << cs.workshop << endl;
					cout << "Type the new number of workshops in operation: ";
					cs.workshop_on = GetCorrectNumber(1, cs.workshop);
					while (cs.workshop < cs.workshop_on)
					{
						cout << "The number of workshops can't be less then the number of workshops in operation.\n";
						cout << "Please, try again: ";
						cs.workshop_on = GetCorrectNumber(1, cs.workshop);
					}
					cout << "The status of compressor station " << choose_cs << " has been successfully changed." << endl;
				}
			}
		}

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
}
void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks) 
{
	if (pipe.size() == 0 && ks.size() == 0)
	{
		cout << "You don't have any objects" << endl;
	}
	else
	{
		for (auto& pipe : pipe) {
			cout << pipe.second << endl;
		}
		for (auto& cs : ks) {
			cout << cs.second << endl;
		}
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
	if (pipe.size() == 0 && ks.size() == 0)
	{
		cout << "You don't have any objects" << endl;
	}
	else
	{
		string filename;
		cout << "Enter the name of your file: ";
		cin >> filename;
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);
		if (fout.is_open())
		{
			fout << pipe.size() << " " << ks.size() << endl;
			for (const auto& tr : pipe)
				Save_truba(fout, tr.second);
			for (const auto& cs : ks)
				Save_CS(fout, cs.second);
			fout.close();
		}
		else
		{
			std::cout << "Failed to open the file." << endl;
		}
	}
}
void Load_Download() 
{
	int count_pipe = 0;
	int count_cs = 0;
	ifstream fin;
	string filename;
	cout << "Enter the name of the file to load: ";
	cin >> filename;
	fin.open((filename + ".txt"), ios::in);
	if (!fin.is_open()) 
	{
		cout << "Failed to open the file for loading." << endl;
	}
	else {
		pipe.clear();
		ks.clear();
		fin >> count_pipe >> count_cs;
		if (count_pipe == 0 && count_cs == 0) 
		{
			cout << "You don't have objects to download" << endl;
		}
		else 
		{
			for (int i = 0; i < count_pipe; i++) 
			{
				truba tr1;
				pipe.insert({ tr1.get_idp(), Download_truba(fin, tr1) });
			}
			for (int i = 0; i < count_cs; i++) 
			{
				CS cs1;
				ks.insert({ cs1.get_idc(), Download_CS(fin, cs1) });
			}
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
		if (((cs.workshop - cs.workshop_on) * 100 / cs.workshop) == procent)
		{
			return cs_entry.first;
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
void Filter() {
	int choice;
	string filter;
	vector<int> matching_pipes;
	vector<int> matching_cs;

	cout << "Select objects to use filter:" << endl;
	cout << "1. Use filter for pipes" << endl;
	cout << "2. Use filter for compressor stations" << endl;
	cout << "Enter your choice: ";
	switch (GetCorrectNumber(1, 2)) 
	{
	case 1: 
		int pipe_id;
		cout << "Write the filter (name or under_repair): ";
		cin >> filter;
		if (filter == "name") 
		{
			string pipe_name;
			cout << "Enter the name of the pipe to find: ";
			cin.ignore();
			getline(cin, pipe_name);
			for (const auto& pipe_entry : pipe) 
			{
				const truba& tr = pipe_entry.second;
				if (tr.name.find(pipe_name) != string::npos) 
				{
					matching_pipes.push_back(pipe_entry.first);
				}
			}

			if (!matching_pipes.empty()) 
			{
				cout << "Pipes found: ";
				for (int pipe_id : matching_pipes) 
				{
					cout << pipe[pipe_id] << endl;
				}
				cout << endl;
			}
			else {
				cout << "No pipes with the specified name found." << endl;
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
				cout << "Pipe found with ID: " << pipe[pipe_id] << endl;
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
		break;

	case 2:
		int cs_id;
		cout << "Write the filter (name or procent): ";
		cin >> filter;

		if (filter == "name") 
		{
			string cs_name;
			cout << "Enter the name of the compressor station to find: ";
			cin.ignore();
			getline(cin, cs_name);

			for (const auto& cs_entry : ks) 
			{
				const CS& cs = cs_entry.second;
				if (cs.name.find(cs_name) != string::npos) 
				{
					matching_cs.push_back(cs_entry.first);
				}
			}

			if (!matching_cs.empty()) 
			{
				cout << "Compressor stations found: ";
				for (int cs_id : matching_cs) 
				{
					cout << ks[cs_id] << endl;
				}
				cout << endl;
			}
			else {
				cout << "No compressor stations with the specified name found." << endl;
			}
		}
		else if (filter == "procent") 
		{
			cout << "Enter the percentage to find: ";
			string cs_procent;
			cin >> cs_procent;
			int cs_id = Find_procent_cs(cs_procent);
			if (cs_id != -1)
			{
				cout << "Compressor station found with ID: " << ks[cs_id] << endl;
			}
			else
			{
				cout << "Compressor station with the specified percentage not found." << endl;
			}

		}
		else
		{
			cout << "Invalid filter entered, press 9 and try again" << endl;
		}
		break;

	default:
		cout << "Invalid choice. Please enter 1 or 2." << endl;
		break;
	}
}
void Delete_objects()
{
	int choice;
	int number_pipes;
	int number_cs;
	int pipe_size = pipe.size();
	int cs_size = ks.size();
	cout << "Select objects to delete:" << endl;
	cout << "1. Delete pipes" << endl;
	cout << "2. Delete compressor stations" << endl;
	cout << "Enter your choice: ";
	choice = GetCorrectNumber(1, 2);

	switch (choice)
	{
	case 1:
		if (pipe_size == 0)
		{
			cout << "You don't have pipes to delete" << endl;
		}
		else
		{
			cout << "Enter the number of pipes you want to delete: ";
			number_pipes = GetCorrectNumber(0, pipe_size);
			if (number_pipes == pipe_size)
			{
				pipe.clear();
				cout << "All of your pipes have been successfully deleted" << endl;
			}
			else
			{
				for (int i = 0; i < number_pipes; i++)
				{
					int choose_pipe;
					cout << "Enter the ID of the pipe you want to delete: ";
					cin >> choose_pipe;
					auto it = pipe.find(choose_pipe);
					if (it != pipe.end())
					{
						pipe.erase(it);
						cout << "Pipe with ID " << choose_pipe << " has been deleted." << endl;
					}
					else
					{
						cout << "Pipe with ID " << choose_pipe << " not found." << endl;
					}
				}
			}
		}
		break;

	case 2:
		if (cs_size == 0)
		{
			cout << "You don't have compressor stations to delete" << endl;
		}
		else
		{
			cout << "Enter the number of compressor stations you want to delete: ";
			number_cs = GetCorrectNumber(0, cs_size);
			if (number_cs == cs_size)
			{
				ks.clear();
				cout << "All of your compressor stations have been successfully deleted" << endl;
			}
			else
			{
				for (int i = 0; i < number_cs; i++)
				{
					int choose_cs;
					cout << "Enter the ID of the compressor station you want to delete: ";
					cin >> choose_cs;

					auto it = ks.find(choose_cs);
					if (it != ks.end())
					{
						ks.erase(it);
						cout << "Compressor station with ID " << choose_cs << " has been deleted." << endl;
					}
					else
					{
						cout << "Compressor station with ID " << choose_cs << " not found." << endl;
					}
				}
			}
		}
		break;

	default:
		cout << "Invalid choice. Please enter 1 or 2." << endl;
		break;
	}
}
int main()
{
	while (true) 
	{
		cout << "Choose the number:\n";
		cout << "1. Add the pipe\n";
		cout << "2. Add the compressor station\n";
		cout << "3. View all objects\n";
		cout << "4. Edit the status 'under repair'\n";
		cout << "5. Edit the compressor station\n";
		cout << "6. Save\n";
		cout << "7. Download\n";
		cout << "8. Choose objects with the filter\n";
		cout << "9. Delete the object\n";
		cout << "0. Exit\n";
		cout << "Selection: ";
		switch (GetCorrectNumber(0,9)) 
		{
		case 1:
			Addpipe();
			break;
		case 2:
			Addcs();
			break;
		case 3:
			Viewall(pipe, ks);
			break;
		case 4:
			Edit_truba();
			break;
		case 5:
			Edit_CS();
			break;
		case 6:
			Save_objects();
			break;
		case 7:
			Load_Download();
			break;
		case 8:
			Filter();
			break;
		case 9:
			Delete_objects();
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
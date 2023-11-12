#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set> 
#include "truba.h"
#include "CS.h"
#include "Utils.h"
using namespace std;
unordered_map<int, truba> pipe;
unordered_map<int, CS> ks;
void Viewall()
{
	if (pipe.size() == 0 && ks.size() == 0)
	{
		Log("You don't have any objects to see");
	}
	else
	{
		Log("It is all of your objects:");
		for (auto& pipe : pipe) {
			cout << pipe.second << endl;
		}
		for (auto& cs : ks) {
			cout << cs.second << endl;
		}
	}
}
void Save_objects()
{
	if (pipe.empty() && ks.empty())
	{
		Log("You don't have any objects to save");
	}
	else
	{
		string filename;
		Log("Enter the name of your file: ");
		cin >> filename;
		Log(filename);
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);
		if (fout.is_open())
		{
			fout << pipe.size() << " " << ks.size() << endl;
			for (const auto& tr : pipe)
			{
				Save_truba(fout, tr.second);
				Log("Pipe with ID " + to_string(tr.first) + " successfully saved! Please, check your file.");
			}
			for (const auto& cs : ks)
			{
				Save_CS(fout, cs.second);
				Log("CS with ID " + to_string(cs.first) + " successfully saved! Please, check your file.");
			}
			fout.close();
		}
		else
		{
			Log("Failed to open the file with name " + filename + " to save.");
		}
	}
}
void Load_Download() {
	int count_pipe = 0;
	int count_cs = 0;
	ifstream fin;
	string filename;
	Log("Enter the name of the file to load: ");
	cin >> filename;
	Log_cin(filename);
	fin.open((filename + ".txt"), ios::in);
	if (!fin.is_open()) {
		Log("Failed to open the file with name " + filename + " for loading.");
	}
	else {
		//pipe.clear();
		//ks.clear();
		fin >> count_pipe >> count_cs;
		if (count_pipe == 0 && count_cs == 0) {
			Log("You don't have objects to download");
		}
		else {
			for (int i = 0; i < count_pipe; i++) {
				truba tr1;
				tr1 = Download_truba(fin, tr1); 
				pipe.insert({ tr1.get_idp(), tr1 });
				Log("Your pipe with ID " + to_string(tr1.get_idp()) + " has been successfully download! Press 3 to check your objects. ");
			}
			for (int i = 0; i < count_cs; i++) {
				CS cs1;
				cs1 = Download_CS(fin, cs1); 
				ks.insert({ cs1.get_idc(), cs1 });
				Log("Your compressor station with ID " + to_string(cs1.get_idc()) + " has been successfully download! Press 3 to check your objects. ");
			}
		}
		fin.close();
	}
}
void Filter() {
	int choice;
	string filter;
	set<int> matching_pipes;
	set<int> matching_cs;
	while (true) {
		Log("Select objects to use filter:");
		Log("1. Use filter for pipes");
		Log("2. Use filter for compressor stations");
		Log("3. Edit found objects");
		Log("4. Delete found objects");
		Log("0. Exit");
		Log("Enter your choice: ");
		choice = GetCorrectNumber(0, 4);
		Log_cin(to_string(choice));
		switch (choice) {
		case 1:
			Log("Write the filter (name or under_repair): ");
			cin >> filter;
			Log_cin(filter);
			if (filter == "name") {
				string pipe_name;
				Log("Enter the name of the pipe to find: ");
				cin.ignore();
				getline(cin, pipe_name);
				for (const auto& pipe_entry : pipe) {
					const truba& tr = pipe_entry.second;
					if (tr.name.find(pipe_name) != string::npos) {
						matching_pipes.insert(pipe_entry.first);
					}
				}
				if (!matching_pipes.empty()) {
					Log("Pipes found: ");
					for (int pipe_id : matching_pipes) {
						cout << pipe[pipe_id] << endl;
					}
				}
				else {
					Log("No pipes with the specified name found.");
				}
			}
			else if (filter == "under_repair") {
				bool isUnderRepair;
				Log("Enter the status 'under_repair' (1 for true, 0 for false): ");
				cin >> isUnderRepair;
				Log_cin(to_string(isUnderRepair));
				int pipe_id = Find_pipe(pipe, isUnderRepair, Find_under_repair<truba>);
				if (pipe_id != -1) {
					matching_pipes.insert(pipe_id);
					Log("Pipe found with ID: ");
					cout << pipe[pipe_id] << endl;
				}
				else {
					Log("No pipe with the specified 'under_repair' status found.");
				}
			}
			else {
				Log("Invalid filter entered, press 8 and try again");
			}
			break;

		case 2:
			Log("Write the filter (name or procent): ");
			cin >> filter;

			if (filter == "name") {
				string cs_name;
				Log("Enter the name of the compressor station to find: ");
				cin.ignore();
				getline(cin, cs_name);

				for (const auto& cs_entry : ks) {
					const CS& cs = cs_entry.second;
					if (cs.name.find(cs_name) != string::npos) {
						matching_cs.insert(cs_entry.first);
					}
				}

				if (!matching_cs.empty()) {
					Log("Compressor stations found: ");
					for (int cs_id : matching_cs) {
						cout << ks[cs_id] << endl;
					}
				}
				else {
					Log("No compressor stations with the specified name found.");
				}
			}
			else if (filter == "procent") {
				Log("Enter the percentage to find: ");
				string cs_procent;
				cin >> cs_procent;
				int cs_id = Find_cs(ks, cs_procent, Find_procent<CS>);
				if (cs_id != -1) {
					matching_cs.insert(cs_id);
					Log("Compressor station found with ID: ");
					cout << ks[cs_id] << endl;
				}
				else {
					Log("Compressor station with the specified percentage not found.");
				}
			}
			else {
				Log("Invalid filter entered, press 9 and try again");
			}
			break;
		case 3:
			Log("Select objects to edit:");
			Log("1. Edit found pipes");
			Log("2. Edit found compressor stations");
			Log("Enter your choice: ");
			int editChoice;
			cin >> editChoice;
			Log_cin(to_string(editChoice));

			if (editChoice == 1) {
				if (matching_pipes.size() == 0) {
					Log("You don't have pipes to edit");
				}
				else {
					for (int pipe_id : matching_pipes)
					{
						truba& tr = pipe[pipe_id];
						tr.under_repair = !tr.under_repair;
						Log("The status of pipe " + to_string(pipe_id) + " has been successfully changed.");
					}
				}
			}
			else if (editChoice == 2) {
				if (matching_cs.size() == 0) {
					Log("You don't have compressor stations to edit");
				}
				else {
					for (int cs_id : matching_cs)
					{
						CS& cs = ks[cs_id];
						Log("The number of workshops: " + to_string(cs.workshop));
						Log("Type the new number of workshops in operation:");
						Log_cin(to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)));
						while (cs.workshop < cs.workshop_on)
						{
							Log("The number of workshops can't be less then the number of workshops in operation.");
							Log("Please, try again: ");
							Log_cin(to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)));
						}
						Log("The status of compressor station " + to_string(cs_id) + " has been successfully changed.");
					}
				}
			}
			else {
				Log("Invalid choice. Please enter 1 or 2.");
			}
			break;
		case 4:
			if (!matching_pipes.empty() || !matching_cs.empty()) {
				Log("Do you want to remove pipes (1), compressor stations (2), or both (3)?");
				int removalChoice = GetCorrectNumber(1, 3);

				if (removalChoice == 1 || removalChoice == 3) {
					for (int id : matching_pipes) {
						auto pipe_iter = pipe.find(id);
						if (pipe_iter != pipe.end()) {
							pipe.erase(pipe_iter);
						}
					}
					Log("Pipes removed successfully.");
					matching_pipes.clear();
				}

				if (removalChoice == 2 || removalChoice == 3) {
					for (int id : matching_cs) {
						auto cs_iter = ks.find(id);
						if (cs_iter != ks.end()) {
							ks.erase(cs_iter);
						}
					}
					Log("Compressor stations removed successfully.");
					matching_cs.clear();
				}
			}
			else {
				Log("No objects found to remove.");
			}
			break;
		case 0:
			return;
		default:
			Log("Invalid choice. Please enter 0-4");
			break;
		}
	}
}
int main()
{
	while (true)
	{
		int choice;
		Log("Choose the number:");
		Log("1. Add the pipe");
		Log("2. Add the compressor station");
		Log("3. View all objects");
		Log("4. Save");
		Log("5. Download");
		Log("6. Choose and Edit objects with the filter");
		Log("0. Exit");
		Log("Selection: ");
		choice = GetCorrectNumber(0, 6);
		Log_cin(to_string(choice));
		switch (choice)
		{
		case 1:
			Addpipe(pipe);
			break;
		case 2:
			Addcs(ks);
			break;
		case 3:
			Viewall();
			break;
		case 4:
			Save_objects();
			break;
		case 5:
			Load_Download();
			break;
		case 6:
			Filter();
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
//Комментарии: 
//Нужно было сделать процент более легким для нахождения (например, если у меня 33.333, то пользователь сможет найти кс и при 66, и при 67)
//Также нужно было распределить все функции относящиеся к трубам в truba.cpp, а кс в CS.cpp
//Также, я усовершенствовала функции поиска по фильтру и логирование - сделала из них шаблоны и поместила в Utils.h, чтобы он был создан не только для одного шаблона
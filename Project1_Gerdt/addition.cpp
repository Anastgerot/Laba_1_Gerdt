#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <sstream>
#include <vector>
#include "addition.h"
#include "truba.h"
#include "CS.h"
#include "Utils.h"
using namespace std;
void Addpipe(unordered_map<int, truba>& pipe)
{
	truba tr1;
	cin >> tr1;
	pipe.insert({ tr1.get_idp(), tr1 });
}
void Addcs(unordered_map<int, CS>& ks)
{
	CS cs1;
	cin >> cs1;
	ks.insert({ cs1.get_idc(), cs1 });
}
void ClearLogFile()
{
	ofstream logFile("log.txt", ios::trunc);
	logFile.close();
}
vector<int> ParseIds(const string& input)
{
	vector<int> ids;
	istringstream iss(input);
	int id;

	while (iss >> id)
	{
		ids.push_back(id);
	}

	return ids;
}
void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks)
{
	if (pipe.size() == 0 && ks.size() == 0)
	{
		cout << "You don't have any objects to see" << endl;
	}
	else
	{
		cout << "It is all of your objects:" << endl;
		for (auto& pipe : pipe) {
			cout << pipe.second << endl;
		}
		for (auto& cs : ks) {
			cout << cs.second << endl;
		}
	}
}
void Save_objects(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks)
{
	if (pipe.empty() && ks.empty())
	{
		cout << "You don't have any objects to save" << endl;
	}
	else
	{
		string filename;
		cout << "Enter the name of your file: ";
		cin >> filename;
		cout << filename;
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);
		if (fout.is_open())
		{
			fout << pipe.size() << " " << ks.size() << endl;
			for (const auto& tr : pipe)
			{
				Save_truba(fout, tr.second);
				cout << "Pipe with ID " << to_string(tr.first) << " successfully saved! Please, check your file." << endl;
			}
			for (const auto& cs : ks)
			{
				Save_CS(fout, cs.second);
				cout << "CS with ID " << to_string(cs.first) << " successfully saved! Please, check your file." << endl;
			}
			fout.close();
		}
		else
		{
			cout << "Failed to open the file with name " << filename << " to save." << endl;
		}
	}
}
void Load_Download(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks) {
	int count_pipe = 0;
	int count_cs = 0;
	ifstream fin;
	string filename;
	cout << "Enter the name of the file to load: ";
	cin >> filename;
	cout << filename;
	fin.open((filename + ".txt"), ios::in);
	if (!fin.is_open()) {
		cout << "Failed to open the file with name " << filename << " for loading." << endl;
	}
	else {
		pipe.clear();
		ks.clear();
		fin >> count_pipe >> count_cs;
		if (count_pipe == 0 && count_cs == 0) {
			cout << "You don't have objects to download" << endl;
		}
		else {
			for (int i = 0; i < count_pipe; i++) {
				truba tr1;
				tr1 = Download_truba(fin, tr1);
				pipe.insert({ tr1.get_idp(), tr1 });
				cout << "Your pipe with ID " << to_string(tr1.get_idp()) << " has been successfully download! Press 3 to check your objects." << endl;
			}
			for (int i = 0; i < count_cs; i++) {
				CS cs1;
				cs1 = Download_CS(fin, cs1);
				ks.insert({ cs1.get_idc(), cs1 });
				cout << "Your compressor station with ID " << to_string(cs1.get_idc()) << " has been successfully download! Press 3 to check your objects." << endl;
			}
		}
		fin.close();
	}
}
void Filter(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks) {
	int choice;
	string filter;
	set<int> matching_pipes;
	set<int> matching_cs;
	while (true) {
		cout << "Select objects to use filter:" << endl;
		cout << "1. Use filter for pipes" << endl;
		cout << "2. Use filter for compressor stations" << endl;
		cout << "3. Edit found objects" << endl;
		cout << "4. Delete found objects" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice: ";
		choice = GetCorrectNumber(0, 4);
		cout << to_string(choice);
		switch (choice) {
		case 1:
			cout << "Write the filter (name or under_repair): ";
			cin >> filter;
			cout << filter;
			if (filter == "name") {
				matching_pipes.clear();
				string pipe_name;
				cout << "Enter the name of the pipe to find: ";
				cin.ignore();
				getline(cin, pipe_name);
				vector<int> matching_id_name_pipe;
				for (const auto& pipe_entry : pipe) {
					const truba& tr = pipe_entry.second;
					if (tr.name.find(pipe_name) != string::npos) {
						matching_id_name_pipe.push_back(pipe_entry.first);
					}
				}
				if (!matching_id_name_pipe.empty()) {
					cout << "Pipes found: " << endl;
					for (int pipe_id : matching_id_name_pipe) {
						cout << pipe[pipe_id] << endl;
						matching_pipes.insert(pipe_id);
					}
					matching_id_name_pipe.clear();
				}
				else {
					cout << "No pipes with the specified name found." << endl;
				}
			}
			else if (filter == "under_repair") {
				matching_pipes.clear();
				bool isUnderRepair;
				cout << "Enter the status 'under_repair' (1 for true, 0 for false): ";
				cin >> isUnderRepair;
				cout << to_string(isUnderRepair);
				vector<int> matching_ids = Find_pipe(pipe, isUnderRepair, Find_under_repair<truba>);
				if (!matching_ids.empty()) {
					cout << "Pipes found: " << endl;
					for (int pipe_id : matching_ids) {
						cout << pipe[pipe_id] << endl;
						matching_pipes.insert(pipe_id);
					}
					matching_ids.clear();
				}
				else {
					cout << "No pipes with the specified 'under_repair' status found." << endl;
				}

			}
			else {
				cout << "Invalid filter entered, press 8 and try again" << endl;
			}
			break;

		case 2:
			cout << "Write the filter (name or procent): ";
			cin >> filter;

			if (filter == "name") {
				matching_cs.clear();
				string cs_name;
				cout << "Enter the name of the compressor station to find: ";
				cin.ignore();
				getline(cin, cs_name);
				vector<int> matching_id_name_cs;
				for (const auto& cs_entry : ks) {
					const CS& cs = cs_entry.second;
					if (cs.name.find(cs_name) != string::npos) {
						matching_id_name_cs.push_back(cs_entry.first);
					}
				}
				if (!matching_id_name_cs.empty()) {
					cout << "Compressor stations found: " << endl;
					for (int cs_id : matching_id_name_cs) {
						cout << ks[cs_id] << endl;
						matching_cs.insert(cs_id);
					}
					matching_id_name_cs.clear();
				}
				else {
					cout << "No compressor stations with the specified name found." << endl;
				}
			}
			else if (filter == "procent") {
				matching_cs.clear();
				cout << "Enter the percentage to find: ";
				string cs_procent;
				cin >> cs_procent;
				cout << cs_procent;
				vector<int> matching_ids = Find_cs(ks, cs_procent, Find_procent<CS>);
				if (!matching_cs.empty()) {
					cout << "Compressor stations found: " << endl;
					for (int cs_id : matching_ids) {
						cout << ks[cs_id] << endl;
						matching_cs.insert(cs_id);
					}
					matching_ids.clear();
				}
				else {
					cout << "No compressor stations with the specified percentage found." << endl;
				}
			}
			else {
				cout << "Invalid filter entered, press 9 and try again" << endl;
			}
			break;
		case 3:
			cout << "Select objects to edit:" << endl;
			cout << "1. Edit found pipes" << endl;
			cout << "2. Edit found compressor stations" << endl;
			cout << "Enter your choice: ";
			int editChoice;
			cin >> editChoice;
			cout << to_string(editChoice);

			if (editChoice == 1) {
				if (matching_pipes.size() == 0) {
					cout << "You don't have pipes to edit" << endl;
				}
				else {
					cout << "Do you want to edit all found pipes (1) or specify IDs (2)?";
					int editAllChoice = GetCorrectNumber(1, 2);
					if (editAllChoice == 1) {
						for (int pipe_id : matching_pipes) {
							truba& tr = pipe[pipe_id];
							tr.under_repair = !tr.under_repair;
							cout << "The status of pipe " << to_string(pipe_id) << " has been successfully changed." << endl;
						}
					}
					else if (editAllChoice == 2) {
						cin.ignore();
						cout << "Enter pipe IDs to edit (separated by space): ";
						string idInput;
						getline(cin, idInput);
						vector<int> ids = ParseIds(idInput);
						for (int id : ids) {
							auto pipe_iter = pipe.find(id);
							if (pipe_iter != pipe.end()) {
								pipe_iter->second.under_repair = !pipe_iter->second.under_repair;
								cout << "The status of pipe " << to_string(id) << " has been successfully changed." << endl;
							}
							else {
								cout << "Pipe with ID " << to_string(id) << " not found." << endl;
							}
						}
					}
				}
			}
			else if (editChoice == 2) {
				if (matching_cs.size() == 0) {
					cout << "You don't have compressor stations to edit" << endl;
				}
				else {
					cout << "Do you want to edit all found compressor stations (1) or specify IDs (2)?";
					int editAllChoice = GetCorrectNumber(1, 2);
					if (editAllChoice == 1) {
						for (int cs_id : matching_cs) {
							CS& cs = ks[cs_id];
							cout << "The number of workshops: " << to_string(cs.workshop) << endl;
							cout << "Type the new number of workshops in operation:" << endl;
							cout << to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)) << endl;
							while (cs.workshop < cs.workshop_on) {
								cout << "The number of workshops can't be less than the number of workshops in operation." << endl;
								cout << "Please, try again: " << endl;
								cout << to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)) << endl;
							}
							cout << "The status of compressor station " << to_string(cs_id) << " has been successfully changed." << endl;
						}
					}
					else if (editAllChoice == 2) {
						cin.ignore();
						cout << "Enter compressor station IDs to edit (separated by space): ";
						string idInput;
						getline(cin, idInput);
						vector<int> ids = ParseIds(idInput);
						for (int id : ids) {
							auto cs_iter = ks.find(id);
							if (cs_iter != ks.end()) {
								CS& cs = cs_iter->second;
								cout << "The status of compressor station " << to_string(id) << " has been successfully changed." << endl;
							}
							else {
								cout << "Compressor station with ID " << to_string(id) << " not found." << endl;
							}
						}
					}
				}
			}
			else {
				cout << "Invalid choice. Please enter 1 or 2." << endl;
			}
			break;
		case 4:
			if (!matching_pipes.empty() || !matching_cs.empty()) {
				cout << "Do you want to remove pipes (1), compressor stations (2), or both (3)?";
				int removalChoice = GetCorrectNumber(1, 3);
				if (removalChoice == 1 || removalChoice == 3) {
					cout << "Do you want to delete all found pipes (1) or specify IDs (2)?";
					int deleteChoice = GetCorrectNumber(1, 2);
					if (deleteChoice == 1) {
						for (int id : matching_pipes) {
							auto pipe_iter = pipe.find(id);
							if (pipe_iter != pipe.end()) {
								pipe.erase(pipe_iter);
							}
						}
						cout << "Pipes removed successfully.";
						matching_pipes.clear();
					}
					else if (deleteChoice == 2) {
						cin.ignore();
						cout << "Enter pipe IDs to remove (separated by space): ";
						string idInput;
						getline(cin, idInput);
						vector<int> ids = ParseIds(idInput);
						for (int id : ids) {
							auto pipe_iter = pipe.find(id);
							if (pipe_iter != pipe.end()) {
								pipe.erase(pipe_iter);
							}
							else {
								cout << "Pipe with ID " << to_string(id) << " not found.";
							}
						}
					}
				}

				if (removalChoice == 2 || removalChoice == 3) {
					cout << "Do you want to delete all found compressor stations (1) or specify IDs (2)?";
					int deleteChoice = GetCorrectNumber(1, 2);
					if (deleteChoice == 1) {
						for (int id : matching_cs) {
							auto cs_iter = ks.find(id);
							if (cs_iter != ks.end()) {
								ks.erase(cs_iter);
							}
						}
						cout << "Compressor stations removed successfully.";
						matching_cs.clear();
					}
					else if (deleteChoice == 2) {
						cin.ignore();
						cout << "Enter compressor station IDs to remove (separated by space): ";
						string idInput;
						getline(cin, idInput);
						vector<int> ids = ParseIds(idInput);
						for (int id : ids) {
							auto cs_iter = ks.find(id);
							if (cs_iter != ks.end()) {
								ks.erase(cs_iter);
							}
							else {
								cout << "Compressor station with ID " << to_string(id) << " not found.";
							}
						}
					}
				}
			}
			else {
				cout << "No objects found to remove.";
			}
			break;
		case 0:
			return;
		default:
			cout << "Invalid choice. Please enter 0-4";
			break;
		}
	}
}
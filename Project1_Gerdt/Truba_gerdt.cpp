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
void Log(const string& message) 
{
	ofstream logFile("log.txt", ios::app);
	if (logFile.is_open()) 
	{
		logFile << message << endl;
		logFile.close();
	}
	cout << message << endl;
}
void Log_cin(const string& message)
{
	ofstream logFile("log.txt", ios::app);
	if (logFile.is_open())
	{
		logFile << message << endl;
		logFile.close();
	}
}
void Edit_truba()
{
	int number_pipes;
	int pipe_size = pipe.size();
	if (pipe_size == 0)
	{
		Log("You don't have any pipes to edit");
	}
	else
	{
		Log("Enter the number of pipes you want to edit: ");
		Log_cin(to_string(number_pipes = GetCorrectNumber(0, pipe_size)));
		if (number_pipes == pipe_size)
		{
			for (int i = 0; i < number_pipes; i++)
			{
				truba& tr = pipe[i];
				tr.under_repair = !tr.under_repair;

			}
			Log("The status of all your pipes has been successfully changed.");
		}
		else
		{
			for (int i = 0; i < number_pipes; i++)
			{
				int choose_pipe;
				Log("Enter the ID of the pipe you want to change: ");
				Log_cin(to_string(choose_pipe = GetCorrectNumber(0, truba::max_id_truba - 1)));
				if (choose_pipe >= 0 && choose_pipe < pipe_size)
				{
					truba& tr = pipe[choose_pipe];
					tr.under_repair = !tr.under_repair;
					Log("The status of pipe " + to_string(choose_pipe) + " has been successfully changed.");
				}
			}
		}
	}
}
void Save_truba (ofstream& fout, const truba& tr)
{
	if (tr.name.empty())
	{
		Log("You don't have the pipe to save");
	}
	else
	{
		fout << "Pipe:" << endl;
		fout << tr.name << endl << tr.length << endl << tr.diameter << endl << tr.under_repair << endl;
	}
}
truba& Download_truba(ifstream& fin, truba& tr)
{
	string line;
	while (getline(fin, line))
	{
		if (line == "Pipe:")
		{
			getline(fin, tr.name);
			fin >> tr.length >> tr.diameter >> tr.under_repair;
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
		Log("You don't have any compressor stations");
	}
	else
	{
		Log("Enter the number of compressor stations you want to edit:");
		Log_cin(to_string(number_cs = GetCorrectNumber(0, cs_size)));
		if (number_cs == cs_size)
		{
			for (int i = 0; i < number_cs; i++)
			{
				CS& cs = ks[i];
				Log("The number of workshops: " + to_string(cs.workshop));
				Log("Type the new number of workshops in operation:");
				Log_cin(to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)));
				while (cs.workshop < cs.workshop_on)
				{
					Log("The number of workshops can't be less then the number of workshops in operation.");
					Log("Please, try again: ");
					Log_cin(to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)));
				}
				Log("Your new data for all of your compressor stations has been successfully modified.");

			}
		}
		else
		{
			for (int i = 0; i < number_cs; i++)
			{
				int choose_cs;
				Log("Enter the ID of the compressor stations you want to change:");
				Log_cin(to_string(choose_cs = GetCorrectNumber(0, CS::max_id_cs-1)));
				if (choose_cs >= 0 && choose_cs < cs_size)
				{
					CS& cs = ks[choose_cs];
					Log("The number of workshops: " + to_string(cs.workshop));
					Log("Type the new number of workshops in operation:");
					Log_cin(to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)));
					while (cs.workshop < cs.workshop_on)
					{
						Log("The number of workshops can't be less then the number of workshops in operation.");
						Log("Please, try again: ");
						Log_cin(to_string(cs.workshop_on = GetCorrectNumber(1, cs.workshop)));
					}
					Log("The status of compressor station " + to_string(choose_cs) + " has been successfully changed.");
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
	}
}
CS& Download_CS(ifstream& fin, CS& cs)
{
	string line;
	while (getline(fin, line))
	{
		if (line == "Compressor station:")
		{
			getline(fin, cs.name);
			fin >> cs.workshop >> cs.workshop_on >> cs.efficiency;
			return cs;
		}
	}
}
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
void Load_Download() 
{
	int count_pipe = 0;
	int count_cs = 0;
	ifstream fin;
	string filename;
	Log("Enter the name of the file to load: ");
	cin >> filename;
	Log_cin(filename);
	fin.open((filename + ".txt"), ios::in);
	if (!fin.is_open()) 
	{
		Log("Failed to open the file with name " + filename + " for loading.");
	}
	else {
		pipe.clear();
		ks.clear();
		fin >> count_pipe >> count_cs;
		if (count_pipe == 0 && count_cs == 0) 
		{
			Log("You don't have objects to download");
		}
		else 
		{
			for (int i = 0; i < count_pipe; i++) 
			{
				truba tr1;
				pipe.insert({ tr1.get_idp(), Download_truba(fin, tr1) });
				Log("Your pipe with ID " + to_string(tr1.get_idp()) + " has been successfully download! Press 3 to check your objects. ");
			}
			for (int i = 0; i < count_cs; i++) 
			{
				CS cs1;
				ks.insert({ cs1.get_idc(), Download_CS(fin, cs1) });
				Log("Your compressor station with ID " + to_string(cs1.get_idc()) + " has been successfully download! Press 3 to check your objects. ");
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

	Log("Select objects to use filter:");
	Log("1. Use filter for pipes");
	Log("2. Use filter for compressor stations");
	Log("Enter your choice: ");
	choice = GetCorrectNumber(0, 9);
	Log_cin(to_string(choice));
	switch (choice)
	{
	case 1:
		int pipe_id;
		Log("Write the filter (name or under_repair): ");
		cin >> filter;
		Log_cin(filter);
		if (filter == "name")
		{
			string pipe_name;
			Log("Enter the name of the pipe to find: ");
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
				Log("Pipes found: ");
				for (int pipe_id : matching_pipes)
				{
					cout << pipe[pipe_id] << endl;
				}
			}
			else {
				Log("No pipes with the specified name found.");
			}
		}
		else if (filter == "under_repair")
		{
			bool isUnderRepair;
			Log("Enter the status 'under_repair' (1 for true, 0 for false): ");
			cin >> isUnderRepair;
			Log_cin(to_string(isUnderRepair));
			pipe_id = Find_under_repair_pipe(isUnderRepair);
			if (pipe_id != -1)
			{
				Log("Pipe found with ID: ");
				cout << pipe[pipe_id] << endl;
			}
			else
			{
				Log("No pipe with the specified 'under_repair' status found.");
			}
		}
		else
		{
			Log("Invalid filter entered, press 8 and try again");
		}
		break;

	case 2:
		int cs_id;
		Log("Write the filter (name or procent): ");
		cin >> filter;

		if (filter == "name")
		{
			string cs_name;
			Log("Enter the name of the compressor station to find: ");
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
				Log("Compressor stations found: ");
				for (int cs_id : matching_cs)
				{
					cout << ks[cs_id] << endl;
				}
				Log("");  // Add an empty line for separation.
			}
			else {
				Log("No compressor stations with the specified name found.");
			}
		}
		else if (filter == "procent")
		{
			Log("Enter the percentage to find: ");
			string cs_procent;
			cin >> cs_procent;
			int cs_id = Find_procent_cs(cs_procent);
			if (cs_id != -1)
			{
				Log("Compressor station found with ID: ");
				cout << ks[cs_id] << endl;
			}
			else
			{
				Log("Compressor station with the specified percentage not found.");
			}
		}
		else
		{
			Log("Invalid filter entered, press 9 and try again");
		}
		break;

	default:
		Log("Invalid choice. Please enter 1 or 2.");
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

	Log("Select objects to delete:");
	Log("1. Delete pipes");
	Log("2. Delete compressor stations");
	Log("Enter your choice: ");
	choice = GetCorrectNumber(0, 9);
	Log_cin(to_string(choice));
	switch (choice)
	{
	case 1:
		if (pipe_size == 0)
		{
			Log("You don't have pipes to delete");
		}
		else
		{
			Log("Enter the number of pipes you want to delete: ");
			number_pipes = GetCorrectNumber(0, pipe_size);
			if (number_pipes == pipe_size)
			{
				pipe.clear();
				Log("All of your pipes have been successfully deleted");
			}
			else
			{
				for (int i = 0; i < number_pipes; i++)
				{
					int choose_pipe;
					Log("Enter the ID of the pipe you want to delete: ");
					cin >> choose_pipe;
					auto it = pipe.find(choose_pipe);
					if (it != pipe.end())
					{
						pipe.erase(it);
						Log("Pipe with ID " + to_string(choose_pipe) + " has been deleted.");
					}
					else
					{
						Log("Pipe with ID " + to_string(choose_pipe) + " not found.");
					}
				}
			}
		}
		break;

	case 2:
		if (cs_size == 0)
		{
			Log("You don't have compressor stations to delete");
		}
		else
		{
			Log("Enter the number of compressor stations you want to delete: ");
			number_cs = GetCorrectNumber(0, cs_size);
			if (number_cs == cs_size)
			{
				ks.clear();
				Log("All of your compressor stations have been successfully deleted");
			}
			else
			{
				for (int i = 0; i < number_cs; i++)
				{
					int choose_cs;
					Log("Enter the ID of the compressor station you want to delete: ");
					cin >> choose_cs;

					auto it = ks.find(choose_cs);
					if (it != ks.end())
					{
						ks.erase(it);
						Log("Compressor station with ID " + to_string(choose_cs) + " has been deleted.");
					}
					else
					{
						Log("Compressor station with ID " + to_string(choose_cs) + " not found.");
					}
				}
			}
		}
		break;

	default:
		Log("Invalid choice. Please enter 1 or 2.");
		break;
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
		Log("4. Edit the status 'under repair'");
		Log("5. Edit the compressor station");
		Log("6. Save");
		Log("7. Download");
		Log("8. Choose objects with the filter");
		Log("9. Delete the object");
		Log("0. Exit");
		Log("Selection: ");
		choice = GetCorrectNumber(0, 9);
		Log_cin(to_string(choice));
		switch (choice) 
		{
		case 1:
			Addpipe();
			break;
		case 2:
			Addcs();
			break;
		case 3:
			Viewall();
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
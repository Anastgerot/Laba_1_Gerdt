#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <sstream>
#include <vector>
#include "truba.h"
#include "CS.h"
#include "Utils.h"
#include "addition.h"
#include <unordered_set>
#include <algorithm>
using namespace std;
void addition::Addpipe(unordered_map<int, truba>& pipe)
{
	truba tr1;
	cin >> tr1;
	pipe.insert({ tr1.get_idp(), tr1 });
}
void addition::Addcs(unordered_map<int, CS>& ks)
{
	CS cs1;
	cin >> cs1;
	ks.insert({ cs1.get_idc(), cs1 });
}
void addition::Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks)
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
void addition::Save_objects(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks)
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
		ofstream fout;
		fout.open((filename + ".txt"), ios::trunc);
		if (fout.is_open())
		{
			fout << pipe.size() << " " << ks.size() << endl;
			for (const auto& tr : pipe)
			{
				if (!tr.second.name.empty()) {
					Save_truba(fout, tr.second);
					cout << "Pipe with ID " << to_string(tr.first) << " successfully saved! Please, check your file." << endl;
				}
			}
			for (const auto& cs : ks)
			{
				if (!cs.second.name.empty()) {
					Save_CS(fout, cs.second);
					cout << "CS with ID " << to_string(cs.first) << " successfully saved! Please, check your file." << endl;
				}
			}
			fout.close();
		}
		else
		{
			cout << "Failed to open the file with name " << filename << " to save." << endl;
		}
	}
}
void addition::Load_Download(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks) {
	int count_pipe = 0;
	int count_cs = 0;
	ifstream fin;
	string filename;
	cout << "Enter the name of the file to load: ";
	cin >> filename;
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
				truba::max_id_truba = 0;
				tr1 = Download_truba(fin, tr1);
				pipe.insert({ tr1.get_idp(), tr1});
				if (truba::max_id_truba < tr1.get_idp()) {
					truba::max_id_truba = tr1.get_idp();
				}
				cout << "Your pipe with ID " << to_string(tr1.get_idp()) << " has been successfully download! Press 3 to check your objects." << endl;
			}
			truba::max_id_truba++;
			for (int i = 0; i < count_cs; i++) {
				CS cs1;
				CS::max_id_cs = 0;
				cs1 = Download_CS(fin, cs1);
				ks.insert({ cs1.get_idc(), cs1});
				if (CS::max_id_cs < cs1.get_idc()) {
					CS::max_id_cs = cs1.get_idc();
				}
				cout << "Your compressor station with ID " << to_string(cs1.get_idc()) << " has been successfully download! Press 3 to check your objects." << endl;
			}
			CS::max_id_cs++;
		}
		fin.close();
	}
}
void addition::Filter(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks, vector<vector<Connection>>& graph) {
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
		switch (choice) {
		case 1:
			cout << "Write the filter (name or under_repair): ";
			cin >> filter;
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
				int cs_procent;
				cin >> cs_procent;
				cout << "Enter the comparison type (equal, greater, less): ";
				string comparison_type;
				cin >> comparison_type;
				vector<int> matching_ids = Find_cs(ks, cs_procent, comparison_type, Find_procent<CS>);
				if (!matching_ids.empty()) {
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
						cout << "Enter pipe IDs to edit (separated by space): ";
						string idInput;
						int n;
						set<int> idPipe;
						cin >> ws;
						getline(cin, idInput);
						istringstream iss(idInput);
						while (iss >> n)
						{
							idPipe.insert(n);
						}
						for (int id : idPipe) {
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
						cout << "Enter compressor station IDs to edit (separated by space): ";
						string idInput;
						int n;
						set<int> idCS;
						cin >> ws;
						getline(cin, idInput);
						istringstream iss(idInput);
						while (iss >> n)
						{
							idCS.insert(n);
						}
						for (int id : idCS) {
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
								Remove_Edge_And_Unused_Vertices(id, graph);

							}
						}
						cout << "Pipes removed successfully.";
						matching_pipes.clear();
					}
					else if (deleteChoice == 2) {
						cout << "Enter pipe IDs to remove (separated by space): ";
						string idInput;
						int n;
						set<int> idPipe;
						cin >> ws;
						getline(cin, idInput);
						istringstream iss(idInput);
						while (iss >> n)
						{
							idPipe.insert(n);
						}
						for (int id : idPipe) {
							auto pipe_iter = pipe.find(id);
							if (pipe_iter != pipe.end()) {
								pipe.erase(pipe_iter);
								cout << "Pipe with id " + to_string(id) + " has been successfully deleted" << endl;
								Remove_Edge_And_Unused_Vertices(id, graph);
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
								if (id < graph.size()) {
									Remove_Vertex(id, graph);
								}
							}
						}
						cout << "Compressor stations removed successfully.";
						matching_cs.clear();
					}
					else if (deleteChoice == 2) {
						cout << "Enter compressor station IDs to remove (separated by space): ";
						string idInput;
						int n;
						set<int> idCS;
						cin >> ws;
						getline(cin, idInput);
						istringstream iss(idInput);
						while (iss >> n)
						{
							idCS.insert(n);
						}
						for (int id : idCS) {
							auto cs_iter = ks.find(id);
							if (cs_iter != ks.end()) {
								ks.erase(cs_iter);
								cout << "Compressor station with id " + to_string(id) + " has been successfully deleted" << endl;
								if (id < graph.size()) {
									Remove_Vertex(id, graph);
								}
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
int addition::Add_newpipe_connect(unordered_map<int, truba>& pipe, int diameter) {
	truba tr1;
	cin >> tr1;
	if (!(tr1.diameter == diameter))
	{
		tr1.set_diameter(diameter);
		cout << "!!!Your diameter has been changed to the previously entered one: "  << diameter << endl;
	}
	int new_pipe_id = tr1.get_idp();
	pipe.insert({ new_pipe_id, tr1 });
	return new_pipe_id;
}
void addition::Connect_CS_and_Pipe(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks, vector<vector<Connection>>& graph) {
	int idIn, idOut, diameter;
	cout << "Enter the ID of the input compressor station: ";
	idIn = GetCorrectNumber(0, CS::max_id_cs);
	if (ks.find(idIn) == ks.end()) {
		cout << "Input compressor station not found. Aborting connection." << endl;
		return;
	}

	int maxId = idIn;
	if (maxId >= graph.size()) {
		graph.resize(maxId + 1);
	}

	if (graph[idIn].size() >= 2) {
		cout << "Input compressor station already has the maximum number of connections (2). Aborting connection." << endl;
		return;
	}

	cout << "Enter the ID of the output compressor station: ";
	idOut = GetCorrectNumber(0, CS::max_id_cs);
	if (ks.find(idOut) == ks.end()) {
		cout << "Output compressor station not found. Aborting connection." << endl;
		return;
	}

	maxId = max(idIn, idOut);
	if (maxId >= graph.size()) {
		graph.resize(maxId + 1);
	}

	if (graph[idOut].size() >= 2) {
		cout << "Output compressor station already has the maximum number of connections (2). Aborting connection." << endl;
		return;
	}

	cout << "Enter the diameter of the pipe: ";
	diameter = GetCorrectNumber(500, 1400);
	while (!(diameter == 500 || diameter == 700 || diameter == 1000 || diameter == 1400)) {
		cout << "The diameter can only be 500, 700, 1000, or 1400. Please try again: ";
		diameter = GetCorrectNumber(500, 1400);
	}

	int available_pipe_id = -1;
	for (const auto& pipe_entry : pipe) {
		const truba& tr = pipe_entry.second;
		if (!tr.under_repair && tr.diameter == diameter) {
			bool isPipeConnected = false;
			for (const auto& connection : graph) {
				for (const auto& conn : connection) {
					if (conn.pipe == pipe_entry.first) {
						isPipeConnected = true;
						break;
					}
				}
				if (isPipeConnected) {
					break;
				}
			}

			if (!isPipeConnected) {
				available_pipe_id = pipe_entry.first;
				break;
			}
		}
	}

	if (available_pipe_id == -1) {
		cout << "No available pipe found. Adding a new pipe." << endl;
		available_pipe_id = Add_newpipe_connect(pipe, diameter);
		cout << "Created a new pipe with ID " << available_pipe_id << " and diameter " << diameter << endl;
	}

	if (pipe[available_pipe_id].under_repair) {
		cout << "Error: The selected pipe is under repair. Aborting connection." << endl;
		return;
	}

	Connection newConnection = { idIn, available_pipe_id, idOut };
	graph[idIn].push_back(newConnection);
	graph[idOut].push_back(newConnection);
	cout << "Successfully connected compressor stations " << idIn << " and " << idOut << " with pipe " << available_pipe_id << endl;


	cout << "Graph (Compressor station -> Pipe -> Compressor station):" << endl;
	for (int i = 0; i < graph.size(); ++i) {
		cout << i << " -> ";
		for (const auto& connection : graph[i]) {
			cout << "(" << connection.inputStation << ", " << connection.pipe << ", " << connection.outputStation << ") ";
		}
		cout << endl;
	}
}
void addition::topologicalSortDFS(int vertex, const vector<vector<Connection>>& graph, vector<bool>& visited, vector<bool>& onPath, stack<int>& resultStack) {
	if (vertex >= graph.size() || graph[vertex].empty()) {
		return;
	}

	visited[vertex] = true;
	onPath[vertex] = true; 

	for (const auto& connection : graph[vertex]) {
		int nextVertex = connection.outputStation;
		if (!visited[nextVertex]) {
			topologicalSortDFS(nextVertex, graph, visited, onPath, resultStack);
		}
	}

	resultStack.push(vertex);
	onPath[vertex] = false;
}
vector<int> addition::topologicalSort(const vector<vector<Connection>>& graph) {
	if (graph.empty()) {
		cout << "Error: Graph is empty!" << endl;
		return vector<int>();  
	}

	vector<int> result;
	vector<bool> visited(graph.size(), false);
	vector<bool> onPath(graph.size(), false);

	stack<int> resultStack;

	for (int i = 0; i < graph.size(); ++i) {
		if (!visited[i]) {
			topologicalSortDFS(i, graph, visited, onPath, resultStack);
		}
	}

	while (!resultStack.empty()) {
		result.push_back(resultStack.top());
		resultStack.pop();
	}
	cout << "Topological Order: ";
	for (int vertex : result) {
		cout << vertex << " ";
	}
	return result;
}
void addition::Remove_Vertex(int vertex, vector<vector<Connection>>& graph) {
	if (vertex >= graph.size()) {
		cout << "Error: Vertex " << vertex << " not found." << endl;
		return;
	}

	graph[vertex].clear();

	for (auto& connections : graph) {
		connections.erase(
			remove_if(connections.begin(), connections.end(), [vertex](const Connection& conn) {
				return conn.inputStation == vertex || conn.outputStation == vertex;
				}),
			connections.end()
		);
	}

	cout << "Vertex " << vertex << " and its connections removed successfully." << endl;

	cout << "Update Graph (Compressor station -> Pipe -> Compressor station):" << endl;
	for (int i = 0; i < graph.size(); ++i) {
		cout << i << " -> ";
		for (const auto& connection : graph[i]) {
			cout << "(" << connection.inputStation << ", " << connection.pipe << ", " << connection.outputStation << ") ";
		}
		cout << endl;
	}
}
void addition::Remove_Edge_And_Unused_Vertices(int pipeId, vector<vector<Connection>>& graph) {

	for (auto& connections : graph) {
		connections.erase(
			remove_if(connections.begin(), connections.end(), [pipeId](const Connection& conn) {
				return conn.pipe == pipeId;
				}),
			connections.end()
		);
	}

	cout << "Pipe " << pipeId << " and its connections removed successfully." << endl;

	cout << "Update Graph (Compressor station -> Pipe -> Compressor station):" << endl;
	for (int i = 0; i < graph.size(); ++i) {
		cout << i << " -> ";
		for (const auto& connection : graph[i]) {
			cout << "(" << connection.inputStation << ", " << connection.pipe << ", " << connection.outputStation << ") ";
		}
		cout << endl;
	}
}
void addition::Remove_Connection(vector<vector<Connection>>& graph){
	int idIn, idOut, idPipe;
	cout << "Enter the ID of the input compressor station: ";
	idIn = GetCorrectNumber(0, CS::max_id_cs);
	cout << "Enter the ID of the output compressor station: ";
	idOut = GetCorrectNumber(0, CS::max_id_cs);
	cout << "Enter the ID of the pipe: ";
	idPipe = GetCorrectNumber(0, truba::max_id_truba);

	for (auto& connections : graph) {
		connections.erase(
			remove_if(connections.begin(), connections.end(), [idPipe](const Connection& conn) {
				return conn.pipe == idPipe;
				}), connections.end()
		);
	}

	cout << "Connection with ID of the input compressor station " +  to_string(idIn) + ", ID of the pipe  " + to_string(idIn) + " and  ID of the output compressor station" + to_string(idOut) + " has been successfully deleted" << endl;

	cout << "Update Graph (Compressor station -> Pipe -> Compressor station):" << endl;
	for (int i = 0; i < graph.size(); ++i) {
		cout << i << " -> ";
		for (const auto& connection : graph[i]) {
			cout << "(" << connection.inputStation << ", " << connection.pipe << ", " << connection.outputStation << ") ";
		}
		cout << endl;
	}
}
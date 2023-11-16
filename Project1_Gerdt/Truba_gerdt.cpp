#include <iostream>
#include <unordered_map>
#include <chrono>
#include <format>
#include "truba.h"
#include "CS.h"
#include "Utils.h"
#include "addition.h"
using namespace std;
using namespace chrono;
void Addcs(unordered_map<int, CS>& ks);
void Addpipe(unordered_map<int, truba>& pipe);
vector<int> ParseIds(const string& input);
void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
void Save_objects(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
void Load_Download(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
void Filter(unordered_map<int, truba>& pipe, unordered_map<int, CS>& ks);
int main()
{
	unordered_map<int, truba> pipe;
	unordered_map<int, CS> ks;
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time);
	if (logfile)
		cerr_out.redirect(logfile);
	while (true)
	{
		int choice;
		cout << "Choose the number:" << endl;
		cout << "1. Add the pipe" << endl;
		cout << "2. Add the compressor station" << endl;
		cout << "3. View all objects" << endl;
		cout << "4. Save" << endl;
		cout << "5. Download" << endl;
		cout << "6. Choose and Edit objects with the filter" << endl;
		cout << "0. Exit" << endl;
		cout << "Selection: ";
		choice = GetCorrectNumber(0, 6);
		switch (choice)
		{
		case 1:
			Addpipe(pipe);
			break;
		case 2:
			Addcs(ks);
			break;
		case 3:
			Viewall(pipe, ks);
			break;
		case 4:
			Save_objects(pipe, ks);
			break;
		case 5:
			Load_Download(pipe, ks);
			break;
		case 6:
			Filter(pipe, ks);
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
//�����������: 
//����� ���� ������� ������� ����� ������ ��� ���������� (��������, ���� � ���� 33.333, �� ������������ ������ ����� �� � ��� 66, � ��� 67)
//����� ����� ���� ������������ ��� ������� ����������� � ������ � truba.cpp, � �� � CS.cpp
//�����, � ����������������� ������� ������ �� ������� � ����������� - ������� �� ��� ������� � ��������� � Utils.h, ����� �� ��� ������ �� ������ ��� ������ �������
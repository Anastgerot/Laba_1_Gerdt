#include <string>
#include <unordered_map>
#include "truba.h"
#include "CS.h"
#include "Utils.h"
#include "addition.h"
using namespace std;
void Addpipe(unordered_map<int, truba>& pipe);
void Addcs(unordered_map<int, CS>& ks);
void ClearLogFile();
void Filter(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);
vector<int> ParseIds(const string& input);
void Viewall(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);
void Save_objects(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);
void Load_Download(unordered_map<int, truba>& pipe, unordered_map<int, CS> ks);
int main()
{
	unordered_map<int, truba> pipe;
	unordered_map<int, CS> ks;
	ClearLogFile();
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
//Комментарии: 
//Нужно было сделать процент более легким для нахождения (например, если у меня 33.333, то пользователь сможет найти кс и при 66, и при 67)
//Также нужно было распределить все функции относящиеся к трубам в truba.cpp, а кс в CS.cpp
//Также, я усовершенствовала функции поиска по фильтру и логирование - сделала из них шаблоны и поместила в Utils.h, чтобы он был создан не только для одного шаблона
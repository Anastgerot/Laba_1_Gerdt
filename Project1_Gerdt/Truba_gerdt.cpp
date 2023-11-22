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
int main()
{
	unordered_map<int, truba> pipe;
	unordered_map<int, CS> ks;
	addition add;
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
	ofstream logfile("log_" + time + ".txt");
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
		cout << "7. Connect the pipe and compressor station in the gas transmission network." << endl;
		cout << "0. Exit" << endl;
		cout << "Selection: ";
		choice = GetCorrectNumber(0, 7);
		switch (choice)
		{
		case 1:
			add.Addpipe(pipe);
			break;
		case 2:
			add.Addcs(ks);
			break;
		case 3:
			add.Viewall(pipe, ks);
			break;
		case 4:
			add.Save_objects(pipe, ks);
			break;
		case 5:
			add.Load_Download(pipe, ks);
			break;
		case 6:
			add.Filter(pipe, ks);
			break;
		case 7:
			add.Connect_CS_and_Pipe(pipe, ks);
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
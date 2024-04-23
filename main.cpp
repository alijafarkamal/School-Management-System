#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<fstream>
#include<sstream>
using namespace std;
string str_teacher_heading;
string str_teacher_ids;
string str_teacher_name;
string str_teacher_salary;
string str_teacher_class;
string str_teacher_join;
string str_teacher_leave;
void attendence_mark() {
	ifstream file("teachers.csv");
	string store_teacher;
	file >> store_teacher;
	istringstream is(store_teacher);
	store_teacher.clear();
	string isa;
	while (getline(is, isa, ',')) {
		store_teacher += isa + " ";
	}
	cout << store_teacher;
	int index = 0;
	for (int i = 0; i < 10; i++)
	{
		if (getline(file, store_teacher)) {
			istringstream iss(store_teacher);
			string token;
			while (getline(iss, token, ',')) {
				index++;
				token += " ";
				if (index == 1) str_teacher_ids += token;
				if (index == 2) str_teacher_name += token;
				if (index == 3) str_teacher_salary += token;
				if (index == 4) str_teacher_class += token;
				if (index == 5) str_teacher_join += token;
				if (index == 6) str_teacher_leave += token;
			}
			index = 0;
		}
	}
}
class attendence {
public:
	void attendence_mark() {
		int enter;
		cout << "Do you want to login as a teacher? \n If yes press 1 else press 0\n";
		cin >> enter;
		if (enter == 1) {
			cout << "Enter your id\n";
			cin >> enter;
			if (str_teacher_ids.find(enter))
			{
				system("CLS");
				cout << "You have entered as the teacher of " << enter << " class\n";
				enter = 0; 
			 	cout << "Press 1 if you want to mark attendence\n";
				cout << "Press 2 if you want to see previous attendences\n";
				cout << "Press 3 if you want to see particular student attendence\n";
				cin >> enter;
				if (enter == 1) {

				}
			}
		}
        /*cout << str_teacher_ids << endl;
		cout << str_teacher_name << endl;
		cout << str_teacher_class << endl;
		cout << str_teacher_salary << endl;*/		
	}
};
int main() {
	attendence att;
	att.attendence_mark();
	system("pause");
	return 0;
}

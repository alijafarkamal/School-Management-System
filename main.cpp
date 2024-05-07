//using namespace std;

//int main() {
//	attendence att;
//	att.attendence_mark();
//	system("pause");
//	return 0;
//}

#include<iostream>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<string>
#include<cstring>
#include<cctype>
#include<conio.h>
#include<iomanip>
#include"functions.h"
#include"sqlite/sqlite3.h"
#include"functions.h"
using namespace std;
class other_staff {
protected:
	string other_staff_id;
	string other_staff_name;
	string other_staff_salary;
	string other_staff_profession;
	static int other_staff_number;
public:
	other_staff() {
		this->initializer();
	}
	void initializer() {
		ifstream file(file_other_staff);
		string store_other_staff;
		file >> store_other_staff;
		istringstream is(store_other_staff);
		store_other_staff.clear();
		string isa;
		while (getline(is, isa, ',')) {
			store_other_staff += isa + " ";
		}
		int index = 0;
		for (int i = 0; i < other_staff_number; i++)
		{
			if (getline(file, store_other_staff)) {
				istringstream iss(store_other_staff);
				string token;
				while (getline(iss, token, ',')) {
					index++;
					token += " ";
					if (index == 1) other_staff_id += token;
					if (index == 2) other_staff_name += token;
					if (index == 3) other_staff_salary += token;
					if (index == 4) other_staff_profession += token;
				}
				index = 0;
			}
		}
	}
};
int other_staff::other_staff_number = 6;
class other_staff_management : public other_staff {
public:
	other_staff_management() {
	}
	void add() {
		int choice;
		string mark("");
		string str_add;
		id_setter:
		cout << "Enter his id \n";
		cin >> str_add;
		choice = other_staff_id.find(str_add);
		if (choice != string::npos) {
			cout << "id already exists\n";
			goto id_setter;
		}
		mark += str_add + ',';
		other_staff_id += " " + str_add;
		cout << "Enter your name \n";
		cin >> str_add;
		mark += str_add + ',';
		other_staff_name += " " + str_add;
		cout << "Enter his salary\n";
		cin >> str_add;
		mark += str_add + ',';
		other_staff_salary += " " + str_add;
		cout << "Enter his Profession\n";
		cin >> str_add;
		mark += str_add + '\n';
		other_staff_profession += " " + str_add;
		ofstream file("other_staff.csv", ios::app);
		file << mark;
		file.close();
	}
	void remove() {	
		int choice;
			string str_remove;
			ID_remover:
			cout << "Enter his id\n";
			cin >> str_remove;
			//cout << other_staff_id;
			choice = other_staff_id.find(str_remove);
			if (choice == string::npos) {
				cout << "ID not found\n";
				goto ID_remover;
			}
			int comma_counter = count(other_staff_id.begin(), other_staff_id.begin() + choice, ' ');
			//cout << comma_counter << endl; 
			string data_store; int counter(0);
			ifstream file(file_other_staff);
			string data_store_temp;
			while (getline(file, data_store)) {		
				if (counter != comma_counter+1) {
					data_store_temp += data_store + "\n";// << endl;
				}
				counter++;
				data_store.empty();
			}
			ofstream file_out(file_other_staff);
			//cout << data_store_temp;ffff
			file_out << data_store_temp;
			file_out.close();
			other_staff_number--;
			other_staff_id.erase();
			other_staff_name.erase();
			other_staff_salary.erase();
			other_staff_profession.erase();
			initializer();
			cout << other_staff_id << endl;
			cout << other_staff_name << endl;
			cout << other_staff_salary << endl;
			cout << other_staff_profession << endl;
		}		
	
	void update() {
		int reply;
			string mark;
			string str_add;
		id_updater:
			cout << "Enter his id \n";
			cin >> str_add;
			reply = other_staff_id.find(str_add);
			if (reply == string::npos) {
				cout << "id not found\n";
				goto id_updater;
			}
			cout << "Enter his updated id\n";
			cin >> str_add;
			mark += str_add + ',';
			//other_staff_id += " " + str_add;
			cout << "Enter his updated name \n";
			cin >> str_add;
			mark += str_add + ',';
			//other_staff_name += " " + str_add;
			cout << "Enter his updated salary\n";
			cin >> str_add;
			mark += str_add + ',';
			//other_staff_salary += " " + str_add;
			cout << "Enter his updated Profession\n";
			cin >> str_add;
			mark += str_add + '\n';
			//other_staff_profession += " " + str_add;
			string data_store;
			ifstream file(file_other_staff);
			int comma_counter = count(other_staff_id.begin(), other_staff_id.begin() + reply, ' ');
			int counter(0);
			string data_store_temp;
			while (getline(file, data_store)) {
				if (counter != comma_counter+1) {
					data_store_temp += data_store + "\n";
				}
				else {
					data_store_temp += mark;
				}
				data_store.empty();
				counter++;
			}
			ofstream file_out(file_other_staff);
			file_out << data_store_temp;
			file_out.close();	
	}
	void display() {
		ifstream file(file_other_staff);
		string display_mode;
		while (getline(file, display_mode)) {
		}
		cout << display_mode;
	}
};
int main()
{
	teachers t;
	t.display();



	//char* err;
	//sqlite3* db;
	//sqlite3_stmt* stmt;
	//sqlite3_open("mydb.db", &db);
	//int rc = sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS algolancer(x1 INT, x2 INT, name varchar(100));", NULL, NULL,&err);
	//if (rc != SQLITE_OK)
	//	cout << "Error ! "<<err;
	//else cout << "Succeeded \n";
	//	for (int i = 0; i < 10; i++) {
	//		string query = "insert into algolancer VALUES ("+to_string(i)+", "+to_string(i+5) +", 'nadjib');";
	//		rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
	//		cout << query << endl;
	//			if (rc != SQLITE_OK)
	//			{
	//				cout << "error \n";
	//			}
	//	}
	//	sqlite3_prepare_v2(db, "select x1, x2, name from algolancer", -1, &stmt, 0);
	//	int a1, a2; const unsigned char* name;
	//	sqlite3_step(stmt);
	//	a1 = sqlite3_column_int(stmt,0);
	//	a2 = sqlite3_column_int(stmt,1);
	//	name = sqlite3_column_text(stmt, 2);
	//	cout << "a1 : " << a1 << endl;
	//	cout << "a2 : " << a2 << endl;
	//	cout << "name : " << name << endl;
	////int rc = sqlite3_open("test.db", &db);

	////if (rc) {
	////	std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
	////	return 1;
	////}
	////else {
	////	std::cout << "Opened database successfully" << std::endl;
	////}

	////sqlite3_close(db);
	//int count = NoofStudents();
	//Student* students = new Student[count];
	//ifstream input("student.txt");
	//string name, password, fathername;
	//int id, fee, invalidTry = 3, choice = 0, PendingBalance, Class, InnerChoice;

	//if (input.is_open())
	//{
	//	for (int i = 0; i < count; i++)
	//	{
	//		input >> id >> fee >> PendingBalance >> Class;
	//		getline(input, name, '#');
	//		getline(input, fathername, '\n');

	//		students[i] = Student(name, fathername, id, fee, PendingBalance, Class);

	//	}
	//	input.close();
	//}
	//else
	//{
	//	cout << "Error Opening the File Student.txt\n";
	//}
	//teachers_management teacher;
	//teacher.update();
	//other_staff_management other;
	//other.update();
	//attendence attend(students, count);
	//attend.attendence_mark();

	//invalid:
	//	if (invalidTry > 0)
	//	{
	//		cout << "Enter the Password To Continue\n";
	//		getline(cin, password);
	//		if (password != "hello")
	//		{
	//			system("cls");
	//			cout << "Invalid Password\n";
	//			invalidTry--;
	//			cout << "Remaining Tries: " << invalidTry << endl;
	//			goto invalid;
	//		}
	//		else
	//		{
	//			system("cls");
	//			cout << "You Successfully Entered as ADMIN\n";
	//		}
	//		while (choice != 7)
	//		{
	//			system("cls");
	//			cout << "WELCOME TO MAIN MENU\n";
	//			cout << "1. To Display Student Records\n";
	//			cout << "2. To Display Details Of a Particular Student\n";
	//			cout << "3. To Give and OverView\n";
	//			cout << "4. To Enter Financial Mode\n";
	//			cout << "5. To Enter A New Student\n";
	//			cout << "6. To Remove a Student\n";
	//			cout << "7. To Exit\n";
	//			cin >> choice;
	//			if (choice == 1)
	//			{
	//				Display(students, count);
	//			}
	//			else if (choice == 2)
	//			{
	//				system("cls");
	//				cout << "1. To Search By Father Name\n";
	//				cout << "2. To Search By ID Number\n";
	//				cin >> InnerChoice;
	//				if (InnerChoice == 1)
	//				{
	//					SearchFamily(students, count);
	//				}
	//				else if (InnerChoice == 2)
	//				{
	//					Search(students, count);
	//				}
	//			}
	//			else if (choice == 3)
	//			{
	//				overview(students, count);
	//			}
	//			else if (choice == 4)
	//			{
	//				financial(students, count);
	//				UpdatingData(students, count);
	//			}
	//			else if (choice == 5)
	//			{
	//				students = addStudent(students, count);
	//				UpdatingData(students, count);
	//			}
	//			else if (choice == 6)
	//			{
	//				students = removeStudent(students, count);
	//				UpdatingData(students, count);
	//			}
	//		}
	//	}
	//	else
	//	{
	//		cout << "Crashed !\n";
	//		return 0;
	//	}
	//	delete[] students;
	system("pause");
	return 0;
}

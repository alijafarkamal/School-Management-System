#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include<cctype>
#include<conio.h>
#include<iomanip>

using namespace std;
const string attend = "attendence.csv";
const string file_other_staff = "other_staff.csv";
const string file_teachers = "teachers.csv";
class Student
{
protected:
	string name;
	string FatherName;
	int id;
	int fee;
	int PendingBalance;
	int Class;
public:
	Student()
	{
		name = "";
		FatherName = "";
		id = 0;
		fee = 0;
		PendingBalance = 0;
		Class = 0;

	}
	Student(string name, string FatherName, int id, int fee, int PendingBalance, int Class)
	{
		this->name = name;
		this->id = id;
		this->fee = fee;
		this->PendingBalance = PendingBalance;
		this->Class = Class;
		this->FatherName = FatherName;


	}
	Student(const Student& obj)
	{
		name = obj.name;
		id = obj.id;
		fee = obj.fee;
		PendingBalance = obj.PendingBalance;
		Class = obj.Class;
		FatherName = obj.FatherName;
	}
	string getname()
	{
		return name;
	}
	int getid()
	{
		return id;
	}
	int getfee()
	{
		return fee;
	}
	int getPendingBalance()
	{
		return PendingBalance;
	}
	int getClass()
	{
		return Class;
	}
	string getfathername()
	{
		return FatherName;
	}
	void setpendingBalance(int temp)
	{
		PendingBalance = temp;
	}
};
class teachers {
protected:
	string str_teacher_heading;
	string str_teacher_ids;
	string str_teacher_name;
	string str_teacher_salary;
	string str_teacher_class;
	string str_teacher_join;
	string str_teacher_leave;
	static int no_of_teachers;
public:
	teachers() {
		this->teacheruploader();
	}
	void teacheruploader()
	{
		ifstream file(file_teachers);
		string store_teacher;
		file >> store_teacher;
		istringstream is(store_teacher);
		store_teacher.clear();
		string isa;
		while (getline(is, isa, ',')) {
			store_teacher += isa + " ";
		}
		//cout << store_teacher;
		int index = 0;
		for (int i = 0; i < no_of_teachers; i++)
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
};
int teachers::no_of_teachers = 11;
class teachers_management : public teachers{
public:
	teachers_management() {
	}
	void add() {
		int choice;
		string mark("");
		string str_add;
	id_teacher_setter:
		cout << "Enter his id \n";
		cin >> str_add;
		choice = str_teacher_ids.find(str_add);
		if (choice != string::npos) {
			cout << "id already exists\n";
			goto id_teacher_setter;
		}
		mark += str_add + ',';
		str_teacher_ids += " " + str_add;
		cout << "Enter name \n";
		cin >> str_add;
		mark += str_add + ',';
		str_teacher_name += " " + str_add;
		cout << "Enter his salary\n";
		cin >> str_add;
		mark += str_add + ',';
		str_teacher_salary += " " + str_add;
		cout << "Enter his class \n";
		cin >> str_add;
		mark += str_add + ',';
		str_teacher_class += " " + str_add;
		cout << "Enter his joining year \n";
		cin >> str_add;
		mark += str_add + ',';
		str_teacher_join += " " + str_add;
		cout << "Enter his leaving year \n";
		cin >> str_add;
		mark += str_add + '\n';
		no_of_teachers++;
		str_teacher_leave += " " + str_add;
		ofstream file(file_teachers, ios::app);
		file << mark;
		file.close();
	}
	void remove() {
		int choice;
		string str_remove;
	ID_teachers_remover:
		cout << "Enter his id\n";
		cin >> str_remove;
		//cout << other_staff_id;
		choice = str_teacher_ids.find(str_remove);
		if (choice == string::npos) {
			cout << "ID not found\n";
			goto ID_teachers_remover;
		}
		int comma_counter = count(str_teacher_ids.begin(), str_teacher_ids.begin() + choice, ' ');
		//cout << comma_counter << endl; 
		string data_store; int counter(0);
		ifstream file(file_teachers);
		string data_store_temp;
		while (getline(file, data_store)) {
			if (counter != comma_counter + 1) {
				data_store_temp += data_store + "\n";// << endl;
			}
			counter++;
			data_store.empty();
		}
		ofstream file_out(file_teachers);
		//cout << data_store_temp;ffff
		file_out << data_store_temp;
		file_out.close();
		no_of_teachers--;
		str_teacher_ids.erase();
		str_teacher_name.erase();
		str_teacher_class .erase();
		str_teacher_salary.erase();
		str_teacher_join.erase();
		str_teacher_leave.erase();
		teacheruploader();
		//cout << str_teacher_ids << endl;
		//cout << str_teacher_name << endl;
		//cout << str_teacher_salary << endl;
		//cout << str_teacher_class << endl;
		//cout << str_teacher_join << endl;
		//cout << str_teacher_leave << endl;
	}

	void update() {
		int reply;
		string mark;
		string str_add;
	id_updater:
		cout << "Enter his id \n";
		cin >> str_add;
		reply = str_teacher_ids.find(str_add);
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
		cout << "Enter his updated class\n";
		cin >> str_add;
		mark += str_add + ',';
		cout << "Enter his joining year\n";
		cin >> str_add;
		mark += str_add + ',';
		cout << "Enter his leaving year\n";
		cin >> str_add;
		mark += str_add + '\n';
		//other_staff_profession += " " + str_add;
		string data_store;
		ifstream file(file_teachers);
		int comma_counter = count(str_teacher_ids.begin(), str_teacher_ids.begin() + reply, ' ');
		int counter(0);
		string data_store_temp;
		while (getline(file, data_store)) {
			if (counter != comma_counter + 1) {
				data_store_temp += data_store + "\n";
			}
			else {
				data_store_temp += mark;
			}
			data_store.empty();
			counter++;
		}
		ofstream file_out(file_teachers);
		file_out << data_store_temp;
		file_out.close();
	}
};
class Exam {
protected:
	string subjects[10];
	Student* student;
	int count;
public:
	Exam() {

	}
	Exam(Student* student, int count) {
		this->student = student;
		this->count = count;

		ifstream file("subjects.txt");
		if (!file.is_open()) {
			cout << "Error opening file: subject.txt" << endl;
			return;
		}

		string subject;
		int index = 0;
		while (getline(file, subject) && index < 10) {
			subjects[index++] = subject;
		}
		file.close();
	}

	void conductExam() {

		int Class;
		cout << "Enter the class for which you want to conduct the exam: ";
		cin >> Class;
		bool True = false;
		for (int i = 0; i < count && !True; i++) {
			//cin.ignore();
			if (Class == student[i].getClass()) {
				True = true;
				cout << "Available subjects for the exam:\n";
				for (int j = 0; j < 5; ++j) {
					cout << j + 1 << " " << subjects[j] << endl;
				}

			}
		}
		if (!True) return;
		cout << "Enter the subject for the exam: ";

		string chosenSubject;
		cin >> chosenSubject;
		for (int i = 0; i < 5; i++) {
			if (subjects[i] == (chosenSubject)) {
				cout << "exam is done \n";
				return;
			}
			else {
				cout << "not found or taught";
				return;
			}
		}
	}
};
class attendence : public teachers, public Exam {
	string student_attendence;
	Student* student;
	int count;
	ofstream file;
public:
	attendence(Student* student, int count) {
		this->student = student;
		this->count = count;
	}
	void attendence_mark() {
		ofstream file("attendence.csv");
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
				int option(0);
				string mark;
				while (option != -1) {
					cout << "Press 1 if you want to mark attendence\n";
					cout << "Press 2 if you want to see previous attendences\n";
					cout << "Press 3 if you want to see particular student attendence\n";
					cout << "Press 4 to conduct exam\n";
					cout << "press 5 to assign  grades\n";
					cout << "Press -1 to exit\n";
					cin >> option;
					if (option == 1) {
						file << "class,id,name,attendence\n";
		for (int i = 0; i < count; i++)
			if (enter == student[i].getClass()) {
				cout << "Press p to mark presence or a to mark absence of student\n";
				cout << "ID of the student " << student[i].getid() << endl;
				cout << "Name of the student " << student[i].getname() << endl;
				cin >> mark;
				mark = to_string(student[i].getClass()) + ',' + to_string(student[i].getid()) +
					',' + student[i].getname() + ',' + mark + "\n";
				file << mark;
				student_attendence += mark;
				mark.empty();
				cout << student_attendence << endl;
			}

	}
					else if (option == 2) {
		cout << "class id name attendence\n";
		for (option = 0; option < student_attendence.length(); option++)
			if (student_attendence[option] == '\n') cout << endl;
			else if (student_attendence[option] == ',') cout << " ";
			else cout << student_attendence[option];
		cout << endl;
	}
	else if (option == 3) {
		cout << "Enter id of particular student\n";
		cin >> mark;
		size_t record = student_attendence.find(mark);
		size_t end_record = student_attendence.find('\n', record);
		mark.empty();
		mark = student_attendence.substr(record, end_record - record);
		cout << mark << endl;
	}
	else if (option == 4) {
		Exam exam(student, count);
		exam.conductExam();
	}
				}
			}
		}
		file.close();
	}

};
string toLower(const string& str) {
	string result;
	for (char ch : str) {
		result += tolower(ch);
	}
	return result;
}

int* resizing(int* array, int& size)
{
	size++;
	int* temp = new int[size];
	for (int i = 0; i < size - 1; i++)
	{
		temp[i] = array[i];
	}
	delete[] array;
	return temp;
}

int NoofStudents()
{
	int count = 0;
	string waste;
	ifstream input("student.txt");
	if (input.is_open())
	{
		while (getline(input, waste, '\n'))
		{
			count++;

		}
		//read no of lines in a txt file
	}
	else
	{
		cout << "File Not Opened \n";
	}
	input.close();
	return count;
}

//Finding how many unique classes are there in a school
//  and how many students are in each class
void UniqueClasses(Student* students, int count, int*& MaxClass, int*& Classes, int& size)
{
	size = 0;
	MaxClass = new int[count];
	Classes = new int[size];
	for (int i = 0; i < count; i++) {
		MaxClass[i] = students[i].getClass();
		bool found = false;
		for (int j = 0; j < size; j++) {
			if (Classes[j] == MaxClass[i]) {
				found = true;
				break;
			}
		}
		if (!found) {
			Classes = resizing(Classes, size);
			Classes[size - 1] = MaxClass[i];
		}
	}
}

void Sort(int*& arr, int n)
{
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void Display(Student* students, int count)
{
	system("cls");
	int size, tempchoice, innerchoice;
	int* MaxClass, * Classes;
	UniqueClasses(students, count, MaxClass, Classes, size);
	Sort(Classes, size);
	cout << "1. To Display Data Of All Students\n";
	cout << "2. To Display Data of A Particular Class\n";
	cin >> tempchoice;
	system("cls");
	if (tempchoice == 1)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < count; ++j)
			{
				if (Classes[i] == students[j].getClass())
				{

					cout << "ID: " << students[j].getid() << endl;
					cout << "Class : " << students[j].getClass() << endl;
					cout << "Name: " << students[j].getname() << endl;
					cout << "Father Name: " << students[j].getfathername() << endl;
					cout << "Fee: " << students[j].getfee() << endl;
					cout << "Pending Balance : " << students[j].getPendingBalance() << endl;
					cout << endl;
				}
			}
		}
	}
	else if (tempchoice == 2)
	{
		cout << "Enter The Class you want to Search: ";
		cin >> innerchoice;
		for (int i = 0; i < count; i++)
		{
			if (innerchoice == students[i].getClass())
			{
				cout << "ID: " << students[i].getid() << endl;
				cout << "Class : " << students[i].getClass() << endl;
				cout << "Name: " << students[i].getname() << endl;
				cout << "Father Name: " << students[i].getfathername() << endl;
				cout << "Fee: " << students[i].getfee() << endl;
				cout << "Pending Balance : " << students[i].getPendingBalance() << endl;
				cout << endl;
			}
		}
	}
	cout << "Press Any Key to Continue\n";
	_getch();
}

void Search(Student* students, int count)
{
	system("cls");
	int check;
	cout << "Enter the ID of the Student You Want to Search: ";
	int id;
	bool found = true;
	cin >> id;
	for (int i = 0; i < count; i++)
	{
		if (id == students[i].getid())
		{
			found = false;
			system("cls");
			cout << "ID: " << students[i].getid() << endl;
			cout << "Name: " << students[i].getname() << endl;
			cout << "Class : " << students[i].getClass() << endl;
			cout << "Monthly Fee: " << students[i].getfee() << endl;
			cout << "Pending Balance: " << students[i].getPendingBalance() << endl;

		}
	}
	if (found)
	{
		cout << "Student With Id " << id << " Not Found" << endl;
	}
	cout << "Press Any Key to Continue\n";
	_getch();
}

void SearchFamily(Student* students, int count)
{
	system("cls");
	bool found = true;
	cout << "Enter the Father Name\n" << endl;
	string tempFatherName;
	cin.ignore();
	getline(cin, tempFatherName, '\n');
	for (int i = 0; i < count; i++)
	{
		if (toLower(tempFatherName) == toLower(students[i].getfathername()))
		{
			found = false;
			cout << endl << endl;
			cout << "ID: " << students[i].getid() << endl;
			cout << "Name: " << students[i].getname() << endl;
			cout << "Class : " << students[i].getClass() << endl;
			cout << "Monthly Fee: " << students[i].getfee() << endl;
			cout << "Pending Balance: " << students[i].getPendingBalance() << endl;
		}
	}
	if (found)
	{
		cout << "\nStudent With Father Name " << tempFatherName << " Not Found\n";
	}
	cout << "\nPress Any Key to Continue\n";
	_getch();
}

void overview(Student* students, int count)
{
	int NetIncome = 0, PendingBalance = 0;
	system("cls");

	int size;
	int* MaxClass, * Classes;
	UniqueClasses(students, count, MaxClass, Classes, size);
	int temp;
	cout << "Total Strength :  " << count << endl << endl;
	for (int i = 0; i < size; i++)
	{
		temp = 0;
		for (int j = 0; j < count; j++)
		{
			if (Classes[i] == MaxClass[j])
			{
				temp++;
			}
		}
		cout << "Strength of Class " << setw(2) << Classes[i] << " : " << temp << endl;
	}
	delete[] MaxClass;
	for (int i = 0; i < count; i++)
	{
		PendingBalance += students[i].getPendingBalance();
		NetIncome += students[i].getfee();
	}
	cout << "\n\n";
	cout << "Pending Balance : " << setw(2) << PendingBalance << endl;
	cout << "The Net Income : " << setw(2) << NetIncome << endl << endl;
	delete[] Classes;
	cout << "Press Any Key to Continue\n";
	_getch();
}

void financial(Student* students, int count)
{
	system("cls");
	int check, tempchoice;
	cout << "1. To Charge Monthly Fee from all Student Accounts\n";
	cout << "2. To Deduct Monthly Fee from all Student Accounts\nOnly Press 2. if you have Accidently Charged Monthly Fee and Now You Want to UNDO\n";
	cin >> tempchoice;
	if (tempchoice == 1)
	{
		int temp = 0;
		for (int i = 0; i < count; i++)
		{
			temp = students[i].getPendingBalance() + students[i].getfee();
			students[i].setpendingBalance(temp);

		}
		system("cls");
		cout << "Monthly Fee Charged from all Accounts\n";
	}
	else if (tempchoice == 2)
	{
		system("cls");
		cout << "Enter Password for Confirmation\n";
		string temppassword;
		cin.ignore();
		getline(cin, temppassword, '\n');
		if (temppassword == "admin")
		{
			int temp = 0;
			for (int i = 0; i < count; i++)
			{
				temp = students[i].getPendingBalance() - students[i].getfee();
				students[i].setpendingBalance(temp);
			}
			system("cls");
			cout << "Monthly Fee Deducted From all Accounts\n";
		}
		else
		{
			cout << "Wrong Password\n";
		}
	}
	cout << "\nPress Any Key To Continue\n";
	_getch();

}

bool uniqueIdNumber(Student* students, int count, int id)
{
	for (int i = 0; i < count; i++)
	{
		if (id == students[i].getid())
		{
			return false;
		}
	}
	return true;
}

Student* addStudent(Student* students, int& count)
{
	system("cls");
	string name, fatherName;
	int id, fee, pendingBalance, Class;
UniqueId:
	cout << "Enter THE ID Number\n";
	cin >> id;
	if (uniqueIdNumber(students, count, id))
	{
		cout << "Enter the Name\n";
		cin.ignore();
		getline(cin, name, '\n');

		cout << "Enter Father Name\n";

		getline(cin, fatherName, '\n');

		cout << "Enter The Class\n";
		cin >> Class;

		cout << "Enter The Monthly Fee\n";
		cin >> fee;

		cout << "Enter Any Remaining Dues . ";
		cout << "If NOT then Enter 0\n";
		cin >> pendingBalance;


		Student* temp = new Student[count + 1];


		for (int i = 0; i < count; ++i)
		{
			temp[i] = students[i];
		}

		temp[count] = Student(name, fatherName, id, fee, pendingBalance, Class);


		++count;


		delete[] students;



		cout << "Student Added\n";
		return temp;

	}
	else
	{
		system("cls");
		cout << "Invalid Id Number\n";
		cout << "Enter a Unique Id Number\n";
		goto UniqueId;
	}
}

Student* removeStudent(Student* students, int& count)
{
	system("cls");
again:
	cout << "Enter the Id Number of the Student You Want to Remove\n";
	int id, check;
	cin >> id;
	bool found = true;
	for (int i = 0; i < count; i++)
	{
		if (id == students[i].getid())
		{
			system("cls");
			found = false;
			cout << "Student With Found\n";
			cout << "ID: " << students[i].getid() << endl;
			cout << "Class : " << students[i].getClass() << endl;
			cout << "Name: " << students[i].getname() << endl;
			cout << "Father Name: " << students[i].getfathername() << endl;
			cout << "Fee: " << students[i].getfee() << endl;
			cout << "Pending Balance : " << students[i].getPendingBalance() << endl;
			cout << endl << endl;
		removal:
			cout << "1. To Confirm The Removal Of Student\n";
			cout << "2. To change Id Number\n";
			cin >> check;
			if (check == 1)
			{
				Student* temp = new Student[count - 1];
				for (int j = 0, k = 0; k < count - 1; j++)
				{
					if (j != i)
					{
						temp[k] = students[j];
						k++;
					}

				}
				count--;
				delete[] students;
				cout << "Studet With Id " << id << " Removed\n";
				return temp;
			}
			else if (check == 2)
			{
				goto again;
			}
			else
			{
				goto removal;
			}

		}
	}
	if (found)
	{
		cout << "Student with Id " << id << " Not Found\n";
		goto again;
	}
}

void UpdatingData(Student* students, int count)
{
	ofstream output("student.txt");

	for (int i = 0; i < count; i++)
	{
		output << students[i].getid() << " "
			<< students[i].getfee() << " " << students[i].getPendingBalance() << " " << students[i].getClass() << students[i].getname() << "#" << students[i].getfathername() << endl;
	}
	output.close();
}

void EditInfo();

void DefaulterList();
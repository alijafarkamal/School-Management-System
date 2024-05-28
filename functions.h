
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include<iomanip>
#include <windows.h>
#include<conio.h>
#include <vector>
#include"sqlite/sqlite3.h"
using namespace std;
const string attend = "attendence.csv";
const string file_other_staff = "non_teaching_staff.csv";
const string file_teachers = "teachers.csv";

//This is the Function to set the cursor position in the console
void setCursorPosition(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//This is the Function to set text color on console
void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
//This is An abstract class which is inherited in many following classes
class Student_management_system {
public:
	virtual void student_info_set() = 0;
	virtual int student_info_get() = 0;
	virtual void teacher_info_set() = 0;
	virtual int teacher_info_get() = 0;
};
class Student : public Student_management_system
{
private:
	string name;
	string FatherName;
	int id; 
	int fee;
	int PendingBalance;
	int Class;
	int monthlyFeePaid = 0;
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
	Student(string name, string FatherName, int id, int fee, int PendingBalance, int Class, int monthlyFeePaid)
	{
		this->name = name;
		this->id = id;
		this->fee = fee;
		this->PendingBalance = PendingBalance;
		this->Class = Class;
		this->FatherName = FatherName;
		this->monthlyFeePaid = monthlyFeePaid;

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
	void setid(int temp)
	{
		id = temp;
	}
	void setname(string temp)
	{
		name = temp;
	}
	void setfathername(string temp)
	{
		FatherName = temp;
	}
	void setfee(int temp)
	{
		fee = temp;
	}
	void setclass(int temp)
	{
		Class = temp;
	}
	int getMonthlyFee()
	{
		return monthlyFeePaid;
	}
	void setMonthlyFee(int monthlyFeePaid)
	{
		this->monthlyFeePaid = monthlyFeePaid;
	}
	friend ostream& operator <<(ostream& output, Student& obj)
	{
		cout << "ID: " << obj.getid() << endl;
		cout << "Class : " << obj.getClass() << endl;
		cout << "Name: " << obj.getname() << endl;
		cout << "Father Name: " << obj.getfathername() << endl;
		cout << "Fee: " << obj.getfee() << endl;
		cout << "Pending Balance : " << obj.getPendingBalance() << endl;
		cout << endl;
		return output;
	}
	~Student()
	{
		//cout << "Destructor of student class called \n";
	}
	void student_info_set() override {
		cout << "This is setter function of student info\n";
	}
	int student_info_get() override {
	 cout << "This is getter function of student info\n";
	 return 1;
	}
	void teacher_info_set()override {
	 cout << "This is setter function of teacher info\n";
	}
	int teacher_info_get() override {
	 cout << "This is getter function of teacher info\n";
	 return 1;
	}
	
};
/// <summary>
///			This class teachers as evident from its name has methods to 
///			take data of teachers from an excel sheet 
///			and then upload it in a database using SQL queries.
///			Then display function takes data from the database formed 
///			and populate all the strings which contain the
///			relevant details of teachers like name, ids etc.
/// </summary>
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
		this->teacherUploader();
	}
	void teacherUploader() {
		sqlite3* db;
		char* err;

		int rc = sqlite3_open("teachers.db", &db);
		if (rc != SQLITE_OK) {
			cout << "Error opening database: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}

		rc = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS teachers(id INT, name TEXT, salary INT, class INT, join_year INT, leave_year INT);", NULL, NULL, &err);
		if (rc != SQLITE_OK) {
			cout << "Error creating table: " << err << endl;
			sqlite3_free(err);
			sqlite3_close(db);
			return;
		}

		ifstream file("teachers.txt");
		if (!file.is_open()) {
			cout << "Error opening file" << endl;
			sqlite3_close(db);
			return;
		}

		string line;
		getline(file, line); // Skip header line
		while (getline(file, line)) {
			istringstream iss(line);
			string id_str, name, salary_str, class_str, join_year_str, leave_year_str;
			if (!(getline(iss, id_str, ',') &&
				getline(iss, name, ',') &&
				getline(iss, salary_str, ',') &&
				getline(iss, class_str, ',') &&
				getline(iss, join_year_str, ',') &&
				getline(iss, leave_year_str))) {
				cout << "Error parsing line: " << line << endl;
				continue;
			}

			int id, salary, class_, join_year, leave_year;
			istringstream(id_str) >> id;
			istringstream(salary_str) >> salary;
			istringstream(class_str) >> class_;
			istringstream(join_year_str) >> join_year;
			istringstream(leave_year_str) >> leave_year;
			//cout << str_teacher_class << endl;
			//cout << str_teacher_ids << endl;
			//cout << str_teacher_join << endl;
			//cout << str_teacher_leave << endl;
			//cout << str_teacher_name << endl;
			////cout << id << endl;
			ostringstream query;
			query << "INSERT INTO teachers VALUES (" << id << ", '" << name << "', " << salary << ", " << class_ << ", " << join_year << ", " << leave_year << ");";
			rc = sqlite3_exec(db, query.str().c_str(), NULL, NULL, &err);
			if (rc != SQLITE_OK) {
				cout << "Error inserting data: " << err << endl;
				sqlite3_free(err);
			}

		}
		sqlite3_close(db);
	}

	virtual void display() {
		sqlite3* db;
		char* err;
		int rc = sqlite3_open("teachers.db", &db);
		if (rc != SQLITE_OK) {
			cout << "Error opening database: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}
		ostringstream query;
		query << "SELECT * FROM teachers;";
		sqlite3_stmt* stmt;
		rc = sqlite3_prepare_v2(db, query.str().c_str(), -1, &stmt, nullptr);
		if (rc != SQLITE_OK) {
			cout << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
			sqlite3_close(db);
			return;
		}
		str_teacher_heading = "id,name,salary,class,Join,Leave\n";
		str_teacher_ids.clear();
		str_teacher_name.clear();
		str_teacher_salary.clear();
		str_teacher_class.clear();
		str_teacher_join.clear();
		str_teacher_leave.clear();
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			str_teacher_ids += to_string(sqlite3_column_int(stmt, 0)) + ",";
			const char* name_cstr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
			if (name_cstr) {
				str_teacher_name += name_cstr;
			}
			str_teacher_name += ",";
			str_teacher_salary += to_string(sqlite3_column_int(stmt, 2)) + ",";
			str_teacher_class += to_string(sqlite3_column_int(stmt, 3)) + ",";
			str_teacher_join += to_string(sqlite3_column_int(stmt, 4)) + ",";
			str_teacher_leave += to_string(sqlite3_column_int(stmt, 5)) + ",";
		}
		// After the loop, remove the trailing comma from str_teacher_name
		if (!str_teacher_name.empty()) {
			str_teacher_name.pop_back(); // Remove the last character (the trailing comma)
		}
		//cout << str_teacher_heading << endl << str_teacher_ids << endl << str_teacher_name << endl << str_teacher_leave << endl << str_teacher_class;
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		//_getch();
	}
	~teachers()
	{
		cout << "Destructor of teacher class called \n";
	}
};
/// <summary>
///			Following is the class for teachers management. It has the 
///         methods for adding teachers,removing teaches, updating data
///         of teaches and displaying the whole data of teachers.
///			Basically this class inherits teachers class and it is a 
///			multilevel inheritance and accesses its memebers like 
///         teachers's name, salary etc. 
/// </summary>
int teachers::no_of_teachers = 11;
class teachers_management : public teachers {
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
		cout << str_teacher_ids;
		cout << "Enter his id\n";
		cin >> str_remove;
		//cout << other_staff_id;
		
		choice = str_teacher_ids.find(str_remove);
		if (choice == string::npos) {
			cout << "ID not found\n";
			goto ID_teachers_remover;
		}
		cout << choice << endl;
		int comma_counter = count(str_teacher_ids.begin(), str_teacher_ids.begin() + choice, ',');
		cout << comma_counter << endl;
		//cout << comma_counter << endl; 
		string data_store; int counter(0);
		ifstream file(file_teachers);
		string data_store_temp;
		while (getline(file, data_store)) {
			if (counter != comma_counter + 1) {
				data_store_temp += data_store + "\n";// << endl;
			}
			else cout <<"My lord "<< data_store << endl;
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
		str_teacher_class.erase();
		str_teacher_salary.erase();
		str_teacher_join.erase();
		str_teacher_leave.erase();
		teacherUploader();
		//cout << str_teacher_ids << endl;
		//cout << str_teacher_name << endl;
		//cout << str_teacher_salary << endl;
		//cout << str_teacher_class << endl;
		//cout << str_teacher_join << endl;
		//cout << str_teacher_leave << endl;
		_getch();
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
		cout << reply << endl;
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
		//cout << reply << endl;
		int comma_counter = count(str_teacher_ids.begin(), str_teacher_ids.begin() + reply, ',');
		//cout << comma_counter << endl;
		int counter(0);
		string data_store_temp;
		while (getline(file, data_store)) {
			if (counter != comma_counter + 1) 
				data_store_temp += data_store + "\n";
			else 
				data_store_temp += mark;
			data_store.empty();
			counter++;
		}
		ofstream file_out(file_teachers);
		file_out << data_store_temp;
		file_out.close();
		_getch();
	}
	void display() override final{
		ifstream file(file_teachers);
		string display_mode;
		cout << string(100, '-') << endl;
		while (getline(file, display_mode)) {
			cout << display_mode << endl;
		}
		_getch();
	}
	~teachers_management()
	{

		cout << "Destructor of teacher management class called \n";
	}
};
/// <summary>
///			This Exam class initializes subjects from a file, conducts exams for a specified class,
///			and allows selection of exam type (midterm/final) and subject. If the chosen subject 
///			is available, it proceeds with the exam; otherwise, it informs that the subject is not found.
///			The class includes constructors to initialize subject data from a file and a destructor.
/// </summary>
class Exam {
protected:
	string subjects[5];
	Student* student;
	int count;
public:

	/// <summary>
	///			IN THIS CLASS THERE IS TWO WORKS 
	///			1.ASSIGN GRADES 2.DISPLAY GRADES
	///			SUBJECTS ARE READING FROM .TXT FILE
	///			STRORED IN STRING
	/// </summary>
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
			//cout << subjects[index - 1] << endl;
		}
		//cout << subject[1];
		file.close();
	}
	/// <summary>
	//			This function opens files to store midterm and final grades, prompts the user to 
	//			input class for grading, displays subjects for grading, and then allows the user 
	//			to input midterm and final exam marks for each subject for all students in the selected
	//		    class.Based on the marks, grades are assigned and stored in strings, which are then 
	//			written into corresponding text files.The function includes checks for valid marks 
	//			and handles cases where the entered class is not found.
	/// </summary>
	void conductExam() {
		string Class;
		cout << string(100, '-') << endl;
		cout << "\t\t\t\tEnter the class for which you want to conduct the exam\n\t\t\t\t ";
		cin >> Class;

		bool classFound = false;
		for (int i = 0; i < count; i++) {
			if (Class == to_string(student[i].getClass())) {
				classFound = true;
				cout << "\t\t\t\tAvailable subjects for the exam:\n";
				for (int j = 0; j < 5; ++j) {
					cout << "\t" << j + 1 << " " << subjects[j] << endl;
				}
				break;
			}
		}

		if (!classFound) {
			cout << "\tClass not found.\n";
			return;
		}

		string examType;
		cout << string(100, '-') << endl;
		cout << "\t\t\t\tEnter the type of exam (midterm/final): ";
		cin >> examType;

		string chosenSubject;
		cout << "\t\t\t\tEnter the subject for the " << examType << " exam\n\t\t\t\t ";

		cin >> chosenSubject;

		for (int i = 0; i < 5; i++) {
			if (subjects[i] == chosenSubject) {
				cout << "\tExam is done\n";
				return;
			}
		}
		cout << "\tSubject not found or taught\n";
		_getch();
	}
	~Exam()
	{

		cout << "Destructor of Exam class called \n";
	}
};
class grades {

protected:
	Student* student;
	string subjects[5];
	int count;
	string midTermGrades[20]; // Array to store mid-term grades
	string finalGrades[20];   // Array to store final exam grades
public:
	grades() {}

	grades(Student* student, int count) {
		this->student = student;
		this->count = count;
		ifstream file("subjects.txt");
		if (!file.is_open()) {
			cout << "Error opening file: subject.txt" << endl;
			return;
		}

		string subject;
		int index = 0;
		while (getline(file, subject) && index < 5) {
			subjects[index++] = subject;
		}
		file.close();
	}

		/// <summary>
		///			This below function which prompts the user to enter either 1 for Midterm grades or 2 for Final grades.
		///			It then asks for a student's class and ID. Based on the choice, it searches for the corresponding grades in either the midtermgrades.txt or finalgrades.txt files.
		///			If found, it displays the grades; otherwise, it informs the user that the student's ID was not found or the teacher has not marked the grade. 
		///			The function includes input validation and utilizes file handling to read the grades from text files.
		/// </summary>
	void assignGrades() {
		system("cls");
		ofstream MgradesFile("midtermgrades.txt", ios::app);
		//MgradesFile << "CLass," << "subject," << "grade," << "id" << "\n";
		ofstream FgradesFile("finalgrades.txt", ios::app);

		//FgradesFile << "CLass," << "subject," << "grade," << "id" << "\n";
		string Class;
		system("cls");

	l:
		cout << "Enter the class for which you want to assign grades : ";
		cin >> Class;
		bool classFound = false;
		for (int i = 0; i < count; i++) {
			if (Class == to_string(student[i].getClass())) {
				classFound = true;
				cout << "Subjects for assigning grades:\n";
				for (int j = 0; j < 5; ++j) {
					cout << j + 1 << " " << subjects[j] << endl;
				}
				cout << "Enter the marks for mid-term exam and final exam for each subject:\n";
				for (int k = 0; k < count; ++k) {
					if (to_string(student[k].getClass()) == Class) {
						cout << "Enter marks for student " << student[k].getname() << ":\n";
						string midTermStudentGrades;
						string finalStudentGrades;
						for (int j = 0; j < 5; ++j) {
							string chosenSubject = subjects[j];
							cout << "Subject: " << chosenSubject << endl;
							cout << "Enter mid-term exam marks:(Integer number only) ";

							int midTermMarks;
						x:
							cin >> midTermMarks;
							if (midTermMarks > 100 || midTermMarks < 0) {
								cout << "enter the valid marks out of 100 (Integer number only)\n";
								goto x;
							}
							cout << "Enter final exam marks:(Integer number only) ";

							int finalExamMarks;
						y:
							cin >> finalExamMarks;
							if (finalExamMarks > 100 || finalExamMarks < 0) {
								cout << "enter the valid marks out of 100\n";
								goto y;
							}
							int totalMidTermMarks = midTermMarks;
							int totalFinalExamMarks = finalExamMarks;
							string midTermGrade;
							string finalGrade;

							if (totalMidTermMarks >= 90) {
								midTermGrade = "A";
							}
							else if (totalMidTermMarks >= 80 && totalMidTermMarks <= 89) {
								midTermGrade = "B";
							}
							else if (totalMidTermMarks >= 70 && totalMidTermMarks <= 79) {
								midTermGrade = "C";
							}
							else if (totalMidTermMarks >= 60 && totalMidTermMarks <= 69) {
								midTermGrade = "D";
							}
							else {
								midTermGrade = "F";
							}

							if (totalFinalExamMarks >= 90) {
								finalGrade = "A";
							}
							else if (totalFinalExamMarks >= 80 && totalFinalExamMarks <= 89) {
								finalGrade = "B";
							}
							else if (totalFinalExamMarks >= 70 && totalFinalExamMarks <= 89) {
								finalGrade = "C";
							}
							else if (totalFinalExamMarks >= 60 && totalFinalExamMarks <= 89) {
								finalGrade = "D";
							}
							else {
								finalGrade = "F";
							}
							midTermStudentGrades.empty();
							finalStudentGrades.empty();
							cout << "Grade for student " << student[k].getname() << " in " << chosenSubject << " mid-term exam: " << midTermGrade << endl;
							cout << "Grade for student " << student[k].getname() << " in " << chosenSubject << " final exam: " << finalGrade << endl;
							midTermStudentGrades += to_string(student[k].getClass()) + "," + chosenSubject + "," + midTermGrade + "," + to_string(student[k].getid()) + "\n";
							finalStudentGrades += to_string(student[k].getClass()) + "," + chosenSubject + "," + finalGrade + "," + to_string(student[k].getid()) + "\n";
						}
						MgradesFile << midTermStudentGrades << endl;
						FgradesFile  << finalStudentGrades << endl;
						midTermGrades[k] = midTermStudentGrades;
						finalGrades[k] = finalStudentGrades;
						system("cls");
					}
				}
				return;
			}
		}
		if (!classFound) {
			cout << "Class not found.\n";
			goto l;
		}

		system("cls");
	}





	void displayGrades() {
		int choice;
	l:
		cout << "Enter the choice (1 for Midterm, 2 for Final): ";
		cin >> choice;

		// Input validation
		if (choice != 1 && choice != 2) {
			cout << "Invalid choice. Please enter 1 for Midterm or 2 for Final." << endl;
			goto l;
		}

		bool idEntered = false;
		string id;
		string Class;
		for (int i = 0; i < count; i++) {
			if (choice == 1) {
				if (!idEntered) {

					cout << "Enter the class of student: ";
					cin >> Class;
					cout << "Enter the ID of the student: ";
					cin >> id;
					cout << "Class,subject,grade,id\n";
					cin.ignore();
					idEntered = true;
				}

				ifstream midtermFile("midtermgrades.txt");
				string midgrade;
				bool found = false;
				while (getline(midtermFile, midgrade)) {

					int pos1 = midgrade.find(",");
					int pos2 = midgrade.find(",", pos1 + 1);
					int pos3 = midgrade.find(",", pos2 + 1);

					string lineClass = midgrade.substr(0, pos1);
					string subject = midgrade.substr(pos1 + 1, pos2 - pos1 - 1);
					string grade = midgrade.substr(pos2 + 1, pos3 - pos2 - 1);
					string lineId = midgrade.substr(pos3 + 1);

					if (lineClass == Class && lineId == id) {
						cout << midgrade << endl;
						found = true;
					}
				}

				if (!found) {
					cout << "Student ID not found in mid grades or teacher has not marked the grade." << endl;
				}
				midtermFile.close();
				if (!found) {
					cout << "Student ID not found in midterm grades." << endl;
				}
				break;
			}
			else if (choice == 2) {
				if (!idEntered) {
					cout << "Enter the class of student: ";
					cin >> Class;
					cout << "Enter the ID of the student: ";
					cin >> id;
					cout << "Class,subject,grade,id\n";
					cin.ignore();
					idEntered = true;
				}

				ifstream finalFile("finalgrades.txt");
				string finalgrade;
				bool found = false;
				while (getline(finalFile, finalgrade)) {

					int pos1 = finalgrade.find(",");
					int pos2 = finalgrade.find(",", pos1 + 1);
					int pos3 = finalgrade.find(",", pos2 + 1);

					string lineClass = finalgrade.substr(0, pos1);
					string subject = finalgrade.substr(pos1 + 1, pos2 - pos1 - 1);
					string grade = finalgrade.substr(pos2 + 1, pos3 - pos2 - 1);
					string lineId = finalgrade.substr(pos3 + 1);

					if (lineClass == Class && lineId == id) {

						cout << finalgrade << endl;
						found = true;
					}
				}
				finalFile.close();
				if (!found) {
					cout << "Student ID not found in final grades or teacher has not marked the grade." << endl;
				}
				break;
			}
			cout << endl;
		}
	}

};

/// <summary>
///			This class deals with the functionalities of teachers of the school and manages methods to mark
///			1: attendence
///			2: take exam
///			3: to see previous attendences
///			4: to see attendence of a particular student
///			5: to assign grades
/// </summary>
class teacher_functionalities : public teachers_management, public Exam {
	string student_attendence;
	Student* student;
	int count;
	ofstream file;
public:
	teacher_functionalities(Student* student, int count) {
		this->student = student;
		this->count = count;
	}
	void functionalities() {
		Exam exam(student, count);
		grades grade(student, count);
		ofstream file(attend);
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
					cout << string(100, '-') << endl;
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
						cout << string(100, '-') << endl;
						cout << "Enter id of particular student\n";
						cin >> mark;
						size_t record = student_attendence.find(mark);
						size_t end_record = student_attendence.find('\n', record);
						mark.empty();
						mark = student_attendence.substr(record, end_record - record);
						cout << mark << endl;
					}
					else if (option == 4) {
						cout << string(100, '-') << endl;
						exam.conductExam();
					}
					else if (option == 5) {
						cout << "Press 1 to assign grades to  whole class or 2 to display grades \n";
						cin >> option;
						cout << string(100, '-') << endl;
						if (option == 1)
							grade.assignGrades();
						else if (option == 2)
							grade.displayGrades();
					}
				}
			}
		}
		file.close();
	}
	~teacher_functionalities()
	{

		cout << "Destructor of teacher_functionalities class called \n";
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
	}
	else
	{
		cout << "File Not Opened \n";
	}
	input.close();
	return count;
}
void studentReadFile(Student*& students, int& count)
{
	count = NoofStudents();
	students = new Student[count];
	ifstream input("student.txt");
	string name, password, fathername;
	int id, fee, invalidTry = 3, choice = 0, PendingBalance, Class, InnerChoice;
	int monthlyFeePaid = 0;
	if (input.is_open())
	{
		for (int i = 0; i < count; i++)
		{
			input >> id >> fee >> PendingBalance >> Class;
			getline(input, name, '#');
			getline(input, fathername, '#');
			input >> monthlyFeePaid;
			students[i] = Student(name, fathername, id, fee, PendingBalance, Class, monthlyFeePaid);
		}
		input.close();
	}
}
//Finding how many unique classes are there in a school and how many students are in each class
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
					cout << students[j] << endl;
				}
			}
		}
	}
	else if (tempchoice == 2)
	{
		cout << string(100, '-') << endl;
		cout << "Enter The Class you want to Search: ";
		cin >> innerchoice;
		for (int i = 0; i < count; i++)
		{
			if (innerchoice == students[i].getClass())
			{
				cout << students[i] << endl;
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
			cout << string(100, '-') << endl;
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
			cout << string(100, '-') << endl;
			cout << "ID: " << students[i].getid() << endl;
			cout << "Name: " << students[i].getname() << endl;
			cout << "Father Name:" << students[i].getfathername() << endl;
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
	cout << string(100, '-') << endl;
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
			students[i].setMonthlyFee(0);
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

		temp[count] = Student(name, fatherName, id, fee, pendingBalance, Class, 0);


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

void UpdatingData(Student* students, int count)
{
	ofstream output("student.txt");

	for (int i = 0; i < count; i++)
	{
		output << students[i].getid() << " " << students[i].getfee() << " " << students[i].getPendingBalance() << " " << students[i].getClass() << students[i].getname() << "#" << students[i].getfathername() << '#' << students[i].getMonthlyFee() << endl;
	}
	output.close();
}



void Search(Student* students, int count, int& index)
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
			index = i;
			found = false;
			system("cls");
			cout << students[i] << endl;
			//cout << "ID: " << students[i].getid() << endl;
			//cout << "Name: " << students[i].getname() << endl;
			//cout << "Class : " << students[i].getClass() << endl;
			//cout << "Monthly Fee: " << students[i].getfee() << endl;
			//cout << "Pending Balance: " << students[i].getPendingBalance() << endl;

		}
	}
	if (found)
	{
		cout << "Student With Id " << id << " Not Found" << endl;
	}
	cout << "Press Any Key to Continue\n";
	_getch();
}
void Search(Student* students, int count, int& index, int id)
{
	for (int i = 0; i < count; i++)
	{
		if (id == students[i].getid())
		{
			index = i;
		}
	}
}

void SearchFamily(Student* students, int count, int& index)
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
			index = i;
			found = false;
			cout << students[i] << endl;
			//cout << endl << endl;
			//cout << "ID: " << students[i].getid() << endl;
			//cout << "Name: " << students[i].getname() << endl;
			//cout << "Class : " << students[i].getClass() << endl;
			//cout << "Monthly Fee: " << students[i].getfee() << endl;
			//cout << "Pending Balance: " << students[i].getPendingBalance() << endl;
		}
	}
	if (found)
	{
		cout << "\nStudent With Father Name " << tempFatherName << " Not Found\n";
	}
	cout << "\nPress Any Key to Continue\n";
	_getch();
}


void EditInfo(Student* students, int count)
{
	int temp, index = -1, update;
	string Update;
	system("cls");
	cout << "1. To Search by ID number\n";
	cout << "2. To Search by Father Name\n";
	cin >> temp;
	if (temp == 1)
	{
		Search(students, count, index);
	}
	else if (temp == 2)
	{
		SearchFamily(students, count, index);
	}
	if (index != -1)
	{
		cout << "\n\n";
		cout << "1. To update Id Number\n";
		cout << "2. To Update Name\n";
		cout << "3. To Update Father Name\n4. To Update Class\n5. To Update Fee\n6. To Update Pending Balance\n7. To Update Monthly Fee Paid\n8. To Update Every Thing\n";
		cin >> temp;
		system("cls");
		if (temp == 1)
		{
		unique:
			cout << "Enter the New Id Number\n";
			cin >> update;
			if (uniqueIdNumber(students, count, update))
			{
				students[index].setid(update);
			}
			else
			{
				cout << "\nWarning : Enter a unique Id Number\n";
				goto unique;
			}

		}
		else if (temp == 4)
		{
			cout << "Enter the New Class\n";
			cin >> update;
			students[index].setclass(update);
		}
		else if (temp == 5)
		{
			cout << "Enter the New Fee\n";
			cin >> update;
			students[index].setfee(update);
		}
		else if (temp == 6)
		{
			cout << "Enter the New Pending Balance\n";
			cin >> update;
			students[index].setpendingBalance(update);
		}
		else if (temp == 2)
		{
			cout << "Enter the New Name\n";
			cin.ignore();
			getline(cin, Update, '\n');
			students[index].setname(Update);
		}
		else if (temp == 3)
		{
			cout << "Enter the New Father Name\n";
			cin.ignore();
			getline(cin, Update, '\n');
			students[index].setfathername(Update);
		}
		else if (temp == 7)
		{
			cout << "Enter the Monthly Fee Paid\n";
			cin >> update;
			students[index].setMonthlyFee(update);
		}
		else if (temp == 8)
		{
		sorry:
			cout << "Enter the New Id Number\n";
			cin >> update;
			if (uniqueIdNumber(students, count, update))
			{
				students[index].setid(update);
			}
			else
			{
				cout << "\nWarning : Enter A unique Id Number\n";
				goto sorry;
			}
			cout << "Enter the New Class\n";
			cin >> update;
			students[index].setclass(update);
			cout << "Enter the New Fee\n";
			cin >> update;
			students[index].setfee(update);
			cout << "Enter the New Pending Balance\n";
			cin >> update;
			students[index].setpendingBalance(update);
			cout << "Enter the New Name\n";
			cin.ignore();
			getline(cin, Update, '\n');
			students[index].setname(Update);
			cout << "Enter the New Father Name\n";
			cin.ignore();
			getline(cin, Update, '\n');
			students[index].setfathername(Update);
			cout << "Enter the Monthly Fee Paid\n";
			cin >> update;
			students[index].setMonthlyFee(update);
		}
		cout << "\nUpdated\n";
		cout << "Press Any KeY TO Continue\n";
		_getch();
	}
}
void DefaulterList(Student* students, int count)
{
	int amount;
	string File_Name;
	system("cls");
	cout << "Enter the Base Amount\n";
	cin >> amount;
	cout << "Enter the Name of .txt File in which You want to Store Data\n";
	cin.ignore();
	getline(cin, File_Name, '\n');
	ofstream output(File_Name);
	for (int i = 0; i < count; i++)
	{
		if (students[i].getPendingBalance() >= amount)
		{
			output << students[i].getid() << endl;
			output << students[i].getname() << endl;
			output << students[i].getfathername() << endl;
			output << students[i].getClass() << endl;
			output << students[i].getPendingBalance() << endl;
			output << students[i].getMonthlyFee() << endl;
			output << endl << endl;
		}
	}
	system("cls");
	output.close();
	cout << "List made Successfully\n";
	cout << "Press Any Key to Continue\n";
	_getch();
}


void appendToAlumniFile(Student* students, int index, int status)
{
	ofstream file("alumni.txt", ios::app);
	file << students[index].getid() << "#" << students[index].getfee() << "#" << students[index].getClass()
		<< "#" << students[index].getname() << "#" << students[index].getfathername() << "#" << status << endl;
	file.close();

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
			cout << string(100, '-') << endl;
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
				appendToAlumniFile(students, i, 0);
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
Student* removeStudent(Student* students, int& count, int id)
{
	bool is_found = false;
	for (int i = 0; i < count; i++)
	{
		if (id == students[i].getid())
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
			is_found = true;
			//delete[] students;
			return temp;
		}
	}
	if (!is_found)
		return students;
}
void addMonthlyFee(Student* students, int count)
{
	int changeCount = 0, iteration = 0;
	system("cls");
	cout << "Enter How Many Students You Want To Add Monthly Fee Of: ";
	cin >> changeCount;

	while (iteration < changeCount)
	{
		system("cls");
		cout << "Enter the Id Number of the Student You Want to Add Monthly Fee For\n";
		int id, monthlyFeePaid;
	again:
		cin >> id;
		bool found = true;
		for (int i = 0; i < count; i++)
		{
			if (id == students[i].getid())
			{
				iteration++;
				system("cls");
				found = false;
				cout << string(100, '-') << endl;
				cout << "Student With Found\n";
				cout << "ID: " << students[i].getid() << endl;
				cout << "Class : " << students[i].getClass() << endl;
				cout << "Name: " << students[i].getname() << endl;
				cout << "Father Name: " << students[i].getfathername() << endl;
				cout << "Fee: " << students[i].getfee() << endl;
				cout << "Pending Balance : " << students[i].getPendingBalance() << endl;
				cout << endl << endl;
				cout << "Enter Fee Paid By Student: ";
				cin >> monthlyFeePaid;
				students[i].setMonthlyFee(students[i].getMonthlyFee() + monthlyFeePaid);
				students[i].setpendingBalance(students[i].getfee() - students[i].getMonthlyFee());
				// total = 1500
				// paid = 0; required = 1500; fee = 0
				// paid = 700; required = 800; fee = 700
				// paid = 800; required =0; fee =1500
				// paid = 200; required = -200; fee = 1700

				UpdatingData(students, count);
				break;
			}
		}
		if (found)
		{
			cout << "Student with Id " << id << " Not Found\nEnter Again: ";
			goto again;
		}
	}
}

/// <summary>
///			Class of Alumni, as evident from the name, represents the data related to the Alumni 
///			of the institution. Alumni refers to
///			1- Students who have passed out from the school
///			2- Students who have left the school before completing the entire degree from the school
/// </summary>


class Alumni
{
	vector<string> alumni_name;
	vector<string> alumni_id;
	vector<string> alumni_fee;
	vector<string> alumni_class;
	vector<string> alumni_father_name;
	vector<string> alumni_status;
	int alumni_count = 0;
public:
	/// <summary>
	///			The constructor of class reads the data from alumni.txt file (if present) 
	///			and then fetches the data from it.
	///			If the alumni.txt file is not present, it creates it.
	///			It also reads data from finalgrades.txt to check if there is any student who 
	///			is from grade 10th and has passed out i-e he/she becomes an alumni.
	/// </summary>
	Alumni()
	{
		Student* students;
		int count = 0;
		studentReadFile(students, count);
		ifstream file("alumni.txt");
		if (file.fail())
		{
			ofstream file2("alumni.txt");
			file2.close();
		}
		else
		{
			string temp;
			while (getline(file, temp))
			{
				string id = "", fee = "", name = "", Class = "", fatherName = "", status = "";
				int turn = 0;
				int index = temp.find('#');
				for (int i = 0; i < temp.length(); i++)
				{
					if (i == index)
					{
						turn++;
						index++;
						index = temp.find('#', index);
						continue;
					}
					if (turn == 0)
						id += temp[i];
					else if (turn == 1)
						fee += temp[i];
					else if (turn == 2)
						Class += temp[i];
					else if (turn == 3)
						name += temp[i];
					else if (turn == 4)
						fatherName += temp[i];
					else if (turn == 5)
						status += temp[i];
				}
				bool is_unique = true;
				for (int m = 0; m < alumni_count; m++)
				{
					if (id == alumni_id[m])
					{
						is_unique = false;
						break;
					}
				}
				if (is_unique)
				{
					alumni_name.push_back(name);
					alumni_id.push_back(id);
					alumni_fee.push_back(fee);
					alumni_class.push_back(Class);
					alumni_father_name.push_back(fatherName);
					alumni_status.push_back(status);
					alumni_count++;
				}
			}



			ifstream gradeFile("finalgrades.txt");

			if (!gradeFile.fail())
			{
				string temp;
				int turn = 0;
				bool valid = true;
				int i = 0;
				while (getline(gradeFile, temp))
				{
					if (1)
					{
						if (temp == "\n")
						{
							turn = 0;
							valid = true;
						}
						if (temp.find(",F,") != string::npos || temp.find(",f,") != string::npos)
						{
							valid = false;
						}
						if (!valid) continue;
						turn++;
						if (turn == 5 && valid == true)
						{
							int pos = temp.rfind(',');
							pos++;
							string id = temp.substr(pos,'\n');

							int index = 0;
							//long int idd = ;

							Search(students, count, index, stoi(id));
							//id.empty();

							if (students[index].getClass() == 10)
							{
								bool is_unique = true;
								for (int m = 0; m < alumni_count; m++)
								{
									if (to_string(students[index].getid()) == alumni_id[m])
									{
										is_unique = false;
										break;
									}
								}
								if (is_unique)
								{
									alumni_name.push_back(students[index].getname());
									alumni_id.push_back(to_string(students[index].getid()));
									alumni_fee.push_back(to_string(students[index].getfee()));
									alumni_class.push_back(to_string(students[index].getClass()));
									alumni_father_name.push_back(students[index].getfathername());
									alumni_status.push_back("1");
									alumni_count++;
									students = removeStudent(students, count, stoi(id));
								}
							}
							turn = 0;
						}
					}
					i++;
				}
			}
		}




		UpdatingData(students, count);
		file.close();
		ofstream file2("alumni.txt");
		for (int i = 0; i < alumni_count; i++)
		{
			file2 << alumni_id[i] << "#" << alumni_fee[i] << '#'
				<< alumni_class[i] << '#' << alumni_name[i] << '#'
				<< alumni_father_name[i] << '#' << alumni_status[i] << endl;
		}
		file2.close();
	}
	/// <summary>
	///			The function addAlumni() adds the alumni to the stored data
	/// </summary>
	void addAlumni(string id, string fee, string Class, string name, string father_name, string status)
	{
		alumni_name.push_back(name);
		alumni_id.push_back(id);
		alumni_father_name.push_back(father_name);
		alumni_fee.push_back(fee);
		alumni_class.push_back(Class);
		alumni_status.push_back(status);
	}
	/// <summary>
	///			The updateData() function updates the data according to the latest available data.
	/// </summary>
	void updateData()
	{
		Student* students;
		int count = 0;
		studentReadFile(students, count);
		ifstream file("alumni.txt");
		if (file.fail())
		{
			ofstream file2("alumni.txt");
			file2.close();
		}
		else
		{
			string temp;
			while (getline(file, temp))
			{
				string id = "", fee = "", name = "", Class = "", fatherName = "", status = "";
				int turn = 0;
				int index = temp.find('#');
				for (int i = 0; i < temp.length(); i++)
				{
					if (i == index)
					{
						turn++;
						index++;
						index = temp.find('#', index);
						continue;
					}
					if (turn == 0)
						id += temp[i];
					else if (turn == 1)
						fee += temp[i];
					else if (turn == 2)
						Class += temp[i];
					else if (turn == 3)
						name += temp[i];
					else if (turn == 4)
						fatherName += temp[i];
					else if (turn == 5)
						status += temp[i];
				}
				bool is_unique = true;
				for (int m = 0; m < alumni_count; m++)
				{
					if (id == alumni_id[m])
					{
						is_unique = false;
						break;
					}
				}
				if (is_unique)
				{
					alumni_name.push_back(name);
					alumni_id.push_back(id);
					alumni_fee.push_back(fee);
					alumni_class.push_back(Class);
					alumni_father_name.push_back(fatherName);
					alumni_status.push_back(status);
					alumni_count++;
				}
			}
			ifstream gradeFile("finalgrades.txt");

			if (!gradeFile.fail())
			{
				string temp;
				int turn = 0;
				bool valid = true;
				int i = 0;
				while (getline(gradeFile, temp))
				{
					if (1)
					{
						if (temp == "\n")
						{
							turn = 0;
							valid = true;
						}
						if (temp.find(",F,") != string::npos || temp.find(",f,") != string::npos)
						{
							valid = false;
						}
						if (!valid) continue;
						turn++;
						if (turn == 5 && valid == true)
						{
							int pos = temp.rfind(',');
							pos++;
							string id = temp.substr(pos);

							int index = 0;

							Search(students, count, index, stoi(id));
							if (students[index].getClass() == 10)
							{
								bool is_unique = true;
								for (int m = 0; m < alumni_count; m++)
								{
									if (to_string(students[index].getid()) == alumni_id[m])
									{
										is_unique = false;
										break;
									}
								}
								if (is_unique)
								{
									alumni_name.push_back(students[index].getname());
									alumni_id.push_back(to_string(students[index].getid()));
									alumni_fee.push_back(to_string(students[index].getfee()));
									alumni_class.push_back(to_string(students[index].getClass()));
									alumni_father_name.push_back(students[index].getfathername());
									alumni_status.push_back("1");
									alumni_count++;
									students = removeStudent(students, count, stoi(id));
								}
							}
							turn = 0;
						}
					}
					i++;
				}
			}
		}
		UpdatingData(students, count);
		file.close();
		ofstream file2("alumni.txt");
		for (int i = 0; i < alumni_count; i++)
		{
			file2 << alumni_id[i] << "#" << alumni_fee[i] << '#'
				<< alumni_class[i] << '#' << alumni_name[i] << '#'
				<< alumni_father_name[i] << '#' << alumni_status[i] << endl;
		}
		file2.close();
	}
	/// <summary>
	///			he display() function displays the entire data of alumni in a presentable way.
	///			This function has been overloaded (i-e Polymorphism) such that if an alumni ID 
	///			is passed in its parameter, it prints the data of that particular student. (if present)
	/// </summary>
	void display()
	{
		system("CLS");
		for (int i = 0; i < alumni_count; i++)
		{
			cout << string(100, '-') << endl;
			cout << "Alumni # " << i + 1 << " \n";
			cout << "ID: " << alumni_id.at(i)
				<< "\nName: " << alumni_name.at(i)
				<< "\nFather Name: " << alumni_father_name[i]
				<< "\nMonthly Fee Before Leaving: " << alumni_fee[i]
				<< "\nClass: " << alumni_class.at(i)
				<< "\nStatus: ";
			if (alumni_status[i] == "1")
				cout << "Graduated!\n";
			else
				cout << "Left the school.\n";
			cout << endl;
		}
		cout << "Press Any Key to Continue\n";
		_getch();
	}
	bool display(string alumniID)
	{
		int index = -1;
		for (int i = 0; i < alumni_id.size(); i++)
		{
			if (alumni_id[i] == alumniID)
			{
				index = i;
				break;
			}
		}
		if (index == (-1))
		{
			cout << "Invalid ID Entered.\n";
			return false;
		}
		else
		{
			system("cls");
			cout << string(100, '-') << endl;
			cout << "Record Found For The ID: " << alumni_id.at(index)
				<< "\nName: " << alumni_name.at(index)
				<< "\nFather Name: " << alumni_father_name[index]
				<< "\nMonthly Fee Before Leaving: " << alumni_fee[index]
				<< "\nClass: " << alumni_class.at(index)
				<< "\nStatus: ";
			if (alumni_status[index] == "1")
				cout << "Graduated!\n";
			else
				cout << "Left the school.\n";
			cout << endl;
			return true;
		}
	}
};

void monthlyReport(Student* students, int count)
{
	system("cls");
	cout << "Enter Month Number: ";
	int month = 0;
rep:
	cin >> month;
	if (!(month <= 12 && month >= 1))
	{
		cout << "Invalid Month Number Entered! Enter Again: ";
		goto rep;
	}
	int totalFee = 0;
	int totalFeePaid = 0;
	for (int i = 0; i < count; i++)
	{
		totalFee += students[i].getfee();
		totalFeePaid += students[i].getMonthlyFee();
	}
	vector <int>other_expenses_value;
	vector <string>other_expenses_name;
	cout << "Enter Other Expenditures. \nEnter -1 In Name To Exit.\n";
	string fileName = "monthlyReport_" + to_string(month) + ".txt";
	ofstream file(fileName);
	int i = 0;
	while (1)
	{
		cout << "\nExpenditure # " << i + 1 << " : \n";
		i++;
		cout << "Name: ";
		string name;
		cin.ignore();
		getline(cin, name);
		if (name != "-1")
			other_expenses_name.push_back(name);
		else
		{
			break;
		}
		cout << "Expense Value: ";
		int value;
		cin >> value;
		other_expenses_value.push_back(value);
	}
	int totalExpenses = totalFee;
	for (int i = 0; i < other_expenses_value.size(); i++)
		totalExpenses += other_expenses_value[i];
	int profit = totalFeePaid - totalExpenses;
	system("cls");
	cout << string(100, '-') << endl;
	cout << "Monthly Report\n";
	cout << "Comultative Fee Of Students: Pkr ";
	cout << totalFee << "/_" << endl;
	cout << "Other Expenditures: \n";

	file << "Monthly Report Of Month # " << month << endl;
	file << "Comultative Fee Of Students: Pkr";
	file << totalFee << "/_" << endl;
	file << "Other Expenditures: \n";
	for (int i = 0; i < other_expenses_value.size(); i++)
	{
		cout << "\tExpenditure # " << i + 1 << "\n\t";
		cout << "\tName: " << other_expenses_name[i] << "\n\t"
			<< "\tValue: Pkr " << other_expenses_value[i] << "/_" << "\n";

		file << "\tExpenditure # " << i + 1 << "\n\t";
		file << "\tName: " << other_expenses_name[i] << "\n\t"
			<< "\tValue: Pkr " << other_expenses_value[i] << "/_" << "\n";
	}
	cout << "Grand Total: Pkr " << totalExpenses << "/_" << endl;
	cout << "\nComultative Fee Paid By Students: Pkr " << totalFeePaid << "/_" << endl;
	cout << "<--------------------------------------------------------->\n";

	file << "\nComultative Fee Paid By Students: Pkr " << totalFeePaid << "/_" << endl;
	if (profit >= 0)
	{
		cout << "Profit: Pkr " << profit << "/_" << endl;
		file << "Profit: Pkr " << profit << "/_" << endl;
	}
	else
	{
		cout << "Loss: Pkr " << profit << "/_" << endl;
		file << "Loss: Pkr " << profit << "/_" << endl;
	}


	file.close();

	cout << "\nEnter Any Key To Continue.";
	_getch();
}
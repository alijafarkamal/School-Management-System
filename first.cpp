//#include<iostream>
//#include<fstream>
//#include<sstream>
//#include<string>
//#include<cstring>
//#include<cctype>
//#include<conio.h>
//#include<iomanip>
//#include<sqlite3.h>
//
//using namespace std;
//int main()
//{
// sqlite3* db;
//int rc = sqlite3_open("test.db", &db);
//
//if (rc) {
//    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//    return 1;
//}
//else {
//    std::cout << "Opened database successfully" << std::endl;
//}
//
//sqlite3_close(db);
//	ofstream file("attendence.csv");
//	file << "1001,";
//	file << "ali,";
//	string mark = "p a p p p p a p p\n p p p";
//	file << mark;
//	file.close();
//	system("pause");
//	return 0;
//}

//class attendence : public teachers, public Exam {
//	string student_attendence;
//	Student* student;
//	int count;
//	ofstream file;
//public:
//	attendence(Student* student, int count) {
//		this->student = student;
//		this->count = count;
//	}
//	void attendence_mark() {
//		ofstream file("attendence.csv");
//		int enter;
//		cout << "Do you want to login as a teacher? \n If yes press 1 else press 0\n";
//		cin >> enter;
//		if (enter == 1) {
//			cout << "Enter your id\n";
//			cin >> enter;
//			if (str_teacher_ids.find(enter))
//			{
//				system("CLS");
//				cout << "You have entered as the teacher of " << enter << " class\n";
//				int option(0);
//				string mark;
//				while (option != -1) {
//					cout << "Press 1 if you want to mark attendence\n";
//					cout << "Press 2 if you want to see previous attendences\n";
//					cout << "Press 3 if you want to see particular student attendence\n";
//					cout << "Press 4 to conduct exam\n";
//					cout << "press 5 to assign  grades\n";
//					cout << "Press -1 to exit\n";
//					cin >> option;
//					if (option == 1) {
//						file << "class,id,name,attendence\n";
//		for (int i = 0; i < count; i++)
//			if (enter == student[i].getClass()) {
//				cout << "Press p to mark presence or a to mark absence of student\n";
//				cout << "ID of the student " << student[i].getid() << endl;
//				cout << "Name of the student " << student[i].getname() << endl;
//				cin >> mark;
//				mark = to_string(student[i].getClass()) + ',' + to_string(student[i].getid()) +
//					',' + student[i].getname() + ',' + mark + "\n";
//				file << mark;
//				student_attendence += mark;
//				mark.empty();
//				cout << student_attendence << endl;
//			}
//
//	}
//					else if (option == 2) {
//		cout << "class id name attendence\n";
//		for (option = 0; option < student_attendence.length(); option++)
//			if (student_attendence[option] == '\n') cout << endl;
//			else if (student_attendence[option] == ',') cout << " ";
//			else cout << student_attendence[option];
//		cout << endl;
//	}
//	else if (option == 3) {
//		cout << "Enter id of particular student\n";
//		cin >> mark;
//		size_t record = student_attendence.find(mark);
//		size_t end_record = student_attendence.find('\n', record);
//		mark.empty();
//		mark = student_attendence.substr(record, end_record - record);
//		cout << mark << endl;
//	}
//	else if (option == 4) {
//		Exam exam(student, count);
//		exam.conductExam();
//	}
//				}
//			}
//		}
//		file.close();
//	}
//
//};



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

//class teachers {
//protected:
//	string str_teacher_heading;
//	string str_teacher_ids;
//	string str_teacher_name;
//	string str_teacher_salary;
//	string str_teacher_class;
//	string str_teacher_join;
//	string str_teacher_leave;
//	static int no_of_teachers;
//public:
//	teachers() {
//		this->teacheruploader();
//	}
//	void teacheruploader()
//	{
//		ifstream file(file_teachers);
//		string store_teacher;
//		file >> store_teacher;
//		istringstream is(store_teacher);
//		store_teacher.clear();
//		string isa;
//		while (getline(is, isa, ',')) {
//			store_teacher += isa + " ";
//		}
//		//cout << store_teacher;
//		int index = 0;
//		for (int i = 0; i < no_of_teachers; i++)
//		{
//if (getline(file, store_teacher)) {
//	istringstream iss(store_teacher);
//	string token;
//	while (getline(iss, token, ',')) {
//		index++;
//		token += " ";
//		if (index == 1) str_teacher_ids += token;
//		if (index == 2) str_teacher_name += token;
//		if (index == 3) str_teacher_salary += token;
//		if (index == 4) str_teacher_class += token;
//		if (index == 5) str_teacher_join += token;
//		if (index == 6) str_teacher_leave += token;
//	}
//	index = 0;
//			}
//		}
//	}
//};
//
//class Exam {
//protected:
//	string subjects[5];
//	Student* student;
//	int count;
//public:
//	Exam() {
//
//	}
//	Exam(Student* student, int count) {
//		this->student = student;
//		this->count = count;
//
//		ifstream file("subjects.txt");
//		if (!file.is_open()) {
//			cout << "Error opening file: subject.txt" << endl;
//			return;
//		}
//
//		string subject;
//		int index = 0;
//		while (getline(file, subject) && index < 10) {
//			subjects[index++] = subject;
//			cout << subjects[index - 1] << endl;
//		}
//		//cout << subject[1];
//		file.close();
//	}
//
//	void conductExam() {
//
//		int Class;
//		cout << "Enter the class for which you want to conduct the exam: ";
//		cin >> Class;
//		bool True = false;
//		for (int i = 0; i < count && !True; i++) {
//			//cin.ignore();
//			if (Class == student[i].getClass()) {
//				True = true;
//				cout << "Available subjects for the exam:\n";
//				for (int j = 0; j < 5; ++j) {
//					cout << j + 1 << " " << subjects[j] << endl;
//				}
//
//			}
//		}
//		if (!True) return;
//		cout << "Enter the subject for the exam: ";
//
//		string chosenSubject;
//		cin >> chosenSubject;
//		for (int i = 0; i < 5; i++) {
//			if (subjects[i] == (chosenSubject)) {
//				cout << "exam is done \n";
//				return;
//			}
//			else {
//				cout << "not found or taught";
//				return;
//			}
//		}
//		cout << "Exam not done\n";
//	}
//};
//class grades {
//protected:
//	Student* student;
//	string subjects[5];
//	int count;
//public:
//
//	grades() {
//
//	}
//	grades(Student* student, int count) {
//		this->student = student;
//		this->count = count;
//		ifstream file("subjects.txt");
//		if (!file.is_open()) {
//			cout << "Error opening file: subject.txt" << endl;
//			return;
//		}
//
//		string subject;
//		int index = 0;
//		while (getline(file, subject) && index < 10) {
//			subjects[index++] = subject;
//		}
//		file.close();
//		ofstream gradesFile("grades.txt");
//		gradesFile << "ID,Name,Class,Subject,Grade\n";
//	}
//	void assignGrades() {
//		ofstream gradesFile("grades.txt", ios::app);
//		int  Class;
//		cout << "Enter the class for which you want to assign grades: ";
//		cin >> Class;
//		bool classFound = false;
//		for (int i = 0; i < count; i++) {
//			if (Class == student[i].getClass()) {
//				classFound = true;
//				cout << "Available subjects for assigning grades:\n";
//				for (int j = 0; j < 5; ++j) {
//					cout << j + 1 << " " << subjects[j] << endl;
//				}
//				cout << "Enter the subject for assigning grades: ";
//				string chosenSubject;
//				cin >> chosenSubject;
//				int subjectIndex = -1;
//				for (int j = 0; j < 5; ++j) {
//					if (subjects[j] == chosenSubject) {
//						subjectIndex = j;
//						break;
//					}
//				}
//				if (subjectIndex == -1) {
//					cout << "Invalid subject.\n";
//					return;
//				}
//				cout << "Enter grades for the subject \"" << chosenSubject << "\" for class " << Class << ":\n";
//				for (int k = 0; k < count; ++k) {
//					if (student[k].getClass() == Class) {
//						cout << "Enter grade for student " << student[k].getname() << ": ";
//						char grade;
//						cin >> grade;
//						grade = toupper(grade);
//						cout << "Grade for student " << student[k].getname() << " in " << chosenSubject << ": " << grade << endl;
//						gradesFile << student[k].getid() << "," << student[k].getname() << ",  " << Class << "," << chosenSubject << "," << grade << endl;
//
//					}
//				}
//				return;
//			}
//		}
//		if (!classFound) {
//			cout << "Class not found.\n";
//		}
//	}
//};

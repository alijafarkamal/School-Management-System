//using namespace std;

//int main() {
//	attendence att;
//	att.attendence_mark();
//	system("pause");
//	return 0;
//}
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cstring>
#include<cctype>
#include<conio.h>
#include<iomanip>

using namespace std;
class teachers;
class student;
class attendence;
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
public:
	teachers() {
		ifstream file("teachers.csv");
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
};
class attendence : public teachers{
	string student_attendence;
	Student* student;
	int count;
	ofstream file;
public:
	attendence(Student* student,int count) {
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
				int option(1);
				while (option>=1 && option<=3) {
					cout << "Press 1 if you want to mark attendence\n";
					cout << "Press 2 if you want to see previous attendences\n";
					cout << "Press 3 if you want to see particular student attendence\n";
					cout << "Press -1 to exit\n";
					cin >> option;
					string mark;
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
						size_t end_record = student_attendence.find('\n',record);
						mark.empty();
						mark = student_attendence.substr(record,end_record-record);
						cout << mark << endl;
					}
				}
			}
		}
		file.close();
	}

};
class other_staff {
protected:
public:

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

int main()
{
	int count = NoofStudents();
	Student* students = new Student[count];
	ifstream input("student.txt");
	string name, password, fathername;
	int id, fee, invalidTry = 3, choice = 0, PendingBalance, Class, InnerChoice;

	if (input.is_open())
	{
		for (int i = 0; i < count; i++)
		{
			input >> id >> fee >> PendingBalance >> Class;
			getline(input, name, '#');
			getline(input, fathername, '\n');

			students[i] = Student(name, fathername, id, fee, PendingBalance, Class);

		}
		input.close();
	}
	else
	{
		cout << "Error Opening the File Student.txt\n";
	}
	attendence attend(students, count);
	attend.attendence_mark();
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


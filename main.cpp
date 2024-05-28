
#include "functions.h"
/// <summary>
///		This class "non-teaching-staff" manages non teaching staff like cook, 
///		peon, guard etc. Bascially it reads their data from an excel sheet 
///		and then populate the strings required for their proper implementation.	
/// </summary>
class non_teaching_staff {
protected:
	string other_staff_id;
	string other_staff_name;
	string other_staff_salary;
	string other_staff_profession;
	static int other_staff_number;
	Student_management_system* student_manage;
	Student student_info;
public:
	non_teaching_staff() {
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
	~non_teaching_staff()
	{

		cout << "Destructor of non teaching staff called \n";
	}
};
int non_teaching_staff::other_staff_number = 6;
/// <summary>
///			This class manages functionalities of non teaching staff and has methods to add,
///			remove and update them. It has all the checks so that admin manages non teaching
///			staff correctly. It inherits non_teaching_staff class as to have an easy access 
///			io the strings which contains the whole data of non_teaching_staff.
/// </summary>
class non_teaching_staff_management : public non_teaching_staff {
public:
	non_teaching_staff_management() {
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
		ofstream file("non_teaching_staff.csv", ios::app);
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
		cout << comma_counter << endl;
		string data_store; int counter(0);
		ifstream file(file_other_staff);
		string data_store_temp;
		while (getline(file, data_store)) {
			if (counter != comma_counter + 1) {
				data_store_temp += data_store + "\n";// << endl;
			}
			counter++;
			data_store.empty();
		}
		ofstream file_out(file_other_staff);
		cout << data_store_temp;
		file_out << data_store_temp;
		file_out.close();
		other_staff_number--;
		other_staff_id.erase();
		other_staff_name.erase();
		other_staff_salary.erase();
		other_staff_profession.erase();
		initializer();
		cout << "Successfully removed id \n";
		//cout << other_staff_id << endl;
		//cout << other_staff_name << endl;
		//cout << other_staff_salary << endl;
		//cout << other_staff_profession << endl;
		_getch();
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
		other_staff_id += " " + str_add;
		cout << "Enter his updated name \n";
		cin >> str_add;
		mark += str_add + ',';
		other_staff_name += " " + str_add;
		cout << "Enter his updated salary\n";
		cin >> str_add;
		mark += str_add + ',';
		other_staff_salary += " " + str_add;
		cout << "Enter his updated Profession\n";
		cin >> str_add;
		mark += str_add + '\n';
		other_staff_profession += " " + str_add;
		string data_store;
		ifstream file(file_other_staff);
		int comma_counter = count(other_staff_id.begin(), other_staff_id.begin() + reply, ' ');
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
		ofstream file_out(file_other_staff);
		file_out << data_store_temp;
		file_out.close();
	}
	void display() {
		ifstream file(file_other_staff);
		if (!file.is_open())
			cout << "File cannot be opened \n";
		string display_mode;
		while (getline(file, display_mode)) {
			cout << display_mode << endl;
		}	
		_getch();
	}
};
/// <summary>
///			Main has initially all the objects of classes and then a menu 
///			is given to the admin to run the system. Admin can opt for any 
///			of the 15 main functionalities of the school management system.
///			Main has implemented exception handling to catch unnecessary 
///			errors. Data from student txt file is fed to all the objects 
///			of classes that deal with students. 
/// </summary>
/// <returns></returns>
int main()
{

	try {
		Student_management_system* stu = new Student;
		Student* pupil = dynamic_cast<Student*>(stu);
		int count = NoofStudents();
		Student* students = new Student[count];
		Alumni alumni;
		ifstream input("student.txt");
		string name, password, fathername;
		non_teaching_staff_management other;
		teacher_functionalities teacher_func(students, count);
		teacher_func.teachers::display();
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
		else
		{
			cout << "Error Opening the File Student.txt\n";
		}

	invalid:
		if (invalidTry > 0)
		{
			//setCursorPosition(10, 10);
			//setColor(12);
			cout << "Enter the Password To Continue\n";
			getline(cin, password);
			if (password != "hello")
			{
				system("cls");
				cout << "Invalid Password\n";
				invalidTry--;
				cout << "Remaining Tries: " << invalidTry << endl;
				goto invalid;
			}
			else
			{
				system("cls");
				setColor(10);
				cout << "You Successfully Entered as ADMIN\n";
			}

			while (choice != -1)
			{
				setCursorPosition(10, 10);
				setColor(15);
				system("cls");
				cout << R"(
 _    _      _                            _         ___  ___      _        ___  ___                 
| |  | |    | |                          | |        |  \/  |     (_)       |  \/  |                 
| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___   | .  . | __ _ _ _ __   | .  . | ___ _ __  _   _ 
| |/\| |/ _ | |/ __/ _ \| '_ ` _ \ / _ \ | __/ _ \  | |\/| |/ _` | | '_ \  | |\/| |/ _ | '_ \| | | |
\  /\  |  __| | (_| (_) | | | | | |  __/ | || (_) | | |  | | (_| | | | | | | |  | |  __| | | | |_| |
 \/  \/ \___|_|\___\___/|_| |_| |_|\___|  \__\___/  \_|  |_/\__,_|_|_| |_| \_|  |_/\___|_| |_|\__,_|
)" << '\n';
				setColor(12);
				cout << string(100, '-') << endl;
				setColor(15);
				cout << "1.  To Display Student Records\n";
				cout << "2.  To Display Details Of a Particular Student\n";
				setColor(14);
				cout << "3.  To Give and OverView\n";
				setColor(15);
				cout << "4.  To Enter Financial Mode\n";
				setColor(14);
				cout << "5.  To Enter A New Student\n";
				setColor(15);	
				cout << "6.  To Remove a Student\n";	
				cout << "7.  To Edit Student Details\n";		
				cout << "8.  To Make A Defaulter List\n";			
				setColor(14);
				cout << "9.  To Enter as a teacher\n";
				setColor(15);		
				cout << "10. To Manage non-teaching staff\n";
				cout << "11. To Manage teachers\n";
				cout << "12. To Enter Monthly Fee Payment\n";
				setColor(14);
				cout << "13. To Enter Alumni Mode\n";
				setColor(15);
				cout << "14. To Update alumni data \n";
				cout << "15. To Generate Monthly Report\n";
				setColor(12);
				cout << "Press -1 to exit\n";
				cout << string(100, '-') << endl;
				setColor(15);
				cin >> choice;
				if (choice < -1) throw choice;
				if (choice == 1)
				{
					Display(students, count);
				}
				else if (choice == 2)
				{
					system("cls");
					cout << "1. To Search By Father Name\n";
					cout << "2. To Search By ID Number\n";
					cin >> InnerChoice;
					if (InnerChoice == 1)
					{
						SearchFamily(students, count);
					}
					else if (InnerChoice == 2)
					{
						Search(students, count);
					}
				}
				else if (choice == 3)
				{
					overview(students, count);
				}
				else if (choice == 4)
				{
					financial(students, count);
					UpdatingData(students, count);
				}
				else if (choice == 5)
				{
					students = addStudent(students, count);
					UpdatingData(students, count);
				}
				else if (choice == 6)
				{
					students = removeStudent(students, count);
					UpdatingData(students, count);
				}
				else if (choice == 7)
				{
					EditInfo(students, count);
					UpdatingData(students, count);
				}
				else if (choice == 8)
				{
					DefaulterList(students, count);
				}
				else if (choice == 9) {
					teacher_func.functionalities();
				}
				else if (choice == 10) {
					cout << string(100, '-') << endl;
					cout << "Press 1 to add non-teaching staff \n";
					cout << "Press 2 to update non-teaching staff \n";
					cout << "Press 3 to remove non-teaching staff \n";
					cout << "Press 4 to display non-teaching staff \n";
					cout << "Press 5 to exit\n";
					cin >> choice;
					if (choice == 1) other.add();
					else if (choice == 2) other.update();
					else if (choice == 3) other.remove();
					else if (choice == 4) other.display();
				}
				else if (choice == 11) {
					cout << string(100, '-') << endl;
					cout << "Press 1 to add teacher\n";
					cout << "Press 2 to update teacher\n";
					cout << "Press 3 to remove teacher\n";
					cout << "Press 4 to display teacher\n";
					cout << "Press 5 to exit\n";
					cin >> choice;
					if (choice == 1) teacher_func.add();
					else if (choice == 2) teacher_func.update();
					else if (choice == 3) teacher_func.remove();
					else if (choice == 4) teacher_func.display();

					cout << "\nTHis is func \n\n";
					//teacher_func.display();
				}
				else if (choice == 12)
				{
					addMonthlyFee(students, count);
				}
				else if (choice == 13)
				{
					system("cls");
					cout << "Enter: \n1. To Display All Alumni\n2. To Search An Alumni\n";
					cout << "Enter Your Choice: ";
					cin >> InnerChoice;
					if (InnerChoice == 1)
					{
						alumni.display();
					}
					else
					{
						cout << "Enter Alumni's ID: ";
						string alumniID;
					rep:
						cin >> alumniID;
						if (alumni.display(alumniID))
						{
							cout << "\nPress Any Key to Continue\n";
							_getch();
						}
						else
						{
							cout << "Enter Again: ";
							goto rep;
						}
					}
				}
				else if (choice == 14) {
					alumni.updateData();
				system("CLS");					
				setColor(14);
				cout << "Alumni Data Updated!\n";
				Sleep(1500);
				setColor(15);
				cout << "Updated Data Is: (If Any)\n";
				Sleep(1500);
				alumni.display();					
				}
				else if (choice == 15)
				{
					monthlyReport(students, count);
				}
			}
		}
		else
		{
			setColor(12); // Red
			cout << "Crashed !\n";
			return 0;
			cout << "Crashed !\n";
			return 0;
		}
		delete[] students;
		delete[] stu;
		cout << string(100, '-') << endl;
	}
	catch (int x) {
		cout << "\nException caught. You entered negative value \n";
	}
	system("pause");
	return 0;
}

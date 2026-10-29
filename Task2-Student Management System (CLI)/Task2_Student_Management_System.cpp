#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <stdexcept>

using namespace std;

// Helper functions
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == string::npos)
        return "";

    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}
string to_lower(const string& s) {
    string r = s;

    transform(r.begin(), r.end(), r.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        });

    return r;
}
// Check if string contains only digits
bool is_integer(const string& s) {
    if (s.empty())
        return false;

    for (unsigned char c : s) {
        if (!isdigit(c))
            return false;
    }

    return true;
}
// Safely convert a numeric string to int
bool try_parse_int(const string& s, int& value) {
    if (!is_integer(s))
        return false;

    try {
        size_t pos = 0;
        int result = stoi(s, &pos);

        if (pos != s.size())
            return false;

        value = result;
        return true;
    }
    catch (const out_of_range&) {
        return false;
    }
}

// Structs
struct Student {
    int id;
    string name;
    int age;
    string email;
};
struct Instructor {
    int id;
    string name;
    string department;
    int class_count = 0;
};
struct Class {
    int id;
    string name;
    string instructor_name;
    int capacity;
    vector<int> enrolled_students;
};

// Prints help
void cmd_help() {
    cout << "Available commands:\n"
         << "  help                              Show this list\n"
         << "  add student                       Add a new student\n"
         << "  add instructor                    Add a new instructor\n"
         << "  create class                      Create a new class\n"
         << "  list students                     List all students\n"
         << "  list instructors                  List all instructors\n"
         << "  list classes                      List all classes\n"
         << "  enroll <student_id> <class_id>    Enroll a student in a class\n"
         << "  show class <class_id>             Show one class with its students\n"
         << "  exit                              Quit the program\n";
}

// Add student
void cmd_add_student(vector<Student>& students, int& next_id) {
    string name, age_str, email;

    cout << "Full name: ";
    getline(cin, name);
    name = trim(name);

    if (name.empty()) {
        cout << "Error: name must not be empty. Student not added.\n";
        return;
    }

    cout << "Age: ";
    getline(cin, age_str);
    age_str = trim(age_str);

    int age;
    if (!try_parse_int(age_str, age) || age < 15 || age > 100) {
        cout << "Error: age must be a whole number between 15 and 100. Student not added.\n";
        return;
    }

    cout << "Email: ";
    getline(cin, email);
    email = trim(email);

    if (email.find('@') == string::npos) {
        cout << "Error: email must contain an @ character. Student not added.\n";
        return;
    }

    students.push_back({next_id, name, age, email});

    cout << "Student added successfully (ID: " << next_id << ").\n";
    next_id++;
}

// Add instructor
void cmd_add_instructor(vector<Instructor>& instructors, int& next_id) {
    string name, dept;

    cout << "Full name: ";
    getline(cin, name);
    name = trim(name);

    if (name.empty()) {
        cout << "Error: name must not be empty. Instructor not added.\n";
        return;
    }

    cout << "Department: ";
    getline(cin, dept);
    dept = trim(dept);

    if (dept.empty()) {
        cout << "Error: department must not be empty. Instructor not added.\n";
        return;
    }

    for (const Instructor& inst : instructors) {
        if (to_lower(inst.name) == to_lower(name)) {
            cout << "Error: an instructor named '" << name
                 << "' already exists. Instructor not added.\n";
            return;
        }
    }

    instructors.push_back({next_id, name, dept, 0});

    cout << "Instructor added successfully (ID: " << next_id << ").\n";
    next_id++;
}

// Create class
void cmd_create_class(
    vector<Class>& classes,
    vector<Instructor>& instructors,
    int& next_id
) 
{
    string cname, iname, cap_str;

    cout << "Class name: ";
    getline(cin, cname);
    cname = trim(cname);

    if (cname.empty()) {
        cout << "Error: class name must not be empty. Class not created.\n";
        return;
    }

    for (const Class& c : classes) {
        if (to_lower(c.name) == to_lower(cname)) {
            cout << "Error: class name already used. Class not created.\n";
            return;
        }
    }

    cout << "Instructor name: ";
    getline(cin, iname);
    iname = trim(iname);

    auto it = find_if(
        instructors.begin(),
        instructors.end(),
        [&](const Instructor& i) {
            return to_lower(i.name) == to_lower(iname);
        }
    );

    if (it == instructors.end()) {
        cout << "Error: instructor '" << iname
             << "' not found. Add the instructor first. Class not created.\n";
        return;
    }

    cout << "Capacity: ";
    getline(cin, cap_str);
    cap_str = trim(cap_str);

    int cap;
    if (!try_parse_int(cap_str, cap) || cap < 1 || cap > 200) {
        cout << "Error: capacity must be a whole number between 1 and 200. Class not created.\n";
        return;
    }

    // Initialize enrolled_students as an empty vector
    classes.push_back({next_id, cname, it->name, cap, {}});

    // Update the instructor's class count
    it->class_count++;

    cout << "Class created successfully (ID: " << next_id << ").\n";
    next_id++;
}

 // List students
void cmd_list_students(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students found.\n";
        return;
    }

    cout << "ID    Name           Age   Email\n"
         << "---   -------------  ----  ---------------\n";

    for (const Student& s : students) {
        cout << right << setw(4) << s.id << "  "
             << left << setw(13) << s.name.substr(0, 13)
             << right << setw(4) << s.age << "   "
             << s.email << "\n";
    }

    cout << "Total: " << students.size() << " student(s)\n";
}

// List instructors
void cmd_list_instructors(const vector<Instructor>& instructors) {
    if (instructors.empty()) {
        cout << "No instructors found.\n";
        return;
    }

    cout << "ID    Name              Department          Classes\n"
         << "---   ---------------   -----------------   -------\n";

    for (const Instructor& i : instructors) {
        cout << right << setw(4) << i.id << "  "
             << left << setw(18) << i.name.substr(0, 15)
             << setw(20) << i.department.substr(0, 17)
             << right << setw(7) << i.class_count << "\n";
    }

    cout << "Total: " << instructors.size() << " instructor(s)\n";
}

// List classes
void cmd_list_classes(const vector<Class>& classes) {
    if (classes.empty()) {
        cout << "No classes found.\n";
        return;
    }

    cout << "ID    Class Name         Instructor        Enrolled\n"
         << "---   ----------------   ---------------   -------\n";

    for (const Class& c : classes) {
        cout << right << setw(4) << c.id << "  "
             << left << setw(19) << c.name.substr(0, 16)
             << setw(17) << c.instructor_name.substr(0, 15)
             << right << c.enrolled_students.size()
             << "/" << c.capacity << "\n";
    }

    cout << "Total: " << classes.size() << " class(es)\n";
}

// Enroll student
void cmd_enroll(
    vector<Class>& classes,
    const vector<Student>& students,
    const string& arg1,
    const string& arg2
) {
    int student_id, class_id;

    if (!try_parse_int(arg1, student_id) ||
        !try_parse_int(arg2, class_id) ||
        student_id <= 0 || class_id <= 0) {
        cout << "Error: IDs must be positive whole numbers.\n";
        return;
    }

    // Find student
    bool student_found = false;
    string student_name;

    for (const Student& s : students) {
        if (s.id == student_id) {
            student_found = true;
            student_name = s.name;
            break;
        }
    }

    if (!student_found) {
        cout << "Error: student not found.\n";
        return;
    }

    // Find class
    for (Class& c : classes) {
        if (c.id == class_id) {

            // Check if student is already enrolled
            for (int id : c.enrolled_students) {
                if (id == student_id) {
                    cout << "Error: student is already enrolled.\n";
                    return;
                }
            }

            // Check class capacity
            if (c.enrolled_students.size() >=
                static_cast<size_t>(c.capacity)) {
                cout << "Error: class is full.\n";
                return;
            }

            // Enroll student
            c.enrolled_students.push_back(student_id);

            cout << student_name
                 << " was enrolled in "
                 << c.name << ".\n";
            return;
        }
    }

    cout << "Error: class not found.\n";
}

void cmd_show_class(
    const vector<Class>& classes,
    const vector<Student>& students,
    const string& arg
) {
    int class_id;

    // Check if the ID is a valid positive integer
    if (!try_parse_int(arg, class_id) || class_id <= 0) {
        cout << "Error: ID must be a positive whole number.\n";
        return;
    }

    // Search for the class
    for (const Class& c : classes) {
        if (c.id == class_id) {

            // Display class information
            cout << "Class ID    : " << c.id << "\n";
            cout << "Name        : " << c.name << "\n";
            cout << "Instructor  : " << c.instructor_name << "\n";
            cout << "Enrolled    : "
                 << c.enrolled_students.size()
                 << "/" << c.capacity << "\n";

            cout << "Students    :\n";

            // Check if the class has no students
            if (c.enrolled_students.empty()) {
                cout << "  (no students enrolled)\n";
            }
            else {
                int index = 1;

                // Search for each enrolled student
                for (int student_id : c.enrolled_students) {

                    for (const Student& s : students) {
                        if (s.id == student_id) {
                            cout << "  " << index
                                 << ". [ID " << s.id << "] "
                                 << s.name << " - "
                                 << s.email << "\n";

                            index++;
                            break;
                        }
                    }
                }
            }

            return;
        }
    }

    // Display an error if the class does not exist
    cout << "Error: class with ID "
         << class_id << " not found.\n";
}

void print_welcome() {
	cout << "==============================================\n";
	cout << "  Student Management System   (type 'help')\n";
	cout << "==============================================\n";
}

vector<string> parse_command(const string& line) {
	stringstream input(line);
	vector<string> words;
	string word;
	while (input >> word) {
		words.push_back(to_lower(word));
	}
	return words;
}

bool execute_command(
    const vector<string>& words,
    const string& line,
    vector<Student>& students,
    vector<Instructor>& instructors,
    vector<Class>& classes,
    int& next_student_id,
    int& next_instructor_id,
    int& next_class_id
) {
    if (words.empty()) {
        return true;
    }

    string command = words[0];

    if (command == "help") {
        cmd_help();
    }
    else if (command == "exit" || command == "quit") {
        cout << "Goodbye!\n";
        return false;
    }
    else if (command == "add" && words.size() >= 2 && words[1] == "student") {
        cmd_add_student(students, next_student_id);
    }
    else if (command == "add" && words.size() >= 2 && words[1] == "instructor") {
        cmd_add_instructor(instructors, next_instructor_id);
    }
    else if (command == "create" && words.size() >= 2 && words[1] == "class") {
        cmd_create_class(classes, instructors, next_class_id);
    }
    else if (command == "list" && words.size() >= 2 && words[1] == "students") {
        cmd_list_students(students);
    }
    else if (command == "list" && words.size() >= 2 && words[1] == "instructors") {
        cmd_list_instructors(instructors);
    }
    else if (command == "list" && words.size() >= 2 && words[1] == "classes") {
        cmd_list_classes(classes);
    }
    else if (command == "enroll") {
        if (words.size() != 3) {
            cout << "Usage: enroll <student_id> <class_id>\n";
        }
        else {
            cmd_enroll(classes, students, words[1], words[2]);
        }
    }
    else if (command == "show" && words.size() >= 2 && words[1] == "class") {
        if (words.size() != 3) {
            cout << "Usage: show class <class_id>\n";
        }
        else {
            cmd_show_class(classes, students, words[2]);
        }
    }
    else {
        cout << "Error: unknown command '" << line
             << "'. Type 'help' to see the available commands.\n";
    }

    return true;
}

void run_command_loop(
    vector<Student>& students,
    vector<Instructor>& instructors,
    vector<Class>& classes,
    int& next_student_id,
    int& next_instructor_id,
    int& next_class_id
) {
    string line;

    while (true) {
        cout << "sms> ";

        if (!getline(cin, line)) {
            break;
        }

        line = trim(line);

        vector<string> words = parse_command(line);

        bool should_continue = execute_command(
            words,
            line,
            students,
            instructors,
            classes,
            next_student_id,
            next_instructor_id,
            next_class_id
        );

        if (!should_continue) {
            break;
        }
    }
}

int main() {
	vector<Student> students;
	vector<Instructor> instructors;
	vector<Class> classes;
	int next_student_id = 1;
	int next_instructor_id = 1;
	int next_class_id = 1;

	print_welcome();
	run_command_loop(
		students,
		instructors,
		classes,
		next_student_id,
		next_instructor_id,
		next_class_id
	);
	return 0;
}

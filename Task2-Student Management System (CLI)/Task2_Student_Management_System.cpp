#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
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

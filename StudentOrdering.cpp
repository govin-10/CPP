#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <stdexcept>

struct Student {
    int id;
    std::string name;
    std::string date_birth;
    int roll_no;
    std::string department;
    std::string address;
    int age;

    void calculate_age() {
        int day, month, year;
        char delimiter;
        std::istringstream date_stream(date_birth);
        date_stream >> day >> delimiter >> month >> delimiter >> year;

        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        int current_year = now->tm_year + 1900;
        int current_month = now->tm_mon + 1;
        int current_day = now->tm_mday;

        age = current_year - year;
        if (current_month < month || (current_month == month && current_day < day)) {
            age--;
        }
    }
};

std::vector<Student> read_csv(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        Student student;
        std::string field;

        try {
            std::getline(line_stream, field, ',');
            student.id = std::stoi(field);
            std::getline(line_stream, student.name, ',');
            std::getline(line_stream, student.date_birth, ',');
            std::getline(line_stream, field, ',');
            student.roll_no = std::stoi(field);
            std::getline(line_stream, student.department, ',');
            std::getline(line_stream, student.address, ',');

            student.calculate_age();
            students.push_back(student);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << " in line: " << line << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << " in line: " << line << std::endl;
        }
    }

    return students;
}

void write_csv(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream file(filename);

    for (const auto& student : students) {
        file << student.id << ","
             << student.name << ","
             << student.date_birth << ","
             << student.roll_no << ","
             << student.department << ","
             << student.address << "\n";
    }
}

bool compare_by_name(const Student& a, const Student& b) {
    return a.name < b.name;
}

bool compare_by_age(const Student& a, const Student& b) {
    return a.age < b.age;
}

int main() {
    std::string input_filename = "students.csv";
    std::vector<Student> students = read_csv(input_filename);

    std::vector<Student> students_by_name = students;
    std::sort(students_by_name.begin(), students_by_name.end(), compare_by_name);
    write_csv("sorted_by_name.csv", students_by_name);

    std::vector<Student> students_by_age = students;
    std::sort(students_by_age.begin(), students_by_age.end(), compare_by_age);
    write_csv("sorted_by_age.csv", students_by_age);

    std::cout << "CSV files have been generated." << std::endl;
    return 0;
}

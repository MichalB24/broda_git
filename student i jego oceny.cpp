#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Student {
    string name;
    vector<int> grades;
    double average_grade;
};

int main() {
    // otwarcie pliku do odczytu
    ifstream input_file("oceny.txt");

    // otwarcie pliku do zapisu
    ofstream output_file("wyniki.txt");

    // sprawdzenie, czy plik zosta³ otwarty poprawnie
    if (!input_file.is_open()) {
        cout << "Blad: Nie udalo sie otworzyc pliku do odczytu." << endl;
        return 1;
    }

    if (!output_file.is_open()) {
        cout << "Blad: Nie udalo sie otworzyc pliku do zapisu." << endl;
        return 1;
    }

    // wektor przechowuj¹cy dane studentów
    vector<Student> students;

    // odczytanie danych z pliku
    string line;
    while (getline(input_file, line)) {
        // rozdzielenie linii na imiê studenta i oceny
        string name = line.substr(0, line.find(":"));
        string grades_str = line.substr(line.find(":") + 1);

        // konwersja ocen z postaci tekstowej na liczbow¹
        vector<int> grades;
        int grade;
        stringstream grades_stream(grades_str);
        while (grades_stream >> grade) {
            // sprawdzenie, czy ocena mieœci siê w zakresie 1-6
            if (grade < 1 || grade > 6) {
                cout << "Blad: Nieprawidlowa ocena dla studenta " << name << endl;
                return 1;
            }

            grades.push_back(grade);
        }

        // dodanie danych studenta do wektora
        students.push_back({name, grades});
    }

    // obliczenie œrednich ocen dla ka¿dego studenta
    for (auto& student : students) {
        double sum = 0.0;
        for (auto grade : student.grades) {
            sum += grade;
        }
        student.average_grade = sum / student.grades.size();
    }

    // zapisanie wyników do pliku
    for (auto& student : students) {
        output_file << student.name << ":";
        for (auto grade : student.grades) {
            output_file << " " << grade;
        }
        output_file << " (srednia: " << fixed << setprecision(2) << student.average_grade << ")" << endl;
    }

    // zamkniêcie plików
    input_file.close();
    output_file.close();

    cout << "Wyniki zostaly zapisane do pliku wyniki.txt" << endl;

    return 0;
}

/*
TITLE: Department maintains a student information. The file contains roll number, name, division
and address. Allow user to add, delete information of student. Display information of particular
employee. If record of student does not exist an appropriate message is displayed. If it is, then the
system displays the student details. Use sequential file to main the data.
*/

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class tel {
public:
    int rollNo;
    char name[20];
    char div;
    char address[50];

    void accept() {
        cout << "\n\tEnter Roll Number : ";
        cin >> rollNo;
        cin.ignore(); // To consume newline character left in buffer
        cout << "\n\tEnter the Name : ";
        cin.getline(name, 20);
        cout << "\n\tEnter the Division: ";
        cin >> div;
        cout << "\n\tEnter the Address: ";
        cin.ignore(); // To consume newline character left in buffer
        cin.getline(address, 50);
    }

    void show() {
        cout << "\n\t" << rollNo << "\t\t" << name << "\t\t" << div << "\t\t" << address;
    }

    int getRollNo() {
        return rollNo;
    }
};

int main() {
    int ch, rec;
    tel t1;
    fstream file;

    do {
        cout << "\n>>>>>>>>>>>>>>>>>>>>>> MENU <<<<<<<<<<<<<<<<<<<<";
        cout << "\n1. Insert and overwrite\n2. Show\n3. Search & Edit (number)\n4. Search & Edit (name)\n5. Delete a Student Record\n6. Exit";
        cout << "\nEnter the Choice: ";
        cin >> ch;

        switch(ch) {
            case 1:
                {
                    file.open("StuRecord.txt", ios::out | ios::trunc);
                    if (!file.is_open()) {
                        cout << "Error opening file!";
                        break;
                    }

                    char choice;
                    do {
                        t1.accept();
                        file.write(reinterpret_cast<char*>(&t1), sizeof(t1));
                        cout << "\nDo you want to enter more records? (y/n): ";
                        cin >> choice;
                    } while (choice == 'y' || choice == 'Y');

                    file.close();
                    break;
                }

            case 2:
                {
                    file.open("StuRecord.txt", ios::in);
                    if (!file.is_open()) {
                        cout << "Error opening file!";
                        break;
                    }

                    while (file.read(reinterpret_cast<char*>(&t1), sizeof(t1))) {
                        t1.show();
                    }

                    file.close();
                    break;
                }

            case 3:
                {
                    cout << "\nEnter the roll number you want to find: ";
                    cin >> rec;
                    file.open("StuRecord.txt", ios::in | ios::out);
                    if (!file.is_open()) {
                        cout << "Error opening file!";
                        break;
                    }

                    bool found = false;
                    while (file.read(reinterpret_cast<char*>(&t1), sizeof(t1))) {
                        if (rec == t1.rollNo) {
                            cout << "\nRecord found";
                            long pos = static_cast<long>(file.tellg()) - sizeof(t1);
                            file.seekg(pos);
                            t1.accept();
                            file.seekp(pos);
                            file.write(reinterpret_cast<char*>(&t1), sizeof(t1));
                            found = true;
                            break;
                        }
                    }
                    file.close();
                    if (!found) {
                        cout << "\nRecord not found";
                    }
                    break;
                }

            case 4:
                {
                    char name[20];
                    cout << "\nEnter the name you want to find and edit: ";
                    cin.ignore(); // To consume newline character left in buffer
                    cin.getline(name, 20);

                    file.open("StuRecord.txt", ios::in | ios::out);
                    if (!file.is_open()) {
                        cout << "Error opening file!";
                        break;
                    }

                    while (file.read(reinterpret_cast<char*>(&t1), sizeof(t1))) {
                        if (strcmp(name, t1.name) == 0) {
                            cout << "\nName found";
                            long pos = file.tellg() - sizeof(t1);
                            file.seekp(pos);
                            t1.accept();
                            file.write(reinterpret_cast<char*>(&t1), sizeof(t1));
                            break;
                        }
                    }

                    if (file.eof()) {
                        cout << "\nRecord not found";
                    }

                    file.close();
                    break;
                }

            case 5:
                {
                    int roll;
                    cout << "Please Enter the Roll No. of Student Whose Info You Want to Delete: ";
                    cin >> roll;

                    file.open("StuRecord.txt", ios::in);
                    ofstream fout("temp.txt", ios::out);
                    if (!file.is_open() || !fout.is_open()) {
                        cout << "Error opening file!";
                        break;
                    }

                    bool found = false;
                    while (file.read(reinterpret_cast<char*>(&t1), sizeof(t1))) {
                        if (t1.getRollNo() != roll) {
                            fout.write(reinterpret_cast<char*>(&t1), sizeof(t1));
                        } else {
                            found = true;
                        }
                    }

                    if (!found) {
                        cout << "The record with the roll no. " << roll << " was not found";
                    } else {
                        cout << "The record with the roll no. " << roll << " has been deleted";
                    }

                    file.close();
                    fout.close();
                    remove("StuRecord.txt");
                    rename("temp.txt", "StuRecord.txt");

                    break;
                }

            case 6:
                cout << "\nThank you";
                break;

            default:
                cout << "\nInvalid choice!";
                break;
        }

    } while (ch != 6);

    return 0;
}

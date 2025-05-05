#include <bits/stdc++.h>
#include <fstream>
using namespace std;

class Student
{
    string name, address;
    int rollNo, division;

public:
    void getData()
    {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Division: ";
        cin >> division;
        cin.ignore();

        cout << "Enter Address: ";
        getline(cin, address);
    }

    void addRecord()
    {
        ofstream file("record.txt", ios::app);
        getData();

        file << "Name: " << name << endl;
        file << "Roll: " << rollNo << endl;
        file << "Division: " << division << endl;
        file << "Address: " << address << endl;
        file << endl;

        file.close();
        cout << "Student record added successfully!" << endl;
    }

    void displayAllRecords()
    {
        ifstream file("record.txt");
        string line;
        bool anyRecord = false;

        cout << "\n----- All Student Records -----\n";
        while (getline(file, line))
        {
            anyRecord = true;
            cout << line << endl;
        }

        file.close();

        if (!anyRecord)
        {
            cout << "No student records found." << endl;
        }
    }

    void displayRecord(int searchRollNo)
    {
        ifstream file("record.txt");
        string line, rollLine;
        bool found = false;

        string search = "Roll: " + to_string(searchRollNo);

        while (getline(file, line))
        {
            cout << line << endl;
            if (line.rfind("Roll: ", 0) == 0)
            {
                rollLine = line;
                if (rollLine == search)
                    found = true;
                else
                    found = false;
            }

            if (line.empty() && found)
                break;
        }

        file.close();

        if (!found)
            cout << "Student record not found!" << endl;
    }

    void deleteRecord(int deleteRollNo)
    {
        ifstream fin("record.txt");
        ofstream fout("temp.txt");

        string line, block[5];
        bool found = false;
        string target = "Roll: " + to_string(deleteRollNo);

        while (getline(fin, block[0]))
        {
            getline(fin, block[1]);
            getline(fin, block[2]);
            getline(fin, block[3]);
            getline(fin, block[4]);

            if (block[1] == target)
            {
                found = true;
                continue;
            }

            for (int i = 0; i < 5; i++)
                fout << block[i] << endl;
        }

        fin.close();
        fout.close();

        remove("record.txt");
        rename("temp.txt", "record.txt");

        if (found)
            cout << "Student record deleted successfully!" << endl;
        else
            cout << "Student record not found!" << endl;
    }

    void updateRecord(int updateRollNo)
    {
        ifstream fin("record.txt");
        ofstream fout("temp.txt");

        string line, block[5];
        bool found = false;
        string target = "Roll: " + to_string(updateRollNo);

        while (getline(fin, block[0]))
        {
            getline(fin, block[1]);
            getline(fin, block[2]);
            getline(fin, block[3]);
            getline(fin, block[4]);

            if (block[1] == target)
            {
                found = true;
                cout << "Existing record found. Enter new details:\n";
                getData();
                fout << "Name: " << name << endl;
                fout << "Roll: " << rollNo << endl;
                fout << "Division: " << division << endl;
                fout << "Address: " << address << endl;
                fout << endl;
            }
            else
            {
                for (int i = 0; i < 5; ++i)
                {
                    fout << block[i] << endl;
                }
            }
        }

        fin.close();
        fout.close();

        remove("record.txt");
        rename("temp.txt", "record.txt");

        if (found)
            cout << "Student record updated successfully!" << endl;
        else
            cout << "Student record not found!" << endl;
    }
};

int main()
{
    Student student;
    int choice, roll;

    do
    {
        cout << "\n----- Student Management System -----" << endl;
        cout << "1. Add Student Record" << endl;
        cout << "2. Display Student Record by Roll No" << endl;
        cout << "3. Delete Student Record" << endl;
        cout << "4. Update Student Record" << endl;
        cout << "5. Display All Student Records" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
            student.addRecord();
            break;

        case 2:
            cout << "Enter Roll No to display: ";
            cin >> roll;
            student.displayRecord(roll);
            break;

        case 3:
            cout << "Enter Roll No to delete: ";
            cin >> roll;
            student.deleteRecord(roll);
            break;

        case 4:
            cout << "Enter Roll No to update: ";
            cin >> roll;
            student.updateRecord(roll);
            break;

        case 5:
            student.displayAllRecords();
            break;

        case 6:
            cout << "Exiting Program." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

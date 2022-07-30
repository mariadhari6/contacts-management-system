#include <iostream>
// #include <conio.h>
#include <fstream>

using namespace std;
class contact
{
private:
    char firstName[50], lastName[50], address[50], email[50];
    long long phone;

public:
    void createContact()
    {
        cout << "Enter your first name: ";
        cin >> firstName;

        cout << "Enter your last name: ";
        cin >> lastName;

        cout << "Enter your phone number: ";
        cin >> phone;

        cout << "Enter address: ";
        cin >> address;

        cout << "Enter email: ";
        cin >> email;
    }
    void showContact()
    {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "Phone: " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
    }
    void writeOnFile()
    {
        char ch;
        ofstream f1;
        f1.open("contacts.dat", ios::binary | ios::app);

        do
        {
            createContact();
            f1.write(reinterpret_cast<char *>(this), sizeof(*this));
            cout << "Dou you have next data to save?(y/n) ";
            cin >> ch;
        } while (ch == 'y');
        cout << "Contact has been successfully created.." << endl;
        f1.close();
    }
    void readFromFile()
    {
        ifstream f2;
        f2.open("contacts.dat", ios::binary | ios::app);

        cout << "\n============================================\n";
        cout << "LIST OF CONTACTS";
        cout << "\n============================================\n";

        while (!f2.eof())
        {
            if (f2.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                showContact();
                cout << "\n============================================\n";
            }
        }
        f2.close();
    }
    void searchOnFile()
    {
        ifstream f3;
        long long phone_number;
        cout << "Enter phone number: ";
        cin >> phone_number;
        f3.open("contacts.dat", ios::binary);

        while (!f3.eof())
        {
            if (f3.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                if (phone_number == phone)
                {
                    showContact();
                    return;
                }
            }
        }
        cout << "\n\nNo record found";
        f3.close();
    }
    void deleteFromFile()
    {
        long long phone_number;
        int flag = 0;
        ofstream f4;
        ifstream f5;

        f5.open("contacts.dat", ios::binary);
        f4.open("temp.dat", ios::binary);

        cout << "Enter phone number to delete: ";
        cin >> phone_number;
        while (!f5.eof())
        {
            if (f5.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                if (phone != phone_number)
                {
                    f4.write(reinterpret_cast<char *>(this), sizeof(*this));
                }
                else
                {
                    flag = 1;
                }
            }
        }
        f5.close();
        f4.close();
        remove("contacts.dat");
        rename("temp.dat", "contacts.dat");
        flag == 1 ? cout << "\tContact deleted..." : cout << "\tContact not found...";
    }
    void editContact()
    {
        long long phone_number;
        fstream f6;

        cout << "Edit contact";
        cout << "\n============================================\n";
        cout << "Enter the phone number to be edit: ";
        cin >> phone_number;

        f6.open("contacts.dat", ios::binary | ios::out | ios::in);
        while (!f6.eof())
        {
            if (f6.read(reinterpret_cast<char *>(this), sizeof(*this)))
            {
                if (phone == phone_number)
                {
                    cout << "Enter new record\n";
                    createContact();

                    long pos = -1 * sizeof(*this);
                    f6.seekp(pos, ios::cur);
                    f6.write(reinterpret_cast<char *>(this), sizeof(*this));
                    cout << endl
                         << endl
                         << "\tContact successfully updated...";
                    return;
                }
            }
        }
        cout << "\n\nNo record found";
        f6.close();
    }
};
int main()
{
    system("clear");
    cout << "\n\n\n\n\n\n\t * WELCOME TO THE CONTACT MANAGEMENT SYSTEM *";
    getchar();
    while (1)
    {
        contact myContact;
        int choice;

        cout << "\nCONTACT MANAGEMENT SYSTEM";
        cout << "\n\nMAIN MENU";
        cout << "\n============================================\n";
        cout << "[1] Add new contact\n";
        cout << "[2] List all contacts\n";
        cout << "[3] Search for contact\n";
        cout << "[4] Delete a contact\n";
        cout << "[5] Edit a contact\n";
        cout << "[0] Exit";
        cout << "\n============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 0)
        {
            system("clear");
            cout << "\n\n\n\t\tThank you for using this app." << endl
                 << endl;
            break;
        }
        else if (choice == 1)
        {
            system("clear");
            myContact.writeOnFile();
        }
        else if (choice == 2)
        {
            system("clear");
            myContact.readFromFile();
        }
        else if (choice == 3)
        {
            system("clear");
            myContact.searchOnFile();
        }
        else if (choice == 4)
        {
            system("clear");
            myContact.deleteFromFile();
        }
        else if (choice == 5)
        {
            system("clear");
            myContact.editContact();
        }
        else
        {
            system("clear");
            continue;
        }
        cout << "\n\n..::Enter the choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "\n\n\n\t\tThank you for using this app." << endl
                 << endl;
            exit(0);
            break;
        default:
            system("clear");
            continue;
        }
    }

    return 0;
}
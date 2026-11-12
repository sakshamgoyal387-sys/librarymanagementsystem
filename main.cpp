#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// ===============================
// BASE CLASS
// ===============================

class Person
{
protected:
    string id;
    string name;

public:
    Person(string i, string n)
    {
        id = i;
        name = n;
    }

    virtual void displayRole()
    {
        cout << "Name: " << name << endl;
    }

    string getID()
    {
        return id;
    }

    string getName()
    {
        return name;
    }
};

// ===============================
// STUDENT CLASS
// ===============================

class Student : public Person
{
public:
    Student(string i, string n) : Person(i, n) {}

    void displayRole()
    {
        cout << "\nStudent: " << name << endl;
        cout << "Student ID: " << id << endl;
    }
};

// ===============================
// ADMIN CLASS
// ===============================

class Admin : public Person
{
public:
    Admin(string i, string n) : Person(i, n) {}

    void displayRole()
    {
        cout << "\nAdministrator: " << name << endl;
    }
};

// ===============================
// BOOK CLASS
// ===============================

class Book
{
private:
    string id;
    string title;
    string author;
    bool available;

public:
    Book(string i, string t, string a, bool status = true)
    {
        id = i;
        title = t;
        author = a;
        available = status;
    }

    string getID()
    {
        return id;
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    bool isAvailable()
    {
        return available;
    }

    void setTitle(string t)
    {
        title = t;
    }

    void setAuthor(string a)
    {
        author = a;
    }

    void setAvailability(bool status)
    {
        available = status;
    }

    void display()
    {
        cout << "\nBook ID: " << id;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: ";

        if (available)
            cout << "Available";
        else
            cout << "Issued";

        cout << "\n------------------------------\n";
    }
};

// ===============================
// ISSUE RECORD CLASS
// ===============================

class Issue
{
public:
    string bookID;
    string studentID;

    Issue(string b, string s)
    {
        bookID = b;
        studentID = s;
    }
};

// ===============================
// LIBRARY CLASS
// ===============================

class Library
{
private:
    vector<Book> books;
    vector<Student> students;
    vector<Issue> issues;

public:

    // Constructor
    Library()
    {
        loadData();

        // Add default books if inventory is empty
        if (books.empty())
        {
            addDefaultBooks();
            saveBooks();
        }
    }

    // ===========================
    // DEFAULT BOOKS
    // ===========================

    void addDefaultBooks()
    {
        books.push_back(Book("B101", "Vinland Saga",
                             "Makoto Yukimura"));

        books.push_back(Book("B102", "Violet Evergarden",
                             "Kana Akatsuki"));

        books.push_back(Book("B103", "One Piece",
                             "Eiichiro Oda"));

        books.push_back(Book("B104", "Attack on Titan",
                             "Hajime Isayama"));

        books.push_back(Book("B105", "Twilight",
                             "Stephenie Meyer"));

        books.push_back(Book("B106", "Rich Dad Poor Dad",
                             "Robert Kiyosaki"));

        books.push_back(Book("B107", "Diary of a Wimpy Kid",
                             "Jeff Kinney"));

        books.push_back(Book("B108", "Diary of a Young Girl",
                             "Anne Frank"));

        books.push_back(Book("B109", "Harry Potter Series",
                             "J.K. Rowling"));

        books.push_back(Book("B110", "Pride and Prejudice",
                             "Jane Austen"));
    }

    // ===========================
    // SAVE DATA
    // ===========================

    void saveBooks()
    {
        ofstream file("books.txt");

        for (int i = 0; i < books.size(); i++)
        {
            file << books[i].getID() << "|"
                 << books[i].getTitle() << "|"
                 << books[i].getAuthor() << "|"
                 << books[i].isAvailable() << endl;
        }

        file.close();
    }

    void saveStudents()
    {
        ofstream file("students.txt");

        for (int i = 0; i < students.size(); i++)
        {
            file << students[i].getID() << "|"
                 << students[i].getName() << endl;
        }

        file.close();
    }

    void saveIssues()
    {
        ofstream file("issues.txt");

        for (int i = 0; i < issues.size(); i++)
        {
            file << issues[i].bookID << "|"
                 << issues[i].studentID << endl;
        }

        file.close();
    }

    // ===========================
    // LOAD DATA
    // ===========================

    void loadData()
    {
        string line, id, title, author, status;

        ifstream file1("books.txt");

        while (getline(file1, line))
        {
            int p1 = line.find('|');
            int p2 = line.find('|', p1 + 1);
            int p3 = line.find('|', p2 + 1);

            if (p1 == -1 || p2 == -1 || p3 == -1)
                continue;

            id = line.substr(0, p1);
            title = line.substr(p1 + 1, p2 - p1 - 1);
            author = line.substr(p2 + 1, p3 - p2 - 1);
            status = line.substr(p3 + 1);

            books.push_back(Book(id, title, author,
                                 status == "1"));
        }

        file1.close();

        ifstream file2("students.txt");

        while (getline(file2, line))
        {
            int p = line.find('|');

            if (p == -1)
                continue;

            id = line.substr(0, p);
            title = line.substr(p + 1);

            students.push_back(Student(id, title));
        }

        file2.close();

        ifstream file3("issues.txt");

        while (getline(file3, line))
        {
            int p = line.find('|');

            if (p == -1)
                continue;

            id = line.substr(0, p);
            title = line.substr(p + 1);

            issues.push_back(Issue(id, title));
        }

        file3.close();
    }

    // ===========================
    // FIND BOOK
    // ===========================

    int findBook(string id)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getID() == id)
                return i;
        }

        return -1;
    }

    // ===========================
    // FIND STUDENT
    // ===========================

    int findStudent(string id)
    {
        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].getID() == id)
                return i;
        }

        return -1;
    }

    // ===========================
    // ADD BOOK
    // ===========================

    void addBook()
    {
        string id, title, author;

        cout << "\nEnter Book ID: ";
        getline(cin, id);

        if (findBook(id) != -1)
        {
            cout << "Book ID already exists!\n";
            return;
        }

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        if (title.empty() || author.empty())
        {
            cout << "Details cannot be empty!\n";
            return;
        }

        books.push_back(Book(id, title, author));

        saveBooks();

        cout << "\nBook added successfully!\n";
    }

    // ===========================
    // DISPLAY BOOKS
    // ===========================

    void displayBooks()
    {
        cout << "\n========== BOOK INVENTORY ==========\n";

        if (books.empty())
        {
            cout << "No books available.\n";
            return;
        }

        for (int i = 0; i < books.size(); i++)
        {
            books[i].display();
        }
    }

    // ===========================
    // SEARCH BOOK
    // ===========================

    void searchBook()
    {
        string search;
        bool found = false;

        cout << "\nEnter Book ID or Title: ";
        getline(cin, search);

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getID() == search ||
                books[i].getTitle().find(search) != string::npos)
            {
                books[i].display();
                found = true;
            }
        }

        if (!found)
            cout << "\nBook not found!\n";
    }

    // ===========================
    // UPDATE BOOK
    // ===========================

    void updateBook()
    {
        string id, title, author;

        cout << "\nEnter Book ID to update: ";
        getline(cin, id);

        int index = findBook(id);

        if (index == -1)
        {
            cout << "Book not found!\n";
            return;
        }

        cout << "Enter New Title: ";
        getline(cin, title);

        cout << "Enter New Author: ";
        getline(cin, author);

        if (title.empty() || author.empty())
        {
            cout << "Details cannot be empty!\n";
            return;
        }

        books[index].setTitle(title);
        books[index].setAuthor(author);

        saveBooks();

        cout << "\nBook updated successfully!\n";
    }

    // ===========================
    // DELETE BOOK
    // ===========================

    void deleteBook()
    {
        string id;

        cout << "\nEnter Book ID to delete: ";
        getline(cin, id);

        int index = findBook(id);

        if (index == -1)
        {
            cout << "Book not found!\n";
            return;
        }

        if (!books[index].isAvailable())
        {
            cout << "Cannot delete an issued book!\n";
            return;
        }

        books.erase(books.begin() + index);

        saveBooks();

        cout << "\nBook deleted successfully!\n";
    }

    // ===========================
    // REGISTER STUDENT
    // ===========================

    void registerStudent()
    {
        string id, name;

        cout << "\nEnter Student ID: ";
        getline(cin, id);

        if (findStudent(id) != -1)
        {
            cout << "Student already registered!\n";
            return;
        }

        cout << "Enter Student Name: ";
        getline(cin, name);

        if (name.empty())
        {
            cout << "Name cannot be empty!\n";
            return;
        }

        students.push_back(Student(id, name));

        saveStudents();

        cout << "\nStudent registered successfully!\n";
    }

    // ===========================
    // DISPLAY STUDENTS
    // ===========================

    void displayStudents()
    {
        cout << "\n========== STUDENT RECORDS ==========\n";

        if (students.empty())
        {
            cout << "No students registered.\n";
            return;
        }

        for (int i = 0; i < students.size(); i++)
        {
            cout << "\nStudent ID: " << students[i].getID();
            cout << "\nName: " << students[i].getName();
            cout << "\n------------------------------\n";
        }
    }

    // ===========================
    // ISSUE BOOK
    // ===========================

    void issueBook(string studentID)
    {
        string bookID;

        cout << "\nEnter Book ID to issue: ";
        getline(cin, bookID);

        int index = findBook(bookID);

        if (index == -1)
        {
            cout << "Book not found!\n";
            return;
        }

        if (!books[index].isAvailable())
        {
            cout << "This book is already issued!\n";
            return;
        }

        books[index].setAvailability(false);

        issues.push_back(Issue(bookID, studentID));

        saveBooks();
        saveIssues();

        cout << "\nBook issued successfully!\n";
    }

    // ===========================
    // RETURN BOOK
    // ===========================

    void returnBook(string studentID)
    {
        string bookID;

        cout << "\nEnter Book ID to return: ";
        getline(cin, bookID);

        for (int i = 0; i < issues.size(); i++)
        {
            if (issues[i].bookID == bookID &&
                issues[i].studentID == studentID)
            {
                int index = findBook(bookID);

                if (index != -1)
                    books[index].setAvailability(true);

                issues.erase(issues.begin() + i);

                saveBooks();
                saveIssues();

                cout << "\nBook returned successfully!\n";
                return;
            }
        }

        cout << "No matching issued book found!\n";
    }

    // ===========================
    // DISPLAY ISSUED BOOKS
    // ===========================

    void displayIssuedBooks()
    {
        cout << "\n========== ISSUED BOOKS ==========\n";

        if (issues.empty())
        {
            cout << "No books are currently issued.\n";
            return;
        }

        for (int i = 0; i < issues.size(); i++)
        {
            cout << "\nBook ID: " << issues[i].bookID;
            cout << "\nStudent ID: " << issues[i].studentID;
            cout << "\n------------------------------\n";
        }
    }

    // ===========================
    // DISPLAY MY BOOKS
    // ===========================

    void displayMyBooks(string studentID)
    {
        bool found = false;

        cout << "\n========== MY ISSUED BOOKS ==========\n";

        for (int i = 0; i < issues.size(); i++)
        {
            if (issues[i].studentID == studentID)
            {
                int index = findBook(issues[i].bookID);

                if (index != -1)
                {
                    books[index].display();
                    found = true;
                }
            }
        }

        if (!found)
            cout << "You have no issued books.\n";
    }

    // ===========================
    // STUDENT LOGIN
    // ===========================

    bool studentLogin(string id)
    {
        int index = findStudent(id);

        if (index == -1)
            return false;

        Student s = students[index];

        Person *p = &s;
        p->displayRole();

        return true;
    }
};

// ===============================
// ADMIN MENU
// ===============================

void adminMenu(Library &lib)
{
    Admin admin("A001", "Administrator");

    Person *p = &admin;
    p->displayRole();

    int choice;

    do
    {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Update Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Register Student\n";
        cout << "7. Display Students\n";
        cout << "8. Display Issued Books\n";
        cout << "9. Logout\n";

        cout << "\nEnter Choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.updateBook(); break;
            case 5: lib.deleteBook(); break;
            case 6: lib.registerStudent(); break;
            case 7: lib.displayStudents(); break;
            case 8: lib.displayIssuedBooks(); break;
            case 9: cout << "Logged out successfully!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 9);
}

// ===============================
// STUDENT MENU
// ===============================

void studentMenu(Library &lib)
{
    int choice;
    string id;

    cout << "\n========== STUDENT PORTAL ==========\n";
    cout << "1. Register New Student\n";
    cout << "2. Student Login\n";

    cout << "\nEnter Choice: ";

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 1)
    {
        lib.registerStudent();
        return;
    }

    if (choice != 2)
    {
        cout << "Invalid choice!\n";
        return;
    }

    cout << "Enter Student ID: ";
    getline(cin, id);

    if (!lib.studentLogin(id))
    {
        cout << "Student not found! Please register first.\n";
        return;
    }

    do
    {
        cout << "\n========== STUDENT MENU ==========\n";
        cout << "1. View All Books\n";
        cout << "2. Search Book\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. View My Issued Books\n";
        cout << "6. Logout\n";

        cout << "\nEnter Choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1: lib.displayBooks(); break;
            case 2: lib.searchBook(); break;
            case 3: lib.issueBook(id); break;
            case 4: lib.returnBook(id); break;
            case 5: lib.displayMyBooks(id); break;
            case 6: cout << "Logged out successfully!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);
}

// ===============================
// MAIN FUNCTION
// ===============================

int main()
{
    Library lib;

    int choice;

    cout << "\n";
    cout << "========================================\n";
    cout << "       LIBRARY MANAGEMENT SYSTEM        \n";
    cout << "========================================\n";

    do
    {
        cout << "\n=============== MAIN MENU ===============\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Portal\n";
        cout << "3. Exit\n";

        cout << "\nEnter Choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
            case 1:
            {
                string password;

                cout << "Enter Admin Password: ";
                getline(cin, password);

                if (password == "admin123")
                {
                    cout << "\nLogin Successful!\n";
                    adminMenu(lib);
                }
                else
                {
                    cout << "\nIncorrect Password!\n";
                }

                break;
            }

            case 2:
                studentMenu(lib);
                break;

            case 3:
                cout << "\nThank you for using the Library Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
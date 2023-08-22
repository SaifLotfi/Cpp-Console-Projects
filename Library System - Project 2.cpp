
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>
#include <map>
using namespace std;
void print_the_list()
{
    cout << "1)Add book" << endl;
    cout << "2)Search book by Prefix" << endl;
    cout << "3)Pring Who borrowed book by name" << endl;
    cout << "4)Print library by id" << endl;
    cout << "5)Print library by Name" << endl;
    cout << "6)Add User" << endl;
    cout << "7)User borrow book" << endl;
    cout << "8)User Return book" << endl;
    cout << "9)Print Users" << endl;
    cout << "10)Exit" << endl;
}
struct book
{
    int id;
    string name;
    int q;
    int borrowed;
    vector <string> borrowers;
};
struct user
{
    string name;
    int id;
    vector <string> borrowedBooks;
};
bool cmpId(book &a,book &b)
{return a.id <= b.id; }
bool cmpName(book& a, book& b)
{return a.name <= b.name;}
bool compareByNameForUsers(user& a, user& b)
{
    return a.name <= b.name;
}
vector <book> books;
map<string, vector<string>> prefix;
void storingPrefix(string str)
{
    string pieces = "";
    for (auto item : str)
    {
        pieces += item;
        prefix[pieces].push_back(str);
    }
}
void addbook()
{
    int id; string name; int q;
    cout << "Enter id , name ,q : ";
    cin >> id >> name >> q;
    books.push_back ({ id, name, q,0 });
    storingPrefix(name);
}
void printById()
{
    
    sort(books.begin(), books.end(), cmpId);
    for (auto item : books)
    {
        cout << "Id = " << item.id << " Name : " << item.name << " Quantity = " << item.q <<" Borrowed = "<<item.borrowed<< endl;
    }
}
void printByName()
{
    
    sort(books.begin(), books.end(), cmpName);
    for (auto item : books)
    {
        cout << "Id = " << item.id << " Name : " << item.name << " Quantity = " << item.q << " Borrowed = " << item.borrowed << endl;
    }
}
void SearchByPrefix()
{
    string pre;
    cout << "Enter Prefix : ";
    cin >> pre;
    for (auto item : prefix[pre])
    {
        cout << item << endl;
    }
}
vector <user> Users;
void addUser()
{
    cout << "Enter User Name & Id : ";
    string name; 
    int NId;
    cin >> name >> NId;
    Users.push_back({name,NId});
}
void userBorrowsABook()
{
    string Uname;  string Bname;
    cout << "Enter User Name & Book Name : ";
    cin >> Uname >> Bname;
    bool flag = false;
    for (auto &item : books)
    {
        if (item.name == Bname)
        {
            item.borrowed=item.borrowed+1;
            
            item.q=item.q-1;
            item.borrowers.push_back(Uname);
            flag = true;
            break;
        }
    }
    if (!flag)
        cout << "No matched Book found" << endl;
    
    flag = false;

    for (auto &item : Users)
    {
        if (item.name == Uname)
        {
            item.borrowedBooks.push_back(Bname);
            flag = true;
            break;
        }
    }
    if (!flag)
        cout << "No matched user found" << endl;

}
void userReturnsABook()
{
    string Uname;
    string Bname;
    cout << "Enter User & Book Names : ";
    cin >> Uname >> Bname;
    bool flag = false;
    bool userflag = false;
    for (auto &item : Users)
    {
        if (item.name == Uname)
        {
            userflag = true;
            for (int i = 0; i < item.borrowedBooks.size(); ++i)
            {
                if (item.borrowedBooks[i] == Bname)
                {
                    item.borrowedBooks.erase(item.borrowedBooks.begin() + i);
                    flag = true;
                    break;
                }
            }

        }
    }
    if (!userflag)
    {
        cout << "No User with such name is found!" << endl;
        return;
    }

    
    if (flag)
    {
        for (auto &book : books)
        {
            if (book.name == Bname)
            {
                book.q++;
                book.borrowed--;
                for (int i = 0; i < book.borrowers.size(); ++i)
                {
                    if (book.borrowers[i] == Uname)
                    {
                        book.borrowers.erase(book.borrowers.begin() + i);
                    }
                }
                break;
            }
        }
    }
    else
    {
        cout << "No such book is borrowed yet!" << endl;
    }
    

}
void printWhoBorrowedBookByName()
{
    string bookName;
    cout << "Enter BookName : ";
    cin >> bookName;
    bool flag = false;
    for (auto &book : books)
    {
        if (book.name == bookName)
        {
            flag = true;
            if (book.borrowers.size() == 0)
            {
                cout << "No borrowers yet !" << endl;
                break;
            }

            for (auto &borrower : book.borrowers)
                cout << borrower << endl;
        }
    }
    if (!flag)
        cout << "Book name Incorroect!" << endl;
}
void printUsers()
{
    for (auto &user : Users)
    {
        cout << "User (" << user.name << " , " << user.id << ")" << "Borrowed Books : ";
        for (auto &book : user.borrowedBooks)
        {
            cout << book;
        }
        cout << endl;
    }
}
void looping_program_starting()
{
    bool continuing = true;
    while (continuing)
    {
        print_the_list();
        cout << "Enter The No of Operation : ";
        int Operation_number;
        cin >> Operation_number;
        /*if (Operation_number > 10 || Operation_number < 1)
            continue;*/
        switch (Operation_number)
        {
        case 1:
            addbook();
            break;
        case 2:
            SearchByPrefix();
            break;
        case 3:
            printWhoBorrowedBookByName();
            break;
        case 4:
            printById();
            break;
        case 5:
            printByName();
            break;
        case 6:
            addUser();
            break;
        case 7:
            userBorrowsABook();
            break;
        case 8:
            userReturnsABook();
            break;
        case 9:
            printUsers();
            break;
        case 10:
            continuing = false;
            break;
        default:
            cout << "Wrong Input !" << endl;
            break;
        }
        cout << endl;
    }
}
int main()
{
    looping_program_starting();
}


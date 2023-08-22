#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <ctime>
using namespace std;
//// current date/time based on current system
//time_t now = time(0);
//
//// convert now to string form
//char* dt = ctime(&now);

int ReadInt(int low, int high) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;

	cin >> value;

	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return ReadInt(low, high);
}

int ShowReadMenu(const vector<string> &choices) {
	cout << "\nMenu:\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return ReadInt(1, choices.size());
}

//ToDo:-
//Next Step : Handeling Admin , Adding PreAdded Admins  => I think I will Put Admins with Normal Users
// 
// Thinking About Where to put the function : User/Admin/Book => functions and data for one item 
// Manger Classes => function and Data for All Items
//
//I was forced to move ViewProfile Function from user class to user manager class , Becuase It is UnReadable from System class => user_manager.getCurrentUser.ViewProfile() >> CE

class Book {
private : 
	int ISBN;
	string Title;
	string AuthorName;
	int NumberOfPages;
	map <int, string> PageAndContent;
	//int CurrentPage = 1;
public:
	Book() :ISBN(-1), NumberOfPages(-1) {

	}
	//Functions
	void PrintPageContent(int PageNumber) {
		cout << "Current Page " << PageNumber << "/" << PageAndContent.size()<<"\n";
		cout << PageAndContent[PageNumber] << "\n";
	}

	//getters & setters
	int getISBN() const{
		return ISBN;
	}
	/*int getCurrentPage()const {
		return CurrentPage;
	}*/
	int getNumberOfPages() const{
		return NumberOfPages;
	}
	 string getTitle()const {
		return Title;
	}
	 string getAuthorName()const {
		return AuthorName;
	}
	 map<int, string> getPagesAndContent() {
		return PageAndContent;
	}
	void setISBN(int ISBN) {
		this->ISBN = ISBN;
	}
	void setNumberOfPages(int NumberOfPages) {
		this->NumberOfPages = NumberOfPages;
	}
	void setTitle(const string &Title) {
		this->Title = Title;
	}
	void setAuthorName( const string& AuthorName) {
		this->AuthorName = AuthorName;
	}
	void setPagesAndContent( const map<int,string>&PagesAndContent) {
		this->PageAndContent = PagesAndContent;
	}
	/*void setCurrentPage(int CurrentPage) {
		this->CurrentPage = CurrentPage;
	}*/
};
class User {
private:
	string UserName;
	string PassWord;
	string name;
	string Email;
	//map<Book,int> BookAndPage;
	bool IsAdmin;
public:
	User() {
		IsAdmin = false;
	}
	//functions: 
	void ReadUser() {
		cout << "Enter UserName(NoSpaces): ";
		string str;
		cin >> str;
		setUserName(str);
		
		

		cout << "Enter password(NoSpaces): ";
		cin >> str;
		setPassWord(str);

		cout << "Enter name(NoSpaces): ";
		cin >> str;
		setName(str);

		cout << "Enter email(NoSpaces): ";
		cin >> str;
		setEmail(str);

	}
	void ViewProfile() {
		cout << "\nName: " << getName() << "\n";
		cout << "E-mail: " << getEmail() << "\n";
		cout << "UserName: " << getUserName() << "\n";
		cout << "\n";
	}
	void ShowWelcomeMessage() {
		cout << "\nHello " << getUserName() << " | ";
		if (getIsAdmin())
			cout << "Admin View\n";
		else
			cout << "User View\n";
		cout << "\n";
	}
	
	/*int ListReadingHistoryAndReturnBookAndPage() {
		return BookAndPage[ListReadingHistoryAndReturnBook()];
	}*/
	//setters & getters
	void setPassWord(const string & PassWord) {
		this->PassWord = PassWord;
	}
	void setUserName(const string& UserName) {
		this->UserName = UserName;
	}
	void setName(const string& name) {
		this->name = name;
	}
	void setEmail(const string& Email) {
		this->Email = Email;
	}
	/*void addBookAndPage( const Book& book , int PageNumber) {
		this->BookAndPage[book] = PageNumber;
	}*/
	 string getPassword() {
		return PassWord;
	}
	 string getUserName() {
		return UserName;
	}
	 string getName() {
		return name;
	}
	 string getEmail() {
		return Email;
	}
	void setIsAdmin(bool IsAdmin) {
		this->IsAdmin = IsAdmin;
	}
	bool getIsAdmin()const {
		return IsAdmin;
	}
	
	/* map<Book, int> getBookAndPage() {
		return BookAndPage;
	}*/
	/* pair<Book,int> ListReadingHistoryAndPrintBook() {
		int i = 1;
		map<int, Book> Fark;
		cout << "Your Book Reading History :\n";
		for (auto book : BookAndPage) {
			cout << i << ")" << book.first.getTitle() << " Page " << book.second << "/" << book.first.getNumberOfPages() << endl;
			Fark[i] = book.first;
			i++;
		}
		int BookNumber = ReadInt(1, i);
		Fark[BookNumber].PrintPageContent(BookAndPage[Fark[BookNumber]]);
		pair<Book, int> please = make_pair(Fark[BookNumber], BookAndPage[Fark[BookNumber]]);
		return please;
	}*/
};

class BookManager {
private:
	vector<Book> AvailableBooks;
	Book OpenedBook; //Didn't Think About it in Drawing time
	int OpenedPage = 1;
public:
	/*void setOpenedBookAndPage(User user) {
		pair<Book, int> PLEASE = user.ListReadingHistoryAndPrintBook();
		this->OpenedBook = PLEASE.first;
		this->OpenedPage = PLEASE.second;
	}*/
	 BookManager() {
		 Book book;
		 map<int, string> PageAndContent;

		 
		 book.setISBN(100);

		 
		 
		 book.setTitle("Tawba");

		 
		 book.setAuthorName("Hadeeth");

		 
		 book.setNumberOfPages(3);

		 PageAndContent[1] = "AllahWants";
		 PageAndContent[2] = "PeopleTo";
		 PageAndContent[3] = "StopSinning";

		 book.setPagesAndContent(PageAndContent);
		 AvailableBooks.push_back(book);

	}
	void ListAvailableBooks() {
		int i = 1;
		for (auto& book : AvailableBooks) {
			cout << "Our Current Book Collection:\n";
			cout << "     " << i << ") " << book.getTitle() << "\n";
			i++;
		}
	}
	Book ChooseABook() {
		cout << "Which Book To Read? \n";
		cout << "Enter Number From " << 1 << " - " << AvailableBooks.size()<<" : ";
		int Choise;
		cin >> Choise;
		return AvailableBooks[Choise-1];
	}
	void OpenABook() {
		OpenedBook.PrintPageContent(this->OpenedPage);
	}
	void ListChooseAndOpen() {
		ListAvailableBooks();
		OpenedBook = ChooseABook();
		OpenABook();
	}
	void PrintNextPage() {
		OpenedBook.PrintPageContent(++OpenedPage);
	}
	void PrintPreviousPage() {
		OpenedBook.PrintPageContent(--OpenedPage);
	}
	void AddBook() {
		Book book;
		string str;
		int ISBN;
		int NoOfPages;
		map<int, string> PageAndContent;

		cout << "Enter ISBN: ";
		cin >> ISBN;
		book.setISBN(ISBN);

		cout << "Enter Title: ";
		cin >> str;
		book.setTitle(str);

		cout << "Enter AuthorName: ";
		cin >> str;
		book.setAuthorName(str);

		cout << "Enter NumberOfPages: ";
		cin >> NoOfPages;
		book.setNumberOfPages(NoOfPages);

		for (int i = 1; i <= NoOfPages; ++i) {
			cout << "Enter Page #" << i << " ";
			cin >> str;
			PageAndContent[i] = str;
		}
		book.setPagesAndContent(PageAndContent);
		AvailableBooks.push_back(book);
	}
	/*const string& ReturnBookReadingHistory() const{
		return OpenedBook.getTitle() + " Page: " + to_string(OpenedPage) + "/" + to_string(OpenedBook.getNumberOfPages()) + " - " + dt;
	}*/
	void StopReading(User user) {
		//user.addBookAndPage( OpenedBook , OpenedPage);
	}
	
};
class UserManager {
private:
	vector <User> AllUsers;
	User CurrentUser;
public:
	UserManager() {
		User Admin1;
		Admin1.setName("Mohamed");
		Admin1.setEmail("Mo@gmail.com");
		Admin1.setUserName("Mohamed");
		Admin1.setPassWord("123");
		Admin1.setIsAdmin(true);
		User Saif;
		Saif.setName("Saif");
		Saif.setEmail("S@y");
		Saif.setUserName("Saif");
		Saif.setPassWord("123");
		Saif.setIsAdmin(false);
		AllUsers.push_back(Admin1);
		AllUsers.push_back(Saif);
	}
	void SignUp() {

		CurrentUser.ReadUser();
		CurrentUser.setIsAdmin(false);
		AllUsers.push_back(CurrentUser);
	}
	void LogIn() {
		cout << "Enter UserName(NoSpaces): ";
		string str1;
		cin >> str1;
		cout << "Enter PassWord(NoSpaces): ";
		string str2;
		cin >> str2;
		for (auto& user : AllUsers) {
			if (str1 == user.getUserName() && str2 == user.getPassword()) {
				CurrentUser = user;
			}
		}
	}
	void AcessSystem() {
		int choise = ShowReadMenu({ "Login","Sign Up" });
		if (choise == 1)
			LogIn();
		else
			SignUp();
	}
	void ShowWelcomeMessage() {
		CurrentUser.ShowWelcomeMessage();
	}
	 User getCurrentUser() const{
		return CurrentUser;
	}
	//Why should I Repeate This !
	void ViewProfile() {
		CurrentUser.ViewProfile();
	}
	

};
class OnlineBookReaderSystem {
private:
	BookManager book_manager;
	UserManager user_manager;
	 vector<string> ReturnUserMenu() {
		vector<string> menu;
		menu.push_back("View Profile");
		menu.push_back("List & Select from My Reading History");
		menu.push_back("List & Select from Available Books");
		menu.push_back("Logout");
		return menu;
	}
	 vector<string> ReturnAdminMenu() {
		vector<string> menu;
		menu.push_back("View Profile");
		menu.push_back("AddBook");
		menu.push_back("Logout");
		return menu;
	}
	 vector<string> ReturnReadingMenu() {
		vector<string> menu;
		menu.push_back("NextPage");
		menu.push_back("PreviousPage");
		menu.push_back("StopReading");
		return menu;
	}
public:
	
	void Run() {
		while (true) {
			user_manager.AcessSystem();
			user_manager.ShowWelcomeMessage();
			if (user_manager.getCurrentUser().getIsAdmin()) {
				while (true){
					int Choise = ShowReadMenu(ReturnAdminMenu());
					if (Choise == 1)
						user_manager.ViewProfile();
					else if (Choise == 2)
						book_manager.AddBook();
					else
						break;
				}
			}
			else {
				while (true) {
					int Choise = ShowReadMenu(ReturnUserMenu());
					if (Choise == 1)
						user_manager.ViewProfile();
					else if (Choise == 2) {
						cout << "Not Available Yet\n";
						/*book_manager.setOpenedBookAndPage(user_manager.getCurrentUser());
						while (true) {
							int Choise2 = ShowReadMenu(ReturnReadingMenu());
							if (Choise == 1)
								book_manager.PrintNextPage();
							else if (Choise == 2)
								book_manager.PrintPreviousPage();
							else {
								book_manager.StopReading(user_manager.getCurrentUser());
								break;
							}
						}*/
					}
					else if (Choise == 3) {
						book_manager.ListChooseAndOpen();
						while (true) {
							int Choise2 = ShowReadMenu(ReturnReadingMenu());
							if (Choise2 == 1)
								book_manager.PrintNextPage();
							else if (Choise2 == 2)
								book_manager.PrintPreviousPage();
							else  {
								book_manager.StopReading(user_manager.getCurrentUser());
								break;
							}
						}
					}
					else
						break;
				}
			}
		}
		Run();
	}

};
int main()
{
	OnlineBookReaderSystem System;
	System.Run();
}


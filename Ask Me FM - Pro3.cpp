#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
struct user
{
    string Username;
    int password;
    string name;
    string Email;
    bool anonymous;
    int id;
};
struct Question
{
    int SenderId;
    int RecieverId;
    bool anonymous;
    //bool IsThread; it is handeled (if ParentQId is -1 == it is not thread) else it is thread
    int ParentQId;
    string QText;
    string Answer;
};
int User_Ids = 0;
int Question_Id = 1;
int Current_User_Id;
vector <user> users;
map<int,Question> Questions;
int menu1()
{
    cout << "Menu:" << endl;
    cout << "         1.Login." << endl;
    cout << "         2.SignUp." << endl;
    cout << "Enter Number in range 1-2 : ";
    int choise;
    cin >> choise;
    return choise;
}
void SignUp()
{
    string Username; int password; string name; string Email; bool anonymous;
    cout << "Enter user name. (No spaces): ";
    cin >> Username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> Email;
    cout << "Allow anonymous questions? (0 or 1): ";
    cin >> anonymous;
    users.push_back({ Username, password, name, Email, anonymous ,User_Ids });
    User_Ids++;
}
int LogIn()
{
    cout << "Enter Name & Password : ";
    string name;
    int password;
    cin >> name >> password;
    bool UserFound = false;
    for (auto& user : users)
    {
        if (user.name == name)
        {
            UserFound = true;
            if (password == user.password)
            {
                Current_User_Id = user.id;
                
                return 1;
            }
            else
            {
                cout << "Wrong Password!" << endl;
                return 0;
            }
        }
    }
    if (!UserFound)
    {
        cout << "No Such User found in the system." << endl;
        return 0;
    }
}
int menu2()
{
    cout << ("        1:Print Questions To Me") << endl;
    cout << ("        2:Print Questions From Me") << endl;
    cout << ("        3:Answer Question") << endl;
    cout << ("        4:Delete Question") << endl;
    cout << ("        5:Ask Question") << endl;
    cout << ("        6:List System Users") << endl;
    cout << ("        7:Feed") << endl;
    cout << ("        8:Logout") << endl;
    cout << "Enter Number in range 1-8 : ";
    int choise;
    cin >> choise;
    return choise;
}
void LogOut()
{
    Current_User_Id = 0;
}
void List_System_Users()
{
    for (auto& user : users)
    {
        cout << "Id: " << user.id << "        Name: " << user.Username << endl;
    }
}
void Ask_A_Question()
{
    int userId;
    bool anonymous = true;

    cout << "Enter User Id Or Enter -1 to Cancel: ";
    cin >> userId;
    if (userId == -1)
        return;
    if (userId < 0 || userId >User_Ids)
    {
        cout << "No Such User with this Id" << endl;
        return;
    }
    if (!users[userId].anonymous)
    {
        cout << "Note: Anonymous Questions are not allowed for this user." << endl;
        anonymous = false;
    }
    else
    {
        cout << "Is anonymous questions ? : (0 or 1) : ";
        int ano;
        cin >> ano;
        if (ano)
            anonymous = true;
        else anonymous = false;
    }
    cout << "For Thread Question : Enter Question Id or -1 for New Question: ";
    int ParentId;
    cin >> ParentId;
    string QText;
    
    cout << "Enter Question Text: ";
    cin >> ws;
    getline(cin, QText);
    Questions[Question_Id]={Current_User_Id,userId,anonymous,ParentId,QText};
    Question_Id++;
    
}
void Print_Questions_To_Me()
{
    bool empty = true;
    for (auto& ParentQuestion : Questions)
    {
        if (Current_User_Id == ParentQuestion.second.RecieverId && (ParentQuestion.second.ParentQId == -1))
        {
            empty = false;
            cout << "Question Id (" << ParentQuestion.first << ") ";
            if (!ParentQuestion.second.anonymous)
                cout << "From User Id (" << ParentQuestion.second.SenderId << ") ";
            cout << "    Qusetion: " << ParentQuestion.second.QText << endl;
            if(ParentQuestion.second.Answer.size()) cout << "      Answer: " << ParentQuestion.second.Answer << endl;
                 
            for (auto& ThreadQuestion : Questions)
            {
                if (ParentQuestion.first == ThreadQuestion.second.ParentQId)
                {
                    cout << "     Thread: Question Id (" << ThreadQuestion.first << ") ";
                    if (!ThreadQuestion.second.anonymous)
                        cout << "From User Id (" << ThreadQuestion.second.SenderId << ") ";
                    cout << "    Qusetion: " << ThreadQuestion.second.QText << endl;
                    if (ThreadQuestion.second.Answer.size())
                        cout << "     Thread:     Answer: " << ThreadQuestion.second.Answer << endl;
                }
            }
        }
    }
    if (empty)
        cout << "No Questions Yet!" << endl;
}
void Print_Questions_From_Me()
{
    bool empty = true;
    for (auto& Question : Questions)
    {
        if (Question.second.SenderId == Current_User_Id)
        {
            empty = false;
            cout << "Question Id (" << Question.first << ") ";
            if (!Question.second.anonymous)
                cout << "!AQ ";
            cout << "To User Id (" << Question.second.RecieverId << ") ";
            cout << "Question: " << Question.second.QText;
            if (Question.second.Answer.size())
                cout << " Answer: " << Question.second.Answer << endl;
            else cout << "NOT Answered Yet!" << endl;
        }
    }
    if (empty)
        cout << "No Questions Yet! " << endl;
}
void Answer_A_Question()
{
    cout << "Enter Question Id Or -1 to cancel : ";
    int QId;
    cin >> QId;
    string Answer;
    if (QId == -1)
    {
        return;
    }
    else if (Questions[QId].QText.empty())
    {
        cout << "No Such Question with this Id" << endl;
        return;
    }
    else
    {
        cout << "Question Id (" << QId << ") ";
        if (!Questions[QId].anonymous)
            cout << "From User Id (" << Questions[QId].SenderId << ") ";
        cout << "    Qusetion: " << Questions[QId].QText << endl;
        if (Questions[QId].Answer.size()) 
        { 
            cout << "      Answer: " << Questions[QId].Answer << endl; 
            cout << "\nWarning: Already Answered.. Answer will be Updated! " << endl;
        }
        cout << "Enter Your Answer: ";
        cin >> ws; //white space 
        getline(cin, Answer);
        Questions[QId].Answer = Answer;

    }
}
void Delete_A_Question()
{
    cout << "Enter Question Id Or -1 to Cancel: ";
    int QId;// Id of Parent Or Thread
    cin >> QId;
    if (QId == -1)
        return;
    else if (Questions[QId].QText.empty())
    {
        cout << "No Such Question with this Id" << endl;
    }
    else Questions.erase(QId);// Delete Parent

    for (auto Question : Questions)
    {
        if (QId == Question.second.ParentQId)
        {
            Questions.erase(Question.first);// Delete Thread
        }
    }

}
void Feed()
{
    bool empty = true;
    for (auto& ParentQuestion : Questions)
    {
        if (ParentQuestion.second.Answer.size() && (ParentQuestion.second.ParentQId==-1))
        {
            empty = false;
            cout << "Question Id(" << ParentQuestion.first << ") ";
            if (!ParentQuestion.second.anonymous) cout << "From User Id: " << ParentQuestion.second.SenderId; 
            cout<< " To User Id: "<< ParentQuestion.second.RecieverId << "     Question: " << ParentQuestion.second.QText << endl;
            cout << "     Answer: " << ParentQuestion.second.Answer << endl;
            for (auto& ThreadQuestion : Questions)
            {
                if (ParentQuestion.first == ThreadQuestion.second.ParentQId)
                {
                    cout << "Thread: PQId(" << ParentQuestion.first << ") TQId(" << ThreadQuestion.first << ") ";
                    if (!ThreadQuestion.second.anonymous) cout << "From User Id: " << ThreadQuestion.second.SenderId;
                    cout << " To User Id: " << ThreadQuestion.second.RecieverId << "     Question: " << ThreadQuestion.second.QText << endl;
                    cout << "     Answer: " << ThreadQuestion.second.Answer << endl;
                }
            }
        }
       
    }
    if (empty)
        cout << "No Questions Yet!" << endl;
}
void LoopingInner()
{
    bool loop = true;
    while (loop)
    {
        switch (menu2())
        {
        case 1:
            Print_Questions_To_Me();
            break;
        case 2:
            Print_Questions_From_Me();
            break;
        case 3:
            Answer_A_Question();
            break;
        case 4:
            Delete_A_Question();
            break;
        case 5:
            Ask_A_Question();
            break;
        case 6 :
            List_System_Users();
            break;
        case 7: 
            Feed();
            break;
        case 8:
            LogOut();
            loop = false;
            break;
        default:
            cout << "Wrong Input!.." << endl;
            break;
        }
    }
}
void LoopingOuter()
{
    while (1)
    {
        switch (menu1())
        {
        case 1: 
            if(LogIn())
                LoopingInner();
            break;
        case 2:
            SignUp();
            LoopingInner();
            break;
        default:
            cout << "Wrong Input." << endl;
            break;
        }
    }

}
int main()
{
    LoopingOuter();
}



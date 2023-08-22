#include <iostream>
#include <deque>
#include <queue>
#include <map>
#include <cstdlib>
using namespace std;
void print_the_list()
{
    
    cout << "1)Add Patient" << endl;
    cout << "2)Pring All Patients" << endl;
    cout << "3)Get Next Patient" << endl;
    cout << "4)Exit" << endl;
}

struct patient
{
    string name;
    int spec;
    bool status;
};

map<int, deque<patient>> spec;

patient getPatientinfo(int spec, string name, bool status)
{
    patient p;
    p.spec = spec;
    p.name = name;
    p.status = status;
    return p;
}

void addPatient(patient p)
{
    if (spec[p.spec].size() == 5)
        cout << "Sorry, Spec is busy now try later please" << endl;
    else
    {
        if (p.status)
            spec[p.spec].push_front(p);
        else
            spec[p.spec].push_back(p);
        cout << "Patient Added Successfully" << endl;
    }

}

void askForAPatient()
{
    cout << "Enter (Spec,Name and status) :";
    int SpHolder;
    string NHolder;
    bool StHolder;
    cin >> SpHolder >> NHolder >> StHolder;
    addPatient(getPatientinfo(SpHolder, NHolder, StHolder));
}

void specPrinting(int specNo)
{
    if (spec[specNo].size())
    {
        cout << "There are " << spec[specNo].size() << " Patients in Spec No : " << specNo << endl;
        deque <patient> holder = spec[specNo];
        for (auto item : holder)
        {
            cout << holder.front().name << " " << holder.front().status<<endl;
            holder.pop_front();
        }
        cout << "\n";
    }

}

void HospitalPrinting()
{
    for (int i = 1; i <= 20; ++i)
        specPrinting(i);
}

void FixingThePatient(int specNo)
{
    if (spec[specNo].size())
    {
        cout << spec[specNo].front().name << " Please, Go to the White-Jacket Man."<<endl;
        spec[specNo].pop_front();
    }
    else
        cout << "No Patients available , Go have some Oranga juice Dr :)" << endl;
}

void getNextPatient()
{
    cout << "Enter Specialization Please : ";
    int specNo;
    cin >> specNo;
    FixingThePatient(specNo);

}

void looping_program_starting()
{
    bool continuing = true;
    while(continuing)
    {
        print_the_list();
        cout << "Enter The No of Operation : ";
        int Operation_number;
        cin >> Operation_number;
        switch (Operation_number)
        {
        case 1 :
            askForAPatient();
            break;
        case 2 :
            HospitalPrinting();
            break;
        case 3 :
            getNextPatient();
            break;
        case 4:
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



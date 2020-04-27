//--------------------------------------------------------------------
//
//  Laboratory 10                                         login.cpp
//
//  Programming Exercise 1: program that reads in username/login pairs 
//  and performs authentication of usernames until EOF is encountered.
//
// ** SOLUTION **
//
//--------------------------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>
#include "HashTable.cpp"


using namespace std;

struct Password
{
    void setKey ( string newKey ) { username = newKey; }
    string getKey () const { return username; }
    static unsigned int hash(const string& str)
    {
        int val = 0;

        for (int i=0; i<str.length(); i++) 
            val += str[i];
        return val;
    }
    string username,
           password;
};

int main()
{
    HashTable<Password, string> passwords(8);
    Password tempPass;
    string name,      // user-supplied name
           pass;      // user-supplied password
    bool userFound;   // is user in table?

    ifstream passFile( "password.dat" );

    if ( !passFile )
    {
        cout << "Unable to open 'password.dat'!" << endl;
        return 1;
    }

    while ( passFile >> tempPass.username >> tempPass.password )
    {
        passwords.insert( tempPass );
    }

    passwords.showStructure();

    cout << "Login: ";
    while ( cin >> name )
    {
        userFound = passwords.retrieve( name, tempPass );
 
        cout << "Password: ";
        cin >> pass;

        if ( ! userFound || pass != tempPass.password )
            cout << "Authentication failure" << endl;
        else
            cout << "Authentication successful" << endl;

        cout << "Login: ";
    }
    
    cout << endl;

    return 0;
}


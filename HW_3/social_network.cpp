#include <iostream>
#include <string>
#include <vector>
#include "network.h"
#include "user.h"

using namespace std;

void printMenu() {
    cout << "Select an option:" << endl;
    cout << "1. Add a user" << endl;
    cout << "2. Add friend connection" << endl;
    cout << "3. Delete friend connection" << endl;
    cout << "4. Write to file" << endl;
    cout << "Enter any other input to exit." << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [user_file.txt]" << endl;
        return 1;
    }

    // initialize and read file for network
    Network net;
    net.readUsers(argv[1]);

    int option;
    while (true) {
        printMenu();
        if (!(cin >> option)) break; // unexpected input closes function

        if (option == 1) {
            string first, last;
            int year, zip;
            cout << "Enter user information in the order of first, last, year, and zip." << endl;
            cin >> first >> last >> year >> zip;
            
            string fullName = first + " " + last;
            
            // empty friends set to add into constructor
            std::set<int> friends;
            // assigns id based off number of users
            User* newUser = new User(net.numUsers(), fullName, year, zip, friends);
            net.addUser(newUser);
            cout << "User added: " << fullName << endl;

        } else if (option == 2) {
            string f1, l1, f2, l2;
            cout << "Enter the two friends to create a connection in the order of first and last name of friend one and first and last name of friend two." << endl;
            cin >> f1 >> l1 >> f2 >> l2;
            
            int result = net.addConnection(f1 + " " + l1, f2 + " " + l2);
            if (result == -1) {
                cout << "Error: One or both users do not exist." << endl;
            } else {
                cout << "Connection added successfully." << endl;
            }

        } else if (option == 3) {
            string f1, l1, f2, l2;
            cout << "Enter the two friends to delete the connection in the order of first and last name of friend one and first and last name of friend two." << endl;
            cin >> f1 >> l1 >> f2 >> l2;
            
            int result = net.deleteConnection(f1 + " " + l1, f2 + " " + l2);
            if (result == -1) {
                cout << "Error: Connection could not be deleted." << endl;
            } else {
                cout << "Connection removed successfully." << endl;
            }

        } else if (option == 4) {
            cout << "Enter name of file to write." << endl;
            string outFileName;
            cin >> outFileName;
            net.writeUsers(outFileName.c_str());
            cout << "Successfully wrote " << net.numUsers() << " users to " << outFileName << endl;

        } else {
            // catchall stuff
            cout << "Exiting program..." << endl;
            break;
        }
    }

    return 0;
}
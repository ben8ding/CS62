#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include "user.h" 

class Network {
public:
    // default constructor
    Network();

    // user accessor
    User* getUser(int id);

    // pre: the user to add
    // post: the user is pushed to the end of users_  
    void addUser(User*);

    // pre: the string names of the two users to add connection
    // post: a connection is added between users with matching ids to the provided strings if found 
    int addConnection(std::string s1, std::string s2);
    // pre: the string names of the two users to add connection
    // post: a connection is deleted between users with matching ids, if the connection exists
    int deleteConnection(std::string s1, std::string s2);
    
    // accessors for user information
    int getId(std::string name);
    int numUsers();

    //pre:
    //post:
    void readUsers(const char* fname);
    void writeUsers(const char* fname);

    //pre:
    //post:
    std::vector<int> Network::shortestPath(int from, int to);



private:
    // stored users
    std::vector<User*> users_;
};

#endif
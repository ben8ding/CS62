#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include "user.h" 
#include "post.h"

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

    //pre: the filename of the text file with the users to be imported
    //post: a network object is created and every user in the file is imported
    void readUsers(const char* fname);
    //pre: the name of the file to output and the network object
    //post: a file with the given name is created with all users formatted in the file
    void writeUsers(const char* fname);

    //pre:
    //post:
    std::vector<int> shortestPath(int from, int to);

    //pre:
    //post:
    std::vector<int> distanceUser(int from, int& to, int distance);

    //pre:
    //post:
    std::vector<int> suggestFriends(int who, int& score);

    //pre:
    //post:
    std::vector<std::vector<int> > groups();

    //pre:
    //post:
    void addPost(Post* post);

    //pre:
    //post:
    std::vector<Post*> getPosts(int id);

    //pre:
    //post:
    std::string postDisplayString(Post* post);

    //pre:
    //post:
    std::string getPostsString(int profileId, int howMany);

    //pre:
    //post:
    int readPosts(char* fname);

    //pre:
    //post:
    int writePosts(char* fname);

private:
    // stored users
    std::vector<User*> users_;
    std::vector<std::vector<Post*>> posts_;

    void groupsHelper(int curr, std::vector<bool>& visited, std::vector<int>& component);
};

#endif
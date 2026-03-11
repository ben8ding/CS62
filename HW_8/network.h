#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include "user.h" 
#include "post.h"

class Network {
public:
    //Default constructor
    Network();

    //User accessor
    User* getUser(int id);

    // Pre: The user to add.
    // Post: The user is pushed to the end of users_.
    void addUser(User*);

    // Pre: The string names of the two users to add connection.
    // Post: A connection is added between users with matching ids to the provided strings if found. Returns 0 if successful, otherwise returns -1.
    int addConnection(std::string s1, std::string s2);
    // Pre: The string names of the two users to add connection.
    // Post: A connection is deleted between users with matching ids, if the connection exists. Returns 0 if successful, otherwise returns -1.
    int deleteConnection(std::string s1, std::string s2);
    
    //Accessors for user information.
    int getId(std::string name);
    int numUsers();

    //Pre: The filename of the text file with the users to be imported.
    //Post: The network is populated with the users within the file.
    void readUsers(const char* fname);
    //Pre: The name of the file to output and the network object.
    //Post: Returns a file with the given name is created with all users formatted in the file.
    void writeUsers(const char* fname);

    //Pre: The user IDs for the beginning and end.
    //Post: Returns a vector with the shortest path of friend connections between the beginning and end
    std::vector<int> shortestPath(int from, int to);

    //Pre: The starting user, a pass by reference int for the found user, and distance to search for.
    //Post: Returns a vector with the path to the found user. The variable passed by reference is set to the ID of the found user.
    std::vector<int> distanceUser(int from, int& to, int distance);

    //Pre:
    //Post:
    std::vector<int> suggestFriends(int who, int& score);

    //Pre:
    //Post:
    std::vector<std::vector<int> > groups();

    //Pre:
    //Post:
    void addPost(Post* post);

    //Pre:
    //Post:
    std::vector<Post*> getPosts(int id);

    //Pre:
    //Post:
    std::string postDisplayString(Post* post);

    //Pre:
    //Post:
    std::string getPostsString(int profileId, int howMany);

    //Pre:
    //Post:
    int readPosts(char* fname);

    //Pre:
    //Post:
    int writePosts(char* fname);

    //Pre: The message ID of the post
    //Post: Returns a pointer to the post if found
    Post* getPost(int messageId);

private:
    //Stored users and psots
    std::vector<User*> users_;
    std::vector<std::vector<Post*>> posts_;
    //Int to keep track of message count for ID purposes
    int globalMessageId;

    void groupsHelper(int curr, std::vector<bool>& visited, std::vector<int>& component);
};

#endif

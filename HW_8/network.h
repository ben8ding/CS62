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

    //Pre: The target user for who to suggest friends, and a score variable reference to pass and return later
    //Post: A full list of friends of friends to suggest, along with the highest score
    std::vector<int> suggestFriends(int who, int& score);

    std::vector<std::vector<int> > groups();

    //Pre: A post object
    //Post: The post object is added to the network set of posts, and a message ID is generated for the newest post.
    void addPost(Post* post);

    //Pre: The profile user ID
    //Post: A vector of posts pertaining to the profile user id.
    std::vector<Post*> getPosts(int id);

    //Pre: The post pointer to be converted
    //Post: A string output with all of the post's data.
    std::string postDisplayString(Post* post);

    //Pre: The profile ID of the user and the amount of posts to return.
    //Post: A string formatted to show the x most recent posts of the provided user with x being the howMany.
    std::string getPostsString(int profileId, int howMany);

    //Pre: An existing network of posts.
    //Post: A .txt file is written and formatted with every post in the network
    int readPosts(char* fname);

    //Pre: a .txt of formatted posts
    //Post: This network's posts are populated with the posts in the .txt
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

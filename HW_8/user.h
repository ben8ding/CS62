#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <vector>

class User
{
public:
    //Default constructor
    User();

    //Legacy constructor
    User(int id, std::string name, int year, int zip, std::set<int> friends);

    //New constructor with inputtable bio
    User(int id, std::string name, int year, int zip, std::set<int> friends, std::string bio);

    //Accessor/getter methods
    int getId() const;
    std::string getName() const;
    int getYear() const;
    int getZip() const;
    // return reference of friends set
    std::set<int> &getFriends();
    std::string getBio();

   
    //Pre: The id of the friend to be added
    //Post: Friends_ is inserted with the id of the
    void addFriend(int id);
    //Pre: The id of the friend to be removed
    //Post: If the friend in friends_ has a matching id, it is removed from the set
    void deleteFriend(int id);
    
    //Pre: The id of the friend to
    //Post: The logic statement on if they friend id is on the user's friend list
    bool isFriend(int);

    //Pre: The string Bio to replace the current user bio
    //Post: bio_ is replaced with the inputted bio
    void setBio(std::string bio);

private:
    // user fields
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
    std::string bio_;
};

#endif

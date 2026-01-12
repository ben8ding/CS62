#ifndef USER_H
#define USER_H

#include <string>
#include <set>
#include <vector>

class User
{
public:
    // default constructor
    User();

    // primary constructor
    User(int id, std::string name, int year, int zip, std::set<int> friends);

    // accessor/getter methods
    int getId() const;
    std::string getName() const;
    int getYear() const;
    int getZip() const;
    // return reference of friends set
    std::set<int> &getFriends();

   
    //Pre: The ID of the friend to be added
    //Post: friends_ is inserted with the ID of the 
    void addFriend(int id);
    //Pre: The ID of the friend to be removed
    //Post: If the friend in friends_ has a matching ID, it is removed from the set
    void deleteFriend(int id);

private:
    // user fields
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
};

#endif
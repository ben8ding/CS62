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

   
    //pre: the id of the friend to be added
    //post: friends_ is inserted with the id of the 
    void addFriend(int id);
    //pre: the id of the friend to be removed
    //post: if the friend in friends_ has a matching id, it is removed from the set
    void deleteFriend(int id);
    
    //pre:
    //post:
    bool isFriend(int);

private:
    // user fields
    int id_;
    std::string name_;
    int year_;
    int zip_;
    std::set<int> friends_;
};

#endif
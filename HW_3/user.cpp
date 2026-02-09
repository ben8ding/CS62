#include "user.h"

// default constructor
User::User()
{
    id_ = 0;
    name_ = "";
    year_ = 2026;
    zip_ = 95053;
    friends_ = std::set<int>();
}

// primary constructor
User::User(int id, std::string name, int year, int zip, std::set<int> friends)
{
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
}

// adds friend with the given id
void User::addFriend(int id)
{
    friends_.insert(id);
}

// deletes friend of the given id
void User::deleteFriend(int id)
{
    friends_.erase(id);
}

// getter methods
int User::getId() const
{
    return id_;
}

std::string User::getName() const
{
    return name_;
}

int User::getYear() const
{
    return year_;
}

int User::getZip() const
{
    return zip_;
}

std::set<int> &User::getFriends()
{
    return friends_;
}

bool User::isFriend(int user)
{
    for(int friendos : friends_){
        if(friendos == user)
            return true;
    }
    return false;
}


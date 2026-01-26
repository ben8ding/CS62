#include "network.h"
#include <fstream>
#include <sstream>

// default constructor
Network::Network() {}

// adds user
void Network::addUser(User *u)
{
    users_.push_back(u);
}

// gets user in users_ with id id
User *Network::getUser(int id)
{
    if (id < 0 || id >= (int)users_.size())
    {
        return nullptr;
    }
    return users_[id];
}

// searches users_ for user with same name as name, and returns an id if found.
int Network::getId(std::string name)
{
    for (size_t i = 0; i < users_.size(); ++i)
    {
        if (users_[i]->getName() == name)
        {
            return users_[i]->getId();
        }
    }
    return -1;
}

// adds a connection between two users if their ids are found
int Network::addConnection(std::string s1, std::string s2)
{
    int id1 = getId(s1);
    int id2 = getId(s2);

    if (id1 == -1 || id2 == -1)
        return -1;

    users_[id1]->addFriend(id2);
    users_[id2]->addFriend(id1);
    return 0;
}

// removes a connection between two users if their ids are found
int Network::deleteConnection(std::string s1, std::string s2)
{
    int id1 = getId(s1);
    int id2 = getId(s2);

    if (id1 == -1 || id2 == -1)
        return -1;

    users_[id1]->deleteFriend(id2);
    users_[id2]->deleteFriend(id1);
    return 0;
}

// returns size of users_
int Network::numUsers()
{
    return users_.size();
}

void Network::readUsers(const char *fname)
{
    std::ifstream ifs(fname);
    if (!ifs.is_open())
        return;

    int numUsers;
    if (!(ifs >> numUsers))
        return;

    for (int i = 0; i < numUsers; ++i)
    {
        int id, year, zip;
        std::string name, line;
        std::set<int> friends;

        ifs >> id;
        ifs.ignore(); // use newline to move to next parameter

        // read name
        std::getline(ifs, name);
        if (!name.empty() && name[0] == '\t')
            name = name.substr(1);

        // read year and then zip
        ifs >> year >> zip;
        ifs.ignore(); // use newline to prepare to read friend ids

        // read the entire line of friend ids for stringstream
        std::getline(ifs, line);
        std::stringstream ss(line);

        // keeps reading vals until the end of the stream
        int friendId;
        while (ss >> friendId)
        {
            friends.insert(friendId);
        }

        // adds new user to network
        addUser(new User(id, name, year, zip, friends));
    }
    ifs.close();
}

void Network::writeUsers(const char *fname)
{
    std::ofstream ofs(fname);
    if (!ofs.is_open())
        return;

    ofs << users_.size() << std::endl;

    for (User *u : users_)
    {
        ofs << u->getId() << std::endl;
        ofs << "\t" << u->getName() << std::endl;
        ofs << "\t" << u->getYear() << std::endl;
        ofs << "\t" << u->getZip() << std::endl;

        ofs << "\t";
        // iterate through the set of friends
        const std::set<int> &friends = u->getFriends();
        for (auto it = friends.begin(); it != friends.end(); ++it)
        {
            ofs << *it << (std::next(it) == friends.end() ? "" : " ");
        }
        ofs << std::endl;
    }
    ofs.close();
}


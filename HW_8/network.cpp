#include "network.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <QDebug>

//global helper function for sorting
bool compareMessageId(Post* a, Post* b){
    return a->getMessageId() < b->getMessageId();
}

// default constructor
Network::Network() {
    globalMessageId = 0;
}

// adds user
void Network::addUser(User *u)
{
    users_.push_back(u);
    // allocate posts_ vector to have a vector of posts for every user
    std::vector<Post *> temp;
    posts_.push_back(temp);
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

std::vector<int> Network::shortestPath(int from, int to)
{
    if (from == to)
        return {from};

    std::queue<int> q;
    std::vector<bool> visited(users_.size(), false);
    std::vector<int> prev(users_.size(), -1);

    visited[from] = true;
    q.push(from);

    while (q.size() > 0)
    {
        int cur = q.front();
        q.pop();
        for (auto neighbor : users_[cur]->getFriends())
        {
            if (!visited[neighbor])
            {
                prev[neighbor] = cur;
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    if (!visited[to])
    {
        return {}; // Return an empty vector if no path exists
    }

    std::vector<int> output;
    int cur = to;
    while (cur != -1)
    {
        output.push_back(cur);
        cur = prev[cur];
    }

    reverse(output.begin(), output.end());
    return output;
}

std::vector<int> Network::distanceUser(int from, int &to, int distance)
{
    if (distance == 0)
    {
        to = from;
        return {from};
    }

    std::vector<int> prev(users_.size(), -1);
    std::vector<int> dist(users_.size(), -1); // distance vector for each node to check, also allows us to replace visited since we assign a distance to each visited node
    std::queue<int> q;

    dist[from] = 0;
    q.push(from);

    while (q.size() > 0)
    {
        int cur = q.front();
        q.pop();

        // process first node we find that is at the target distance
        if (dist[cur] == distance)
        {
            to = cur;
            std::vector<int> output;
            int temp = cur; // not reusing to for loop because we want to keep to reference clean
            while (temp != -1)
            {
                output.push_back(temp);
                temp = prev[temp];
            }
            std::reverse(output.begin(), output.end());
            return output;
        }

        for (auto neighbor : users_[cur]->getFriends())
        {
            if (dist[neighbor] == -1)
            {
                // assigning distance to all found nodes
                dist[neighbor] = dist[cur] + 1;
                prev[neighbor] = cur;
                q.push(neighbor);
            }
        }
    }
    // return if not found
    to = -1;
    return {};
}

std::vector<int> Network::suggestFriends(int who, int &score)
{
    // find list of friends of friends
    std::vector<int> suggestions;
    for (auto fri1 : users_[who]->getFriends())
    {
        for (auto fof : users_[fri1]->getFriends())
        {
            bool isDupe = false;
            for (int dupeCheck : suggestions)
            {
                if (dupeCheck == fof)
                    isDupe = true;
            }

            if (!users_[who]->isFriend(fof) && who != fof && !isDupe)
            {
                suggestions.push_back(fof);
            }
        }
    }

    if (suggestions.size() == 0)
    {
        score = -1;
        return {};
    }

    // initialize scores vector to create a score for each friend of friend found
    std::vector<int> scores(suggestions.size(), 0);
    for (int i = 0; i < suggestions.size(); i++)
    {
        for (auto fri2 : users_[who]->getFriends())
        {
            if (users_[fri2]->isFriend(suggestions[i]))
            {
                scores[i]++;
            }
        }
    }

    // find max score and process
    score = *std::max_element(scores.begin(), scores.end());
    std::vector<int> results;
    for (int s = 0; s < scores.size(); s++)
    {
        if (scores[s] == score)
            results.push_back(suggestions[s]);
    }
    return suggestions;
}

std::vector<std::vector<int>> Network::groups()
{
    std::vector<std::vector<int>> allComponents;
    std::vector<bool> visited(users_.size(), false);

    for (int i = 0; i < (int)users_.size(); ++i)
    {
        if (!visited[i])
        {
            std::vector<int> component;

            groupsHelper(i, visited, component);
            allComponents.push_back(component);
        }
    }
    return allComponents;
}

void Network::groupsHelper(int curr, std::vector<bool> &visited, std::vector<int> &component)
{
    visited[curr] = true;
    component.push_back(curr);

    const std::set<int> &friends = users_[curr]->getFriends();
    for (int neighbor : friends)
    {
        if (!visited[neighbor])
        {
            groupsHelper(neighbor, visited, component);
        }
    }
}

void Network::addPost(Post *post)
{
    post->setMessageId(globalMessageId);
    globalMessageId++;
    posts_[post->getProfileId()].push_back(post);
}

std::vector<Post *> Network::getPosts(int id)
{
    if (id < 0 || id >= posts_.size())
    {
        return {};
    }
    return posts_[id];
}

std::string Network::postDisplayString(Post *post)
{
    return users_[post->getAuthorId()]->getName() + " wrote: " + post->toString();
}

std::string Network::getPostsString(int profileId, int howMany)
{
    if (profileId < 0 || profileId >= posts_.size())
        return "";

    std::string result = "";
    int count = 0;

    for (int i = posts_[profileId].size() - 1; i >= 0 && count < howMany; --i)
    {
        result += postDisplayString(posts_[profileId][i]);

        count++;
        if (count < howMany && i > 0)
        {
            result += "\n\n";
        }
    }
    return result;
}

//see readUsers for documentation
int Network::readPosts(char *fname)
{
    std::ifstream ifs(fname);
    if (!ifs.is_open())
        return -1;

    int numPosts;
    ifs >> numPosts;

    for (int i = 0; i < numPosts; ++i)
    {

        int mId, pId, aId, likes;
        std::string message, url, line;

        ifs >> mId;
        ifs.ignore();

        std::getline(ifs, message);

        ifs >> pId >> aId >> likes;

        ifs.ignore();

        std::getline(ifs, url);

        Post *newPost;
        if (url.empty())
        {
            newPost = new Post(pId, aId, message, likes);
        }
        else
        {
            //remove tab from reading
            url.erase(std::remove(url.begin(), url.end(), '\t'), url.end());
            newPost = new LinkPost(pId, aId, message, likes, url);
        }

        addPost(newPost);
    }

    ifs.close();

    return 0;
}

int Network::writePosts(char* fname)
{
    std::ofstream ofs(fname);
    if (!ofs.is_open())
        return -1;

    int totalPosts = 0;
    for (std::vector<Post*> postVector : posts_) {
        totalPosts += postVector.size();
    }

    ofs << totalPosts << std::endl;

    // move all posts into a single vector to sort
    std::vector<Post*> sortVector;
    for(int i = 0; i < posts_.size(); i++) {
        for(Post* p : posts_[i]){
            sortVector.push_back(p);
        }
    }
    std::sort(sortVector.begin(), sortVector.end(), compareMessageId);

    for(Post* p : sortVector){
        ofs << p->getMessageId() << std::endl;
        ofs << "\t" << p->getMessage() << std::endl;
        ofs << "\t" << p->getProfileId() << "\n\t" << p->getAuthorId() << "\n\t" << p->getLikes() << std::endl;
        std::string url = p->getURL();
        if (url.empty()) {
        ofs << std::endl;
        } else {
            ofs << "\t" << url << std::endl;
        }
    }
        

    ofs.close();
    return 0;
}


#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include "user.h"
#include "network.h"

using namespace std;

int main()
{
    Network net;
    net.readUsers("suggest5.txt");

    int score;
    vector<int> suggestions = net.suggestFriends(2, score);
    assert(score == 2);
    cout << "size: " << suggestions.size() << endl;
    assert(suggestions.size() == 2);
    assert(suggestions[0] + suggestions[1] == 4);
    assert(suggestions[0] * suggestions[1] == 0);
    

    return 0;
}
#ifndef USER_H
#define USER_H

#include <vector>
#include <string>

using namespace std;

class User {
public:
    User(string pName);
    string getName();
    string getFriendsName(int i);
    void setFriend(User *newFriend);
    void removeFromFriendsList(string friendName);
    void printFriends();
    int getSize();

private:
    string name;
    int size;
    vector<User *> friendList;

};

#endif
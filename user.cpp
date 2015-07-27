#include <iostream>
#include "user.h"

using namespace std;

User::User(string pName) {
    name = pName;
    size = 0;
}

string User::getName() {
    return name;
}

void User::setFriend(User *newFriend) {
    friendList.push_back(newFriend);
    size++;
}

int User::getSize() {
    return size;
}

void User::removeFriend(string friendName) {
    for (int i = 0; i < size; i++) {
        if (friendList[i]->getName() == friendName) {
            friendList.erase(friendList.begin() + i);
            size--;
        } 
    }
}

void User::removeFromFriendsList(string friendName) {
    for (int i = 0; i < size; i++) {
        if (friendList[i]->getName() == friendName) {
            friendList[i]->removeFriend(name);
        } 
    }
}

string User::getFriendsName(int i) {
    return friendList[i]->getName();
}

void User::printFriends() {
    cout << "Friends for: " << name << endl;
    cout << "HERE" << endl;
    exit(0);
    for (int i = 0; i < friendList.size(); i++) {
        if (friendList[i] != NULL) {
            cout << friendList[i]->getName() << endl;
        }
    }
    // cout << "HERE" << endl;
    // exit(0);
}

void User::clearFriendlist() {
    friendList.clear();
    size = 0;
}

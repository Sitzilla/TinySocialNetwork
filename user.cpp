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

void User::removeFromFriendsList(string friendName) {
    for (int i = 0; i < size; i++) {
        if (friendList[i]->getName() == friendName) {
            friendList.erase(friendList.begin() + i);
            size--;
        }
    }
}

string User::getFriendsName(int i) {
    return friendList[i]->getName();
}

void User::printFriends() {
    cout << "Friends for: " << name << endl;

    if (size == 0) {
        cout << name << " has no friends." << endl;
    }

    for (int i = 0; i < friendList.size(); i++) {
        if (friendList[i] != NULL) {
            cout << friendList[i]->getName() << endl;
        }
    }
}
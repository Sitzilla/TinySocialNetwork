#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "basic.h"
#include "user.h"
#include "friendhash.h"
#include <iostream>

using namespace std;

class GameLogic {

public:
    GameLogic();
    void startGameLoop();
    void registerUser(string name);
    void unregisterUser(string userName);
    void friendUsers(string userName1, string userName2);
    void unfriendUsers(string userName1, string userName2);
    void list(string name);
    void listUsers();
    void checkFriends(string userName1, string userName2);
    void printInstructions();
    bool areFriends(string userName1, string userName2);
    bool samePerson(string userName1, string userName2);
    bool isUser(string userName);
    bool checkTwoUsersExist(string userName1, string userName2);

private:
    BasicHT userHashtable;
    FriendHash friendshipHashtable;

};

#endif
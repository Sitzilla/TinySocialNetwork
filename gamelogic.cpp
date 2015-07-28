#include "gamelogic.h"
#include "tokenizer.h"
#include <iostream>
#include "basic.h"
#include "user.h"
#include "friendhash.h"
using namespace std;

GameLogic::GameLogic(BasicHT pUserHashtable, FriendHash pFriendshipHashtable) {
    userHashtable = pUserHashtable;
    friendshipHashtable = pFriendshipHashtable;
}

void GameLogic::startGameLoop() {

    string registerCommand = "register";
    string unregisterCommand = "unregister";
    string friendCommand = "friend";
    string unfriendCommand = "unfriend";
    string listCommand = "list";
    string listUsersCommand = "listusers";
    string checkfriendsCommand = "checkfriends";
    string quitCommand = "quit";


    cout << "Welcome to the Sitzes Social System!" << endl;
    printInstructions();

    while (true) {
        while (true) {

            string input;
            Tokenizer tokenizer;
            string token;

            cout << endl << "Enter in a command..." << endl;
            getline(cin, input);

            tokenizer.tokenize(input);
            tokenizer.nextToken(token);

            string command = token;
            int inputNamesSize = tokenizer.getSize();

            // Registers a User in the system
            if (command == registerCommand) {
                if (inputNamesSize != 1) {
                    cout << "Incorrect number of usernames" << endl;
                    break;
                }

                tokenizer.nextToken(token);
                registerUser(token);
            }
            // Unregisters a user
            else if (command == unregisterCommand) {
                if (inputNamesSize != 1) {
                    cout << "Incorrect number of usernames" << endl;
                    break;
                }

                tokenizer.nextToken(token);
                unregisterUser(token);
            }
            // Friends two users
            else if (command == friendCommand) {
                if (inputNamesSize != 2) {
                    cout << "Incorrect number of usernames" << endl;
                    break;
                }

                tokenizer.nextToken(token);
                string userName1 = token;
                tokenizer.nextToken(token);
                string userName2 = token;

                if (samePerson(userName1, userName2)) {
                    break;
                } 

                friendUsers(userName1, userName2);
            }
            // Unfriends two users
            else if (command == unfriendCommand) {
                if (inputNamesSize != 2) {
                    cout << "Incorrect number of usernames" << endl;
                    break;
                }

                tokenizer.nextToken(token);
                string userName1 = token;
                tokenizer.nextToken(token);
                string userName2 = token;

                if (samePerson(userName1, userName2)) {
                    break;
                } 

                unfriendUsers(userName1, userName2);
            }
            // Print out all friends for a User
            else if (command == listCommand) {
                if (inputNamesSize != 1) {
                    cout << "Incorrect number of usernames" << endl;
                    break;
                }

                tokenizer.nextToken(token);
                list(token);
            }
            // List all registered users
            else if (command == listUsersCommand) {
                listUsers();
            }
            // Checks whether two users are friends
            else if (command == checkfriendsCommand) {
                if (inputNamesSize != 2) {
                    cout << "Incorrect number of usernames" << endl;
                    break;
                }

                tokenizer.nextToken(token);
                string userName1 = token;
                tokenizer.nextToken(token);
                string userName2 = token;

                if (samePerson(userName1, userName2)) {
                    break;
                } 

                checkFriends(userName1, userName2);
            }
            // Exit the program
            else if (command == quitCommand) {
                cout << "Exiting Sitzes Social System" << endl;
                exit(0);
            } else {
                cout << "Error... unrecognizable command" << endl;
                printInstructions();
            }
        }
    }
}

void GameLogic::registerUser(string userName) {
    if (!isUser(userName)) {
        User * user = new User(userName);
        userHashtable.set(user->getName(), user);
        cout << "Registered " << userName << " as a new user." << endl;
    } else {
        cout << userName << " is already registered." << endl;
    }
}

void GameLogic::unregisterUser(string userName) {
    if (isUser(userName)) {
        User *user = userHashtable.get(userName);
        int i = 0;

        // For each friend that a user has, remove them from the friendHashmap
        while (i < user->getSize()) {
            string usersFriendsName = user->getFriendsName(i);
            unfriendUsers(userName, usersFriendsName);
        }

        // Remove user from userHashtable
        userHashtable.remove(userName);

        cout << "Deactivated user: " << userName << endl;
    } else {
        cout << userName << " is not a registered user." << endl;
    }
}

void GameLogic::friendUsers(string userName1, string userName2) {
    if (checkTwoUsersExist(userName1, userName2)) {
        if (!areFriends(userName1, userName2)) {
            string name1 = userName1 + userName2;
            string name2 = userName2 + userName1;

            User *user1 = userHashtable.get(userName1);
            User *user2 = userHashtable.get(userName2);

            user1->setFriend(*&user2);
            user2->setFriend(*&user1);

            friendshipHashtable.set(name1, true);
            friendshipHashtable.set(name2, true);

            cout << userName1 << " and " << userName2 << " are now friends!" << endl;
        } else {
            cout << userName1 << " and " << userName2 << " are already friends... cannot 'double' friend." << endl;
            return;
        }
    } else {
        cout << userName1 << " and " << userName2 << " are not both registered users... cannot unfriend." << endl;        
    }
}

void GameLogic::unfriendUsers(string userName1, string userName2) {
    if (checkTwoUsersExist(userName1, userName2)) {
        if (areFriends(userName1, userName2)) {

            User *user1 = userHashtable.get(userName1);
            User *user2 = userHashtable.get(userName2);

            string name1 = userName1 + userName2;
            string name2 = userName2 + userName1;

            friendshipHashtable.remove(name1);
            friendshipHashtable.remove(name2);

            user1->removeFromFriendsList(userName2);
            user2->removeFromFriendsList(userName1);

            cout << "Unfriended " << userName1 << " and " << userName2 << endl;
        } else {
            cout << userName1 << " and " << userName2 << " not friends... cannot unfriend." << endl;
            return;
        }
    } else {
        cout << userName1 << " and " << userName2 << " are not both registered users... cannot unfriend." << endl;        
    }
}

void GameLogic::list(string userName) {
    if (isUser(userName)) {
        userHashtable.list(userName);
    }
    else {
        cout << userName << " is not a registered user." << endl;
    }
}

void GameLogic::listUsers() {
    cout << "Listing all registered users: " << endl;
    userHashtable.printUsers();
}

void GameLogic::checkFriends(string userName1, string userName2) {

    if (!checkTwoUsersExist(userName1, userName2)) {
        cout << userName1 << " and " << userName2 << " are not both registered users... cannot perform operation." << endl;
        return;
    }

    if (areFriends(userName1, userName2)) {
        cout << userName1 << " and " << userName2 << " are friends." << endl;
    } else {
        cout << userName1 << " and " << userName2 << " are not friends." << endl;
    }
}

void GameLogic::printInstructions() {
    cout << endl << endl << "Legal commands: " << endl
        << "Register a user: register <name>" << endl
        << "Unregister a user: unregister <name>" << endl
        << "Friend two users: friend <name1> <name2>" << endl
        << "Unfriend two users: unfriend <name1> <name2>" << endl
        << "List all registered users: listusers" << endl
        << "List all friends for a user: list <name>" << endl
        << "Check if two users are friends: checkfriend <name1> <name2>" << endl
        << "Exit the program: quit" << endl << endl;
}

bool GameLogic::areFriends(string userName1, string userName2) {
    if (!checkTwoUsersExist(userName1, userName2)) {
        cout << userName1 << " and " << userName2 << " are not both registered users... cannot perform operation." << endl;
        return false;
    }

    string combinedName = userName1 + userName2;

    if (friendshipHashtable.has(combinedName)) {
        return true;
    }
    return false;
}

bool GameLogic::samePerson(string userName1, string userName2) {
    if (userName1 == userName2) {
        cout << userName1 << " and " << userName2 << " are the same person." << endl;
        return true;
    }
    return false;
}

bool GameLogic::isUser(string userName) {
    if (userHashtable.has(userName)) {
        return true;
    }
    return false;
}

bool GameLogic::checkTwoUsersExist(string userName1, string userName2) {
    if (isUser(userName1) && isUser(userName2)) {
        return true;
    }
    return false;
}
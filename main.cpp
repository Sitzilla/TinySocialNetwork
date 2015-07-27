#include <iostream>
#include "basic.h"
#include "user.h"
#include "friendhash.h"
#include "tokenizer.h"

using namespace std;
void makeFriends(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName1, string userName2);
bool checkTwoUsersExist(BasicHT &userHashtable, string userName1, string userName2);
void registerUser(BasicHT &userHashtable, string name);
void unfriendUsers(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName1, string userName2);
bool checkFriends(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName1, string userName2);
void unregisterUser(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName);
void list(BasicHT &userHashtable, string name);
void printInstructions();


void startGameLoop(BasicHT &userHashtable, FriendHash &friendshipHashtable) {

    // REORDER EVERYTHING TO BE LOGICAL
    string quitCommand = "quit";
    string listUsersCommand = "listusers";
    string listCommand = "list";
    string registerCommand = "register";
    string friendCommand = "friend";
    string unfriendCommand = "unfriend";
    string unregisterCommand = "unregister";
    string checkfriendsCommand = "checkfriends";

    cout << "Welcome to the Sitzes Social System!" << endl;
    printInstructions();

    while (true) {
        while (true) {

            string input;
            Tokenizer tokenizer;
            string token;

            cout << "Enter in a command..." << endl;
            getline(cin, input);

            tokenizer.tokenize(input);
            tokenizer.nextToken(token);

            string command = token;


            // Exit the program
            if(command == quitCommand) {
                cout << "Exiting Sitzes Social System" << endl;
                exit(0);          
            }
            // Print out all friends for a User
            else if(command == listCommand) {
                tokenizer.nextToken(token);
                list(userHashtable, token);                  
            }
            // Registers a User in the system
            else if(command == registerCommand) {
                
                tokenizer.nextToken(token);
                registerUser(userHashtable, token);    
            }
            // Friends two users
            else if(command == friendCommand) {
                tokenizer.nextToken(token);
                string userName1 = token;
                tokenizer.nextToken(token);
                string userName2 = token;

                makeFriends(userHashtable, friendshipHashtable, userName1, userName2);
            }        
            // Unfriends two users
            else if(command == unfriendCommand) {
                tokenizer.nextToken(token);
                string userName1 = token;
                tokenizer.nextToken(token);
                string userName2 = token;

                unfriendUsers(userHashtable, friendshipHashtable, userName1, userName2);
            }
            // Unregisters a user
            else if(command == unregisterCommand) {
                tokenizer.nextToken(token);
                unregisterUser(userHashtable, friendshipHashtable, token);
            }
            // List all registered users
            else if(command == listUsersCommand) {
                list(userHashtable, token);
            } else {
                cout << "Error... unrecognizable command" << endl;
                printInstructions();
            }
        }
    }
}

void printInstructions() {
    cout << "Legal commands: " << endl
    << "Register a user: register <name>" << endl
    << "Unregister a user: unregister <name>" << endl
    << "Friend two users: friend <name1> <name2>" << endl
    << "Unfriend two users: unfriend <name1> <name2>" << endl
    << "List all registered users: listusers" << endl
    << "List all friends for a user: list <name>" << endl
    << "Check if two users are friends: checkfriend <name1> <name2>" << endl
    << "Exit the program: quit" << endl;
}

// 'Make Friends' method.  Can possibly be refactored
void makeFriends(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName1, string userName2) {
    if (!checkFriends(userHashtable, friendshipHashtable, userName1, userName2)) {
        string name1 = userName1 + userName2;
        string name2 = userName2 + userName1;

        User *user1 = userHashtable.get(userName1);
        User *user2 = userHashtable.get(userName2);

        user1->setFriend(*&user1);
        user2->setFriend(*&user1);

        friendshipHashtable.set(name1, true);
        friendshipHashtable.set(name2, true);

        cout << userName1 << " and " << userName2 << " are now friends!" << endl;
    } else {
        cout << userName1 << " and " << userName2 << " are already friends... cannot 'double' friend.";
    }
}

bool checkFriends(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName1, string userName2) {

    if (!checkTwoUsersExist(userHashtable, userName1, userName2)) {
        cout << userName1 << " and " << userName2 << " are not both registered users... cannot perform operation.";
        return false;
    }
    string name1 = userName1 + userName2;
    string name2 = userName2 + userName1;

    if (friendshipHashtable.has(name1) && friendshipHashtable.has(name2)) {
        return true;
    }
    // cout << userName1 << " and " << userName2 << " are not friends." << endl;
    return false;
}


bool checkTwoUsersExist(BasicHT &userHashtable, string userName1, string userName2) {
    if (userHashtable.has(userName1) && userHashtable.has(userName2)) {
        return true;
    }
    return false;
}

void registerUser(BasicHT &userHashtable, string name) {
    User user(name);
    userHashtable.set(user.getName(), &user);
}

void unfriendUsers(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName1, string userName2) {
    if (checkFriends(userHashtable, friendshipHashtable, userName1, userName2)) {
        cout <<  "Unfriending " << userName1 << " and " << userName2 << endl;

        User *user1 = userHashtable.get(userName1);
        User *user2 = userHashtable.get(userName2);
        // CAN PROBABLY MODULARIZE THIS
        string name1 = userName1 + userName2;
        string name2 = userName2 + userName1;

        friendshipHashtable.remove(name1);
        friendshipHashtable.remove(name2);

        user1->removeFromFriendsList(userName2);
        user2->removeFromFriendsList(userName1);
    } else {
        cout << userName1 << " and " << userName2 << " are not both registered users... cannot unfriend.";
    }
}

void unregisterUser(BasicHT &userHashtable, FriendHash &friendshipHashtable, string userName) {
    User *user = userHashtable.get(userName);

    // For each friend that a user has, remove them from the friendHashmap
    for (int i = 0; i < user->getSize(); i++) {
        string usersFriendsName = user->getFriendsName(i);
        unfriendUsers(userHashtable, friendshipHashtable, userName, usersFriendsName);
    }
    
    // Remove user from userHashtable
    userHashtable.remove(userName);

    // Clear users friendlist
    user->clearFriendlist();
}

void listUsers(BasicHT &userHashtable) {
    cout << "Listing all registered users: " << endl;
    userHashtable.printUsers();
}

void list(BasicHT &userHashtable, string name) {
    userHashtable.list(name);
}

int main() {
    BasicHT userHashtable(5);
    FriendHash friendshipHashtable(5);

    startGameLoop(userHashtable, friendshipHashtable);

    return 0;
}
#include <iostream>
#include "basic.h"
#include "user.h"
#include "friendhash.h"

using namespace std;


// 'Make Friends' method.  Can possibly be refactored
void makeFriends(FriendHash &friendshipHashmap, User &user1, User &user2) {
    string name1 = user1.getName() + user2.getName();
    string name2 = user2.getName() + user1.getName();

    user1.setFriend(&user2);
    user2.setFriend(&user1);

    // Sets the friends in the friendship hashmap
    friendshipHashmap.set(name1, true);
    friendshipHashmap.set(name2, true);

    cout << user1.getName() << " and " << user2.getName() << " are now friends!" << endl;

}

User registerUser(BasicHT &userHashmap, string name) {
    User user(name);
    userHashmap.set(user.getName(), &user);
    return user;
}

void unfriendUsers(FriendHash &friendshipHashmap, User &user1, User &user2) {
    // CHECK IF ALREADY FRIENDS
    string nameUser1 = user1.getName();
    string nameUser2 = user2.getName();

    cout <<  "Unfriending " << nameUser1 << " and " << nameUser2 << endl;

    // CAN PROBABLY MODULARIZE THIS
    string name1 = nameUser1 + nameUser2;
    string name2 = nameUser2 + nameUser1;

    friendshipHashmap.remove(name1);
    friendshipHashmap.remove(name2);

    user1.removeFromFriendsList(nameUser2);
    user2.removeFromFriendsList(nameUser1);
}

bool checkFriends(FriendHash &friendshipHashmap, string nameUser1, string nameUser2) {
    // CAN PROBABLY MODULARIZE THIS
    string name1 = nameUser1 + nameUser2;
    string name2 = nameUser2 + nameUser1;

    if (friendshipHashmap.has(name1) && friendshipHashmap.has(name2)) {
        cout << nameUser1 << " and " << nameUser2 << " are friends." << endl;
        return true;
    }
    cout << nameUser1 << " and " << nameUser2 << " are not friends." << endl;
    return false;
}


void unregisterUser(BasicHT &userHashmap, FriendHash &friendshipHashmap, User &user) {
    string nameUser = user.getName();

    // For each friend that a user has, remove them from the friendHashmap
    for (int i = 0; i < user.getSize(); i++) {
        User *usersFriend = userHashmap.get(user.getFriendsName(i));
        unfriendUsers(friendshipHashmap, user, *usersFriend);
    }
    
    // Remove user from UserHashmap
    userHashmap.remove(nameUser);

    // Clear users friendlist
    user.clearFriendlist();
}

void list(BasicHT &userHashmap, User &user) {
    userHashmap.list(user.getName());
}

int main() {
    BasicHT userHashmap(1);
    FriendHash friendshipHashmap(1);

    User user1 = registerUser(userHashmap, "Evan");
    User user2 = registerUser(userHashmap, "Scott");
    User user3 = registerUser(userHashmap, "Dempe");
    User user4 = registerUser(userHashmap, "Kenny");
 
    // userHashmap.set(user1.getName(), &user1);
    // userHashmap.set(user2.getName(), &user2); 
    // userHashmap.set(user3.getName(), &user3);  

    // bool areFriends;
    makeFriends(friendshipHashmap, user1, user2);
    makeFriends(friendshipHashmap, user1, user3);
    makeFriends(friendshipHashmap, user1, user4);
    makeFriends(friendshipHashmap, user3, user4);


    // cout << "Friend list: " << endl;
    // user1.printFriends();
        
    // list(userHashmap, user1);

    // unregisterUser(userHashmap, friendshipHashmap, user3);


    checkFriends(friendshipHashmap, "Evan", "Kenny");
    checkFriends(friendshipHashmap, "Scott", "Kenny");

    // list(userHashmap, user1);

    // cout << "Friend list now: " << endl;
    // user1.printFriends();

    // cout << userHashmap.get(user1.getName());

    return 0;
}
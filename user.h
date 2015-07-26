#ifndef USER_H
#define USER_H

#include <vector>
using namespace std;

class User
{
    public:
        User(string pName);
        string getName();
        string getFriendsName(int i);
        void setFriend(User *newFriend);
        void removeFriend(string friendName);
        void removeFromFriendsList(string friendName);
        void printFriends();
        int getSize();
        void clearFriendlist();
        

    private:
        string name;
        int size;
        vector<User *> friendList;

};

#endif

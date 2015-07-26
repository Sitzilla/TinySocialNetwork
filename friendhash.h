#ifndef FRIENDHASH_H
#define FRIENDHASH_H

#include <vector>
using namespace std;

class FriendHash
{
    public:
        FriendHash(int capacity = 257);
        FriendHash(const FriendHash &other);
        ~FriendHash();
        void set(string key, bool val);
        const bool *get(string key) const;
        bool has(string key) const;
        int size() const;
        void remove(string key);

    private:
        void resize();
        int n;
        int hash(string key) const;
        vector<bool *> vals;
        vector<string *> keys;
};

#endif

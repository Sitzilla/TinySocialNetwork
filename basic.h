#ifndef BASIC_H
#define BASIC_H

#include <vector>
#include "user.h"
using namespace std;

class BasicHT
{
    public:
        BasicHT(int capacity = 257);
        BasicHT(const BasicHT &other);
        ~BasicHT();
        void set(string key, User *val);
        User * get(string key);
        bool has(string key);
        int size() const;
        void remove(string key);
        void list(string key);
        void printUsers();

    private:
        void resize();
        int n;
    	int hash(string key) const;
    	vector<User *> vals;
        vector<string *> keys;
};

#endif

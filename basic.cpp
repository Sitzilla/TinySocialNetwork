#include <iostream>
#include "basic.h"
#include "user.h"

using namespace std;

BasicHT::BasicHT(int capacity)
: vals(capacity), keys(capacity) {
    n = 0;
}

BasicHT::BasicHT(const BasicHT &other)
: vals(other.vals.size()), keys(other.keys.size())
{
    for (int i = 0; i < vals.size(); i++)
    {
        if (other.vals[i] != NULL)
        {
            vals[i] = new User(*other.vals[i]);
        }
    }

    for (int i = 0; i < keys.size(); i++)
    {
        if (other.keys[i] != NULL)
        {
            keys[i] = new string(*other.keys[i]);
        }
    }
}

BasicHT::~BasicHT()
{
    for (int i = 0; i < vals.size(); i++)
    {
        delete vals[i];
    }

    for (int i = 0; i < keys.size(); i++)
    {
        delete keys[i];
    }
}

void BasicHT::remove(string key)
{
    int i = hash(key);
    while (keys[i] != NULL && *keys[i] != key)
    {
        i = (i + 1) % keys.size();
    }

    if (keys[i] != NULL)
    {
        int j = (i + 1) % keys.size();
        int k;
        while (keys[j] != NULL)
        {
            k = hash(*keys[j]);
            if ((j > i && (k <= i || k > j))
                || (j < i && k <= i && k > j))
            {
                keys[i] = keys[j];
                vals[i] = vals[j];
                i = j;
            }
            j = (j + 1) % keys.size();
        }
        delete keys[i];
        delete vals[i];
        keys[i] = NULL;
        vals[i] = NULL;
    }
}

void BasicHT::list(string key) {
    int i = hash(key);
    vals[i]->printFriends();
}


void BasicHT::resize()
{
    vector<string *> keysCopy(keys);
    vector<User *> valsCopy(vals);

    int newSize = keys.size() * 2;

    keys.clear();
    vals.clear();

    keys.resize(newSize);
    vals.resize(newSize);

    for (int i = 0; i < keysCopy.size(); i++)
    {
        if (keysCopy[i] != NULL)
        {
            set(*keysCopy[i], valsCopy[i]);
        }
    }
}

void BasicHT::set(string key, User *&val)
{
    int i = hash(key);
    while (keys[i] != NULL && *keys[i] != key)
    {
        i = (i + 1) % keys.size();
    }
    if (keys[i] == NULL) {
        n++;
    }

    keys[i] = new string(key);
    vals[i] = val;

    if (n / (double)keys.size() > 0.6)
    {
        resize();
    }
}

User *BasicHT::get(string key)
{
    int i = hash(key);
    while (keys[i] != NULL && *keys[i] != key)
    {
        i = (i + 1) % keys.size();
    }
    return vals[i];
}


int BasicHT::hash(string key) const
{
    // int x = 0;
    // for (int i = 0; i < key.length(); i++)
    // {
    //     x = x * 31 + key[i];
    // }
    // return x % vals.size();
    int x = 0;
    for(int i = 0; i < key.size(); i++)
    {
        x = x * 31 + key[i];
    }
    x %= key.size();
    if(x < 0)
    {
        x += key.size();
    }
    return x;
}

void BasicHT::printUsers() {

    for (int i = 0; i < vals.size(); i++) {
        if (vals[i] != NULL) {
            cout << vals[i]->getName() << endl;
        }
    }

}

bool BasicHT::has(string key) {
    return get(key) != NULL;
}

int BasicHT::size() const {
    return n;
}
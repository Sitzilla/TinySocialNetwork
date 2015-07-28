#include <iostream>
#include "friendhash.h"

using namespace std;

FriendHash::FriendHash(int capacity)
: vals(capacity), keys(capacity) {
    n = 0;
}

FriendHash::FriendHash(const FriendHash &other)
: vals(other.vals.size()), keys(other.keys.size())
{
    for (int i = 0; i < vals.size(); i++)
    {
        if (other.vals[i] != NULL)
        {
            vals[i] = new bool(*other.vals[i]);
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

FriendHash::~FriendHash()
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

void FriendHash::remove(string key)
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
        keys[i] = NULL;
        vals[i] = NULL;
    }
}

void FriendHash::resize()
{
    vector<string *> keysCopy(keys);
    vector<bool *> valsCopy(vals);

    int newSize = keys.size() * 2;

    keys.clear();
    vals.clear();

    keys.resize(newSize);
    vals.resize(newSize);

    for (int i = 0; i < keysCopy.size(); i++)
    {
        if (keysCopy[i] != NULL)
        {
            set(*keysCopy[i], *valsCopy[i]);
            delete keysCopy[i];
            delete valsCopy[i];
        }
    }
}

void FriendHash::set(string key, bool val)
{
    int i = hash(key);
    while (keys[i] != NULL && *keys[i] != key)
    {
        i = (i + 1) % keys.size();
    }
    if (keys[i] != NULL)
    {
        delete keys[i];
        delete vals[i];
    }
    else {
        n++;
    }

    keys[i] = new string(key);
    vals[i] = new bool(val);

    if (n / (double)keys.size() > 0.6)
    {
        resize();
    }
}

const bool * FriendHash::get(string key) const
{
    int i = hash(key);
    while (keys[i] != NULL && *keys[i] != key)
    {
        i = (i + 1) % keys.size();
    }
    return vals[i];
}


int FriendHash::hash(string key) const
{
    int x = 0;
    for (int i = 0; i < key.length(); i++)
    {
        x = x * 31 + key[i];
    }
    return x % vals.size();
}

bool FriendHash::has(string key) const {
    return get(key) != NULL;
}

int FriendHash::size() const {
    return n;
}
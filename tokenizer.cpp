/*
 * File:	tokenizer.cpp
 * Author:	Luke Godfrey
 */

#include <iostream>
#include <sstream>
#include "tokenizer.h"
using namespace std;

Tokenizer::Tokenizer() {}

void Tokenizer::tokenize(string str)
{
	string token;

	stringstream ss(str);
	while(!ss.eof())
	{
		ss >> token;
		tokens.push_back(token);
	}
}

bool Tokenizer::nextToken(string &str)
{
	if(tokens.size() == 0)
	{
		return false;
	}

	str = tokens[0];
	tokens.erase(tokens.begin());

	return true;
}


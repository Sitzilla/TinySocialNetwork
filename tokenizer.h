/*
 * File:	tokenizer.h
 * Author:	Luke Godfrey
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
using namespace std;

class Tokenizer
{
	public:
		Tokenizer();
		void tokenize(string str);
		bool nextToken(string &str);
        
	private:
		vector<string> tokens;
};

#endif


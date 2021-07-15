#ifndef HEADER_TOKENIZER
#define HEADER_TOKENIZER

#include <string>
#include <boost/algorithm/string.hpp>
#include <bits/stdc++.h>

using namespace std;

class Tokenizer{
	public:
		Tokenizer();
		~Tokenizer();
		
		void tokenizer_line(string line);
		void set_delimiter(string d);
		bool empty();
		int  sizeof_toks();
		
		string last();
		string next();
 

    private:
    	string delimiter;
    	string *token;
    	vector<string> tokens;
};

#endif

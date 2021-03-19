#include "tokenizer.h"

Tokenizer::Tokenizer(){
	tokens.clear();
	delimiter.clear();
}

Tokenizer::~Tokenizer(){
	tokens.clear();
	delimiter.clear();
}

void Tokenizer::set_delimiter(string d){
	delimiter  = d;
}

void Tokenizer::tokenizer_line(string line){
	tokens.clear();
	boost::algorithm::split(tokens, line, boost::is_any_of(delimiter));
}

string Tokenizer::last(){
	string item;

	if(!tokens.empty()){
		item = tokens.back();
		tokens.pop_back();
	}

	return item;
}

bool Tokenizer::empty(){
	return tokens.empty();
}

string Tokenizer::next(){
	string item; 
	
	if(!tokens.empty()){
		item = tokens.front();
		tokens.erase(tokens.begin());
	}

	return item;
}

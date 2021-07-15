#include "tokenizer.h"

Tokenizer::Tokenizer(){
	this->tokens.clear();
	delimiter.clear();
}

Tokenizer::~Tokenizer(){
	this->tokens.clear();
	delimiter.clear();
}

void Tokenizer::set_delimiter(string d){
	delimiter  = d;
}

void Tokenizer::tokenizer_line(string line){
	this->tokens.clear();
	boost::algorithm::split(this->tokens, line, boost::is_any_of(delimiter));
}

string Tokenizer::last(){
	string item;

	if(!this->tokens.empty()){
		item = this->tokens.back();
		this->tokens.pop_back();
	}
	
	return item;
}

bool Tokenizer::empty(){
	return this->tokens.empty();
}

int Tokenizer::sizeof_toks(){
	return this->tokens.size();
}

string Tokenizer::next(){
	string item; 
	
	if(!this->tokens.empty()){
		item = this->tokens.front();
		this->tokens.erase(this->tokens.begin());
	}

	return item;
}

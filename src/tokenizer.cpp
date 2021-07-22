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

int Tokenizer::sizeof_toks(){
	return this->tokens.size();
}

bool Tokenizer::empty(){
	return this->tokens.empty();
}

string Tokenizer::next(){
	std::string item; 
	
	if(!this->tokens.empty()){
		item = this->tokens.front();
		this->tokens.erase(this->tokens.begin());
	}

	std::string::iterator end_pos = std::remove(item.begin(), item.end(), ' ');
	item.erase(end_pos, item.end());

	return item;
}

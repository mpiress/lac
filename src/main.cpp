#include<stdio.h>
#include<stdlib.h>
#include "lac.h"



/*
int main(int argc, char const *argv[])
{
	LAC *lac = new LAC();
	list<string> rule;
	lac->preprocessing("dataset/census.test");
	map<string, list<float> > resp;
	map<string, list<float> >::iterator it;
	list<float>::iterator itl;
	list<float> aux;
	string classe;

	rule.push_back("(12,0.000000)");
	rule.push_back("(13,0.000000)");
	rule.push_back("(14,0.198594)");

	resp = lac->getRule(0.0, 0.0, &rule);
	for(it=resp.begin(); it != resp.end(); ++it){
		printf("CLASSE:%s\n", it->first.c_str());
		for(itl = it->second.begin(); itl != it->second.end(); ++itl){
			printf("VALOR:%f\n", *itl);
		}
	}

	return 0;
}
*/
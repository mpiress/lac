#ifndef LAC_H 
#define LAC_H

#include <list>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <boost/python.hpp>
#include <boost/foreach.hpp>
#include "tokenizer.h"


using namespace std;

class C_LAC{

	private:
		unordered_map< string, vector<int> > features;
		unordered_map< string, vector<int> > classes;
		int size_of_train;
		float minsup, minconf;
		string path;

	public:
		~C_LAC();
		C_LAC(float minsup, float minconf, string path);
		void preprocessing();
		void printFeatures();
		void printClasses();
		void getRule(list<string> rule, unordered_map<string, list<float> > &resp);
		boost::python::dict execute_task(boost::python::list &task);
		boost::python::list get_itemset(boost::python::list &task);
};

#endif

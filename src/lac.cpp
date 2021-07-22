#include "lac.h"

C_LAC::C_LAC(float minsup, float minconf, string path){
  this->path = path;//"../dataset/census.test";
  this->minsup = minsup;
  this->minconf = minconf;
}

C_LAC::~C_LAC(){
	features.clear();
  classes.clear();
}

void C_LAC::preprocessing(){
	Tokenizer *toks = new Tokenizer();
	string line, key; 
  string it;
	int index, ifeature, sizeof_toks;
  string delimiter (",");
  
	ifstream myfile(this->path);
  if (myfile.is_open())
		index = 0;
  
  toks->set_delimiter(delimiter);
  
	while (getline(myfile,line)){
    
    toks->tokenizer_line(line);
    
    it = toks->next();
    ifeature = 0;
    sizeof_toks = toks->sizeof_toks();
    while(ifeature < sizeof_toks){
      
      it = "(" + to_string(ifeature) + "," + it + ")";
      
      if(features.find(it) != features.end()){
          features[it].push_back(index);
      }else{
          vector<int> f;
          f.push_back(index);
          features.insert(pair<string, vector<int> >(it, f));
      }
      
      it = toks->next();
      ifeature ++;
    }

    if(classes.find(it) != classes.end()){
      classes[it].push_back(index);
    }else{
      vector<int> f;
      f.push_back(index);
      classes.insert(pair<string, vector<int> >(it, f));
    }
    
    index ++;

	}
  
  size_of_train = index;
  myfile.close();

  cout << "FEATURES:" << features.size() << "\n";

}

void C_LAC::getRule(list<string> rule, unordered_map<string, list<float> > &resp){
      vector<vector<int> > aux;
      list<string>::iterator it;
      vector<int> l1, l2, l3;
      int size_l; 
      float sup, conf;
      unordered_map<string, vector<int> >::iterator itc;
      
      for(it = rule.begin(); it != rule.end(); ++it){
        if(features.find(*it) != features.end())
            aux.push_back(features[*it]);
      }

      if(!aux.empty()){
        l1 = aux.front();
        aux.erase(aux.begin());
        while(!aux.empty()){
              l2 = aux.front();
              aux.erase(aux.begin());
              //std::sort(l1.begin(), l1.end());
              //std::sort(l2.begin(), l2.end());
              std::set_intersection(l1.begin(), l1.end(), l2.begin(), l2.end(), back_inserter(l3));
              l1 = l3;
              l3.clear();
        }

        if(!l1.empty()){
              size_l = l1.size();
              //std::sort(l1.begin(), l1.end());
              for(itc=classes.begin(); itc != classes.end(); ++itc){
                  string classe = itc->first;
                  l2 = itc->second;
                  //std::sort(l2.begin(), l2.end());
                  std::set_intersection(l1.begin(), l1.end(), l2.begin(), l2.end(), back_inserter(l3));
                  if(!l3.empty()){
                        sup = (float) l3.size()/size_of_train;
                        if(sup >= minsup){
                              resp[itc->first].push_back(sup);
                              conf = l3.size()/size_l;
                              if(conf >= minconf)
                                    resp[itc->first].push_back(conf);
                        }
                  }

                  l3.clear();
              }
        }
    }
}

boost::python::list C_LAC::get_itemset(boost::python::list &task){
  boost::python::list pylist;

  for (int i = 0; i < len(task); ++i){
    string key = boost::python::extract<string>(task[i]);
    if(features.find(key) != features.end())
      pylist.append(key);
  }

  return pylist;
}


boost::python::dict C_LAC::execute_task(boost::python::list &task){
	string delimiter = " ";
  unordered_map<string, list<float> > resp;
  unordered_map<string, list<float> >::iterator itm;
	list<list<string> >::iterator itl;
	boost::python::dict dictionary;
  Tokenizer *toks = new Tokenizer();
  list<string> rule;
  list<string>::iterator rit;
  
  toks->set_delimiter(delimiter);
  
  for (int i = 0; i < len(task); ++i){
    string value = boost::python::extract<string>(task[i]);
    toks->tokenizer_line(value);
    
    string it = toks->next();
    //it = it.erase(remove(it.begin(), it.end(), ' '), it.end());

    while(!toks->empty()){
      rule.push_back(it);
      it = toks->next();
      //if(it != NULL)
        //it = it.erase(remove(it.begin(), it.end(), ' '), it.end());
    }

    getRule(rule, resp);
    rule.clear();
    
  }

	for(itm=resp.begin(); itm != resp.end(); ++itm){
    boost::python::list pylist;
    BOOST_FOREACH(float f, itm->second) pylist.append(f);
    dictionary[itm->first] = pylist;
  }
  
	return dictionary;
}

void C_LAC::printFeatures(){
  unordered_map< string, vector<int> >::iterator mit;
  vector<int>::iterator lit;

  for(mit=features.begin(); mit != features.end(); ++mit){
    printf("FEATURE: %s\n", mit->first.c_str());
  }
  
}

void C_LAC::printClasses(){
  unordered_map< string, vector<int> >::iterator mit;
  vector<int>::iterator lit;

  for(mit=classes.begin(); mit != classes.end(); ++mit){
    printf("CLASSE: %s\n", mit->first.c_str());
  }
  
}


BOOST_PYTHON_MODULE(lac){
  using namespace boost::python;
  class_<C_LAC>("C_LAC", init<float,float,string>())
    .def("preprocessing", &C_LAC::preprocessing)
    .def("execute_task", &C_LAC::execute_task)
    .def("showFeatures", &C_LAC::printFeatures)
    .def("showClasses", &C_LAC::printClasses)
    .def("get_itemset", &C_LAC::get_itemset)
  ;

}





#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include "Joiner.hpp"
#include "Parser.hpp"

#define NUM_THREAD 60

using namespace std;
Joiner joiner;

string * line_[NUM_THREAD];
string * thread_ret[NUM_THREAD];
pthread_t threads[NUM_THREAD];
void* ThreadFunc(void* arg) {
   long index = (long)arg;
   QueryInfo i;
   string &line = *(line_[index]);
   i.parseQuery(line);
   thread_ret[index] = new string(joiner.join(i));
   return nullptr;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {

   // Read join relations
   string line;
   while (getline(cin, line)) {
      if (line == "Done") break;
      joiner.addRelation(line.c_str());
   }
   // Preparation phase (not timed)
   // Build histograms, indexes,...
   //
   
   long i = 0;
   while (getline(cin, line)) {
      if (line == "F"){ // End of a batch
        for(int j = 0 ; j < i ; ++j){
          pthread_join(threads[j], NULL);
          string& ret =  *(thread_ret[j]);
	  cout << ret << std::flush;
          delete line_[j];
	  delete thread_ret[j];
	}
        i = 0;
        continue;
      }
      line_[i] = new string(line);
      pthread_create(&threads[i], 0, ThreadFunc, (void*)i);
      ++i;

      if(i == NUM_THREAD){
        for(int j = 0 ; j < NUM_THREAD ; ++j){
          pthread_join(threads[j], NULL);
          string& ret =  *(thread_ret[j]);
	  cout << ret << std::flush;
          delete line_[j];
	  delete thread_ret[j];
	}
        i = 0;
      }
   }

   for(int j = 0 ; j < i ; ++j){
      pthread_join(threads[j], NULL);
      string& ret =  *(thread_ret[j]);
      cout << ret ;
      delete line_[j];
      delete thread_ret[j];
   }

   return 0;
}


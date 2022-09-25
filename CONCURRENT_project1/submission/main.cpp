#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include "Joiner.hpp"
#include "Parser.hpp"

#define NUM_THREAD 1

using namespace std;
Joiner joiner;

string * line_[NUM_THREAD];
string * thread_ret[NUM_THREAD];
pthread_t threads[NUM_THREAD];
void* ThreadFunc(void* arg) {
   long index = (long)arg;
   QueryInfo i;
   i.parseQuery(*(line_[index]));
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
      if (line == "F") continue; // End of a batch
      line_[i] = new string(line);
      pthread_create(&threads[i], 0, ThreadFunc, (void*)i);
      ++i;

      if(i == NUM_THREAD){
        for(int j = 0 ; j < NUM_THREAD ; ++j){
          pthread_join(threads[j], NULL);
	  cout << *(thread_ret[j]) << std::flush;
          delete line_[j];
	  delete thread_ret[j];
	}
        i = 0;
      }
   }

   for(int j = 0 ; j < i ; ++j){
      pthread_join(threads[j], NULL);
      cout << *(thread_ret[j]);
      delete line_[j];
      delete thread_ret[j];
   }

   return 0;
}

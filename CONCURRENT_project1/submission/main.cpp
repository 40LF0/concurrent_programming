#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include "Joiner.hpp"
#include "Parser.hpp"

#define NUM_THREAD 60

using namespace std;
/// joiner is shared for all threads
Joiner joiner;
/// line_ store string info about query
string * line_[NUM_THREAD];
/// thread_ret store outcome about join execution
string * thread_ret[NUM_THREAD];
/// array for thread
pthread_t threads[NUM_THREAD];

///ThreadFunc do join execution
/// 1. get info about thread index(tid)
/// 2. get info about input string(query info)
/// 3. parse query
/// 4. do join execution and store result to thread_ret
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
   

   /// i is for thread index(thread_id) and checking number of workers(threads).
   long i = 0;
   while (getline(cin, line)) {
      /// At the end of a batch, we should flush batch outcome.
      /// To do that, we wait and print out outcome.
      if (line == "F"){ // End of a batch
        for(int j = 0 ; j < i ; ++j){
          pthread_join(threads[j], NULL);
          string& ret =  *(thread_ret[j]);
	  cout << ret << std::flush;
          delete line_[j];
	  delete thread_ret[j];
	}
        /// becasue there is no worker, we should init i to 0;
        i = 0;
        continue;
      }
      /// store query info to line_
      /// create worker thread and increment i
      line_[i] = new string(line);
      pthread_create(&threads[i], 0, ThreadFunc, (void*)i);
      ++i; 
   

      /// If there is no available worker thread, we should wait for threads finishing their jobs
      /// After finishing jobs, we flush outcomes.
      if(i == NUM_THREAD){
        for(int j = 0 ; j < NUM_THREAD ; ++j){
          pthread_join(threads[j], NULL);
          string& ret =  *(thread_ret[j]);
	  cout << ret << std::flush;
          delete line_[j];
	  delete thread_ret[j];
	}
        /// becasue there is no worker, we should init i to 0;
        i = 0;
      }
   }
   // End of input query
   // all threads must be join to main thread.
   for(int j = 0 ; j < i ; ++j){
      pthread_join(threads[j], NULL);
      string& ret =  *(thread_ret[j]);
      cout << ret ;
      delete line_[j];
      delete thread_ret[j];
   }

   return 0;
}


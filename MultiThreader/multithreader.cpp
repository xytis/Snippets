#include <iostream>

#include <pthread.h>
#include <vector>

typedef std::vector<pthread_t> Threads;
typedef std::vector<pthread_t>::Iterator ThreadsIterator;

Threads _threads;

void thread_starter()
{
  pthread_create( &thread, NULL, &thread_function, NULL);
}

int main(int argc, char* argv[])
{
  
  for (ThreadsIterator i = _threads.begin(); 
  return 0;
}
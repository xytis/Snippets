#include "dz_watch.hpp"

ThreadWatcher::ThreadWatcher(const char* filename, int line, const char* msg):
m_msg(msg),
m_file(filename),
m_line(line)
{
  barrier = PTHREAD_COND_INITIALIZER;
  mutex = PTHREAD_MUTEX_INITIALIZER;
}

ThreadWatcher::~ThreadWatcher()
{
  //Nothing?
}

void ThreadWatcher::entry()
{
  entry_time = clock();
  pthread_create( &thread, NULL, &thread_function, this);
}

void ThreadWatcher::process()
{
  pthread_cond_signal( &barrier );  
}

void ThreadWatcher::exit()
{
  pthread_cond_signal( &barrier );
  pthread_join( thread, NULL);
  //Output the gathered information
  double w = double(process_time - entry_time)/CLOCKS_PER_SEC;
  double p = double(exit_time - process_time)/CLOCKS_PER_SEC;
  if (m_msg != "") log << m_msg << ": ";
  log << "Thread at " << m_file << ":" << m_line << " wait: " << w << " process: " << p << std::endl;
}

void* thread_function(void* ptr)
{
  ThreadWatcher * caller = reinterpret_cast<ThreadWatcher *>(ptr);
  //Wait for process signal
  pthread_mutex_lock( &caller->mutex );
  pthread_cond_wait( &caller->barrier, &caller->mutex );
  caller->process_time = clock();
  pthread_mutex_unlock( &caller->mutex );
  //Wait for exit signal
  pthread_mutex_lock( &caller->mutex );
  pthread_cond_wait( &caller->barrier, &caller->mutex );
  caller->exit_time = clock();
  pthread_mutex_unlock( &caller->mutex );
  return NULL;
}
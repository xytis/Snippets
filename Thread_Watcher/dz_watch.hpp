#ifndef __THREAD_WATCHER_HPP_
#define __THREAD_WATCHER_HPP_

#define DZ_ENTRY ThreadWatcher thread_watcher(__FILE__, __LINE__); thread_watcher.entry()
#define DZ_ENTRY_MSG(a) ThreadWatcher thread_watcher(__FILE__, __LINE__, a); thread_watcher.entry()
#define DZ_PROCESS thread_watcher.process()
#define DZ_EXIT thread_watcher.exit()

#include <iostream>
#include <string>
#include <pthread.h>
#include <ctime>
#include "../Logger/Logger.hpp"

void* thread_function(void* ptr);

class ThreadWatcher
{
private:
  pthread_cond_t         barrier;
  pthread_mutex_t        mutex;
  pthread_t              thread;
  clock_t                entry_time;
  clock_t                process_time;
  clock_t                exit_time;
  std::string            m_msg;
  std::string            m_file;
  int                    m_line;
  friend void* thread_function(void* ptr);
public:
  ThreadWatcher(const char* filename, int line, const char* msg = "");
  ~ThreadWatcher();
  void entry();
  void process();
  void exit();
};

#endif
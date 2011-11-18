#include <iostream> 

#include "LoggerSystem.hpp"
#include "Priority.hpp"

int main()
{
  std::cout << "yay" << std::endl;
  Logger * logger = LoggerSystem::instance()->get();
  logger->log(Log::INFO) << "Hello again" << 5 << std::endl;
  return 0;
}
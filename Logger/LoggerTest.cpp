#include <iostream> 

#include "LoggerSystem.hpp"
#include "Logger.hpp"
#include "Priority.hpp"

int main()
{
  std::cout << "yay" << std::endl;
  Log::Logger * logger = LoggerSystem::instance()->build();
  logger->log(Log::INFO) << "Hello again" << std::endl;
  return 0;
}
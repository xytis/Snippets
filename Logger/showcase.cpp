#include <iostream>
#include <fstream>

#include "Logger.hpp"

std::string header (Log::PRIORITY)
{
  return "THIS IS SPARTA: ";
}

int main()
{
  log << "Some random info" << 4 << std::endl;
  err << "Some error" << std::endl;
  warn << "Some warning" << std::endl;
  debug << "debug text" << std::endl;
  
  logf("Simple String");
  errf("%d %d %d\n", 2112, 12, 21);
  warnf("THE WORLD WILL END IN %f SEC\n", 5);
  debugf("debug text\n");

  std::ofstream file("temp");
  
  Log::Logger::Instance()->set_output(Log::INFO, &file);
  Log::Logger::Instance()->set_header(header);

  log << "Some random info" << 4 << std::endl;
  err << "Some error" << std::endl;
  warn << "Some warning" << std::endl;
  debug << "debug text" << std::endl;
  
  logf("Simple String");
  errf("%d %d %d\n", 2112, 12, 21);
  warnf("THE WORLD WILL END IN %f SEC\n", 5);
  debugf("debug text\n");

  return 0;
}
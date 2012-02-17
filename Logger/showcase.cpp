#include <iostream>
#include <fstream>
#include "Logger.hpp"

#define my_print(format, ...) formated_output(std::cout, format , ##__VA_ARGS__)
#define my_debug(format, ...) formated_output(std::cout, (std::string("[%s:%d] ")+ std::string(format)).c_str(), __FILE__, __LINE__ , ##__VA_ARGS__)

void formated_output(std::ostream & output, const char *s)
{
  while (*s) {
    if (*s == '%' && *(++s) != '%')
      throw std::runtime_error("invalid format string: missing arguments");
    output << *s++;
  }
}

template<typename T, typename... Args>
void formated_output(std::ostream & output, const char *s, T value, Args... args)
{
  while (*s) {
    if (*s == '%' && *(++s) != '%') {
      output << value;
      ++s;
      formated_output(output, s, args...); // call even when *s == 0 to detect extra arguments
        return;
    }
    output << *s++;
  }
  throw std::logic_error("extra arguments provided to formated_output");
}

std::string header (Log::PRIORITY)
{
  return "THIS IS SPARTA: ";
}

int main()
{

  //Works
  log << "Some random info" << 4 << std::endl;
  err << "Some error" << std::endl;
  warn << "Some warning" << std::endl;
  debug << "debug text" << std::endl;

  my_print("Simple String\n");
  my_print("%d %d %d\n", 2112, 12, 21);
  //my_debug("THE WORLD WILL END IN %f SEC\n", 5);
  //my_debug("debug text\n");
  
  
  logf("Simple String");
  errf("%d %d %d\n", 2112, 12, 21);
  //warnf("THE WORLD WILL END IN %f SEC\n", 5);
  //debugf("debug text\n");
/*

  std::ofstream file("temp");
  
  Log::Logger::Instance()->set_output(Log::INFO, &file);
  Log::Logger::Instance()->set_header(header);

  log << "Some random info" << 4 << std::endl;
  err << "Some error";
  warn << "Some warning";
  debug << "debug text";
  
  logf("Simple String");
  errf("%d %d %d\n", 2112, 12, 21);
  warnf("THE WORLD WILL END IN %f SEC\n", 5);
  debugf("debug text\n");
*/
  return 0;
}
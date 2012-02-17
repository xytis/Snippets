#include "Logger.hpp"

namespace Log
{
  std::string empty(PRIORITY priority)
  {
    return "";
  }

  std::string date(PRIORITY priority)
  {
    return "today";
  }
  
  std::string date_priority(PRIORITY priority)
  {
    std::string post;
    switch (priority)
    {
      case ERROR:
        post = "error: ";
        break;
      case WARNING:
        post = "warning: ";
        break;
      case INFO:
        post = "info: ";
        break;
      case DEBUG:
        post = "debug: ";
        break;
      default:
        throw std::invalid_argument("unknown PRIORITY passed to date_priority");
    }
    return date(priority) + post;
  }

  Logger* Logger::m_instance = NULL;
  
  Logger* Logger::Instance()
  {
    //Not multithreading safe.
    return m_instance ? m_instance : m_instance = new Logger();
  }
  
  // Manually destroy an existing instance. Call at end of program to clean up.
  void Logger::destroy()
  {
    delete m_instance;
    m_instance = NULL;
  }

  Logger::Logger():
    log_stream(&std::cout),
    err_stream(&std::cout),
    warn_stream(&std::cout),
    debug_stream(&std::cout),
    header(empty),
    header_flag(true)
  {
    
  }
  
  Logger::~Logger()
  {
    
  }

  std::ostream & Logger::get_stream(PRIORITY priority)
  {
    switch (priority)
    {
      case ERROR:
        return *err_stream;
      case WARNING:
        return *warn_stream;
      case INFO:
        return *log_stream;
      case DEBUG:
        return *debug_stream;
      default:
        throw std::invalid_argument("unknown PRIORITY passed to get_stream");
    }
  }

  std::ostream & Logger::get_stream_with_header(PRIORITY priority)
  {
    return get_stream(priority) << (*header)(priority);
  }

  void Logger::set_output(PRIORITY priority, std::ostream * output)
  {
    if (!output)
      throw std::runtime_error("invalid output stream: 0x0");
    switch (priority)
    {
      case ERROR:
        log_stream = output;
      case WARNING:
        warn_stream = output;
      case INFO:
        log_stream = output;
      case DEBUG:
        debug_stream = output;
      default:
        throw std::invalid_argument("unknown PRIORITY passed to set_output");
    }
  }

  void Logger::set_header(std::string (*header_generator) (PRIORITY))
  {
    if (!header_generator)
      throw std::runtime_error("invalid header generator function given: 0x0");
    header = header_generator;
  }

  void Logger::formated_output(std::ostream & output, const char *s)
  {
    while (*s) {
      if (*s == '%' && *(++s) != '%')
        throw std::runtime_error("invalid format string: missing arguments");
      output << *s++;
    }
  }
  
  template<typename T, typename... Args>
  void Logger::formated_output(std::ostream & output, const char *s, T value, Args... args)
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
}

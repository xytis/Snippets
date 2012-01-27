#ifndef __LOGGER_HPP_
#define __LOGGER_HPP_

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring>

#define log Log::Logger::Instance()->get_stream_with_header(Log::INFO)
#define err Log::Logger::Instance()->get_stream_with_header(Log::ERROR)
#define warn Log::Logger::Instance()->get_stream_with_header(Log::WARNING)
#define debug Log::Logger::Instance()->get_stream_with_header(Log::DEBUG) << '[' << __FILE__ << ' ' << __LINE__ << ']'

#define logf(...) Log::Logger::Instance()->formated_output(Log::INFO, __VA_ARGS__)
#define errf(...) Log::Logger::Instance()->formated_output(Log::ERROR, __VA_ARGS__)
#define warnf(...) Log::Logger::Instance()->formated_output(Log::WARNING, __VA_ARGS__)
#define debugf(...) Log::Logger::Instance()->formated_debug(__FILE__, __LINE__, __VA_ARGS__)

namespace Log
{
  enum PRIORITY
  {
    ERROR,
    WARNING,
    INFO,
    DEBUG
  };

  std::string empty(PRIORITY priority);
  std::string date(PRIORITY priority);
  std::string date_priority(PRIORITY priority); //Default

  class Logger
  {
  private:
    std::ostream * log_stream;
    std::ostream * err_stream;
    std::ostream * warn_stream;
    std::ostream * debug_stream;

    std::string (*header) (PRIORITY priority);

    bool header_flag;

    //Singleton part
	Logger();
    ~Logger();
    Logger(Logger &); //Empty
    Logger& operator=(Logger const&); //Empty

    static Logger * m_instance;
  public:
    static Logger * Instance();
    static void destroy();
    
    std::ostream & get_stream(PRIORITY priority);

    std::ostream & get_stream_with_header(PRIORITY priority);

    void set_output(PRIORITY priority, std::ostream * output);
    void set_header(std::string (*header_generator) (PRIORITY));
    
    void formated_output(PRIORITY priority, const char *s);
    template<typename T, typename... Args>
    void formated_output(PRIORITY priority,const char *s, T value, Args... args);
    template<typename... Args>
    void formated_debug(const char *s, int line, const char *f, Args... args);
  };  
}

#endif

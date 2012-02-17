#ifndef __LOGGER_HPP_
#define __LOGGER_HPP_

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring>

#define log Log::Logger::Instance()->get_stream_with_header(Log::INFO)
#define err Log::Logger::Instance()->get_stream_with_header(Log::ERROR)
#define warn Log::Logger::Instance()->get_stream_with_header(Log::WARNING)
#define debug Log::Logger::Instance()->get_stream_with_header(Log::DEBUG) << '[' << __FILE__ << ':' << __LINE__ << "] "

//Explanation of ## is here: http://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html

#define logf(format, ...) Log::Logger::Instance()->formated_output(Log::Logger::Instance()->get_stream_with_header(Log::INFO), format , ##__VA_ARGS__)
#define errf(format, ...) Log::Logger::Instance()->formated_output(Log::Logger::Instance()->get_stream_with_header(Log::ERROR), format , ##__VA_ARGS__)
#define warnf(format, ...) Log::Logger::Instance()->formated_output(Log::Logger::Instance()->get_stream_with_header(Log::WARNING), format , ##__VA_ARGS__)
#define debugf(format, ...) Log::Logger::Instance()->formated_output(Log::Logger::Instance()->get_stream_with_header(Log::DEBUG), (std::string("[%s:%d] ")+ std::string(format)).c_str(), __FILE__, __LINE__ , ##__VA_ARGS__)



namespace Log
{
  enum PRIORITY
  {
    ERROR,
    WARNING,
    INFO,
    DEBUG
  };

  //Headers
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
    Logger(Logger &); //Non existant
    Logger& operator=(Logger const&); //Non existant
    
    static Logger * m_instance;
  public:
    static Logger * Instance();
    static void destroy();
    
    std::ostream & get_stream(PRIORITY priority);

    std::ostream & get_stream_with_header(PRIORITY priority);

    void set_output(PRIORITY priority, std::ostream * output);
    void set_header(std::string (*header_generator) (PRIORITY));
    
    void formated_output(std::ostream &, const char *s);
    template<typename T, typename... Args>
    void formated_output(std::ostream &,const char *s, T value, Args... args);
  };
}

#endif

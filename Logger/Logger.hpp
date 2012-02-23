#ifndef __LOGGER_HPP_
#define __LOGGER_HPP_

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstring>
#include <ctime>

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
  std::string empty(PRIORITY priority)
  {
    return "";
  };
  
  std::string date(PRIORITY priority)
  {
    time_t rawtime;
    time ( &rawtime );
    char buffer [80];   
    
    strftime (buffer,80,"<%Y-%m-%d %H:%M>", localtime ( &rawtime ));
    return std::string(buffer);
  };
  
  //Default
  std::string date_priority(PRIORITY priority)
  {
    std::string post;
    switch (priority)
    {
      case ERROR:
        post = " Error: ";
        break;
      case WARNING:
        post = " Warning: ";
        break;
      case INFO:
        post = " Info: ";
        break;
      case DEBUG:
        post = " Debug: ";
        break;
      default:
        throw std::invalid_argument("unknown PRIORITY passed to date_priority");
    }
    return date(priority) + post;
  };
  
  /**
   * class Logger
   * 
   * Singleton class, which controls streams to various log channels.
   */ 
  class Logger
  {
  public:
    /**
     * Singleton instance getter
     * @return Logger instance
     */
    static Logger * Instance()
    {
      //Not multithreading safe.
      return m_instance ? m_instance : m_instance = new Logger();
    };
    
    /**
     * Singleton cleanup method
     * Should be used at end of program.
     */
    static void destroy()
    {
      delete m_instance;
      m_instance = NULL;
    };
    
    /**
     * Method returning a stream for given priority
     * @return std::ostream & output stream.
     */
    std::ostream & get_stream(PRIORITY priority)
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
    };
    
    /**
     * Method returning a formated stream for given priority
     * @return std::ostream & formated output stream.
     */
    std::ostream & get_stream_with_header(PRIORITY priority)
    {
      return get_stream(priority) << (*header)(priority);
    };
    
    /**
     * Method for linking streams with priorities
     * @param PRIORITY target priority
     * @param std::ostream* target stream
     */
    void set_output(PRIORITY priority, std::ostream * output)
    {
      if (!output)
        throw std::runtime_error("invalid output stream: 0x0");
      switch (priority)
      {
        case ERROR:
          log_stream = output;
          break;
        case WARNING:
          warn_stream = output;
          break;
        case INFO:
          log_stream = output;
          break;
        case DEBUG:
          debug_stream = output;
          break;
        default:
          throw std::invalid_argument("unknown PRIORITY passed to set_output");
      }
    };
    
    /**
     * Method for setting the header function
     * @param std::string (*header_generator) (PRIORITY)
     */
    void set_header(std::string (*header_generator) (PRIORITY))
    {
      if (!header_generator)
        throw std::runtime_error("invalid header generator function given: 0x0");
      header = header_generator;
    };
    
    /**
     * End of recursive variadic template
     */
    void formated_output(std::ostream & output, const char *s)
    {
      while (*s) {
        if (*s == '%' && *(++s) != '%')
          throw std::runtime_error("invalid format string: missing arguments");
        output << *s++;
      }
    };
    
    /**
     * Variadic template, for printing out like fprintf.
     */
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
    };
    
  private:
    std::ostream * log_stream;
    std::ostream * err_stream;
    std::ostream * warn_stream;
    std::ostream * debug_stream;

    std::string (*header) (PRIORITY priority);

    bool header_flag;

    //Singleton part
    /**
     * Constructor
     * 
     * Sets all channels to std::cout,
     * default header: date_priority
     */
    Logger():
      log_stream(&std::cout),
      err_stream(&std::cout),
      warn_stream(&std::cout),
      debug_stream(&std::cout),
      header(date_priority),
      header_flag(true)
    {
      
    };
    
    /**
     * Destructor
     * 
     * Can be called only from inner method.
     */
    ~Logger()
    {
      
    };
    
    Logger(Logger &); //Non existant
    Logger& operator=(Logger const&); //Non existant
    
    
    static Logger * m_instance;
  
  };
  
  /**
   * Singleton init line
   */
  Logger* Logger::m_instance = NULL;
}

#endif

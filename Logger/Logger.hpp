#ifndef __LOGGER_HPP_
#define __LOGGER_HPP_

#include <iostream>
#include <string>

#include "Format.hpp"
#include "Priority.hpp"

namespace Log
{

  class LoggerFactory;

  class LogChannel
  {
  private:
	std::ostream * m_output;
	Format * m_format;
  protected:
	LogChannel(std::ostream * output, Format * format);
  public:
	friend class LoggerFactory;
	std::ostream & operator << (const char[]); //Adds format to begining of line
	std::ostream & operator << (const std::string &); //Adds format to begining of line
	std::ostream & operator << (const double &);      //Adds format to begining of line
  };

  class Logger
  {
  private:
	LogChannel * m_error;
	LogChannel * m_warning;
	LogChannel * m_info;
	LogChannel * m_debug;

  protected:
	Logger(LogChannel * error, LogChannel * warning, LogChannel * info, LogChannel * debug);
  public:
	friend class LoggerFactory;

	void log(std::string msg, PRIORITY priority);

	void error(std::string msg);
	void warning(std::string msg);
	void info(std::string msg);
	void debug(std::string msg);

	LogChannel & log(PRIORITY priority);
  };
}

#endif

#include "Logger.hpp"

namespace Log
{
  LogChannel::LogChannel(std::ostream * output, Format * format):m_output(output), m_format(format)
  {
	//NOP
  }

  std::ostream & LogChannel::operator << (const char msg[])
  {
	m_format->apply(m_output);
	(*m_output) << msg;
	return (*m_output);
  }
  
  std::ostream & LogChannel::operator << (const std::string & msg)
  {
	m_format->apply(m_output);
	(*m_output) << msg;
	return (*m_output);
  }

  std::ostream & LogChannel::operator << (const double & msg)
  {
	m_format->apply(m_output);
	(*m_output) << msg;
	return (*m_output);
  }

  Logger::Logger(LogChannel * error, LogChannel * warning, LogChannel * info, LogChannel * debug):
  m_error(error), m_warning(warning), m_info(info), m_debug(debug)
  {
	//NOP
  }

  void Logger::log(std::string msg, PRIORITY priority)
  {
	switch (priority)
	{
	  case ERROR:
	  {
		error(msg);
		break;
	  }
	  case WARNING:
	  {
		warning(msg);
		break;
	  }
	  case INFO:
	  {
		info(msg);
		break;
	  }
	  case DEBUG:
	  {
		debug(msg);
		break;
	  }
	}
  }

  void Logger::error(std::string msg)
  {
	(*m_error) << msg << std::endl;
  }
  
  void Logger::warning(std::string msg)
  {
	(*m_warning) << msg << std::endl;
  }
  
  void Logger::info(std::string msg)
  {
	(*m_info) << msg << std::endl;
  }
  
  void Logger::debug(std::string msg)
  {
	(*m_debug) << msg << std::endl;
  }

  LogChannel & Logger::log(PRIORITY priority)
  {
	switch (priority)
	{
	  case ERROR:
	  {
		return (*m_error);
	  }
	  case WARNING:
	  {
		return (*m_warning);
	  }
	  case INFO:
	  {
		return (*m_info);
	  }
	  case DEBUG:
	  {
		return (*m_debug);
	  }
	}
  }
  
}

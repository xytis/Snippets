#include "Logger.hpp"

namespace Log
{
  LogChannel::LogChannel(std::ostream * output, Format * format):m_output(output), m_format(format)
  {
	//NOP
  }

  std::ostream & LogChannel::get()
  {
	m_format->apply(m_output);
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
	m_error->get() << msg << std::endl;
  }
  
  void Logger::warning(std::string msg)
  {
	m_warning->get() << msg << std::endl;
  }
  
  void Logger::info(std::string msg)
  {
	m_info->get() << msg << std::endl;
  }
  
  void Logger::debug(std::string msg)
  {
	m_debug->get() << msg << std::endl;
  }

  std::ostream & Logger::log(PRIORITY priority)
  {
	switch (priority)
	{
	  case ERROR:
	  {
		return m_error->get();
	  }
	  case WARNING:
	  {
		return m_warning->get();
	  }
	  case INFO:
	  {
		return m_info->get();
	  }
	  case DEBUG:
	  {
		return m_debug->get();
	  }
	}
  }
  
}

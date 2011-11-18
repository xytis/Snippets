#ifndef __LOGGERFACTORY_HPP_
#define __LOGGERFACTORY_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Logger.hpp"
#include "Format.hpp"

namespace Log
{
  class LoggerFactory
  {
  private:
	std::map<std::string, Logger *> m_running_loggers;

	std::vector<Format *> m_format_heap;
	std::map<std::string, std::ostream *> m_output_heap;
	std::vector<LogChannel *> m_channel_heap;

	LogChannel * default_channel(PRIORITY priority, std::string id);
	Format * default_format(PRIORITY priority, std::string id);
	std::ostream * default_output(PRIORITY priority);

  public:
	LoggerFactory();
	~LoggerFactory();

	Logger * get(std::string id = "main");

	Logger * build(std::string id);
	Logger * build(std::string filename, std::string id);
	Logger * build(Format * format, std::string id);
	Logger * build(std::string filename, Format * format, std::string id);
	Logger * build(std::map<PRIORITY, Format *>, std::string id);
	Logger * build(std::map<PRIORITY, std::string>, std::map<PRIORITY, Format *>, std::string id);
  };
}
#endif


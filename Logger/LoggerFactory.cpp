#include "LoggerFactory.hpp"

namespace Log
{
  LogChannel * LoggerFactory::default_channel(PRIORITY priority, std::string id)
  {
	static std::map<PRIORITY, LogChannel*> default_channels;
	if (default_channels[priority])
	  return default_channels[priority];
	
	Format * format = default_format(priority, id);
	std::ostream * output = default_output(priority);
	
	default_channels[priority] = new LogChannel(output, format);
	
	m_channel_heap.push_back(default_channels[priority]);
	
	return default_channels[priority];
  }

  Format * LoggerFactory::default_format(PRIORITY priority, std::string id)
  {
	static std::map<PRIORITY, Format*> default_formats;
	if (default_formats[priority])
	  return default_formats[priority];
	Format * format;
	switch (priority)
	{
	  case ERROR:
	  {
		format = new Format(id, "EE: ");
		break;
	  }
	  case WARNING:
	  {
		format = new Format(id, "WW: ");
		break;
	  }
	  case INFO:
	  {
		format = new Format(id, "II: ");
		break;
	  }
	  case DEBUG:
	  {
		format = new Format(id, "DEBUG: ");
		break;
	  }
	}
	m_format_heap.push_back(format);
	return format;
  }

  std::ostream * LoggerFactory::default_output(PRIORITY priority)
  {
	return &std::cout;
  }

  LoggerFactory::LoggerFactory()
  {
	
  }
  
  LoggerFactory::~LoggerFactory()
  {
	std::map<std::string, Logger *>::iterator logger;	

	for (logger = m_running_loggers.begin(); logger != m_running_loggers.end(); logger++)
	{
	  delete logger->second;
	}

	std::vector<Format *>::iterator format;
	for (format = m_format_heap.begin(); format !=  m_format_heap.end(); format++)
	{
	  delete (*format);
	}

	std::map<std::string, std::ostream *>::iterator output;
	for (output = m_output_heap.begin(); output != m_output_heap.end(); output++)
	{
	  delete output->second;
	}
	
	std::vector<LogChannel *>::iterator channel;
	for (channel = m_channel_heap.begin(); channel != m_channel_heap.end(); output++)
	{
	  delete (*channel);
	}
	
  }

  Logger * LoggerFactory::get(std::string id)
  {
	Logger * logger = m_running_loggers[id];
	if (logger)
	  return logger;
	return this->build(id);
  }

  Logger * LoggerFactory::build(std::string id)
  {
	Logger * logger = m_running_loggers[id];
	if (logger)
	  return logger;

	//Create new one.
	logger = new Logger(default_channel(ERROR, id), default_channel(WARNING, id), default_channel(INFO, id), default_channel(DEBUG, id));
	m_running_loggers[id] = logger;
	return logger;
  }
  
  Logger * LoggerFactory::build(std::string filename, std::string id)
  {
	std::map<PRIORITY, std::string> filenames;
	std::map<PRIORITY, Format *> formats;

	filenames[ERROR] = filename;
	filenames[WARNING] = filename;
	filenames[INFO] = filename;
	filenames[DEBUG] = filename;

	formats[ERROR] = default_format(ERROR, id);
	formats[WARNING] = default_format(WARNING, id);
	formats[INFO] = default_format(INFO, id);
	formats[DEBUG] = default_format(DEBUG, id);

	return this->build(filenames, formats, id);
  }
  
  Logger * LoggerFactory::build(Format * format, std::string id)
  {
	std::map<PRIORITY, Format *> formats;
	formats[ERROR] = format;
	formats[WARNING] = format;
	formats[INFO] = format;
	formats[DEBUG] = format;
	
	return this->build(formats, id);
  }
  
  Logger * LoggerFactory::build(std::string filename, Format * format, std::string id)
  {
	std::map<PRIORITY, std::string> filenames;
	std::map<PRIORITY, Format *> formats;
	
	filenames[ERROR] = filename;
	filenames[WARNING] = filename;
	filenames[INFO] = filename;
	filenames[DEBUG] = filename;

	formats[ERROR] = format;
	formats[WARNING] = format;
	formats[INFO] = format;
	formats[DEBUG] = format;
	
	return this->build(filenames, formats, id);
  }
  
  Logger * LoggerFactory::build(std::map<PRIORITY, Format *> formats, std::string id)
  {
	Logger * logger = m_running_loggers[id];
	if (logger)
	{
	  //Warn user that such logger exists, recreate it
	  this->get()->log(WARNING) << "Logger " << id << " exists. Recreating logger with new configuration." << std::endl;
	}
	LogChannel * error = new LogChannel(default_output(ERROR), formats[ERROR]);
	m_channel_heap.push_back(error);
	LogChannel * warning = new LogChannel(default_output(WARNING), formats[WARNING]);
	m_channel_heap.push_back(warning);
	LogChannel * info = new LogChannel(default_output(INFO), formats[INFO]);
	m_channel_heap.push_back(info);
	LogChannel * debug = new LogChannel(default_output(DEBUG), formats[DEBUG]);
	m_channel_heap.push_back(debug);
	if (logger)
	  delete logger;
	logger = new Logger(error, warning, info, debug);
	m_running_loggers[id] = logger;
	return logger;
  }
  
  Logger * LoggerFactory::build(std::map<PRIORITY, std::string> filenames, std::map<PRIORITY, Format *> formats, std::string id)
  {
	Logger * logger = m_running_loggers[id];
	if (logger)
	{
	  //Warn user that such logger exists, recreate it
	  this->get()->log(WARNING) << "Logger " << id << " exists. Recreating logger with new configuration." << std::endl;
	}

	std::ostream * error_file = m_output_heap[filenames[ERROR]];
	if (!error_file)
	{
	  error_file = reinterpret_cast<std::ostream *>(new std::ofstream(filenames[ERROR].c_str()));
	  if (!error_file)
	  {
		//Rollback to default_output, warn user via main logger.
		this->get()->log(ERROR) << "Error creating logger " << id << ". File " << filenames[ERROR] << " not created. Falling back to default output." << std::endl;
		error_file = default_output(ERROR);
	  }
	  m_output_heap[filenames[ERROR]] = error_file;
	}
	std::ostream * warning_file = m_output_heap[filenames[WARNING]];
	if (!warning_file)
	{
	  warning_file = reinterpret_cast<std::ostream *>(new std::ofstream(filenames[WARNING].c_str()));
	  if (!warning_file)
	  {
		//Rollback to default_output, warn user via main logger.
		this->get()->log(ERROR) << "Error creating logger " << id << ". File " << filenames[WARNING] << " not created. Falling back to default output." << std::endl;
		warning_file = default_output(WARNING);
	  }
	  m_output_heap[filenames[WARNING]] = warning_file;
	}
	std::ostream * info_file = m_output_heap[filenames[INFO]];
	if (!info_file)
	{
	  info_file = reinterpret_cast<std::ostream *>(new std::ofstream(filenames[INFO].c_str()));
	  if (!info_file)
	  {
		//Rollback to default_output, warn user via main logger.
		this->get()->log(ERROR) << "Error creating logger " << id << ". File " << filenames[INFO] << " not created. Falling back to default output." << std::endl;
		info_file = default_output(INFO);
	  }
	  m_output_heap[filenames[INFO]] = info_file;
	}
	std::ostream * debug_file = m_output_heap[filenames[DEBUG]];
	if (!debug_file)
	{
	  debug_file = reinterpret_cast<std::ostream *>(new std::ofstream(filenames[DEBUG].c_str()));
	  if (!debug_file)
	  {
		//Rollback to default_output, warn user via main logger.
		this->get()->log(ERROR) << "Error creating logger " << id << ". File " << filenames[DEBUG] << " not created. Falling back to default output." << std::endl;
		debug_file = default_output(DEBUG);
	  }
	  m_output_heap[filenames[DEBUG]] = debug_file;
	}
	
	LogChannel * error = new LogChannel(error_file, formats[ERROR]);
	m_channel_heap.push_back(error);
	LogChannel * warning = new LogChannel(warning_file, formats[WARNING]);
	m_channel_heap.push_back(warning);
	LogChannel * info = new LogChannel(info_file, formats[INFO]);
	m_channel_heap.push_back(info);
	LogChannel * debug = new LogChannel(debug_file, formats[DEBUG]);
	m_channel_heap.push_back(debug);
	if (logger)
	  delete logger;
	logger = new Logger(error, warning, info, debug);
	m_running_loggers[id] = logger;
	return logger;
  }
}

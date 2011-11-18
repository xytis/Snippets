#ifndef __LOGGERSYSTEM_HPP_
#define __LOGGERSYSTEM_HPP_

#include "../Singleton/Singleton.hpp"
#include "LoggerFactory.hpp"
#include "Logger.hpp"

typedef Singleton<Log::LoggerFactory> LoggerSystem;
typedef Log::Logger Logger;

#endif
#ifndef __LOGGERSYSTEM_HPP_
#define __LOGGERSYSTEM_HPP_

#include "../Singleton/Singleton.hpp"
#include "LoggerFactory.hpp"

typedef Singleton<Log::LoggerFactory> LoggerSystem;

#endif
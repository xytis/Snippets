#include <iostream>
#include <string>
#include <cstdlib>

#include "Singleton.hpp"

using namespace std;

// ----------------- Logger class --------------------------------

class Logger
{
public:
  Logger()  { cout << "Creating logger..."   << endl; };
  ~Logger() { cout << "Destroying logger..." << endl; };
  
  bool openLogFile(string theFilename);
  bool closeLogFile(string theFilename);
  bool writeToLogFile(string theFilename, string theData);
  
private:
  //...
};

bool Logger::openLogFile(string theFilename)
{
  cout << "Opening log file: " << theFilename << endl;
  //...
  return true;
}

bool Logger::writeToLogFile(string theFilename, string theData)
{
  cout << "Writing " << theData << " to the file: " << theFilename << endl;
  // ...
  return true;
}

bool Logger::closeLogFile(string theFilename)
{
  cout << "Closing log file: " << theFilename << endl;
  // ...
  return true;
}

// ----------------- End of Logger class --------------------------------

// ----------------- App class --------------------------------

class App
{
public:
  App()
  {
	cout << "Creating app..." << endl;
	uptimeInSeconds = 0;
	appData = (char*) malloc (1024 * 1024 * 150); // Allocate 150MB of RAM on the heap (to demonstrate we can free it)
  }
  
  ~App()
  {
	cout << "Destroying app..." << endl;
	free(appData); // Release our 150MB of RAM
  }
  
  int getUptime();
  void tick();
  
private:
  int uptimeInSeconds;
  char *appData; // Pointer to our allocated 150MB of RAM
};

int App::getUptime()
{
  return uptimeInSeconds;
}

void App::tick()
{
  uptimeInSeconds++;
}

// ----------------- End of App class --------------------------------


// Global declarations of templatised singleton typedefs (not instantiated until instance() is first called)
typedef Singleton<Logger> loggerSingleton;
typedef Singleton<App>    myApp;
typedef Singleton<App>    myApp2; // Create a second App singleton typedef to show that we never really do due to the singleton instance mechanism


int main()
{
  // Start off by trying to break stuff... as you do. The below can't be done because we've set the instance member
  // pointer as private, which forces us to use the ::instance method, which itself forces creation of our singleton.
  //cout << "here is a value: " << loggerSingleton::m_pInstance << endl;
  
  // Create a logger instance if it doesn't exist. Once an instance exists then use it instead of creating another instance
  loggerSingleton::instance()->openLogFile("LogFile.txt");
  loggerSingleton::instance()->writeToLogFile("AnotherFile.log", "abc123");
  loggerSingleton::instance()->closeLogFile("SomeOtherFile.txt");
  
  cout << endl << endl;
  
  // Create an app instance if it doesn't exist. Once an instance exists then use it instead of creating another instance.
  cout << "App uptime at start is: " << myApp::instance()->getUptime() << endl;
  
  // Add a tick to the uptime counter
  myApp::instance()->tick();
  
  // Display the uptime counter for our App instance
  cout << "App uptime after one tick is: " << myApp::instance()->getUptime() << endl;
  
  // Try to break things again using our second typedef that points to the same class as our "myApp" typedef. The uptime of the below
  // myApp2 singleton will be 1 (and not the default 0) because it's reusing myApp instead of creating myApp2 due to our Singleton template!
  cout << "Second app uptime is: " << myApp2::instance()->getUptime() << endl;
  
  // Destroy our singletons and release their resources
  myApp::destroy();
  loggerSingleton::destroy();
  
  return 0;
}
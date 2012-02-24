/******************************************************************************
 *                                                                            *
 *                           Singleton template                               *
 *                                                                            *
 *  from:  http://www.yolinux.com/TUTORIALS/C++Singleton.html                 *
 *  usage: #include "Singleton.hpp"                                           *
 *         typedef Singleton<MyClass> MySingleton;                            *
 *         MySingleton::instance()->do_stuff();                               *
 *         MySingleton::destroy();                                            *
 *                                                                            *
 *  warning: no multithreading support.                                       *
 ******************************************************************************/
#ifndef __SINGLETON_HPP_
#define __SINGLETON_HPP_

#include <iostream>

template <class T>
class Singleton
{
public:
  // Return existing or create new instance
  static T* instance()
  {
	// Do we have an instance of this type? If so return it, otherwise create a new one.
	return m_pInstance ? m_pInstance : m_pInstance = new T;
  }
  
  // Manually destroy an existing instance. Call at end of program to clean up.
  static void destroy()
  {
      if (m_pInstance)
      {
          delete m_pInstance;
      }
      m_pInstance = NULL;
  }
  
private:
  Singleton();                            // Constructor                   (empty & cannot be called externally)
  ~Singleton();                           // Destructor                    (empty & cannot be called externally)
  Singleton(Singleton const&);            // Copy constructor              (empty & cannot be called externally - no copies allowed)
  Singleton& operator=(Singleton const&); // Assignment operator           (empty & cannot be called externally - no assignment allowed)
  static T* m_pInstance;                  // Static template-type instance
};

// Set static instance value to NULL
template <class T> T* Singleton<T>::m_pInstance = NULL;

#endif

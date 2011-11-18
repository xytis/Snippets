#ifndef __FORMAT_HPP_
#define __FORMAT_HPP_

#include <iostream>
#include <string> 

namespace Log
{
  class Format
  {
  private:
	std::string m_header;
  public:
	Format(std::string owner, std::string header);

	void apply (std::ostream &);
	void apply (std::ostream *);
  };
}

#endif
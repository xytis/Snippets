#include "Format.hpp"

namespace Log
{
  Format::Format(std::string owner, std::string header):m_header(owner + std::string(": ") + header)
  {
	//NOP
  }

  void Format::apply(std::ostream & out)
  {
	out << m_header;
  }

  void Format::apply(std::ostream * out)
  {
	(*out) << m_header;
  }
}

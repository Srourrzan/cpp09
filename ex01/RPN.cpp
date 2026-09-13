#include "RPN.hpp"

RPN::RPN( )
  : _data()
{}

RPN::~RPN( ) {}

RPN::RPN( const RPN &src ) : _data(src._data) {}

RPN &RPN::operator=( const RPN &rhs ) {
  if (this != &rhs)
    _data = rhs._data;
  return(*this);
}

int RPN::getLength() {
  return (_data.size());
}


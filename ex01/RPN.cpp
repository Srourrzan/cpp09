#include "RPN.hpp"
#include <iostream>

RPN::RPN()
    : _data(),
	  _valFlag(1)
{}

RPN::~RPN( ) {}

RPN::RPN(const RPN &src)
    : _data(src._data),
	  _valFlag(1)
{}

RPN::RPN(const std::string &ipt)
    : _data(),
	  _valFlag(1)
{
  std::stringstream ss(ipt);
  std::string token;

  while (ss >> token) {
    if (token.length() != 1) {
      _valFlag = 0;
	  break;
    }
    if (isDigit(token[0])) {
      _data.push(strToFlt(token));
    } else if (isOperator(token[0])) {
      evaluation(token[0]);
      if (!_valFlag)
		return ;
    } else {
      _valFlag = 0;
	  return ;
    }
  }
}

RPN &RPN::operator=( const RPN &rhs ) {
  if (this != &rhs)
    _data = rhs._data;
  return(*this);
}

void RPN::debug( ) {
  std::stack<float> temp = _data;
  while (!temp.empty()) {
    std::cout << temp.top() << "\n";
	temp.pop();
  }
}

float RPN::getValue() {
  float value;
  
  if (!_data.empty()) {
    value = _data.top();
	_data.pop();
  }
  return (value);
}

bool RPN::isDigit( char c ) {
  return (std::isdigit(c));
}

bool RPN::isSpace( char c ) {
  return c == ' ';
}

bool RPN::isOperator( char c ) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::getLength( ) {
  return (_data.size());
}

int RPN::getValFlag( ) {
  return (_valFlag);
}

void RPN::evaluation( char op ) {
  float left;
  float right;
  float result;
  
  if (_data.size() < 2) {
    std::cerr << "Error\n";
    _valFlag = 0;
    return;
  }
  right = getValue();
  left = getValue();
  if (op == '+')
    result = right + left;
  else if (op == '-')
    result = left - right;
  else if (op == '*')
    result = right * left;
  else {
    if (right == 0) {
      std::cerr << "Error\n";
      _valFlag = 0;
	  return ;
    }
	result = left / right;
  }
  _data.push(result);
}

float RPN::strToFlt( const std::string& str ) {
  std::stringstream ss(str);
  float f;

  ss >> f;
  return (f);
}

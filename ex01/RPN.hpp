#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <sstream>
#include <iostream>
#include <exception>

class RPN {
public:
  RPN( );
  ~RPN( );
  RPN( const RPN & );
  RPN( const std::string & );
  RPN &operator=( const RPN & );

  void debug( );
  int getLength( );
  float getValue( );
  bool isDigit( char );
  bool isSpace( char );
  void evaluation( char );
  bool isOperator( char );
  float strToFlt(const std::string &);

  class RPNError: public std::exception {
  public:
	virtual const char* what() const throw();
  };

private:
  std::stack<float> _data;
};

#endif

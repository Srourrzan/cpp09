#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <sstream>
#include <iostream>

class RPN {
public:
  RPN( );
  ~RPN( );
  RPN( const RPN & );
  RPN( const std::string & );
  RPN &operator=( const RPN & );

  void debug( );
  int getLength( );
  int getValFlag( );
  float getValue( );
  bool isDigit( char );
  bool isSpace( char );
  void evaluation( char );
  bool isOperator( char );
  float strToFlt( const std::string & );

private:
  std::stack<float> _data;
  int _valFlag;
};

#endif

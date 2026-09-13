#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>


class RPN {
public:
  RPN( );
  ~RPN( );
  RPN( const RPN & );
  RPN &operator=( const RPN & );

  int getValue( );
  int getLength( );
  // RPN parseInput( std::string );


private:
  std::stack<int> _data;
};

#endif

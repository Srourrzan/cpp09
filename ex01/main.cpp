#include "RPN.hpp"
#include <cctype>
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
  RPN rpn;
  
  if (argc != 2) {
    std::cerr << "Error" << "\n";
	return (1);
  }
  try {	
  rpn = RPN(argv[1]);
  if (rpn.getLength() != 1) {
    std::cerr << "Error" << "\n";
	return (2);
  }
  rpn.debug();
  } catch (const std::exception& e) {
	std::cerr << e.what();
  }
  return (0);
}

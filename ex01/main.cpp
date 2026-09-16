#include "RPN.hpp"
#include <cctype>

int main(int argc, char *argv[]) {
  RPN rpn;
  
  if (argc != 2) {
    std::cerr << "Error" << "\n";
	return (1);
  }
  rpn = RPN(argv[1]);
  if (!rpn.getValFlag())
    return (1);
  if (rpn.getLength() != 1) {
    std::cerr << "Error" << "\n";
	return (2);
  }
  rpn.debug();
  return (0);
}

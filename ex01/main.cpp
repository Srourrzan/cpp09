#include "RPN.hpp"
#include <cctype>

inline bool isDigit(char c) { return (std::isdigit(c)); }
inline bool isSpace(char c) { return c == ' '; }
inline bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

RPN parseInput(std::string ipt) {
  RPN rpn;
  
  for (size_t i = 0; i < ipt.size(); i++) {
    if (!isDigit(ipt[i]) && !isSpace(ipt[i]) && !isOperator(ipt[i])) {
      std::cerr << "Error" << "\n";
	  return (rpn);
    }
  }
  return (rpn);
}

int main(int argc, char *argv[]) {
  RPN rpn;
  
  if (argc != 2) {
    std::cerr << "Error" << "\n";
	return (1);
  }
  rpn = parseInput(argv[1]);
  if (rpn.getLength())
    return (1);
  return (0);
}

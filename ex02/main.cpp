#include "PmergeMe.hpp"
#include "iostream"

int main(int argc, char *argv[]) {
  PmergeMe pm;

  try {
	pm.parseInput(argc, argv);
        std::cout << "Before " << pm << "\n";
		pm.sortByVector();
  } catch (const std::exception &e) {
	std::cerr << e.what();
  }
  return (0);
}

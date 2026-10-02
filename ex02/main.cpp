#include "PmergeMe.hpp"
#include "iostream"
#include <vector>

void sortData(const PmergeMe &pm) {
  std::vector<int> sortedVect;
  std::vector<int> unsortedVect;

  unsortedVect = pm.getData();
  sortedVect = pm.fordJohnsonSortVectors(unsortedVect);
  std::cout << "sorted vector: " << sortedVect << "\n";
}

int main(int argc, char *argv[]) {
  PmergeMe pm;
  std::vector<int> sortedVector;

  try {
    pm.parseInput(argc, argv);
	sortData(pm);
  } catch (const std::exception &e) {
	std::cerr << e.what();
  }
  return (0);
}

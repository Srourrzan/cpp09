#include "PmergeMe.hpp"
#include <sys/time.h>
#include "iostream"
#include <vector>

void sortData(const PmergeMe &pm) {
  std::deque<int> sortedDeque;
  std::vector<int> sortedVect;
  std::vector<int> unsortedVect;

  unsortedVect = pm.getData();
  std::cout << "Before: " << unsortedVect << std::endl;

  // Start vector part
  {
    double time_vec_ms;
    long long time_vec_us;
    struct timeval end_vec;
    struct timeval start_vec;

    gettimeofday(&start_vec, NULL);
    sortedVect = pm.fordJohnsonSortVectors(unsortedVect);
    gettimeofday(&end_vec, NULL);
    time_vec_us = (end_vec.tv_sec - start_vec.tv_sec) * 1000000LL + (end_vec.tv_usec - start_vec.tv_usec);
    time_vec_ms = time_vec_us / 100.0;
    // std::cout << "sorted vector: " << sortedVect << "\n";
    // std::cout << "sorting time: " << time_vec_ms << "\n";
    double time_deq_ms;
    long long time_deq_us;
    struct timeval end_deq;
    struct timeval start_deq;

    std::deque<int> unsortedDeque(unsortedVect.begin(), unsortedVect.end());
    gettimeofday(&start_deq, NULL);
    sortedDeque = pm.fordJohnsonSortDeque(unsortedDeque);
    gettimeofday(&end_deq, NULL);
    time_deq_us = (end_deq.tv_sec - start_deq.tv_sec) * 1000000LL + (end_deq.tv_usec - start_deq.tv_usec);
    time_deq_ms = time_deq_us / 100.0;
    // std::cout << "sorted deque: " << sortedDeque << "\n";
    // std::cout << "sorting time: " << time_deq_ms << "\n";
    std::cout << "After: " << sortedVect << std::endl;
    std::cout << "Time to process a range of " << unsortedVect.size()
              << " elements with std::vector : " << time_vec_ms << " ms" << std::endl;
    std::cout << "Time to process a range of " << unsortedDeque.size()
              << " elements with std::deque : " << time_deq_ms << " ms" << std::endl;
  }
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

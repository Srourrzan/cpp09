#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>

# define LOG_INFO() std::cout << __FILE__ << ":" << __LINE__ << " " << __func__<< ": ";

struct Pair {
  int winner;
  int loser;
};

class PmergeMe {
public:
  PmergeMe( );
  ~PmergeMe( );
  PmergeMe( const PmergeMe & );
  PmergeMe &operator=( const PmergeMe & );
  
  std::vector<int> getData( ) const;
  void parseInput( int, char *argv[] );
  bool isValidPositiveInt( const std::string &, int & );
  
  void seperateVectors( std::vector<Pair> & );
  void simpleSortVectors( std::vector<int> & ) const;
  std::vector<int> generateJacobsthalVectors( int ) const;
  std::vector<int> fordJohnsonSortVectors( std::vector<int> & ) const;
  void binaryInsertVectors(std::vector<Pair> & , std::vector<int> &, int ) const;
  void insertLosersVectors(std::vector<Pair> &, std::vector<int> &) const;

  class PmergeMeError : public std::exception {
  public:
	virtual const char* what( ) const throw( );
  };

private:
  std::vector<int> _data;
};

std::ostream & operator<<( std::ostream &, const PmergeMe & );
std::ostream & operator<<( std::ostream &, const std::vector<int> & );
std::ostream & operator<<( std::ostream &, const std::vector<Pair> & );

#endif

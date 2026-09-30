#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>
#include <cstddef>
#include <sstream>
#include <iostream>
#include <exception>

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
  
  void sortByVector( );
  void seperateVectors( std::vector<Pair> & );
  void simpleSortVectors( std::vector<Pair> & );
  void fordJohnsonSortVectors( std::vector<Pair> & );
  std::vector<int> generateJacobsthalVectors( int );
  void insertLosersVectors( std::vector<Pair> & , std::vector<Pair> & );

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

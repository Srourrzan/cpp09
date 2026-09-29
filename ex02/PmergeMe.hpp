#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <string>
#include <vector>
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
  void sortByVector( );
  std::vector<int> getData( ) const;
  void parseInput( int, char *argv[] );
  void simpleSort( std::vector<Pair> & );
  void seperateVectors( std::vector<Pair> & );
  void fordJohnsonSort( std::vector<Pair> & );
  bool isValidPositiveInt( const std::string &, int & );

  class PmergeMeError : public std::exception {
  public:
	virtual const char* what( ) const throw( );
  };

private:
  std::vector<int> _data;
};

std::ostream & operator<<( std::ostream &, const PmergeMe & );

#endif

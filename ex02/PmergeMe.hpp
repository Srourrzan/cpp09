#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <exception>

class PmergeMe {
public:
  PmergeMe( );
  ~PmergeMe( );
  PmergeMe( const PmergeMe & );
  PmergeMe &operator=( const PmergeMe & );
  std::vector<int> getData( ) const;
  float sortDeque( std::string & );
  float sortVector( std::string & );
  void parseInput( int, char *argv[] );
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

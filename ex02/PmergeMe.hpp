#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <exception>

class PmergeMe {
public:
  PmergeMe( );
  ~PmergeMe( );
  PmergeMe( const PmergeMe & );
  PmergeMe &operator=( const PmergeMe & );
  float sortVector( std::string & );
  float sortDeque( std::string & );
  void parseInput( int, char *argv[] );

  class PmergeMeError : public std::exception {
  public:
	virtual const char* what() const throw();
  };
};

#endif

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>

PmergeMe::PmergeMe( )
  : _data()
{}

PmergeMe::~PmergeMe( )
{}

PmergeMe::PmergeMe( const PmergeMe &src )
  : _data(src._data)
{}

PmergeMe &PmergeMe::operator=( const PmergeMe &rhs )
{
  if (this != &rhs)
	{
	  _data = rhs._data;
	}
  return (*this);
}

std::vector<int> PmergeMe::getData( ) const
{
  return (_data);
}

void PmergeMe::parseInput( int argc, char *argv[] )
{
  int i;
  int result;
  
  if (argc < 2)
	throw (PmergeMeError());
  i = 1;
  result = 0;
  while(argv[i])
	{
	  if (!isValidPositiveInt(argv[i], result))
		throw (PmergeMeError());
	  _data.push_back(result);
	  i++;
	}
}

bool PmergeMe::isValidPositiveInt( const std::string &str, int &res )
{
  char extra;
  std::stringstream ss(str);

  if (!(ss >> res))
	return (false);
  if (ss >> extra)
	return (false);
  if (res < 0)
	return (false);
  return (true);
}

void PmergeMe::simpleSort( std::vector<Pair> & pairs ) {
  if (pairs.size() <= 1)
    return ;
  if (pairs.size() == 2) {
    if (pairs[0].winner > pairs[1].winner)
      std::swap(pairs[0], pairs[1]);
	return ;
  }
  if (pairs[0].winner > pairs[1].winner)
    std::swap(pairs[0], pairs[1]);
  if (pairs[1].winner > pairs[2].winner)
	std::swap(pairs[1], pairs[2]);
}

void PmergeMe::fordJohnsonSort( std::vector<Pair> & pairs ) {
  if (pairs.size() <= 3) {
    simpleSort(pairs);
	return ;
  }
  std::vector<Pair> mainChainWinners;
  std::vector<Pair> mainChainLosers;
  // logic to seperate them based on comparing
  // pairs[i].winner and pairs[i + 1].winner
  fordJohnsonSort(mainChainWinners);
  // Insert the loasing Pairs into mainChainWinners using Jacobsthal
  // sequence (Comparison during insertion still uses the 'winner' attribute)

  pairs = mainChainWinners;
}

void PmergeMe::sortByVector( ) {
  Pair p;
  int first;
  int second;
  int unpaired;
  std::vector<Pair> pairs;

  unpaired = -1;
  for (size_t i = 0; i < _data.size(); i += 2) {
    if (i + 1 < _data.size()) {
      first = _data[i];
      second = _data[i + 1];
      if (first < second) {
        p.loser = first;
		p.winner = second;
      } else {
        p.loser = second;
		p.winner = first;
      }
	  pairs.push_back(p);
    } else {
	  unpaired = _data[i];
    }
  }
  fordJohnsonSort(pairs);
    for (unsigned long int i = 0; i < pairs.size(); i++)
	{
	  if (i > 0)
		std::cout << " ";
	  std::cout << pairs[i].winner;
    }
    std::cout << "\n";
	for (unsigned long int i = 0; i < pairs.size(); i++)
	{
	  if (i > 0)
		std::cout << " ";
	  std::cout << pairs[i].loser;
    }
    std::cout << "\n";
    std::cout << "unpaired " << unpaired << "\n";
}

const char* PmergeMe::PmergeMeError::what() const throw()
{
  return ("Error\n");
}

std::ostream & operator<<( std::ostream &os, const PmergeMe &src )
{
  for (unsigned long int i = 0; i < src.getData().size(); i++)
	{
	  if (i > 0)
		os << " ";
	  os << src.getData()[i];
	}
  return (os);
}

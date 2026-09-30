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

void PmergeMe::simpleSortVectors( std::vector<Pair> & pairs ) {
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

void PmergeMe::fordJohnsonSortVectors( std::vector<Pair> & pairs ) {
  if (pairs.size() <= 3) {
    simpleSortVectors(pairs);
	return ;
  }
  std::vector<Pair> mainChainWinners;
  std::vector<Pair> mainChainLosers;
  // std::cout << "info 2\n";
  for (size_t i = 0; i < pairs.size(); i += 2) {
	if (i + 1 < pairs.size()) {
	  if (pairs[i].winner > pairs[i + 1].winner) {
		mainChainWinners.push_back(pairs[i]);
		mainChainLosers.push_back(pairs[i + 1]);
	  } else {
		mainChainWinners.push_back(pairs[i + 1]);
		mainChainLosers.push_back(pairs[i]);
	  }
	} else {
	  mainChainWinners.push_back(pairs[i]);
	}
  }
  fordJohnsonSortVectors(mainChainWinners);
  // Insert the loasing Pairs into mainChainWinners using Jacobsthal
  // sequence (Comparison during insertion still uses the 'winner' attribute)
  //std::cout << "info 3\n";
  insertLosersVectors(mainChainWinners, mainChainLosers);
  //std::cout << "info 4\n";
  pairs = mainChainWinners;
}

std::vector<int> PmergeMe::generateJacobsthalVectors( int size )
{
  int j0;
  int j1;
  int next;
  std::vector<int> jacob;
  
  if (size <= 0)
	return jacob;

  j0 = 0;
  j1 = 1;
  jacob.push_back(j1);
  //std::cout << "info 6\n";
  while(j1 < size)
	{
	  next = j1 + 2 * j0;
	  j0 = j1;
	  j1 = next;
	  if (j1 <= size)
		jacob.push_back(j1);
	}
  //std::cout << "info 7\n";
  return (jacob);
}

void PmergeMe::insertLosersVectors( std::vector<Pair> & mainChainWinners, std::vector<Pair> & mainChainLosers )
{
  std::vector<int> jacobChain;

  (void)mainChainWinners;
  //std::cout << "info 5\n";
  jacobChain = generateJacobsthalVectors(mainChainLosers.size());
  //std::cout << "info 8\n";
  std::cout << "JacobChain: " << jacobChain << "\n";
  //std::cout << "info 9\n";
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
  // std::cout << "info 1\n";
  fordJohnsonSortVectors(pairs);
    
  std::cout << pairs;
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

std::ostream & operator<<( std::ostream &os, const std::vector<Pair> & pairs )
{
  os << "winners: \n";
  for (unsigned long int i = 0; i < pairs.size(); i++)
	{
	  if (i > 0)
		os << " ";
	  os << pairs[i].winner;
    }
  os << "\nlosers: \n";
  for (unsigned long int i = 0; i < pairs.size(); i++)
	{
	  if (i > 0)
		os << " ";
	  os << pairs[i].loser;
    }
  return (os);
}

std::ostream & operator<<( std::ostream &os, const std::vector<int> & vect )
{
  for (unsigned long int i = 0; i < vect.size(); i++)
	{
	  if (i > 0)
		os << " ";
	  os << vect[i];
    }
  return (os);
}

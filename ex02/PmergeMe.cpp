#include "PmergeMe.hpp"

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

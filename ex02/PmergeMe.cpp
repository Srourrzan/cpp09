#include "PmergeMe.hpp"
#include <cstddef>
#include <iterator>
#include <utility>
#include <algorithm>

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
  if (res <= 0)
	return (false);
  return (true);
}

// VECTOR ALGO

void PmergeMe::simpleSortVectors( std::vector<int> & vect ) const{
  if (vect.size() <= 1)
    return ;
  if (vect.size() == 2) {
    if (vect[0] > vect[1])
      std::swap(vect[0], vect[1]);
	return ;
  }
  if (vect[0] > vect[1])
    std::swap(vect[0], vect[1]);
  if (vect[1] > vect[2])
    std::swap(vect[1], vect[2]);
  if (vect[0] > vect[1])
    std::swap(vect[0], vect[1]);
}

std::vector<int> PmergeMe::generateJacobsthalVectors(int size) const {
  int a0;
  int a1;
  int next;
  std::vector<int> jacob;

  if (size <= 0)
    return (jacob);
  a0 = 1;
  a1 = 3;
  jacob.push_back(a0);
  while (a1 <= size) {
    jacob.push_back(a1);
    next = a1 + 2 * a0;
    a0 = a1;
	a1 = next;
  }
  if (jacob.back() < size) {
	jacob.push_back(a1);
  }
  return (jacob);
}

void PmergeMe::binaryInsertVectors(std::vector<Pair> &pairs,
                                   std::vector<int> &winners, int g) const {
  size_t low;
  size_t mid;
  size_t high;
  int loser_val;
  int winner_val;
  std::vector<int>::iterator it;

  low = 0;
  loser_val = pairs[g].loser;
  winner_val = pairs[g].winner;
  it = std::find(winners.begin(), winners.end(), winner_val);
  high = std::distance(winners.begin(), it);
  while (low < high) {
    mid = low + (high - low) / 2;
    if (winners[mid] < loser_val)
      low = mid + 1;
    else
	  high = mid;
  }
  winners.insert(winners.begin() + low, loser_val);
}

void PmergeMe::insertLosersVectors(std::vector<Pair> &pairs,
                                   std::vector<int> &winners) const {
  size_t group_end;
  size_t group_start;
  std::vector<int> jacob;

  group_start = 0;
  jacob = generateJacobsthalVectors(pairs.size());
  for (size_t i = 0; i < jacob.size(); ++i) {
    group_end = jacob[i];
    if (group_end > pairs.size()) {
	  group_end = pairs.size();
    }

    for (int g = static_cast<int>(group_end) - 1;
         g >= static_cast<int>(group_start); --g) {
	  binaryInsertVectors(pairs, winners, g);
    }
	group_start = group_end;
  }
}

std::vector<int>
PmergeMe::fordJohnsonSortVectors(std::vector<int> &vect) const {
  Pair p;
  int unpaired;
  std::vector<Pair> pairs;
  std::vector<int> winners;

  unpaired = -1;
  // Base case
  if (vect.size() <= 3) {
    simpleSortVectors(vect);
	  return (vect);
  }
  // Pairing phase
  for (size_t i = 0; i < vect.size(); i += 2) {
    if (i + 1 < vect.size()) {
      if (vect[i] > vect[i + 1]) {
        p.winner = vect[i];
		p.loser = vect[i + 1];
      } else {
        p.winner = vect[i + 1];
		p.loser = vect[i];
      }
	  pairs.push_back(p);
    } else {
	  unpaired = vect[i];
    }
  }
  // Fetch winners
  for (size_t i = 0; i < pairs.size(); ++i) {
	winners.push_back(pairs[i].winner);
  }
  // Recursive sort
  fordJohnsonSortVectors(winners);
  // Insert losers
  insertLosersVectors(pairs, winners);
  // Insert unpaired element
  if (unpaired != -1) {
    size_t low = 0;
    size_t high = winners.size();
    while (low < high) {
      size_t mid = low + (high - low) / 2;
      if (winners[mid] < unpaired)
        low = mid + 1;
      else
		high = mid;
    }
	winners.insert(winners.begin() + low, unpaired);
  }
  vect = winners;
  return (vect);
}

// END OF VECTOR ALGO

// Deque algo

void PmergeMe::simpleSortDeque( std::deque<int> & deq ) const {
  if (deq.size() <= 1)
    return;
	if (deq.size() == 2) {
		if (deq[0] > deq[1])
			std::swap(deq[0], deq[1]);
		return;
	}
	if (deq[0] > deq[1])
		std::swap(deq[0], deq[1]);
	if (deq[1] > deq[2])
		std::swap(deq[1], deq[2]);
	if (deq[0] > deq[1])
		std::swap(deq[0], deq[1]);
}

std::deque<int> PmergeMe::generateJacobsthalDeque( int size ) const {
	int a0;
	int a1;
	int next;
	std::deque<int> jacob;

	if (size <= 0)
		return (jacob);
	a0 = 1;
	a1 = 3;
	jacob.push_back(a0);
	while (a1 <= size) {
		jacob.push_back(a1);
		next = a1 + 2 * a0;
		a0 = a1;
		a1 = next;
	}
	if (jacob.back() < size) {
		jacob.push_back(a1);
	}
	return (jacob);
}

void PmergeMe::binaryInsertDeque(std::deque<Pair> &pairs, 
																	std::deque<int> &winners, int g) const {
	size_t low;
	size_t mid;
	size_t high;
	int loser_val;
	int winner_val;
	std::deque<int>::iterator it;

	low = 0;
	loser_val = pairs[g].loser;
	winner_val = pairs[g].winner;
	it = std::find(winners.begin(), winners.end(), winner_val);
	high = std::distance(winners.begin(), it);
	while (low < high) {
		mid = low + (high - low) / 2;
		if (winners[mid] < loser_val)
			low = mid + 1;
		else
			high = mid;
	}
	winners.insert(winners.begin() + low, loser_val);
}


void PmergeMe::insertLosersDeque(std::deque<Pair> &pairs,
                                   std::deque<int> &winners) const {
	size_t group_end;
	size_t group_start;
	std::deque<int> jacob;

	group_start = 0;
	jacob = generateJacobsthalDeque(pairs.size());
	for (size_t i = 0; i < jacob.size(); ++i) {
		group_end = jacob[i];
		if (group_end > pairs.size()) {
			group_end = pairs.size();
		}
		for (int g = static_cast<int>(group_end) - 1;
					g >= static_cast<int>(group_start); --g) 
		{
						binaryInsertDeque(pairs, winners, g);
		}
		group_start = group_end;
	}
}

void PmergeMe::insertUnpairedDeque(std::deque<int> &winners, int unpaired) const {
	size_t low = 0;
	size_t mid = 0;
	size_t high = winners.size();

	while (low < high) {
		mid = low + (high - low) / 2;
		if (winners[mid] < unpaired)
			low = mid + 1;
		else
			high = mid;
	}
	winners.insert(winners.begin() + low, unpaired);
}

std::deque<int>
PmergeMe::fordJohnsonSortDeque(std::deque<int> &deq) const {
  Pair p;
  int unpaired;
  std::deque<Pair> pairs;
  std::deque<int> winners;

  unpaired = -1;
  if (deq.size() <= 3) {
    simpleSortDeque(deq);
    return(deq);
  }
	for (size_t i = 0; i < deq.size(); i += 2) {
		if (i + 1 < deq.size()) {
			if (deq[i] > deq[i + 1]) {
				p.winner = deq[i];
				p.loser = deq[i + 1];
			} else {
				p.winner = deq[i + 1];
				p.loser = deq[i];
			}
			pairs.push_back(p);
		} else {
			unpaired = deq[i];
		}
	}
	for (size_t i = 0; i < pairs.size(); ++i)
		winners.push_back(pairs[i].winner);
	fordJohnsonSortDeque(winners);
	insertLosersDeque(pairs, winners);
	if (unpaired > -1) {
		insertUnpairedDeque(winners, unpaired);
	}
	deq = winners;
	return (deq);
}


const char* PmergeMe::PmergeMeError::what( ) const throw( )
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

std::ostream & operator<<( std::ostream &os, const std::deque<int> &src )
{
  for (size_t i = 0; i < src.size(); ++i) {
    if (i > 0)
      os << " ";
    os << src[i];
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

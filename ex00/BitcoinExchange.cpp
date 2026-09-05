#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( )
: _data( )
{}

BitcoinExchange::~BitcoinExchange( )
{}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & src )
: _data(src._data)
{}

BitcoinExchange::BitcoinExchange( const std::map<std::string, int> data )
: _data(data)
{}

BitcoinExchange & BitcoinExchange::operator=( const BitcoinExchange & rhs )
{
	if (this != &rhs)
		_data = rhs._data;
	return (*this);
}

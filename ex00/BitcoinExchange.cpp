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

void BitcoinExchange::readEntry( const std::string val )
{
	size_t position;
	std::string valStr;
	std::string dateStr;

	position = val.find(" | ");
	if (position == std::string::npos or position != 10)
	{
		std::cerr << "Error: bad input: " << val << std::endl;
		return ;
	}
	dateStr = val.substr(0, position);
	valStr = val.substr(position + 3);
	if (valStr.length() == 0)
	{
		std::cerr << "Error: missing value: " << val << '\n';
		return ;
	}
	if (validateDate(dateStr) < 0)
		return ;
	return;
}

int BitcoinExchange::validateDate( std::string dateStr )
{
	size_t position;
	std::string Ystr;
	std::string Mstr;
	std::string Dstr;

	position = dateStr.find("-");
	Ystr = dateStr.substr(0, position);
	if (Ystr.length() != 4)
	{
		std::cerr << "Error: bad input => " << dateStr << '\n';
		return (-1);
	}
	std::cout << "position: " << position
	<< "\nYstr: " << Ystr
	<< "\n";
	return (0);
}

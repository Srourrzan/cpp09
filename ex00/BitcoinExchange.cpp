#include "BitcoinExchange.hpp"
#include <iostream>

BitcoinExchange::BitcoinExchange( )
: _data( )
{}

BitcoinExchange::~BitcoinExchange( )
{}

BitcoinExchange::BitcoinExchange( const BitcoinExchange & src )
: _data(src._data)
{}

BitcoinExchange::BitcoinExchange( const std::map<std::string, float> data )
: _data(data)
{}

BitcoinExchange & BitcoinExchange::operator=( const BitcoinExchange & rhs )
{
	if (this != &rhs)
		_data = rhs._data;
	return (*this);
}

void BitcoinExchange::evaluateData( const std::string date, float val )
{
  std::map<std::string, float>::iterator it = _data.upper_bound(date);
  if (it != _data.end()) {
    --it;
    std::cout << date
			  << " => "
              << it->second
			  << " = "
              << val * it->second
			  << "\n";
  }
}

void BitcoinExchange::validateEntry( const std::string val )
{
  size_t position;
  float fltVal;
	std::string valStr;
	std::string dateStr;

	position = val.find(" | ");
	if (position == std::string::npos or position != 10)
	{
		std::cerr << "Error: bad input => " << val << std::endl;
		return ;
	}
	dateStr = val.substr(0, position);
	valStr = val.substr(position + 3);
	if (valStr.length() == 0)
	{
		std::cerr << "Error: missing value => " << val << '\n';
		return ;
	}
	if (validateDate(dateStr) < 0)
          return;
	fltVal = validateVal(valStr);
	if (fltVal < 0)
          return;
	std::cout << "validating date: " << dateStr << "\n";
	evaluateData(dateStr, fltVal);
	return;
}

int BitcoinExchange::validateDate( const std::string dateStr )
{
	int day;
	int year;
	int month;
	std::string Ystr;
	std::string Mstr;
	std::string Dstr;

	if (dateStr[4] != '-' || dateStr[7] != '-')
		return(indicateError("bad input => ", dateStr));
	Ystr = dateStr.substr(0, 4);
	Mstr = dateStr.substr(5, 2);
	Dstr = dateStr.substr(8, 2);
	year = stringToFlt(Ystr);
	if (!rangeValid(year, 2009, 2100))
		return(indicateError("bad input => ", dateStr));
	month = stringToFlt(Mstr);
	if (!rangeValid(month, 1, 12))
		return(indicateError("bad input => ", dateStr));
	day = stringToFlt(Dstr);
	if (!rangeValid(day, 1, 31))
		return (indicateError("bad input => ", dateStr));
	return (0);
}

int BitcoinExchange::indicateError( const std::string msg, const std::string var )
{
	std::cerr << "Error: " << msg << var << '\n';
	return (-1);
}

float BitcoinExchange::stringToFlt( const std::string input )
{
	int ctr;
	float res;
	std::stringstream ss;

	ctr = 0;
	res = -1;
	for (size_t i = 0; i < input.size(); i++)
	{
		input[i] == '.' ? ctr++ : ctr;
		if ((!std::isdigit(input[i]) && (input[i] != '.')) || (ctr > 1))
			return (-1);
	}
	ss << input;
	ss >> res;
	ss.clear();
	return (res);
}

int BitcoinExchange::rangeValid( int val, int min, int max )
{
	if (val < min || val > max)
		return (false);
	return (true);
}

float BitcoinExchange::validateVal( const std::string val )
{
	float fltVal;

	fltVal = stringToFlt(val);
	if (fltVal < 0)
		return(indicateError("not a positive number.", ""));
	if (fltVal > 1000)
		return(indicateError("too large a number.", ""));
	return (fltVal);
}

BitcoinExchange BitcoinExchange::loadDatabase( )
{
	BitcoinExchange btc;

	std::ifstream inf("data.csv");
	if (!inf)
		throw(BitcoinExchange::FileCannotLoad());
	btc = read_data(inf, 1);
	return (btc);
}

void BitcoinExchange::readEntry( const std::string str)
{
	std::string dateStr;
	std::string valStr;

	dateStr = str.substr(0, 10);
	valStr = str.substr(11, str.length() - 11);
	_data.insert(std::make_pair(dateStr, stringToFlt(valStr)));
	return ;
}

BitcoinExchange BitcoinExchange::read_data(std::ifstream & inf, int type )
{
  int counter;
  std::string strInput;
  BitcoinExchange btc;

  counter = 0;
  std::cout << "type: " << type << "\n";
  while(std::getline(inf, strInput))
  {
    if (counter++ == 0)
    {
      if ((strInput == "date | value" && type == 0)
				|| (strInput == "date,exchange_rate" && type == 1))
        continue;
      throw (BitcoinExchange::InvalidHeader());
    }
		if (type == 0)
		{
			btc.validateEntry(strInput);
			continue;
		}
		else
		  btc.readEntry(strInput);
  }
  return (btc);
}

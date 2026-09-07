#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <cctype>
# include <string>
# include <fstream>
# include <sstream>
# include <iostream>
# include <algorithm>
# include <exception>

class BitcoinExchange
{
public:
	BitcoinExchange( );
	~BitcoinExchange( );
	BitcoinExchange( const BitcoinExchange & );
	BitcoinExchange( const std::map<std::string, int> );
	BitcoinExchange & operator=( const BitcoinExchange & );
	int 						rangeValid( int, int, int );
	void 						readEntry( const std::string );
	static 					BitcoinExchange loadDatabase( );
	float 					stringToFlt( const std::string );
	float 					validateVal( const std::string );
	int 						validateDate( const std::string );
	void 						validateEntry( const std::string );
	// void 						addEntry( const std::string, float );
	static BitcoinExchange read_data(std::ifstream &, int );
	int 						indicateError( const std::string, const std::string );


	class FileCannotLoad: public std::exception
	{
		public:
		virtual const char* what() const throw()
		{
			return ("Unable to load input file\n");
		}
	};

	class InvalidHeader: public std::exception
	{
		public:
		virtual const char* what() const throw()
		{
			return ("Incorrect file header\n");
		}
	};

private:
	std::map<std::string, int> _data;
};

#endif
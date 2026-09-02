#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
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
  int readEntry( std::string );
  void addEntry( std::string, int );

  class FileCannotLoad: public std::exception
  {
    public:
    virtual const char* what() const throw()
    {
      return ("Unable to load input file\n");
    }
  };

  

private:
  std::map<std::string, int> _data;
};

#endif
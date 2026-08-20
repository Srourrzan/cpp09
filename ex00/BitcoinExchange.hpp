#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <iostream>
# include <algorithm>

class BitcoinExchange
{
public:
  BitcoinExchange( );
  ~BitcoinExchange( );
  BitcoinExchange( const BitcoinExchange & );
  BitcoinExchange( const std::map<std::string, int> );
  BitcoinExchange & operator=( const BitcoinExchange & );

  

private:
  std::map<std::string, int> _data;
};

#endif
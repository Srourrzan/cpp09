#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    std::cerr << "provide database file in csv format\n";
    return (1);
  }
  
  return (0);
}
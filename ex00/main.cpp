#include <fstream>
#include "BitcoinExchange.hpp"

BitcoinExchange read_data(std::ifstream & inf)
{
  std::string strInput;
  BitcoinExchange btc;

  while(std::getline(inf, strInput))
  {
    std::cout << strInput << '\n';
  }
  return (btc);
}

void parse_file(char *file_name)
{
  BitcoinExchange btc;

  std::ifstream inf(file_name);
  if (!inf)
    throw(BitcoinExchange::FileCannotLoad());
  btc = read_data(inf);
  return ;
}

int validate_parameters( int argc )
{
  if(argc < 2)
  {
    std::cerr << "provide database file in csv format\n";
    return (-1);
  }
  if (argc > 2)
  {
    std::cerr << "Too many passed parameters\n";
    return (-1);
  }
  return (0);
}

int main(int argc, char **argv)
{
  if (validate_parameters(argc) < 0)
    return (1);
  try {
    parse_file(argv[1]);

  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }
  return (0);
}
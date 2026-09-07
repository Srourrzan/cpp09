#include "BitcoinExchange.hpp"

void parse_file(char *file_name)
{
  std::ifstream inf(file_name);
  if (!inf)
    throw(BitcoinExchange::FileCannotLoad());
  BitcoinExchange::read_data(inf, 0);
  return ;
}

int validate_parameters( int argc )
{
  if(argc < 2)
  {
    std::cerr << "Error: could not open file.\n";
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
  BitcoinExchange btc;

  if (validate_parameters(argc) < 0)
    return (1);
  try {
    btc = BitcoinExchange::loadDatabase( );
    parse_file(argv[1]);
  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }
  return (0);
}
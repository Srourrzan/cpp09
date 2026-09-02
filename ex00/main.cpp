#include <fstream>
#include "BitcoinExchange.hpp"

void read_file(char *file_name)
{
  std::cout << "file name: " 
  << file_name
  << std::endl;

  std::ifstream inf(file_name);
  if (!inf)
    throw(BitcoinExchange::FileCannotLoad());
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
    read_file(argv[1]);

  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }
  return (0);
}
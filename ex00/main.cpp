#include "BitcoinExchange.hpp"

void read_data(BitcoinExchange & btc, std::ifstream & inf, int type )
{
  int counter;
  std::string strInput;

  counter = 0;
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
}

void parse_file(BitcoinExchange & btc, const char *file_name, int type) {
  std::ifstream inf(file_name);
  if (!inf)
    throw(BitcoinExchange::FileCannotLoad());
  
  read_data(btc, inf, type);
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
	parse_file(btc, "data.csv", 1);
    parse_file(btc, argv[1], 0);
  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }
  return (0);
}

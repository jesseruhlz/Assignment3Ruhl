//main file
#include "GenStack.h"

#include <iostream>
#include <fstream>
using namespace std;

//converts a given string to be all upper case
string toUpperFunction(string value)
{
  //char str[value.length()] = value;
  string rtn = "";
  for (int i = 0; i < value.length(); i++)
  {
    rtn += toupper(value[i]);
  }
  return rtn;
}

int main (int argc, char **argv)
{
  cout << "This program checks the delimiters of a given .cpp file." << endl;
  cout << "If the given file is balanced, it will automatically ask for another file. To break the loop type STOP" << endl;
  cout << "Delimiters include: () {} []" << endl;

  string fileName;

  while(true)
  {
    cout << "Enter a location of a .cpp file or type STOP" << endl;
    cout << "Format should be like ../TestFile/file.cpp" << endl;
    cin >> fileName;
    if (toUpperFunction(fileName) == "STOP"){
      cout << "PROGRAM TERMINATED" << endl;
      break;
    }

    ifstream infile(fileName);
    if(!infile){
      cerr << "ERROR: cannot open " << fileName << endl;
      break;
    }
    else
    {
      GenStack<char> BalanceCheck;
      if (BalanceCheck.balanceCheck(infile) == false)
        break;
    }
  }


  return 0;
}

//template class
//will include both the header as well as implementation
#include <iostream>
#include <fstream>
//#include <stack>
using namespace std;
//constant amount at which stack is increased to allocate more namespace
//#define BOUND 4

template<class T>
class GenStack
{
  public:
    GenStack(); //default
    GenStack(T maxSize); // overloaded constructor w/ T being any value type
    ~GenStack(); // destructor
    //GenStackResize(T arr); // a copy of the original stack that allocates new size

    T push(T data);
    T pop();
    T peek();
    T print(T arr);

    bool matchingDelims(char c, char d);
    void printFile(ifstream &infile);
    bool balanceCheck(ifstream &infile);

    bool isFull();
    bool isEmpty();
    int getSize();

  private:
    T *myArray;
    int top;
    int mSize;

};

//default constructor
template <class T>
GenStack<T>::GenStack()
{
  myArray = new T[100];
  mSize = 100;
  top = -1;
}

//overloaded constructor
template <class T>
GenStack<T>::GenStack(T maxSize)
{
  myArray = new T[maxSize];
  mSize = maxSize;
  top = -1;
}

// destructor
template <class T>
GenStack<T>::~GenStack()
{
  delete myArray;
}


template <class T>
T GenStack<T>::push(T data)
{
  //checks if stack is full
  if(isFull())
  {
    cout << "ERROR: stack is full" << endl;
    //this is where we will possibly send it to create a copy of stack w/ increased size
  }
  myArray[++top] = data;
}

template <class T>
T GenStack<T>::pop()
{
  //check if empty before removing
  if(isEmpty()){
    cout << "ERROR: stack is empty" << endl;
    return '\0';
    }
  return myArray[top--];
}
//function to create a new stack
//this will be a copy of the original, but allocate more space to it
/*
template <class T>
GenStack<T>::GenStackResize(int newSize)
{
  maxSize = newSize;
  T* copy = new T[maxSize];
  for (int i = 0; i < top; i++)
    copy[i] = arr[i];
  //msize = maxSize + BOUND;
  delete [] myArray;
  myArray = new T[maxSize];
  myArray = copy;
  delete[] copy;
}
*/
template <class T>
T GenStack<T>::peek()
{
  return myArray[top];
}

template <class T>
T GenStack<T>::print(T arr)
{
  if(isEmpty()){
    cout << "ERROR: stack is empty" << endl;
    return '\0';
  }
  else{
    cout << "Stack: ";
    for(int i = 0; i <= top; i++)
      cout << arr[i] << " ";
    cout << endl;
  }
}

template <class T>
bool GenStack<T>::isFull()
{
  return (top == mSize - 1);
}

template <class T>
bool GenStack<T>::isEmpty()
{
  return (top == -1);
}

template <class T>
int GenStack<T>::getSize()
{
  return top + 1;
}

//function prints the .cpp file that is being read in

template <class T>
void GenStack<T>::printFile(ifstream &infile)
{
  string line;
  //just teseting to see if the file is being read in properly
  //and that everything ios
  while(getline(infile,line))
  {
    cout << line << endl;
  }
  infile.close();
}

//function will read in the needed delimiters and add them to a stack
template <class T>
bool GenStack<T>::balanceCheck(ifstream &infile)
{
  //infile.open(fileName);
  bool match = true;

  GenStack *myStack = new GenStack();
  char c, d, e;
  int counter = 0;
  int linenumber = 1;

  while (infile.get(c))
  {
    if (c == '\n')
    {
      //increases the number line by 1 each time a new line is read
      linenumber++;
    }
    //pushing left hand delimter onto stack
    //cout << "line " << linenumber << endl;
    if (c == '(' || c == '{' || c == '['){
      //add while myStack is not full, push
      //if full allocate more memory to it
      myStack->push(c);
      cout << "push " <<  c << endl;
      //cout << "Placement 1" << endl;
    }
    //makes c be the right hand delimiter
    //this way, it compares stack to char c
    else if (c == ')' || c == '}' || c == ']')
    {
      //if stack is empty and a right hand delimter is read in
      //the file will automatically be unbalanced
      if (myStack->isEmpty())
      {
        //cout << "Placement 2" << endl;
        cout << "Stack empty. Unballanced delimiter " << c << " on line: " << linenumber << endl;
        match = false;
        break;
      }
      //d is the left hand delimiter
      d = myStack->peek();
      //cout << "peek" <<  d << endl;
      //pops the left hand delimiter from the stack to be compared to d
      myStack->pop();


      if (matchingDelims(c,d))
      {
        //cout << "Placement 3" << endl;
        //lines->pop();
        //match = true;
        //cout << "the delimiters are matching" << endl;
      }
      if (!matchingDelims(c,d))
      {
        //cout << "Placement 4" << endl;
        cout << "Unbalanced " << c << " delimiter at line: " << linenumber << endl;
        cout << "Line: " << linenumber << " expected " << d << endl;
        match = false;
        break;
      }

    }
  }

  if (!myStack->isEmpty())
  {
    //cout << "Placement 5" << endl;
    cout << "Unbalanced delimiter " << myStack->peek() << " on line: " << linenumber <<endl;
    cout << "Expected " << d << " to be on line " << linenumber << endl;
    match = false;
  }
  if (match == true){
    //cout << "Placement 6" << endl;
    cout << "The delimiters are balanced and match up with each other. " << endl;
  }
  else{
    //cout << "Placement 7" << endl;
    cout << "The delimiters are unbalanced and do not match up with each other. " << endl;
    //return false;
  }
  delete myStack;
  //infile.close();

  return match;
}

template <class T>
bool GenStack<T>::matchingDelims(char c, char d)
{
  if (c == '}' && d == '{')
		return true;
	else if (c == ')' && d == '(')
		return true;
	else if (c == ']' && d == '[')
		return true;
	else return false;
}

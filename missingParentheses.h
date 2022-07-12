/****************************************************
Name: Collan Parker
Date: 7 May 2020
Problem Number: 7
Instructor: Komogortsev, TSU
*****************************************************/

#ifndef prog7_h
#define prog7_h

#include <string>
#include <fstream>

using namespace std;

class EquationStack
{
private:
   struct EqNode //Linked-List structure
   {
      string equation;
      EqNode *nextEq;  // points to the next node in the stack
   };

   EqNode *lifo;      // points to the data that was added most recently
                      // L(ast) I(n) F(irst) O(ff)

public:
   EquationStack( ) // Constructor
      {  lifo = NULL; }

   ~EquationStack( ); // Destructor

   string setEq( ifstream& );
   void push( string );
   string pop( string& );
   bool isEmpty( );
};

#endif // prog7_h

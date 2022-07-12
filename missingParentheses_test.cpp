/****************************************************
Name: Collan Parker
Date: 7 May 2020
Problem Number: 7
Instructor: Komogortsev, TSU
*****************************************************/
#include <iostream>
#include <fstream>

#include "missingParentheses.h"

using namespace std;

int main()
{
    char inFileName[128]; // this will be read into, from the console

    string lineFromFile, // one individual line
           popped_str; // stores the return value of pop

    int number_of_eq = 0;

    EquationStack EqLibrary; // Constructor call

    cout << "What is the name of your input file? ";
    cin >> inFileName;

    ifstream fin;
    ofstream fout;

    fin.open( inFileName );
    while (!fin) {
        cout << "Can't find file: " << inFileName << endl;
        cout << "What is the name of your input file? ";
        cin >> inFileName;
        fin.open(inFileName);
    }

    fout.open( "output.dat" );

    while( !fin.eof( ) )
    {
        lineFromFile = EqLibrary.setEq( fin );
        EqLibrary.push( lineFromFile );
        number_of_eq++;
    }

    for( int i = 0; i < number_of_eq; i++ )
    {
        popped_str = EqLibrary.pop( lineFromFile );
        fout << popped_str << endl;
    }

    fin.close( );
    fout.close( );
    
    return 0;
}

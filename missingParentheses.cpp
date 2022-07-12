/****************************************************
Name: Collan Parker
Date: 7 May 2020
Problem Number: 7
Instructor: Komogortsev, TSU
*****************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string.h>

#include "missingParentheses.h"

using namespace std;

/*
function: EquationStack::~EquationStack, this destructor creates two
                                         pointers, one pointer that points
                                         to the head pointer and another
                                         that points to the next node, then
                                         the list is traversed and deleted.

parameters: none

returns: nothing
*/

EquationStack::~EquationStack( )
{
    EqNode *nodePtr,
           *nextNode;

    // Position nodePtr at the top of the stack.
    nodePtr = lifo;

    while (nodePtr != NULL) // Traverse stack
    {
        nextNode = nodePtr->nextEq;
        delete nodePtr; // delete stack
        nodePtr = nextNode;
    }
}

/*
function: EquationStack::push, this void function pushes the string passed in
                               onto the top of the stack, by checking if the
                               list is empty, then if the list is not full a
                               pointer points to the top node.

parameters: string eq, this stores the data of an equation in a string

returns: nothing
*/

void EquationStack::push( string eq )
{
    EqNode *newNode; // Pointer to a new node

    newNode = new EqNode;
    newNode->equation = eq;

    if (isEmpty())
    {
        lifo = newNode;
        newNode->nextEq = NULL;
    }
    else  // Otherwise, insert NewNode before lifo(top of stack).
    {
        newNode->nextEq = lifo;
        lifo = newNode;
    }
}

/*
function: EquationStack::pop, this function creates a temporary pointer, then
                              checks to see if the stack is empty. If the stack
                              is not empty then the data is removed from the
                              top of the stack, and the memory allocated for
                              the node is deleted.

parameters: string eq, this stores the data of an equation in a string

returns: a string, of the equation that was removed.
*/

string EquationStack::pop(string &eq)
{
    EqNode *temp; // temporary pointer

    if (isEmpty())
    {
        cout << "The stack is empty." << endl;
    }
    else  // pop value off top of stack
    {
        eq = lifo->equation;
        temp = lifo->nextEq;
        delete lifo;
        lifo = temp;
    }

    return eq;
}

/*
function: EquationStack::isEmpty, this function creates a boolean variable that
                                  stores the status of emptiness. If the last
                                  in data is empty then the function returns
                                  empty as true, and if not then the function
                                  returns empty as false.

parameters: none

returns: true if the stack is empty, and false if the stack is not empty
*/
bool EquationStack::isEmpty()
{
    bool emp;

    if (!lifo)
       emp = true;
    else
       emp = false;

    return emp;
}

/*
function: EquationStack::setEq, this string function creates an array of
                                chars that stores the order missing parentheses
                                or brackets, if there are more than 6
                                mistakes the program responds with an error.
                                An array of the parentheses and brackets in
                                a given equation is saved here. Then two empty
                                strings are created, one to store a running
                                string that will eventually by the return value.
                                The running string revieves the original
                                equation followed by the status of validity,
                                depending on if non-accepted characters are
                                in the equation. And if necessary what is wrong
                                with equation is also added to the string, that
                                will eventually be pushed to stack after
                                it is return to it's call. Then several
                                checks are done to see if the data is valid,
                                and what is missing in order to have a correct
                                equation.


parameters: ifstream &fin, this will be used to get the correct amount of
                           equations

returns: a string, of the original equation concatenated with whether or not
                   the equation has acceptable characters, too many errors,
                   and the necessary parentheses and brackets.
*/

string EquationStack::setEq( ifstream &fin )
{
    const int MAX_MISSING = 6;

    char equation[128],
         order_of[64], // order of parentheses and brackets
         missing[MAX_MISSING] = {'\0'};

    int eq_index = 0, //specific index of an equation
        order_index = 0, // index of array of used parentheses and brackets
        total_missing = 0, // count of missing parentheses and brackets
        par_count = 0, // parentheses counter
        bra_count = 0; // brackets counter

    string working_eq = "";
    string whats_missing = "";

    bool balanced_par = true, // are parentheses/ bracket opened and closed?
         balanced_bra = true, // true b/c no par/ bra is settled
         satisfied = true;

    while( fin.get( equation[eq_index] ) )
    {
        if( equation[eq_index] == '\n' )
            break;

        eq_index++;
    }

    equation[eq_index + 1] == '\0';

    for( int i = 0; i < eq_index; i++ )
    {

        working_eq = working_eq + equation[i];

        if( isalnum( equation[i] ) || equation[i] == '+' || equation[i] == '-'
             || equation[i] == '*' || equation[i] == '/' ); //do nothing

        else if( equation[i] == '(' )
        {
            order_of[order_index] = '(';

            order_index++;
        }

        else if( equation[i] == ')' )
        {
            order_of[order_index] = ')';
            order_index++;
        }

        else if( equation[i] == '[' )
        {
            order_of[order_index] = '[';
            order_index++;
        }
        else if( equation[i] == ']' )
        {
            order_of[order_index] = ']';
            order_index++;
        }
        else
            whats_missing = " === INVALID EXPRESSION, data not accepted" ;
    }

    order_of[order_index] = '\0';

    for( int j = 0; j < order_index; j++ )
    {
        if( order_of[j] == '(' )
        {
            par_count++;
        }

        else if( order_of[j] == ')' )
        {
            par_count--;
        }

        else if( order_of[j] == '[' )
        {
            bra_count++;
        }

        else
        {
            bra_count--;
        }
    }

    if( par_count > 0 )
    {
        total_missing += par_count;
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            for( int k = total_missing - par_count;
                ( k < ( total_missing + par_count ) ); k++ )
            {
                missing[k] = ')';
            }
        }
    }

    else if( par_count < 0 )
    {
        total_missing += ( par_count * -1 );
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            for( int k = total_missing - par_count;
                ( k < ( total_missing + par_count ) ); k++ )
            {
                missing[k] = '(';
            }
        }
    }

    if( bra_count > 0 )
    {
        total_missing += bra_count;
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            for( int k = total_missing - bra_count;
                ( k < ( total_missing + bra_count ) ); k++ )
            {
                missing[k] = ']';
            }
        }
    }

    else if( bra_count > 0 )
    {
        total_missing += bra_count;
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            for( int k = total_missing - bra_count;
                ( k < ( total_missing + bra_count ) ); k++ )
            {
                missing[k] = ']';
            }
        }
    }

    if( order_of[0] == ')' )
    {
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            missing[total_missing] = '(';
            total_missing++;
        }
    }

    if( order_of[0] == ']' )
    {
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            missing[total_missing] = '[';
            total_missing++;
        }
    }

    if( order_of[order_index - 1] == '(' )
    {
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            missing[total_missing] = ')';
            total_missing++;
        }
    }

    if( order_of[order_index - 1] == '[' )
    {
        satisfied = false;

        if( total_missing < MAX_MISSING )
        {
            missing[total_missing] = ']';
            total_missing++;
        }
    }



    for( int j = 0; j < order_index - 1; j++ )
    {
        if( order_of[j] == '(' && order_of[j + 1] == ']' )
        {
            satisfied = false;
            if( total_missing + 2 < MAX_MISSING )
            {
                missing[total_missing] = ')';
                total_missing++;

                missing[total_missing] = '[';
                total_missing++;
            }
        }

        else if( order_of[j] == '[' && order_of[j + 1] == ')' )
        {
            satisfied = false;
            if( total_missing + 2 < MAX_MISSING )
            {
                missing[total_missing] = ']';
                total_missing++;

                missing[total_missing] = '(';
                total_missing++;
            }
        }
    }

    if( satisfied == true && bra_count == 0 && par_count == 0 )
    {
        working_eq = working_eq + " === valid expression";
    }

    if( total_missing >= MAX_MISSING )
    {
        working_eq = working_eq + " === invalid expression, there are more than"
                   + " six elements missing" ;
    }

    if( total_missing < MAX_MISSING && satisfied == false )
    {
        working_eq = working_eq + " === missing ";
        for( int c = 0; c < total_missing; c++ )
        {
            working_eq = working_eq + missing[c] + " ";
        }
    }

    working_eq = working_eq + whats_missing;

    //cout << working_eq << endl;

    return working_eq;
}

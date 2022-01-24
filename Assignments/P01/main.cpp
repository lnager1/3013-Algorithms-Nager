/*****************************************************************************
*                    
*  Author:           Lindsey
*  Email:            nager.lindsey@gmail.com
*  Label:            04-A03B
*  Title:            Comment Practice
*  Course:           CMPS 3013-201
*  Semester:         Spring 2022
* 
*  Description:
*        This program implements a linked list that has the [] operator overladed
*        to be accessed similarly to an array
*  
*  Usage:
*        N/A
* 
*  Files:   
*       main.cpp    :   driver program
*****************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

// Default Values
const int defSize = 10;
const double defGrow = 1.0;
const double defShrink = .15;
const double defEnl = 2.0;
const double defRed = .5;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack
{
    private:
        int *A;           // pointer to array of int's
        int size;         // current max stack size
        int top;          // top of stack 

        double shrinkThresh;  // how small it's allowed to get
        double growThresh;    // how big it's allowed to get
        double enlargeThresh; // the rate it grows by
        double reduceThresh;  // the rate it shrinks by
        
        int maxSize;        // maximum size reached
        int numOfResizes;   // number of resizes 

    public:

        /**
         * ArrayStack
         * 
         * Description:
         *      Constructor with all params
         * 
         * Params:
         *     - double gt
         *     - double st
         *     - double et
         *     - double rt
         *     - int s
         * 
         * Returns:
         *     - NULL
         */
        ArrayStack(double gt, double st, double et, double rt, int s)
        {
            // Creates array of size and assigns top
            size = s;
            A = new int[s];
            top = -1;   

            // assigns values to thresholds
            gt == 0? growThresh = defGrow : growThresh = gt;
            st == 0? shrinkThresh = defShrink : shrinkThresh = st;
            et == 0? enlargeThresh = defEnl : enlargeThresh = et;
            rt == 0? reduceThresh = defRed : reduceThresh = rt;
            
            // assigns maxSize and numOfResizes
            maxSize = size;
            numOfResizes = 0;
        } 

        /**
         * ArrayStack
         * 
         * Description:
         *      Constructor no params
         * 
         * Params:
         *     - None
         * 
         * Returns:
         *     - NULL
         */
        ArrayStack() : ArrayStack(0, 0, 0, 0, defSize){}

        /**
         * ArrayStack
         * 
         * Description:
         *      Constructor size param
         * 
         * Params:
         *     - int size
         * 
         * Returns:
         *     - NULL
         */
        ArrayStack(int s) : ArrayStack(0, 0, 0, 0, s){}

        /**
         * ArrayStack
         * 
         * Description:
         *      Constructor with theshold parameters
         * 
         * Params:
         *     - double gt
         *     - double st
         *     - double et
         *     - double rt
         * 
         * Returns:
         *     - NULL
         */
        ArrayStack(double gt, double st, double et, double rt) : ArrayStack(gt, st, et, rt, defSize){}

        

        /**
         * Public bool: Empty
         * 
         * Description:
         *      Stack empty?
         * 
         * Params:
         *      NULL
         * 
         * Returns:
         *      [bool] true = empty
         */
        bool tooEmpty()
        {
            // If the percentage empty is less than or equal to shrinkThresh
            return (((double)(top)/size) <= shrinkThresh);
        }
        
        /**
         * Public bool: Full
         * 
         * Description:
         *      Stack full?
         * 
         * Params:
         *      NULL
         * 
         * Returns:
         *      [bool] true = full
         */
        bool tooFull()
        {
            // If the percentage full is greater than or equal to grow Thresh
            return (((double)(top+1)/size) >= growThresh);
        }

        /**
         * Public void: checkResize
         * 
         * Description:
         *      checks if the stack needs to be resized 
         * 
         * Params:
         *      NULL
         * 
         * Returns:
         *      NULL
         */
        void checkResize()
        {
            // Doesn't allow it to go below 10
            if(size > 10 && tooEmpty())
            {
                ContainerShrink();         
            }
            if(tooFull())
            {
                ContainerGrow();
            }
        }

        /**
         * Public int: Peek
         * 
         * Description:
         *      Returns top value without altering the stack
         * 
         * Params:
         *      NULL
         * 
         * Returns:
         *      [int] top value if any
         */
        int Peek()
        {
            if(!tooEmpty())
            {
                return A[top];
            }
            
            return -99; // some sentinel value
                        // not a good solution
        }

        /**
         * Public int: Pop
         * 
         * Description:
         *      Returns top value and removes it from stack
         * 
         * Params:
         *      NULL
         * 
         * Returns:
         *      [int] top value if any
         */
        int Pop()
        {   
            checkResize();
            if(!tooEmpty())
            {
                top--;
                return A[top+1];
            }

            return -99; // some sentinel value
                        // not a good solution
        }

        /**
         * Public void: Print
         * 
         * Description:
         *      Prints stack to standard out
         * 
         * Params:
         *      std::ofstream& : outfile
         * 
         * Returns:
         *      NULL
         */
        void Print(std::ofstream& outfile)
        {
            std::cout << "######################################################################\n";
            
            std::cout << "\tAssignment 4 - Resizing the Stack\n";
            std::cout << "\tCMPS 3013\n";
            std::cout << "\tLindsey Nager\n\n\n";

            std::cout << "\tMax Stack Size: " << maxSize << "\n";
            std::cout << "\tEnd Stack Size:: " << size << "\n";
            std::cout << "\tStack Resized: " << numOfResizes << " times\n\n";

            std::cout << "######################################################################\n";

            outfile << "######################################################################\n";
            
            outfile << "\tAssignment 4 - Resizing the Stack\n";
            outfile << "\tCMPS 3013\n";
            outfile << "\tLindsey Nager\n\n\n";

            outfile << "\tMax Stack Size: " << maxSize << "\n";
            outfile << "\tEnd Stack Size:: " << size << "\n";
            outfile << "\tStack Resized: " << numOfResizes << " times\n\n";

            outfile << "######################################################################\n";
        } 

        /** 
         * Public bool: Push
         * 
         * Description:
         *      Adds an item to top of stack
         * 
         * Params:
         *      [int] : item to be added
         * 
         * Returns:
         *      [bool] ; success = true
         */
        bool Push(int x)
        {
            checkResize();

            A[++top] = x;
            return true;
        }

        /**
         * Public void: ContainerGrow
         * 
         * Description:
         *      Resizes the container for the stack by doubling
         *      its capacity
         * 
         * Params:
         *      NULL
         * 
         * Returns:
         *      NULL
         */
        void ContainerGrow()
        {
            int newSize = size*enlargeThresh;   // double size of original
            int *B = new int[newSize];          // allocate new memory

            for(int i=0;i<size;i++)             // copy values to new array
            {    
                B[i] = A[i];
            }

            delete [] A;                        // delete old array

            size = newSize;                     // save new size

            A = B;                              // reset array pointer

            // Resets MaxSize
            size > maxSize? maxSize = size : maxSize = maxSize;
            numOfResizes++;
        }

        /**
         * Public void: ContainerShrink
         * 
         * Description:
         *      Resizes the container for the stack by halfing
         *      its capacity
         * 
         * Params:
         *      NULL
         * 
         * Returns:
         *      NULL
         */
        void ContainerShrink()
        {
            int newSize = size*(1-reduceThresh);  // half the size of original
            
            int *B = new int[newSize];            // allocate new memory

            for(int i=0; i< newSize; i++)         // copy values to new array
            {    
                B[i] = A[i];
            }

            delete [] A;                // delete old array

            size = newSize;             // save new size

            A = B;                      // reset array pointer
            numOfResizes++;
        }

};



// MAIN DRIVER
// Simple Array Based Stack Usage:
int main() 
{
    // Creates stream variables
    std::ifstream infile;
    std::ofstream outfile;

    infile.open("data.txt");
    outfile.open("output.txt");

    // variables
    int useNum;

    // Stack Object
    ArrayStack stack;

    // While loop that pushes or pops
    while(infile >> useNum) useNum%2 == 0? stack.Push(useNum) : stack.Pop();
    
    // Print
    stack.Print(outfile);

    // Closes program
    infile.close();
    outfile.close();
    return 0;
}
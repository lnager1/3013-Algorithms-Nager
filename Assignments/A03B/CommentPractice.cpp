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
#include <string>

using namespace std;

// Statically declared variable
int A[100];

/**
 * Node
 * 
 * Description:
 *      This class implements a node structure
 *      
 * Public Methods:
 *                       Node()
 *                       Node(int val) 
 * 
 * Private Methods:
 *      N/A
 * 
 * Usage: 
 *     
 *      Used primarly in other data structures
 *      
 */
struct Node 
{
    // Variables
    int x;
    Node *next;

    /**
    * Public : Node
    * 
    * Description:
    *      Default constuctor that initializes values
    * 
    * Params:
    *      No parameters
    *
    * Returns:
    *      No return values
    */
    Node() 
    {
        x = -1;
        next = NULL;
    }

    /**
    * Public : Node
    * 
    * Description:
    *      Constuctor that initializes values passed in
    * 
    * Params:
    *      int      :   n
    *
    * Returns:
    *      No return values
    */
    Node(int n) 
    {
        x = n;
        next = NULL;
    }
};

/**
 * List
 * 
 * Description:
 *      This class implements a list based around the struct Node
 *      
 * Public Methods:
 *                       List()
 *      void             Push(int val)
 *      void             Insert(int val)
 *      void             PrintTail()
 *      string           Print()
 *      int              Pop()
 *      List             operator+(const List &Rhs)
 *      int              operator[](int index)
 *      friend ostream   &operator<<(ostream &os, List L)
 * 
 * Private Methods:
 *      N/A
 * 
 * Usage: 
 *     
 *      List L()         Create instance of List
 *      
 */
class List 
{
    private:
        Node *Head;
        Node *Tail;
        int Size;

    public:
        /**
        * Public : List
        * 
        * Description:
        *      Default constuctor that initializes list
        * 
        * Params:
        *      N/A
        *
        * Returns:
        *      No return values
        */
        List() 
        {
            Head = Tail = NULL;
            Size = 0;
        }

        /**
        * Public : Push
        * 
        * Description:
        *      Adds a value to the end 
        * 
        * Params:
        *      int      :   value to add
        *
        * Returns:
        *      No return values
        */
        void Push(int val) 
        {
            // allocate new memory and init node
            Node *Temp = new Node(val);

            if (!Head && !Tail) 
            {
                Head = Tail = Temp;
            } 
            else
            {
                Tail->next = Temp;
                Tail = Temp;
            }

            Size++;
        }

        /**
        * Public : Insert
        * 
        * Description:
        *      Adds a value to the end 
        * 
        * Params:
        *      int      :   value to add
        *
        * Returns:
        *      No return values
        */
        void Insert(int val) 
        {
            // allocate new memory and init node
            Node *Temp = new Node(val);

            // figure out where it goes in the list

            Temp->next = Head;
            Head = Temp;
            if (!Tail) 
            {
                Tail = Head;
            }
            Size++;
        }

        /**
        * Public : PrintTail
        * 
        * Description:
        *      Prints tail value
        * 
        * Params:
        *      N/A
        *
        * Returns:
        *      No return values
        */
        void PrintTail() 
        {
            cout << Tail->x << endl;
        }

        /**
        * Public : Print
        * 
        * Description:
        *      Prints entire list
        * 
        * Params:
        *      N/A
        *
        * Returns:
        *      string   :   entire list on one string
        */
        string Print() 
        {
            Node *Temp = Head;
            string list;

            while (Temp != NULL) 
            {
                list += to_string(Temp->x) + "->";
                Temp = Temp->next;
            }

            return list;
        }

        /**
        * Public : Pop
        * 
        * Description:
        *      Removes an item from the list
        * 
        * Params:
        *      No parameters
        *
        * Returns:
        *      int      :   the value popped
        */

        // not implemented
        int Pop() 
        {
            Size--;
            return 0; //
        }

        /**
        * Public : operator+
        * 
        * Description:
        *      Adds two lists together
        * 
        * Params:
        *      const List   :    &Rhs
        *
        * Returns:
        *      int      :   the value popped
        */
        List operator+(const List &Rhs) 
        {
            // Create a new list that will contain both when done
            List NewList;

            // Get a reference to beginning of local list
            Node *Temp = Head;

            // Loop through local list and Push values onto new list
            while (Temp != NULL) 
            {
                NewList.Push(Temp->x);
                Temp = Temp->next;
            }

            // Get a reference to head of Rhs
            Temp = Rhs.Head;

            // Same as above, loop and push
            while (Temp != NULL) 
            {
                NewList.Push(Temp->x);
                Temp = Temp->next;
            }

            // Return new concatenated version of lists
            return NewList;
        }

        /**
        * Public : operator[+]
        * 
        * Description:
        *      accesses list like an array
        * 
        * Params:
        *      int   :    index
        *
        * Returns:
        *      int      :   the value accessed
        */
        int operator[](int index) 
        {
            Node *Temp = Head;

            if (index >= Size) 
            {
                cout << "Index out of bounds, exiting";
                exit(0);
            } 
            else 
            {
                for (int i = 0; i < index; i++) 
                {
                    Temp = Temp->next;
                }
                return Temp->x;
            }
        }

        /**
        * Function : operator<<
        * 
        * Description:
        *      Overloads the << operator so that the queue can be printed as a normal variable
        * 
        * Params:
        *      ostream &           :   reference to the stream
        *      List                :   Instance of list to be printed
        *
        * Returns:
        *     ostream &            :   a referece to the stream
        */
        friend ostream &operator<<(ostream &os, List L) 
        {
            os << L.Print();
            return os;
        }
};

int main(int argc, char **argv) 
{
    // Two list instances
    List L1;
    List L2;
    
    // Push loop
    for (int i = 0; i < 25; i++) 
    {
        L1.Push(i);
    }

    // Push loop
    for (int i = 50; i < 100; i++) 
    {
        L2.Push(i);
    }


    // Print and access
    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
/**
 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it 
 * lets you decide what to do based on what character you are pressing.
 * 
 * You can test which characters are being pressed using thier ascii values. 
 * 
 * An ascii table here should be helpful 
 *      http://www.asciitable.com/
 * 
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *      
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between 
 *                            the two (in this context).
 * 
 * Code below is a basic example of using a "getch" function along with
 * searching an array of words for partial matches. 
 * 
 * https://repl.it/@rugbyprof/getchexample#main.cpp
 */

#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

/**
 * wordNode
 * 
 * Description:
 *      Node holding a word
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class wordNode
{
    public:
        std::string word;
        wordNode* next;

        /**
         * wordNode
         * 
         * Description:
         *      Constructor with word and next pointer
         * 
         * Params:
         *     - std::string w
         *     - wordNode*
         * 
         * Returns:
         *     - NULL
         */
        wordNode(std::string w, wordNode* n)
        {
            word = w;
            next = n;
        }
};

/**
 * linkedList
 * 
 * Description:
 *      Singly linked list that contains word nodes
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class linkedList
{
    public:
        // pointer to head
        wordNode* head;

        /**
        * linkedList
        * 
        * Description:
        *      Singly linked list that contains word nodes
        * 
        * Public Methods:
        *      - See class below
        * 
        * Returns: 
        *      NULL
        *      
        */
        linkedList()
        {
            // points head to nothing
            head = nullptr;
        }

        /** 
        * Public void : Push
        * 
        * Description:
        *      Adds an item to end of list
        * 
        * Params:
        *      std::string : item to be added
        * 
        * Returns:
        *      NULL
        */
        void push(std::string data)
        {
            // No Items
            if(head == nullptr)
            {
                head = new wordNode(data, nullptr);
            }

            // One item
            else if(head->next == nullptr)
            {
                head->next = new wordNode(data, nullptr);
            }

            // Many Items
            else
            {
                wordNode* temp = head;

                while(temp->next)
                {
                    temp = temp->next;
                }

                temp->next = new wordNode(data, nullptr);
            }
        }

};

/**
 * Description:
 *      Originally wrote this to count size of input file so
 *      I could allocate enough memory for an array of strings
 *      but I went with a vector below. But I'm keeping it and
 *      using it anyway!
 * Params:
 *      string file_name - file to get the line count
 * 
 * Returns:
 *      int - line count
 */
int CountLines(string file_name) 
{
    ifstream inFile(file_name);
    return (std::count(istreambuf_iterator<char>(inFile), istreambuf_iterator<char>(), '\n'));
}

/**
 * Description:
 *      Loads a file of strings (words, names, whatever) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 * 
 * Returns:
 *      int - line count
 */
linkedList LoadDict(std::string file_name) 
{
    ifstream fin;                            // file to get animal names
    int count = (CountLines(file_name) + 1); // get size of input file

    linkedList dictList;                     // create linkedList object

    fin.open(file_name);                    // open file for reading

    std::string readIn;
    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    for (int i = 0; i < count; i++) 
    {
        fin >> readIn;
        dictList.push(readIn);         // read in words
    }

    return dictList;
}

/**
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 * 
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> FindMatches(linkedList dictList, std::string substring) 
{
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.

    wordNode* temp = dictList.head; //points to head

    while(temp->next)       // loop through list
    {   
        found = temp->word.find(substring);    // check for substr match

        if(found == 0)           // if found >= 0 (its found then)
        {  
            matches.push_back(temp->word);     // add to matches
        }

        temp = temp->next; // traverseres list
    }

    return matches;
}

int main() 
{
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    linkedList words;       // list of all words
    vector<string> matches; // any matches found in linkedList of words

    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it

    words = LoadDict("dictionary.txt");

    T.End(); // end the current timer

    // print out how long it took to load the animals file
    // cout << T.Seconds() << " seconds to read in and print json" << endl;
    // cout << T.MilliSeconds() << " milli to read in and print json" << endl;

    // Instructions
    cout << "Type capital Z to quit.\n\n" ;
    
    // Starts new timer
    Timer matchTimer;
    matchTimer.Start();

    // While capital Z is not typed keep looping
    while((k = getch()) != 'Z') 
    {
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) 
        {
            if (word.size() > 0) 
            {
                word = word.substr(0, word.size() - 1);
            }
        } 
        else 
        {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) 
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) 
            {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word
        matches = FindMatches(words, word);
    }

    // Ends Timer
    matchTimer.End();

    // Outputs cute
    std::cout << "String submitted: " << termcolor::red << word << termcolor::reset << "\n\n";
    std::cout << termcolor::blue << matches.size() << " words found in " << std::setprecision(2) << matchTimer.Seconds() << " seconds.\n";

    std::cout << termcolor::bright_magenta;
    std::cout << "Matches Found: ";

    int loopSize;
    matches.size() < 10 ? loopSize = matches.size() : loopSize = 10;

    // This prints out all found matches
    for (int i = 0; i < loopSize; i++) 
    {
        std::cout << matches[i] << " ";
    }
    std::cout << termcolor::reset << endl << endl;    
            
    return 0;
}
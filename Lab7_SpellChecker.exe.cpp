/////////////////////////////////////////////////////////////////////
// Your name:Kimberly Harlow
// Date:11/11/2026
// Class: CSCI 1470
// Semester: Fall 2026
// CSCI 1470 Instructor: Dr. Jonatan Reyes
// Program Description:This program is a spell checker that allows users to enter English words and checks if they are spelled correctly using a dictionary file. 
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>   // sort
#include <chrono>      // timing
using namespace std;

// ---------- GLOBAL CONSTANTS ----------
const int MAX_WORDS = 466551;
const string LINEAR_SEARCH_UNSORTED = "LINEAR_UNSORTED";
const string LINEAR_SEARCH_SORTED = "LINEAR_SORTED";
const string BINARY_SEARCH = "BINARY";
const bool DEBUG = true;

// ---------- FUNCTION PROTOTYPES ----------
void initializeArray(string* words);
void loadDictionary(string* words, bool& fileError);
bool searchWord(const string* words, string target, string searchType);
bool linearSearchUnsorted(const string* words, string target);
bool linearSearchSorted(const string* words, string target);
bool binarySearch(const string* words, string target);

int main()
{
    int maxMistakes;
    string searchType;
    int mistakes = 0;
    bool fileError = false;
    string word;


    ifstream settings("settings.txt");
    if (!settings.is_open())
    {
        cerr << "Error: Could not open settings.txt" << endl;
        return 1;
    }

    settings >> maxMistakes;
    settings >> searchType;
    settings.close();
    string* words = new string[MAX_WORDS];
    initializeArray(words);
    loadDictionary(words, fileError);
   
    
    
    if (fileError)
    {
        cerr << "Error: could not open dictionary.txt" << endl;
        delete[] words;    
        return 1;
    }
    if (searchType == LINEAR_SEARCH_SORTED || searchType == BINARY_SEARCH)
    {
        sort(words, words + MAX_WORDS);
    }

    cout << "**********************************************************" << endl;
    cout << "WEEEELLLLLCOMMMMEEEEEE to the spelling checker!!!!!!!!" << endl;
    cout << "**********************************************************" << endl;
   
   
    char choice = 'Y';
    while (mistakes < maxMistakes && choice != 'N' && choice != 'n')
    {
        cout << "Please enter a word: ";
        cin >> word;

        auto begin = chrono::high_resolution_clock::now();
        bool found = searchWord(words, word, searchType);
        auto finish = chrono::high_resolution_clock::now();
        auto micro = chrono::duration_cast<chrono::microseconds>(finish - begin).count();

        if (found)
        {
            cout << "The word " << word << " is spelled correctly!" << endl;

            if (DEBUG)
            {
                if (searchType == BINARY_SEARCH)
                {
                    cout << "Binary search took " << micro << " microseconds." << endl;
                }
                else
                {
                    cout << "Linear search took " << micro << " microseconds." << endl;
                }
            }

            mistakes = 0;

            cout << "Do you want to continue (Y/N): ";   // moved here
            cin >> choice;                                // moved here
        }
        else
        {
            mistakes++;
            cout << "Oops! It looks like '" << word
                << "' isn't quite right. No worries, you're "
                << "doing great - let's try spelling it again." << endl;
        }
    }

    
        
    if (mistakes == maxMistakes)
    {
        cout << "\nYou have reached the maximum number ("
            << maxMistakes << ") of misspelled words allowed." << endl;
    }

    cout << "Thank you for playing!" << endl;

    delete[] words;
    return 0;
}

//FUNCTION DEFINITIONS 


//FUNCTION 1 
void initializeArray(string* words)
{
    for (int i = 0; i < MAX_WORDS; i++)
    {
        words[i] = "";
    }
}
//FUNCTION 2
void loadDictionary(string* words, bool& fileError)
{
    ifstream file("dictionary.txt");
    if (!file.is_open())
    {
        fileError = true;
        return;
    }

    int i = 0;
    while (i < MAX_WORDS && file >> words[i])
    {
        i++;
    }
    file.close();
}
//FUNCTION 3
bool linearSearchUnsorted(const string* words, string target)
{
    for (int i = 0; i < MAX_WORDS; i++)
    {
        if (words[i] == target)
        {
            return true;     // found it, stop right away
        }
    }
    return false;            // checked every slot, never found it
}
//FUNCTION 4
bool searchWord(const string* words, string target, string searchType)
{
    if (searchType == LINEAR_SEARCH_UNSORTED)
    {
        return linearSearchUnsorted(words , target);
    }
    else if (searchType == LINEAR_SEARCH_SORTED)
    {
        return linearSearchSorted(words , target);
    }
    else
    {
        return binarySearch(words, target);
    }
}

//FUNCTION 5
bool linearSearchSorted(const string* words, string target)
{
    for (int i = 0; i < MAX_WORDS; i++)
    {
        if (words[i] == target)
        {
            return true;
        }
        if (words[i] > target)    // already past where it would be
        {
            return false;
        }
    }
    return false;
}

//FUNCTION 6 
bool binarySearch(const string* words, string target)

{
    int low = 0;
    int high = MAX_WORDS - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (words[mid] == target)
        {
            return true;
        }
        else if (words[mid] < target)
        {
            low = mid + 1;     
        }
        else
        {
            high = mid - 1;     // wanted is in the lower half
        }
    }
    return false;
}



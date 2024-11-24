#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

int main () {
//get each token and store them in the unordered_map (or map) increment
//its frequencies. You MAY be able to do myTokens[aToken]++. Work on this.
    unordered_map<string, int> allWords; // the map where the word and its frequency will be stored
    string line; // variable receives the entire text file
    getline(cin, line); // assigns the text into this variable
    string token; // holds each individual tokens
    int start = 0; //first letter of the word
    int end = line.find(' ', 0); // index of where the next space is
    
    while (end <= line.length()) { // while loops ends when the token variable is empty
        token = line.substr(start, end - start);

        if ((allWords).find(token) != (allWords).end()) { // Map does have the key
            allWords.at(token) = allWords.at(token) + 1; // increases its frequency by one
        }
        else { // Map does not have key
            allWords.insert(make_pair(token , 1)); // adds the new token into the map
        }

        start = end + 1; // sets new start of word
        end = line.find(' ', start); // finds index of the next space
    }

    allWords.insert(make_pair(line.substr(start, line.length() - start), 1)); // gets the last word, which will be missed in loop

//sort the myTokens in the decreasing order of VALUE which is frequencies
    // My strategy for sorting is to first create an array of strings, then iterate through the entire unordered_map
    // Inserting each element at the end of the array then moving it to its correct spot
    string sortedWords[allWords.size()];
    int currentSize = 0; // amount of elements currently in the array
    string temp; // used for swapping

    for (unordered_map<string, int>::iterator it = allWords.begin(); it != allWords.end(); it++) {
            sortedWords[currentSize] = it -> first; // inserts the key into the end of array

            if (currentSize > 0) { // only needs to change position if theres more than 1 element
                for (int a = currentSize; a > 0; --a) {
                    if (allWords.at(sortedWords[a]) > allWords.at(sortedWords[a-1])) { // if value is greater, it moves it over
                        temp = sortedWords[a];
                        sortedWords[a] = sortedWords[a-1];
                        sortedWords[a-1] = temp;
                    }
                    if ((allWords.at(sortedWords[a]) == allWords.at(sortedWords[a-1])) && (sortedWords[a] < sortedWords[a-1])) { // if the values are equal, then sort it alphabetically
                        temp = sortedWords[a];
                        sortedWords[a] = sortedWords[a-1];
                        sortedWords[a-1] = temp;
                    }
                }
            }

            currentSize++; // increments currentSize to update size and so the next key will continue to be inserted to the end rather then replacing
    }

//print the KEYS in myTokens (which has been sorted)separated by a space.
    for (int i = 0; i < allWords.size(); ++i) {
        cout << sortedWords[i] << " ";
    }

//after you printed the KEYS Do this
        cout << endl;
        cout << "**********" << endl;

//Now open the filename.text file again for reading
//Read token by token as you have done this before
//each time you get a token, find its position in the myTokens (sorted
//data structure and print the position followed by space
        start = 0; // resets start
        end = line.find(' ', 0); // resets end

        while (end <= line.length()) { // while loops ends when the token variable is empty
            token = line.substr(start, end - start); // gets each word using substr method
            for (int b = 0; b < currentSize; ++b) {
                if (sortedWords[b] == token) {
                    int position = b;
                    cout << position + 1 << " ";
                    break;
                }
            }
            start = end + 1;
            end = line.find(' ', start);
        }

        token = line.substr(start, line.length() - start); // finds index position of last word, which will be missed in for loop
        for (int b = 0; b < currentSize; ++b) {
                if (sortedWords[b] == token) {
                    int position = b;
                    cout << position + 1 << " ";
                    break;
                }
        }

    return 0;
}

/***** Debugging plan and LLM Usage ******/
/*

Approach:
    
    I will be working on the main function from top to bottom, meaning I will work on each part in sequential order. I will also be using
the "input1.txt" file as a guide to debug.
-----------------------------------------------------------------------------------------------------------------------------------------
Getting each token and putting it in the map

LLM Usage:
    I asked ChatGPT for all of the methods that are included in unordered_map. Specifically, "What are all of the fucntion in unordered map 
in C++?" It gave me the methods of at(const Key& key), find(const Key& key), and insert(const value_type& value), which are the methods I 
believe will be used to implement this portion of the code. To know more about the find function, I asked "What does the find function in
unordered map return and how can I indicate that a key is not found?" I also used GeekForGeeks.com to get a better understanding of the
structures functions. I also asked "How to put a text file content into a variable." I also asked "How to split a string based off a character?"
and "How to get the index of a specific character?" and "How to get a specific index if there are multiple of the same characters?"

Debugging:
    To check whether or not it worked, I created a for loop that goes through all of the elements in the map. I made...

    for (unordered_map<string, int>::iterator it = allWords.begin(); it != allWords.end(); it++) {
            cout << it -> first << " " << it -> second << " " << endl;
    }

I created this by using a LLM model, asking "How can I iterate through the elements of the hashmap?" However, nothing would be printed out even
when the code was continuing to run, so I checked if anything was even being put into the map. I placed...

    cout << token << endl

in the while loop to ensure that there is a token actually being read. After adding this, it would cause an infinite loop. Thus, I went to
ChatGPT and asked "What does cin read after the last word of text file?" and it give me the idea to change the while condition into cin << token,
which fixed the infinite loop issue, and it printed out all of the words in the text file. When checking if the correct value for each key is correct,
I used the search function that all applications have to find the key with the biggest value which is the with 9. This matches with the output file, so
I feel like I am on the right track.
-----------------------------------------------------------------------------------------------------------------------------------------
Sorting the keys by its value

LLM Usage:
    I did not use any LLM Tools. If I did, I would have asked "How can I sort the elements in an unordered_map based off its value?"
    

Debugging:
    Because I will be eventually printing out the sorted keys, I can tell that sorting went right if its printed outputs matches with the
output file. After implementing sorting, I noticed that some of it was off. This was due to me not noticing that whenever the values match, it 
then goes to alphabetical order. I added a conditional to consider this and now it is correct.
-----------------------------------------------------------------------------------------------------------------------------------------
Printing the position of each word in the text

LLM Usage:
    I asked ChatGPT "How can I get the index position of a key in an unordered map?" There was not a way too do it.

Debugging:
    I can tell if this section of code was working if its printed statements match the output file. It does, so I implemented it correctly.
-----------------------------------------------------------------------------------------------------------------------------------------
Final:
    When I was turning the code into GradeScope, I was unable to pass test. I noticed the reason this was happening was because the loop would
neglect the last word, so the index positions of the words that are after it would be one less and I also missed the last index position on the last section.
To fix this, I created another section of code made just for the last value.
*/
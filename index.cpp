/*
 *
 * COMP15
 * Spring 2018
 * Helper code for Gerp project
 *
 */

#include <string>
#include <functional>
#include <iostream>
#include "Index.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "FSTree.h"
using namespace std;

// default constructor
Index::Index()
{
}

//constructor with parameters
Index::Index(string directory, DirNode *root)
{
    make_index(directory, root);
}

// Function make_index
// Input: string, DirNode pointer
// Returns: None
// Does: populate index
void Index::make_index(string directory, DirNode *root)
{
    traversal(root, directory);
}

// Function process_query
// Input: string, bool ref, bool
// Returns: None
// Does: find the query word
void Index::find_query(string query, bool &word_in_file, 
                       bool case_sensitive) const
{
    string word = query;
    // for indexing same words at same index
    transform(word.begin(), word.end(), word.begin(), ::tolower);
    size_t index = hash(word);

    // reverse the order
    hashtable[index].print_reverse(query, 
                                   word_in_file, case_sensitive);
}

// Function traversal
// Input: DirNode pointer, string
// Returns: none
// Does: loop through the directories
void Index::traversal(DirNode *root, string dir)
{
    string directory = dir;
    if(root->has_subdir())
    {
        for (int i = 0; i < root->num_subdirs(); i++)
        {
            string sub_dir = directory + "/" 
                           + root->get_subdir(i)->get_name();
            traversal(root->get_subdir(i), sub_dir);
        }
    } 
            
    if (root->has_files())
    {
        for (int i = 0; i < root->num_files(); i++)
        {
            string file_name = directory + "/" + root->get_file(i);
            open_file(file_name);
        }
    }
}

// Function open file
// Input: string
// Returns: none
// Does: open a file
void Index::open_file(string file_name)
{
    ifstream infile;
    infile.open(file_name.c_str());
    if (!infile.is_open()) 
    { 
        cerr << "Error opening " << file_name << endl;
        exit(1);
    }
    // go thorugh word
    iterate_word(infile, file_name);
    infile.close();
}

// Function iterate_word
// Input: ifstream ref, string
// Returns: none
// Does: go through every word
void Index::iterate_word(ifstream &infile, string file_name)
{
    string line;
    int line_number = 1;
    while (getline(infile, line))
    {
        string intake; 
        stringstream ss(line); 
        while (ss >> intake)
        {
            // insert into hashtable
            string word = process_query(intake);
            // put uppercase with lower case
            transform(word.begin(), word.end(), 
                      word.begin(), ::tolower);
            string info = file_name + string(":") 
                        + to_string(line_number) + string(": ") + line;

            if (info != hashtable[hash(word)].get_first_line())
               insert_word(hash(word), info);
        }
        
        line_number++;
    } 
}

// Function insert_word
// Input: size_t, string
// Returns: none
// Does: insert word into hashtable
void Index::insert_word(size_t index, string info)
{
    hashtable[index].insert_string(info);
}

// Function process_query
// Input: string
// Returns: string
// Does: process the query word
string Index::process_query(string intake)
{
    unsigned int start = intake.length();
    unsigned int end = 0;
  
    for (unsigned int i = 0; i < intake.length(); i++)
    {
        char c = intake[i];
        // check is valid letter or number
        if (isalnum(c))
        {
            if (i < start)
                start = i;

            if (i > end)
                end = i;
        }
    }
    
    int word_length = end - start + 1;
    // get the right query word
    string query = intake.substr(start, word_length);
    return query;
}

// Function hash
// Input: string
// Returns: size_t
// Does: hash strings
size_t Index::Index::hash(string word) const
{
    std::hash<std::string> hash_str;
    return hash_str(word) % length;
}

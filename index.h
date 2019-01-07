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
#include "LinkedList.h"
#include "FSTree.h"
using namespace std;

#ifndef INDEX_H
#define INDEX_H

const int length = 50000;
class Index
{

public:
    // constructor
    Index();

    // constructor with parameters
    Index(string directory, DirNode *root);
    
    // populate index
    void make_index(string directory, DirNode *root);

    // find a query
    void find_query(string, bool &, bool) const;

    // loops through directories
    void traversal(DirNode *root, string dir);

    // open a file
    void open_file(string file_name);

    // go through every word
    void iterate_word(ifstream &infile, string file_name);

    // insert word into hashtable
    void insert_word(size_t index, string info);

    // standard hash function
    size_t hash(string word) const;

    string process_query(string);

private:
    //array for hashtable of linkedlist
    LinkedList hashtable[length];

};

#endif

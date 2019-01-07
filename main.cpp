/* 
 * FSTreeTraversal.cpp
 * COMP15
 * Spring 2018
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include "FSTree.h"
#include "Index.h"

using namespace std;

int main(int argc, char *argv[]) 
{
    // avoid warning
    (void) argc;
    string directory = argv[1];
    FSTree tree(directory);
    DirNode *root = tree.get_root();
    // makes the index
    Index index(directory, root);
    while (true)
    {
        cout << "Query? ";
        string intake;
        cin >> intake; 
        bool case_sensitive = true;
        bool word_in_file = false;
        if (intake == "@q"|| intake == "@quit" || cin.eof())
        {
            cout << "\nGoodbye! Thank you and have a nice day." << endl;
            break;
        } else if (intake == "@insensitive")
        {
            cin >> intake;
            case_sensitive = false;
        } else if (intake == "@i")
        {
            cin >> intake;
            case_sensitive = false;
        } 
        string query = index.process_query(intake);
        // search for query
        index.find_query(query, word_in_file, case_sensitive);

        if (!word_in_file && case_sensitive)
             cout << query << " Not Found. Try with @insensitive or @i." 
                           << endl;
        else if (!word_in_file)
             cout << query << " Not Found." << endl;
    } 
    // destroy the tree to free memory
    tree.burn_tree();
    return 0;
}
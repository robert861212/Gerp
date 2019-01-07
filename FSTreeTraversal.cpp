/* 
 * FSTreeTraversal.cpp
 * COMP15
 * Spring 2018
 *
 */

#include <iostream>
#include <string>
#include "FSTree.h"

using namespace std;

void print(DirNode *, string);
int main(int argc, char *argv[]) 
{
    string directory = argv[1];
    FSTree tree(directory);
    DirNode *root = tree.get_root();
    
    print(root, directory);
    
    return 0;
}

void print(DirNode *root, string dir)
{
    string directory = dir;
    if(root->has_subdir())
    {
        for (int i = 0; i < root->num_subdirs(); i++)
        {
            print(root->get_subdir(i), directory + "/" + root->get_subdir(i)->get_name());
        }

    } 
            
    if (root->has_files())
    {
        for (int i = 0; i < root->num_files(); i++)
        {
            cout << directory << "/" << root->get_file(i) << endl;
        }
    }

    cout << directory << endl;
    
}
/*
 * FSTree.h
 *
 * n-ary tree of DirNodes
 *
 * COMP15
 * Spring 2018
 * Helper code for Gerp project
 *
 */

#include <string>
#include "DirNode.h"
using namespace std;

// Non-memeber helper functions
void burner(DirNode *);
DirNode *build_tree(string);
DirNode *pre_order_copy(DirNode *, DirNode *);
string base_name(string const &);
bool is_file(const char *);
bool is_dir(const char *);

#ifndef FSTREE_H
#define FSTREE_H

class FSTree {

public:
    FSTree();
    FSTree(string);

    // Rule of Three
    FSTree(const FSTree &);
    FSTree& operator = (const FSTree &);
    ~FSTree();

    DirNode *get_root() const;

    bool is_empty() const;
    void burn_tree();

private:

    DirNode *root;

};

#endif

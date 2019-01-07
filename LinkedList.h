
#include <fstream>
#include <string>
using namespace std;


#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

struct NodeType
{
    string info;
    NodeType *next;
};

class LinkedList
{
public:
    // Default constructor
    LinkedList();

    // Copy constructor
    LinkedList(const LinkedList &);

    // Destructor
    ~LinkedList();

    // Assignment Operator
    LinkedList & operator = (const LinkedList &);

    // Insert a planet
    void insert_string(string);

    // Return next planet
    string get_next_string();

    // Look for and return the input planet
    // Modify the input bool
    string find_string(string p, bool &found);

    // Delete the input planet
    void delete_string(string p);

    // Make the LinkedList empty
    void make_empty();

    // Make current position pointer to null
    void reset_list();

    // Check if memory heap is full
    bool is_full();

    // Return the length of LinkedList
    int get_length() const;

    string process_query(string) const;

    // Print the list
    void print(string query, bool &, bool) const;

    // Print the reversed list
    void print_reverse(string query, bool &, bool) const;

    // Get the first line
    string get_first_line();


private:
    // Attributes
    int length;
    NodeType *head;
    NodeType *curr_pos;
};

#endif

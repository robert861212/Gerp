/*
 * LinkedList.cpp
 * COMP15
 * Spring 2018
 * Homework 2
 * Robert(Jhih-Yong Yang)
 * Implementation for Linked List of Planets
 */

#include "LinkedList.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
    length = 0;
    head = NULL;
    curr_pos = NULL;
}
// Copy constructor
LinkedList::LinkedList(const LinkedList &linkedlist)
{
    NodeType *original = linkedlist.head;
    length = linkedlist.length;
    curr_pos = NULL;
    // If the LinkedList to copy is empty,
    // point head to null and end the function.
    if (original == NULL)
    {
        head = NULL;
        // End the function
        return;
    } 
    // Allocate a curr pointer, so that
    // head can point to something
    NodeType *curr = new NodeType;
    head = curr;
    // If the function does not end in the conditional statement 
    // above, the LinkedList is not empty.
    // Copy first info
    curr->info = original->info;
    // In while loop, nodetypes between second nodetype and
    // last notype are copied if they exist.
    while (original->next != NULL)
    {
        curr->next = new NodeType;
        curr->next->info = original->next->info;
        curr = curr->next;
        original = original->next;
    }
    // Make last NodeType point to null
    curr->next = NULL;
}

// Destructor
LinkedList::~LinkedList()
{
    NodeType *curr = head;
    // Go thorugh every NodeType
    while (curr != NULL)
    {
        NodeType *temp = curr->next;
        delete curr;
        // Go on to next NodeType
        curr = temp;
    }
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l)
{
    NodeType *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    length = l.length;
    curr_pos = NULL;
    if (l.head == NULL)
        head = NULL;
    else
    {
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL)
        {
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Function make_empty
// Input: None
// Returns: None
// Does: Make the LinkedList empty
void LinkedList::make_empty()
{
    NodeType *curr = head;
    // Everything is deleted, but head needs to points 
    // to null to keep the LinkedList
    head = NULL;
    while (curr != NULL)
    {
        NodeType *temp = curr->next;
        delete curr;
        // Go on to next NodeType
        curr = temp;
    }
}

// Function insert_planet
// Input: Planet object
// Returns: None
// Does: Adds Planet to beginning of array, increases length
void LinkedList::insert_string(string p)
{
    NodeType *location = new NodeType;
    location->info = p;
    location->next = head;

    head = location;
    length++;
}

string LinkedList::get_first_line()
{
    
    if (length == 0 || head == NULL)
    {    
        return "";
    }
        NodeType *first = head;
        return first->info;
}

// Function get_next_planet
// Inputs: none
// Returns: none
// Does: Returns the Planet object at the current pos
//       Wraps around to beginning if we're at the end
//       Returns a default planet if empty
string LinkedList::get_next_string()
{
    if (length == 0)
    {
         
        return "";
    }
    if (curr_pos == NULL)
        curr_pos = head;
    else
        curr_pos = curr_pos->next;
    return curr_pos->info;
}

// Function find_planet
// Inputs: Planet object and bool
// Returns: Planet object
// Does: Return the first instance of Planet 
//       found in the LinkedList if there is 
//       any and reset the bool value accordingly 
string LinkedList::find_string(string p, bool &found)
{
    NodeType *curr = head;
    while (curr != NULL)
    {
        if (curr->info == p)
        {
            // Make value of bool true and return found object
            found = true;
            return curr->info;
        }
        curr = curr->next;
    }
    return p;
}

// Function delete_planet
// Inputs: Planet object
// Returns: none
// Does: Delete the first instance of Planet 
//       found in the LinkedList if there is any
void LinkedList::delete_string(string p)
{
    NodeType *curr = head;
    NodeType *temp;
    // The info of the curr NodeType can only be reached when
    // the NodeType is not null (Special case of empty LinkedList)
    if (curr != NULL && curr->info == p)
    {
        // Head points to the NodeType after the NodeType
        // to be deleted
        head = curr->next;
        delete curr;
        length --;
    }

    while (curr != NULL)
    {
        temp = curr->next;
        // Check the NodeType is not last one
        // that points to null
        if (temp != NULL)
        {
            if (temp->info == p)
            {
                // Curr points to the NodeType after the 
                // NodeType to be deleted
                curr->next = temp->next;
                delete temp;
                length --;
            }
        }
        // Go on to next one
        curr = curr->next;
    }
}

// Function reset_list
// Inputs: none
// Returns: none
// Does: Set the current position pointer to null
void LinkedList::reset_list()
{
    curr_pos = NULL;
}

bool LinkedList::is_full()
{
    // Try to allocate a new NodeType to see
    // if memory heap is full
    try
    {
        NodeType *attempt = new NodeType;
        delete attempt;
        // Heap memory is not full
        return false;
    }
    // When bad allocation occurs, heap memory is full
    catch(bad_alloc exception)
    {
        return true;
    }
}

// Function get_length, const
// Inputs: none
// Returns: int, length of list
int LinkedList::get_length() const
{
    return length;
}

// Function process_query
// Input: string
// Returns: string
// Does: process the query word
string LinkedList::process_query(string intake) const
{
    unsigned int start = intake.length();
    unsigned int end = 0;
  
    for (unsigned int i = 0; i < intake.length(); i++)
    {
        char c = intake[i];
        // makes sure it's letter or number
        if (isalnum(c))
        {
            if (i < start)
                start = i;

            if (i > end)
                end = i;
        }
    }
    
    int word_length = end - start + 1;
    string query = intake.substr(start, word_length);
    return query;
}

// Function print, const
// Inputs: ostream object, bool ref, bool
// Returns: none
// Does: prints every element in the list
void LinkedList::print(string query, bool &word_in_file, 
                       bool case_sensitive) const
{
    NodeType *location = head;
    if (!case_sensitive)
    {
        transform(query.begin(), query.end(), query.begin(), ::tolower);
    }
    while (location != NULL)
    {
        bool to_print = false;
        string intake;
        string line = location->info;

        if (!case_sensitive)
        {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
        }

        stringstream ss(line);
        // makes sure the line contains the word
        while (ss >> intake)
        {
            string word = process_query(intake);
            if (word == query)
                to_print = true;
        }

        if (to_print)
        {
            word_in_file = true;
            cout << location->info << endl;
        }

        location = location->next;
    }
}

// Function print_reverse
// Input: string, bool ref, bool
// Returns: None
// Does: print linkedlist reversedly
void LinkedList::print_reverse(string query, 
                               bool &word_in_file, bool case_sensitive) const
{
    LinkedList right_order;
    NodeType *location = head;
    while (location != NULL)
    {
        string s = location->info;
        right_order.insert_string(s);
        location = location->next;
    }
    right_order.print(query, word_in_file, case_sensitive);
}




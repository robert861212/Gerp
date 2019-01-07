/* 
 * StringProcessing.cpp
 * COMP15
 * Spring 2018
 *
 */

#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>

using namespace std;

int main()
{
    string intake;
    string output;
    cin >> intake;
    int start = intake.length();
    int end = 0;
    for (int i = 0; i < intake.length(); i++)
    {
        char c = intake[i];
        if (isalnum(c))
        {
            if (i < start)
                start = i;

            if (i > end)
                end = i;
        }
    }
    
    int word_length = end - start + 1;
    output = intake.substr(start, word_length);
    cout << output << endl;

    return 0;
}
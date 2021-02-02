#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <set>

using namespace std;


int main() 
{
    set<char> currentGroup;
    int count = 0;
    string line;
    ifstream myfile( "6input.txt");
    if (myfile) 
    {

        while (getline( myfile, line)) 
        {
                if(line == "") 
                {
                    //next group
                    count += currentGroup.size();
                    currentGroup.clear();
                }
                else
                {
                    for (char const &c: line) {
                        currentGroup.insert(c);
                    }
                }
            }
        count += currentGroup.size();
        cout << count;
    }
    else cout << "fooey\n";

    return 0; 

}

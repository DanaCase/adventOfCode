#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <map>

using namespace std;

int getCount(map<char, int> & currentGroup, int & currentGroupSize)
{
    map<char, int>::iterator i;
    int count = 0;
    for (i = currentGroup.begin(); i != currentGroup.end(); i++)
    {
        if(i->second == currentGroupSize) {
            cout <<  i->first << " " << i->second << "\n";
            cout << "current group size " << currentGroupSize << "\n"; 
            count++;
        }
    }
    return count;
}

int main() 
{
    map<char, int> currentGroup;
    int currentGroupSize = 0;
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
                    count += getCount(currentGroup, currentGroupSize);
                    cout << "current group size " << currentGroupSize << "\n";
                    cout << "current count is " << count << "\n";
                    currentGroup.clear();
                    currentGroupSize = 0;
                }
                else
                {
                    currentGroupSize++;
                    for (char const &c: line) {
                        if (currentGroup.find(c) != currentGroup.end()) {
                            currentGroup[c]++;
                            cout << "current group at is " << currentGroup[c] << "\n";
                        }
                        else
                        {
                            currentGroup[c] = 1;
                        }
                    }
                }
            }
        count += getCount(currentGroup, currentGroupSize);
        cout << count;
    }
    else cout << "fooey\n";

    return 0; 

}

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
//#include "utils.h"

using namespace std;

bool hasbeenvisited(int i, vector<bool> arr)
{
    cout << "the index is " << i << "\n";
    cout << "the value is " << arr[i] << "\n";
    return arr[i];
}


int main() 
{
    vector<pair<string, int> > v;
    int acc;
    int index = 0;
    string line;
    ifstream myfile( "8input.txt");
    if (myfile) 
    {

        while (getline( myfile, line)) 
        {
            cout << line << "\n";
            size_t spliti = line.find(' '); 
            string inst = line.substr(0, spliti);
            int a = stoi(line.substr(spliti));
            pair<string, int> p(inst, a);
            v.push_back(p);
        }

        vector<bool> indexes(v.size(), false);
        for(int i=0; i < v.size(); i++)
        {
            cout << indexes[i] << "\n";
        }
        cout << "size is " << v.size() << "\n";

        while(!hasbeenvisited(index, indexes)) 
        {
            cout << "index is " << index << " \n";
            cout << "command " << v[index].first << "  number " << v[index].second << "\n";
            indexes[index] = true;
            if(v[index].first == "acc")
            {
                acc += v[index].second;
                index += 1;
                continue;
            }
            else if(v[index].first == "nop")
            {
                index += 1;
                continue;
            }
            else if(v[index].first == "jmp")
            {
                index += v[index].second;
                continue;
            }
            else
            {
                cout << "ERROR";
            }


        }
        cout << "accumulator is " << acc << "\n";
    }
    else cout << "fooey\n";

    return 0; 

}

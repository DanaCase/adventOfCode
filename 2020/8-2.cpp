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
    //cout << "the index is " << i << "\n";
    //cout << "the value is " << arr[i] << "\n";
    return arr[i];
}

string changeIt(string command)
{
    if(command == "nop")
    {
        return "jmp";
    }
    else if(command == "jmp")
    {
        return "nop";
    }
    else
    {
        return command;
    }
}

bool doIt(vector<pair<string, int> > v, int toChange)
{
    v[toChange].first = changeIt(v[toChange].first);

    cout << "I ran " << toChange << "\n";
    int index = 0;
    int acc = 0;
    vector<bool> indexes(v.size(), false);
    while(!hasbeenvisited(index, indexes)) 
    {
        //cout << "index is " << index << " \n";
        //cout << "command " << v[index].first << "  number " << v[index].second << "\n";
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
            cout << "ERROR " << v[index].first << "\n";
        }


        if(index == v.size())
        {
            cout << "I've got it";
            cout << "last index is " << index << "\n";
            cout << "accumulator is " << acc << "\n";
            return true;
        }
    }
        cout << "last index is " << index << "\n";
        cout << "accumulator is " << acc << "\n";
    return false;
}


int main() 
{
    vector<pair<string, int> > v;
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

        cout << "size is " << v.size() << "\n";

        for (int i; i < v.size(); i++)
        {
            bool shouldExit = false;
            shouldExit = doIt(v, i);
            if (shouldExit)
            {
            break;
            }
        }

    }
    else cout << "fooey\n";

    return 0; 

}

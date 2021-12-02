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

bool isEnd(string& s)
{
    size_t i = s.find("bag");
    if(i == string::npos)
    {
        return 1;
    }
    if(s[i + 3] ==  '.' || (s[i + 3] == 's' && s[i + 4] == '.' ))
    {
        return 1;
    }
    return 0;
}




void parseLine(string line, map<string, map<string, int> >& m, bool reverse) 
{
    size_t bag1i = line.find("bag");
    string bagcontains = line.substr(0, bag1i - 1);

    //cout << bagcontains << "\n";

    size_t bag2i = bag1i + 5 + 8;
    string count1 = line.substr(bag2i, 2);
    //cout << count1 << "\n";

    if(count1[0] == 'n')
    {
        //its a leaf
        if(reverse)
        {
            //we need them for the second map
            m[bagcontains]["none"] = 0;
        }

    }
    else
    {
        string workingSubstring = line.substr(bag2i); 
        do {
            int offset;
            string count = workingSubstring.substr(0, 2);
            //cout << "count " << count << '\n';
            //bags vs bag
            if(workingSubstring.find("bag") == workingSubstring.find("bags"))
            {
                offset = 2;
            }
            else
            {
                offset = 1;
            }
            int bagiii = workingSubstring.find("bag");
            string colorSubstring = workingSubstring.substr(2, bagiii - 3);
            //cout << "color substr " << colorSubstring << "\n";

            if (bagcontains == "shiny violet") {
                cout << "bag contains is shiny black and color is " << colorSubstring << "and count is " << count <<  "\n";
            }
            
        
            if(reverse)
            {
                m[bagcontains][colorSubstring] = stoi(count);
            }
            else
            {
                m[colorSubstring][bagcontains] = stoi(count);
            }

            int cutoff = bagiii + 4 + offset;
            if(workingSubstring.size() > cutoff) {
                workingSubstring = workingSubstring.substr(bagiii + 4 + offset);
                //cout << "working substring " << workingSubstring << "\n";
            } else {
                break;
            }
        }
        while(workingSubstring.size() > 0);
    }
}

//would be more efficent if I also kept a map of where I have already traversed?
void getAll(set<string>& shinyGoldHolders,  map<string, map<string, int> >& m, map<string, int>& workingMap) {
    map<string, int>::iterator i;
    for(i = workingMap.begin(); i != workingMap.end(); i++)
    {
        shinyGoldHolders.insert(i->first);
        //cout << "new working map size " << m[i->first].size() << "\n";
        getAll(shinyGoldHolders, m, m[i->first]);
    }
}

void doPart1(map<string, map<string, int> >& m) {
        map<string, int> shinyGoldMap = m["shiny gold"];
        //cout << "shiny gold size" << shinyGoldMap.size() << "\n";
        set<string> shinyGoldHolders;
        map<string, int>::iterator i;
        for(i = shinyGoldMap.begin(); i != shinyGoldMap.end(); i++)
        {
            shinyGoldHolders.insert(i->first);
            cout << i->first << "\n";
            getAll(shinyGoldHolders, m, m[i->first]);
        }
        cout << "final answer " << shinyGoldHolders.size() << "\n";
}

int getAllCount(int& count, map<string, map<string, int> >& m, map<string, int>& workingMap)
{
    map<string, int>::iterator i;
    for(i = workingMap.begin(); i != workingMap.end(); i++)
    {
        if(i->first != "none")
        {
            int memCount = 0;
            int subCount = getAllCount(memCount, m, m[i->first]);
            cout << i->first << " has " << subCount << " bags\n";
            count += i->second * subCount;
            count += i->second;
        }
        //its a leaf
        else
        {
            return 0;
        }
    }
    return count;
}

void doPart2(map<string, map<string, int> >& m)
{
    map<string, int> shinyGoldMap = m["shiny gold"];
    map<string, int>::iterator i;
    int count = 0;
    for(i = shinyGoldMap.begin(); i != shinyGoldMap.end(); i++)
    {
        //count += i->second * getAllCount(count, m, m[i->first]);
        int memCount = 0;
        int subCount = getAllCount(memCount, m, m[i->first]);
        cout << i->first << " has " << subCount << " bags\n";
        count += i->second * subCount;
        count += i->second;
    }
    cout << "Part 2 count is " << count << "\n";
}

int main() 
{
    map<string, map<string, int> > m;
    map<string, map<string, int> > m2;
    int count = 0;
    string line;
    ifstream myfile( "7input.txt");
    if (myfile) 
    {

        while (getline( myfile, line)) 
        {
            //cout << line << "\n";
            parseLine(line, m, false);
            parseLine(line, m2, true);
        }

        doPart1(m);
        doPart2(m2);
    }
    else cout << "fooey\n";

    return 0; 

}

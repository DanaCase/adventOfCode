#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <vector>
#include <deque> 


using namespace std;

bool checkElements(deque<long>& q, long test)
{
    for (int i = 0; i != q.size() - 1; i++)
    {
        for(int ii = 1; ii != q.size(); ii++)
        {
            cout << "testing: " << q[i] << " + " << q[ii] << " = " << q[i] + q[ii] << " aganist " << test << "\n";
            if(q[i] + q[ii] == test)
            {
                return true;
            }
        }
    }
    return false;
}

vector<long> getContinuousV(long goal, vector<long>&v)
{
    for(int i = 0; i != v.size(); i++)
    {
        long runningSum = v[i];    
        for(int ii = i + 1; runningSum < goal; ii++)
        {
            runningSum += v[ii];
            if(runningSum == goal)
            {
                vector<long> v2(v.begin() + i, v.begin() + ii + 1);
                return v2;
            }
        }
        
    }
    vector<long> v2;
    return v2;
}

void puz(vector<long> v)
{
    long largest = 0;
    long smallest = 0;
    for(int i = 0; i != v.size(); i++)
    {
        cout << v[i] << "\n";
        if (i == 0)
        {
            smallest = v[i];
        }
        if (v[i] > largest)
        {
            largest = v[i];
        }
        if (v[i] < smallest)
        {
            smallest = v[i];
        }
    }
    cout << "smallest " << smallest << ", largest " << largest << "\n";
    cout << "the answer: " << smallest + largest << "\n";
}

int main() 
{
    int index = 0;
    deque<long> q;
    vector<long> v;
    vector<long> slice;
    long magicNumber = 0;
    bool foundIt = false;
    string line;
    int preamble = 25;
    ifstream myfile( "9input.txt");
    if (myfile) 
    {

        while (getline( myfile, line)) 
        {
            cout << line << "\n";
            long test = stol(line);
            if(index > preamble)
            {
                q.pop_front();
                if (!foundIt && !checkElements(q, test))
                {
                    cout << test << " found it\n";
                    magicNumber = test;
                    foundIt = true;
                }
            }
            q.push_back(test);
            v.push_back(test);
            index++;
        }
        slice = getContinuousV(magicNumber, v);
        puz(slice);
    }
    else cout << "fooey\n";

    return 0; 

}

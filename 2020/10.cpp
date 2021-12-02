#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <vector>


using namespace std;


int main() 
{
    int index = 0;
    vector<int> v;
    vector<int> differences;
    string line;
    ifstream myfile( "10input.txt");
    if (myfile) 
    {
        while (getline( myfile, line)) 
        {
            cout << line << "\n";
            v.push_back(stoi(line));
        }
        sort(v.begin(), v.end());
        int last = 0;
        int oneCount = 0;
        int threeCount = 0;
        for(int i=0; i != v.size(); i++)
        {
            int count = v[i] - last;
            cout << "count " << count << "\n";
            if(count == 1)
            {
                oneCount++;
            }
            if(count == 3)
            {
                threeCount++;
            }
            last = v[i];
        }
        //last adapter is always 3
        threeCount++;
        cout << "one count = " << oneCount << " three count = " << threeCount << "\n";
        cout << oneCount * threeCount << "\n";
    }
    else cout << "fooey\n";

    return 0; 

}

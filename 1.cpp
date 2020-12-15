#include <string>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

int main() {
    string line;
    map<int, bool> mymap;
    ifstream myfile( "1input.txt");
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            mymap.insert(pair<int, bool> (stoi(line), true));

            if(mymap[2020 - stoi(line)]) {
                int one = stoi(line);
                cout << (2020 - one) * one;
            }

        }
        myfile.close();
    }
    else cout << "fooey\n";

    return 0; 

}

#include <string>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

int main() {
    string line;
    //map<int, bool> mymap;
    int count = 0;
    int previous;
    int i = 0;
    ifstream myfile( "data/1.txt");
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            int current = stoi(line);
            if(i == 0) {
                previous = current;
            } 
            else {
                if (current > previous) {
                    count++;
                }
                previous = current;
            }

            i++;
        }
        cout << count << "\n";
        myfile.close();
    }
    else cout << "fooey\n";

    return 0; 

}

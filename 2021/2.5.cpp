#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string line;
    //map<int, int> mymap;
    vector<int> xy = {0,0,0}; // horizontal, depth, aim
    int previous;
    ifstream myfile("data/2.txt");
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            int val;
            if(string::npos != line.find("forward") ) {
                val = line[8] - '0';
                xy[0] += (val);
                xy[1] += xy[2] * val;
            }
            else if(string::npos != line.find("down") ) {
                xy[2] += (line[5] - '0');
            }
            else if(string::npos != line.find("up") ) {
                xy[2] -= (line[3] - '0');
            }
            else {
                cout << "what the heck happened here? " << line << "\n";
            }

        }
        cout << xy[0] << "\n";
        cout << xy[1] << "\n";
        cout << xy[2] << "\n";
        cout << xy[0] * xy[1] << "\n";
        myfile.close();
    }
    else cout << "fooey\n";

    return 0; 

}

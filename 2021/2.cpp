#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string line;
    //map<int, int> mymap;
    vector<int> xy = {0,0};
    int previous;
    ifstream myfile("data/2.txt");
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            if(string::npos != line.find("forward") ) {
                xy[0] += (line[8] - '0');
            }
            else if(string::npos != line.find("down") ) {
                xy[1] += (line[5] - '0');
            }
            else if(string::npos != line.find("up") ) {
                xy[1] -= (line[3] - '0');
            }
            else {
                cout << "what the heck happened here? " << line << "\n";
            }

        }
        cout << xy[0] << "\n";
        cout << xy[1] << "\n";
        cout << xy[0] * xy[1] << "\n";
        myfile.close();
    }
    else cout << "fooey\n";

    return 0; 

}

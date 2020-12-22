#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;


//first attempt, not realizing it was just binary...
int convertToNum(string a, char high, char low, int first, int last, int top, int bottom) {
    vector<float> numRange{(float) top, (float) bottom};
    int final;
    for(int i = first; i != last + 1; i++) {
        char current = a.at(i);
        if (i == last) 
        {
            if (current == low) 
            {
                final = numRange[0];   
            } else 
            {
                final = numRange[1];
            }
        }
        if (current == low) {
            numRange[1] = floor(numRange[1] / 2);
        } else {
            numRange[0] = ceil(numRange[1] / 2);
        }
    }
    cout << "Num range " << numRange[0] << "," << numRange[1] << "\n";
    return final;
}

int convertStringToBinaryToDec(string& s) {
    replace(s.begin(), s.end(), 'F', '0');
    replace(s.begin(), s.end(), 'B', '1');
    replace(s.begin(), s.end(), 'L', '0');
    replace(s.begin(), s.end(), 'R', '1');

    return stoi(s, nullptr, 2);
}

int main() 
{
    string line;
    int largest;
    ifstream myfile( "5input.txt");
    bool first = true;
    if (myfile) 
    {

        while (getline( myfile, line)) 
        {
            if (line != "") 
            {
                int dec = convertStringToBinaryToDec(line);
                if (first == true) {
                    largest = dec;
                    first = false;
                }
                if (largest < dec) {
                    largest = dec;
                    cout << "new largest " << largest << "\n";
                }
            }
        }
        cout << "largest: " << largest << "\n";

    }
    else cout << "fooey\n";

    return 0; 

}

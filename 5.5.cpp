#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

struct seatId {
    int dec;
    string s;
};


int convertStringToBinaryToDec(string& s) {
    replace(s.begin(), s.end(), 'F', '0');
    replace(s.begin(), s.end(), 'B', '1');
    replace(s.begin(), s.end(), 'L', '0');
    replace(s.begin(), s.end(), 'R', '1');

    return stoi(s, nullptr, 2);
}

int main() 
{
    vector<seatId> v;
    seatId current;
    string line;
    ifstream myfile( "5input.txt");
    if (myfile) 
    {

        while (getline( myfile, line)) 
        {
            if (line != "") 
            {
                int dec = convertStringToBinaryToDec(line);
                
                current = seatId();
                current.dec = dec;
                current.s = line;
                v.push_back(current);
            }
        }
        sort(v.begin(), v.end(),
                [](const seatId & L, const seatId & R) -> bool
        {
            return L.dec < R.dec;
        });

        for(int j = 1; j != v.size(); j++) {
            int a = v[j -1].dec;
            int b = v[j].dec;
            if(a != b -1) {
                int answer = a + 1;
                cout << "answer is " << answer << '\n';
                break;
            }
        }

    }
    else cout << "fooey\n";

    return 0; 

}

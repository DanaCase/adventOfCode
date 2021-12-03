#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    string line;
    vector<int> num;
    int count = 0;
    int i = 0;
    ifstream myfile( "data/1.txt");
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            int current = stoi(line);
            num.push_back(current);
            if(i < 3) {
                //do nothing
            } 
            else {
                int sum1 = num[i - 3] + num[i - 2] + num[i - 1];
                int sum2 = num[i -2] + num[i - 1] + num[i];
                cout << sum1 << "\n";
                if (sum2 > sum1) {
                    count++;
                }
            }

            i++;
        }
        cout << count << "\n";
        myfile.close();
    }
    else cout << "fooey\n";

    return 0; 

}

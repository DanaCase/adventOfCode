#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> getCountAtPos(vector<string>& inputVector, int pos) {
    vector<int> returnVector = {0,0};
    for (int i = 0; i < inputVector.size(); ++i) {
        if(inputVector[i][pos] == '0') {
            returnVector[0]++;
        } else {
            returnVector[1]++;
        }
    }
    return returnVector;
}

vector<string> filterOut(vector<string>& inputVector, char val, int pos) {
    vector<string> returnVector;
    for(size_t i = 0; i < inputVector.size(); ++ i) {
        if(inputVector[i][pos] == val) {
            returnVector.push_back(inputVector[i]);
        }
    }
    return returnVector;
}

char getOx(vector<string>& ox, int pos) {
    vector<int> counts = getCountAtPos(ox, pos);
    if (counts[1] >= counts[0]) {
        return '1';
    } else {
        return '0';
    }
}

char getCo2(vector<string>& co2, int pos) {
    vector<int> counts = getCountAtPos(co2, pos);
    if (counts[1] < counts[0]) {
        return '1';
    } else {
        return '0';
    }
}

int main() {
    string line;
    vector<int> ones = {0,0,0,0,0,0,0,0,0,0,0,0};
    vector<int> zeros = {0,0,0,0,0,0,0,0,0,0,0,0};
    vector<string> lines;
    string gamma;
    string epsilon;
    ifstream myfile("data/3.txt");
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            lines.push_back(line);
            int N = line.length();
            for (int i = 0; i < N; i++) {
                if(line[i] == '0') {
                    zeros[i]++;
                }
                else {
                    ones[i]++;
                }
            }
        }
        for(size_t j = 0; j < ones.size(); ++j) {
            if(ones[j] > zeros[j]){
                gamma+='1';
                epsilon+='0';
            }
            else {
                gamma+='0';
                epsilon+='1';
            }
        }
        cout << stoi(gamma, 0, 2) << "\n";
        cout << stoi(epsilon, 0, 2) << "\n";
        cout << "gamma times epsilon " << stoi(gamma, 0, 2) * stoi(epsilon, 0, 2) << "\n";
        myfile.close();
    
        /*
         * Part 2
         */
        vector<string> ox = lines;
        vector<string> co2 = lines;
        string oxRating;
        string co2Rating;
        
        for(size_t k = 0; k < ones.size(); ++ k) {
            cout << ox.size() << "\n";
            ox = filterOut(ox, getOx(ox, k), k);
            co2 = filterOut(co2, getCo2(co2, k), k);

            if(ox.size() == 1) {
                cout << "ox is 1 and it is" << ox[0] << "\n";
                oxRating = ox[0];
            }
            
            if(co2.size() == 1) {
                cout << "co2 is 1 and it is" << co2[0] << "\n";
                co2Rating = co2[0];
            }
        }
        
        cout << "life support rating is " << stoi(oxRating, 0, 2) * stoi(co2Rating, 0, 2) << "\n";

    }
    else cout << "fooey\n";

    return 0; 

}


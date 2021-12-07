#include <string>
#include <fstream>
#include <iostream>
#include<sstream>
#include <vector>
#include <cmath>

using namespace std;


vector<int> parse_line(string line) {
    vector<int> v;
    stringstream ss(line);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(stoi(substr));
    }
    //printMatrix(v);
    return v;
}

int getMin(vector<pair<int, int>> v) {
    int min = v[0].second;
    int minVal = v[0].first;
    for(int i = 0; i < v.size(); i++) {
        if (v[i].second < min) {
            min = v[i].second;
            minVal = v[i].first;
        }
    }
    return min;
}

int calculateDistance(int starting, int distance) {
    int difference = abs(starting - distance);
    //cout << "difference is " << difference << "for "<< starting << " " << distance << "\n";
    int sum = 0;
    for(int i = 1; i <= difference; i++) {
        sum += i;
        //cout << "sum is " << sum << " for " << starting << "\n";
    }
    return sum;
}


int main() {
    string line;
    vector<int> startingPositions;
    ifstream myfile("data/7.txt");
    if (myfile)  
    {
        while (getline( myfile, line)) {
            startingPositions = parse_line(line);
        }
        //get range so you know which positions to consider?
        auto max = *max_element(begin(startingPositions), end(startingPositions));
        auto min = *min_element(begin(startingPositions), end(startingPositions));
        cout << "max location " << max << "\n";
        cout << "min location " << min << "\n";

        vector<pair<int, int>> distancesSum;
        int ii = 0;
        for(int i = min; i < max; i++) {
            distancesSum.push_back(pair<int, int>(i, 0));
            for(int j = 0; j< startingPositions.size(); j++) {
                //distance calculation part 1
                //distancesSum[ii].second += abs(startingPositions[j] - i);
                //distance calculation part 2
                int calcFuel = calculateDistance(startingPositions[j], i);
                distancesSum[ii].second += calcFuel;
            }
            ii++;
        }

        int minfuel = getMin(distancesSum);
        cout << "min location is " << minfuel << "\n";
            
        

    }
    else cout << "fooey\n";

    return 0; 

}


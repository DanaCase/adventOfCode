#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


vector<int> parse_line(string line) {
    vector<int> v;
    for(int i = 0; i < line.size(); i++){
        v.push_back(line[i] - '0');
    }
    return v;
}

int getSum(vector<int> lowPoints) {
    int count = 0;
    for(int i=0; i < lowPoints.size(); i++) {
        count += (lowPoints[i] + 1);
    }
    return count;
}

int main() {
    string line;
    vector<vector<int>> heights;
    vector<int> lowPoints;
    vector<pair<int,int>> lowPointLocations;
    ifstream myfile("data/9-test");
    if (myfile)  
    {
        while (getline( myfile, line)) {
            heights.push_back(parse_line(line));
        }
        for(int i = 0; i < heights.size(); i++) {
            for(int j = 0; j < heights[i].size(); j++) {
                int myPoint = heights[i][j];
                vector<int> pointsToConsider;
                if(i-1 >= 0) {
                    pointsToConsider.push_back(heights[i-1][j]);
                } 
                if(i+1 < heights.size()) {
                    pointsToConsider.push_back(heights[i+1][j]);
                }
                if(j-1 >= 0) {
                    pointsToConsider.push_back(heights[i][j-1]);
                }
                if(j+1 < heights[0].size()) {
                    pointsToConsider.push_back(heights[i][j+1]);
                }
                
                //sure would be cool if I could reference a variable in a lambda 
                //if ( all_of(pointsToConsider.begin(), pointsToConsider.end(), [](int i){return i > myPoint;}) ) {

                //}

                //bool allSmaller = 1;
                for(int ii = 0; ii < pointsToConsider.size(); ii++) {
                    if(heights[i][j] >= pointsToConsider[ii]) {
                        //allSmaller = 0;
                        break;
                    } 
                    if (ii == pointsToConsider.size() - 1) {
                        lowPoints.push_back(heights[i][j]);
                        lowPointLocations.push_back(pair<int, int>(i, j));

                    }
                    //cout << allSmaller << "\n";
                }
                //guess I dont understand variable scope here...
                //if(allSmaller == 0) {
                        //lowPoints.push_back(heights[i][j]);
                        //cout << "new low point " << heights[i][j] << "\n";
                //}
            }
        }

        int sum = getSum(lowPoints);
        cout << "sum is " << sum << "\n";

        //part 2
        //for each low point...traverse out in all directions until you hit an edge or a  9
        //you could pre calculate 9s if you wanted...
        for(auto &x : lowPointLocations) {
            for()
        }

    }
    else cout << "fooey\n";

    return 0; 

}


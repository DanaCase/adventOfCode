#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>

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
    vector<pair<int,int>> nines;
    ifstream myfile("data/9.txt");
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
                //
                //for part 2
                if (myPoint == 9) {
                    //cout << "nine found " << i << " " << j << "\n";
                    nines.push_back(pair<int, int>(i, j));
                }
            }
        }

        int sum = getSum(lowPoints);
        cout << "sum is " << sum << "\n";

        vector<int>basinSizes;

        for (auto &myLowPoint : lowPointLocations) {
            vector<pair<int, int>> basin;
            basin.push_back(myLowPoint);
            //had to use an iterator instead of auto, not sure why
            for(int i = 0; i < basin.size(); i++) {
                pair<int, int> p = basin[i];
                cout << "leng " << basin.size() << "\n";
                if(p.first - 1 >= 0 && heights[p.first - 1][p.second] !=9) {
                    pair<int, int> point (p.first -1, p.second);
                    if(count(basin.begin(), basin.end(), point) == 0) {
                        basin.push_back(pair<int, int>(p.first -1, p.second));
                    }
                }
                if(p.first + 1 < heights.size() && heights[p.first + 1][p.second] !=9) {
                    pair<int, int> point (p.first +1, p.second);
                    if(count(basin.begin(), basin.end(), point) == 0) {
                        basin.push_back(point);
                    }
                }
                if(p.second - 1 >= 0 && heights[p.first][p.second -1] !=9) {
                    pair<int,int> point (p.first, p.second -1);
                    if(count(basin.begin(), basin.end(), point) == 0) {
                        basin.push_back(point); 
                    }
                }
                if(p.second + 1 < heights[0].size() && heights[p.first][p.second + 1] != 9) {
                    pair<int, int> point(p.first, p.second + 1);
                    if(count(basin.begin(), basin.end(), point) == 0) {
                        basin.push_back(point);
                    }
                }
            }
            for(auto &p : basin) {
                cout << p.first << " " << p.second << "\n";
            }
            basinSizes.push_back(basin.size());
        }

        for(auto &x : basinSizes) {
            cout << x << "\n";
        }

        sort(basinSizes.begin(), basinSizes.end(), greater<int>());

        cout << basinSizes[0] * basinSizes[1] * basinSizes[2] << "\n";

    }
    else cout << "fooey\n";

    return 0; 

}


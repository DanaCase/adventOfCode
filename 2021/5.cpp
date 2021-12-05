#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include<sstream>
#include <cstdlib>

using namespace std;

int printMatrix(vector<vector<int>> &matrix) {
    for(int j=0;j<matrix.size();j++)
    {
        for(int k=0;k<matrix[j].size();k++)
        {
            cout<<matrix[j][k]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}

//start with horizontal
vector<int> getRangeH(vector<vector<int>> points) {
    vector<int> v; 
    cout << points[1][0] << "\n";
    if (points[0][0] > points[1][0]) {
        v.push_back(points[1][0]);
        v.push_back(points[0][0]);
    } else {
        v.push_back(points[0][0]);
        v.push_back(points[1][0]);
    }
    return v;
}

vector<int> getRangeV(vector<vector<int>> points) {
    vector<int> v;
    if (points[0][1] > points[1][1]) {
        v.push_back(points[1][1]);
        v.push_back(points[0][1]);
    } else {
        v.push_back(points[0][1]);
        v.push_back(points[1][1]);
    }
    return v;
}

bool isDiag(vector<vector<int>> &points) {
    if(abs(points[0][0] - points[1][0]) == abs(points[0][1] - points[1][1])) {
        cout << "oh its diag " << points[0][0] << "," << points[0][1] << " " << points[1][0] << "," << points[1][1] << "\n";
        return 1;
    }
    return 0;
}

//wish I was better at functional programming in C++, this is the same logic as printing
int countTwo(vector<vector<int>> matrix) {
    int sum = 0;
    for(int j=0;j<matrix.size();j++)
    {
        for(int k=0;k<matrix[j].size();k++)
        {
            if(matrix[j][k] > 1) {
                sum++;
            }
        }
    }
    return sum;
    
}

vector<vector<int>> parse_line(string line) {
    vector<vector<int>> v;
    stringstream ss(line);
    while (ss.good()) {
        string substr;
        getline(ss, substr, ' ');
        if(substr != "->") {
            vector<int> v2;
            //cout << substr << "\n";
            stringstream sss(substr);
            while (sss.good()) {
                string ssubstr;
                getline(sss, ssubstr, ',');
                v2.push_back(stoi(ssubstr));
            }
            v.push_back(v2);
        }
    }
    //printMatrix(v);
    return v;
}


int main() {
    string line;
    vector<vector<int>> lineCounts(1000, vector<int>(1000, 0));
    ifstream myfile("data/5.txt");
    if (myfile) 
    {
        while (getline( myfile, line)) {
            vector<vector<int>> currentPoints = parse_line(line);
            cout << "current points" << "\n";
            printMatrix(currentPoints);
            //horizontal
            if(currentPoints[0][1] == currentPoints[1][1]){
                vector<int> range = getRangeH(currentPoints);
                for(int i = range[0]; i <= range[1]; i++){
                    cout << "range " << i << "\n";
                    int yval = currentPoints[0][1];
                    lineCounts[yval][i] += 1;
                }

            }
            ////vertical
            if(currentPoints[0][0] == currentPoints[1][0]) {
                vector<int> range = getRangeV(currentPoints);
                for(int i = range[0]; i <= range[1]; i++) {
                    cout << "vertical range " << range[0] << " " << range[1] << "\n";
                    int xval = currentPoints[0][0];
                    lineCounts[i][xval] += 1;
                }
            }
            //diag
            //first determine if diag 
            bool diag = isDiag(currentPoints);
            if(diag) {
                auto smallerX = currentPoints[0][0] < currentPoints[1][0] ? currentPoints[0] : currentPoints[1]; 
                auto largerX = currentPoints[0][0] > currentPoints[1][0] ? currentPoints[0] : currentPoints[1]; 
                int y = smallerX[1];
                cout << "y is " << y << "\n";
                for(int x = smallerX[0]; x <= largerX[0]; x++) {
                   //not exactly sure how I swapped these 
                    lineCounts[y][x] += 1;
                    cout << "x is " << x << " y is " << y << "\n";
                    cout << "lineCount is " << lineCounts[x][y] << "\n";
                    if(smallerX[1] < largerX[1]){
                        y++;
                    } else {
                        y--;
                    }
                }
            }
            //printMatrix(lineCounts);
            //count 2 or more
            int sum = countTwo(lineCounts);
            cout << "sum is " << sum << "\n";
        }
    }
    else cout << "fooey\n";

    return 0; 

}


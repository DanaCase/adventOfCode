#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


vector<int> parse_line(string line) {
    vector<int>v;
    for(int i=0; i<line.size(); i++) {
        v.push_back(line[i] -'0');
        //cout << v[i] <<  "\n";
    }
    return v;
}

void printMatrix(vector<vector<bool>> v) {
    for(int i = 0; i < v.size(); i ++) {
        for(int j =0;  j< v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
}


void flash(int r, int c, vector<vector<int>> &v) {
    vector<pair<int, int>> f = {
        pair<int, int>(r - 1, c),
        pair<int, int>(r - 1, c + 1),
        pair<int, int>(r - 1, c - 1),
        pair<int, int>(r + 1, c),
        pair<int, int>(r + 1, c + 1),
        pair<int, int>(r + 1, c - 1),
        pair<int, int>(r, c + 1),
        pair<int, int>(r, c - 1),
    };
    //cout << "flashing " << r << " " << c << "\n";
    v[r][c] = 0;
    for(auto &x :f) {
        if(
                x.first >= 0 &&
                x.first < v.size() &&
                x.second >= 0 &&
                x.second < v[0].size() &&
                v[x.first][x.second] !=0
        ) {
            //cout << "incrementing by 1 at " << x.first << " " << x.second << " was : " << v[x.first][x.second] << "\n";
            v[x.first][x.second] += 1;
            if(v[x.first][x.second] > 9) {
                flash(x.first, x.second, v);
            }
        }
    }
}


int countFlashes(vector<vector<int>> &v) {
    int count = 0;
    for(int r = 0; r < v.size(); r++)  {
        for(int c = 0; c < v[0].size(); c++) {
            string start = "";
            string end = "";
            if (v[r][c] == 0) {
                count++;
                //v[r][c] = 0;
                start = "\e[1m";
                end = "\e[0m";
            }
            cout << start << v[r][c] << end << " ";
        }
        cout << "\n";
    }
    return count;
}


int main() {
    string line;
    int count = 0;
    vector<vector<int>> v;
    ifstream myfile("data/11.txt");
    if (myfile)  
    {
        while (getline( myfile, line)) {
            v.push_back(parse_line(line));
        }
        for(int i=0; i < 1000; i++ ){
            //could keep track, but I'll just keep incre
            //vector<pair<int, int> flashedThisStep;
            for(int r = 0; r < v.size(); r++)  {
                for(int c = 0; c < v[0].size(); c++) {
                    v[r][c] += 1;
                    //cout << v[r][c] << "\n";
                    //if(v[r][c] > 9) {
                    //}
                }
            }
            for(int r = 0; r < v.size(); r++)  {
                for(int c = 0; c < v[0].size(); c++) {
                    //v[r][c] += 1;
                    //cout << v[r][c] << "\n";
                    if(v[r][c] > 9) {
                        flash(r, c, v);
                    }
                }
            }
            int flashCount = countFlashes(v);
            if(flashCount == v.size() * v[0].size()) {
                return 0;
            }
            count += flashCount;
            cout << count << " flashes in step " << i << "\n";
        }
    }
    else cout << "fooey\n";

    return 0; 

}


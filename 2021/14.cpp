#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


map<string, string> parse_line(string line, map<string, string> &m) {
    int pos = line.find(" -> ");
    string a = line.substr(0, pos);
    string b  = line.substr(pos + 4, line.size());
    //cout << a << " " << b << "\n";
    cout  << a << "\n";
    cout << b << "\n";
    m.insert(pair<string, string>(a, b));
    return m;
}

void printMatrix(vector<vector<bool>> v) {
    for(int i = 0; i < v.size(); i ++) {
        for(int j =0;  j< v[i].size(); j++) {
            cout << v[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    string line;
    int i = 0;
    map<string, string> m;
    map<char, int> freq;
    string s;
    ifstream myfile("data/14.txt");
    if (myfile)  
    {
        while (getline( myfile, line)) {
            if(i == 0) {
                s = line;
                for(int ii = 0; ii < line.size(); ii++) {
                    if(freq.count(line[ii]) == 0) {
                        freq.insert(pair<char, int>(line[ii], 1));
                    }
                    else {
                        freq[line[ii]] += 1;
                    }
                }
            } else if (i == 1) {
            } else {
                parse_line(line, m);
            }
            i++;
        }
        for (auto &x: m) {
            cout << x.first << " " << x.second << "\n";
        }
        for(int i = 0; i < 10; i++){
            string ss;
            for(int j = 0; j < s.size(); j++) {
                ss.push_back(s[j]);
                string p;
                p.push_back(s[j]);
                p.push_back(s[j+1]);
                //cout << "p is " << p << "\n";
                //cout << "map says insert "<< m[p] << "\n";
                ss.push_back(m[p][0]);
                if(freq.count(m[p][0]) == 0) {
                    freq.insert(pair<char, int>(m[p][0], 1));
                }
                else {
                    freq[m[p][0]] += 1;
                }
            }
            cout << ss << "\n";
            cout << ss.size() << "\n";
            s = ss;
        }
        int max = 0;
        int min = 0;
        for(auto &x: freq) {
            cout << x.first << " is " << x.second << "\n";
            if(min == 0) {
                min = x.second;
            }
            if(x.second > max) {
                max = x.second;
            }
            if(x.second < min) {
                min = x.second;
            }
        }
        cout <<  max - min  << "\n";
        //cout << max - min << "\n";

    }
    else cout << "fooey\n";

    return 0; 

}


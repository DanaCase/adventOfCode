#include <string>
#include <fstream>
#include <iostream>
#include<sstream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;


vector<string> parse_line(string &line, char split) {
    vector<string> v;
    stringstream ss(line);
    while (ss.good()) {
        string substr;
        getline(ss, substr, split);
        v.push_back(substr);
    }
    return v;
}

int part1(string &segment, int &count) {
    vector<int> unique = {2, 4, 3, 7};
    string first = "";
    string last = "";
    if(find(begin(unique), end(unique), segment.size()) != end(unique)) {
        count++;
        first = "\e[1m";
        last = "\e[0m";
    }
    //cout << segment << " ";
    //cout << first << segment << last << " ";
    return count;
}

map<char, int> getLetterCounts(vector<string> in) {
    map<char, int> mymap;
    for(int i = 0; i < in.size(); i++) {
        for(int j = 0; j < in[i].size(); j++) {
            char letter = in[i][j];
            if(mymap.count(letter) == 0) {
                mymap.insert(pair<char, int>(letter, 1));
            } else {
                mymap[letter]++;
            }
        }
    }
    return mymap;
}

char getE(map<char, int> &myMap) {
    for(const auto &x : myMap) {
        //cout << x.first << " " << x.second << "\n";
        if(x.second == 4) {
            return x.first;
        }
    }
}

char getF(map<char, int> &myMap) {
    for(const auto &x : myMap) {
        //cout << x.first << " " << x.second << "\n";
        if(x.second == 9) {
            return x.first;
        }
    }
}

char getC(map<string, int> myMap, char f) {
    //get desired string
    string one;
    for(const auto x : myMap) {
        if(x.second == 1) {
            one = x.first;
        }
    }
    one.erase(std::remove(one.begin(), one.end(), f), one.end());
    return one[0];
}

int printNumberMap(map<string, int>  &numberMap) {
    for(auto &x : numberMap) {
        cout << x.first << " : " << x.second << "\n";
    }
}

string findCharMatch(string &x, map<string, int> &numberMap) {
    vector<char> v(x.begin(), x.end());
    sort(v.begin(), v.end());
    string s(v.begin(), v.end());
    for(auto &y : numberMap) {
        vector<char> v2(y.first.begin(), y.first.end());
    }

}

int getOutputDigits(vector<string> &output, map<string, int> numberMap)  {
    string out;
    for(auto &x : output) {
        //shit I just realized the chars are scrambled :/
        vector<char> v(x.begin(), x.end());
        sort(v.begin(), v.end());
        string s(v.begin(), v.end());

        for(auto &y : numberMap) {
            vector<char> v2(y.first.begin(), y.first.end());
            sort(v2.begin(), v2.end());
            string s2(v2.begin(), v2.end());
            if(s2 == s) {
                //cout << "digit is " << y.second << "\n";
                out += to_string(y.second);
            }
        }
    }
    return stoi(out);
}


int main() {
    string line;
    //vector<vector<string>> out;
    vector<int> unique = {2, 4, 3, 7};
    int count = 0;
    int part2Count = 0;
    ifstream myfile("data/8.txt");
    if (myfile)  
    {
        while (getline( myfile, line)) {
            cout << "line is " << line << "\n";
            vector<string> tmpv= parse_line(line, '|');
            
            //part1
            //just parse the second half for now
            vector<string> o = parse_line(tmpv[1], ' ');
            //cout << "length " << o.size() << "\n";
            for (int i= 0; i < o.size(); i++) {
                count = part1(o[i], count);
            }
            cout << "\n";
            cout << count << "\n";

            //part2
            vector<string> sig = parse_line(tmpv[0], ' ');
            map<char, int> letterCount = getLetterCounts(sig);
            map<string, int> numberMap;
            //find unique by length, and the 9 which has an'e' segment
            
            char e = getE(letterCount);
            char f = getF(letterCount);
            
            for (int i = 0; i < sig.size(); i++) {
                if(sig[i].size() == 2) {
                    numberMap.insert(pair<string, int>(sig[i], 1));
                } 
                else if(sig[i].size() == 3) {
                    numberMap.insert(pair<string, int>(sig[i], 7));
                }
                else if(sig[i].size() == 4) {
                    numberMap.insert(pair<string, int>(sig[i], 4));
                } 
                else if(sig[i].size() == 7) {
                    numberMap.insert(pair<string, int>(sig[i], 8));
                }
                else if(sig[i].size() == 5) {
                    if(sig[i].find(e) != string::npos) {
                        numberMap.insert(pair<string, int>(sig[i], 2));
                    }
                }
                else if(sig[i].size() == 6) {
                    if(sig[i].find(e) == string::npos) {
                        numberMap.insert(pair<string, int>(sig[i], 9));
                    }
                }
            }
            //next we distinguish 0 from 6 and 3 from 5 based on segment c which is 4 - 7 - 1
            char c = getC(numberMap, f);
            cout << "c is " <<c << "\n";
            cout << "e is " <<e << "\n";
            for(int i = 0; i < sig.size(); i++) {
                if(sig[i].size() == 5) {
                    if(sig[i].find(c) == string::npos && sig[i].find(e) == string::npos) {
                        numberMap.insert(pair<string, int>(sig[i], 5));
                    }
                    else if(sig[i].find(e) != string::npos) {
                        numberMap.insert(pair<string, int>(sig[i], 2));
                    }
                    else {
                        numberMap.insert(pair<string, int>(sig[i], 3));
                    } 
                }
                if(sig[i].size() == 6) {
                    if(sig[i].find(c) == string::npos) {
                        numberMap.insert(pair<string, int>(sig[i], 6));
                    }
                    else if(sig[i].find(e) == string::npos) {
                        numberMap.insert(pair<string, int>(sig[i], 9));
                    }
                    else {
                        numberMap.insert(pair<string, int>(sig[i], 0));
                    }
                }
            }

            printNumberMap(numberMap);
            
            //now get the output digits
            int digits = getOutputDigits(o, numberMap);
            cout << "digits  are " << digits << "\n";
            part2Count += digits;

        }
        //part 1
        cout << "1, 4, 7, 8 count: " << count << "\n";

        //part 2
        cout << "part 2 sum " << part2Count << "\n";
    }
    else cout << "fooey\n";

    return 0; 

}


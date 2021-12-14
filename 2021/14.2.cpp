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

int main() {
    string line;
    int i = 0;
    map<string, string> rules;
    map<char, long long> freq;
    map<string, long long> tokens;
    string s;
    ifstream myfile("data/14.txt");
    if (myfile)  
    {
        while (getline( myfile, line)) {
            if(i == 0) {
                s = line;
                for(int ii = 0; ii < line.size(); ii++) {
                    //fill out freq
                    if(freq.count(line[ii]) == 0) {
                        freq.insert(pair<char, long long>(line[ii], 1));
                    }
                    else {
                        freq[line[ii]] += 1;
                    }
                    if(ii < line.size() - 1) {
                        //fill out tokens
                        string token;
                        token.push_back(line[ii]);
                        token.push_back(line[ii+1]);
                        cout << "original parse " << token << "\n";
                        if(tokens.count(token) == 0) {
                            tokens.insert(pair<string, long long>(token, 1));
                        } 
                        else {
                            tokens[token] +=1;
                        }

                    }
                }
            } else if (i == 1) {
            } else {
                parse_line(line, rules);
            }
            i++;
        }
        for (auto &x: rules) {
            cout << x.first << " " << x.second << "\n";
        }
        for (auto &x: tokens) {
            cout << "original tokens " << x.first << "\n";
        }
        for(int i = 0; i < 40; i++){
            map<string, long long> newTokens;
            for (auto &x : tokens) {
                //cout << "original is " << x.first << "\n";
                string oldToken = x.first;
                long long count = x.second;
                char l = rules[oldToken][0];
                //cout << rules[oldToken] << "\n";
                //cout << "iserted char is " << l << "\n";
                
                string new1;
                new1.push_back(oldToken[0]);
                new1.push_back(l);
                //cout << "first new token " << new1 << "\n";
                
                string new2;
                new2.push_back(l);
                new2.push_back(oldToken[1]);
                //cout << "second new token " << new2 << "\n";
                
                if(newTokens.count(new1) == 0) {
                    newTokens.insert(pair<string, long long>(new1, count));
                } else {
                    newTokens[new1] += count;
                }
                
                if(newTokens.count(new2) == 0) {
                    newTokens.insert(pair<string, long long>(new2, count));
                } else {
                    newTokens[new2] += count;
                }

                if(freq.count(l) == 0) {
                    freq.insert(pair<char, long long>(l, count));
                }
                else {
                    freq[l] += count;
                }
            }
            tokens = newTokens;
        }
        long long max = 0;
        long long min = 0;
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

    }
    else cout << "fooey\n";

    return 0; 

}


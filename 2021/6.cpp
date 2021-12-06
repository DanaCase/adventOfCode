#include <string>
#include <fstream>
#include <iostream>
#include<sstream>
#include <vector>
#include <map>

using namespace std;
using std::map;


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

int print_fishies(vector<int> &fishies) {
    for (int i = 0; i < fishies.size(); i ++) {
        cout << fishies[i] << ' ';
    }
    cout << "\n";
    return 0;
}

map<int, long long> getNewFishiesMap(map<int, long long> fishiesMap) {
    map<int, long long> newFishiesMap;
    for (const auto &x : fishiesMap) {
        //for example if it's 3;
        int num = x.first; //0
        long long fishCount = x.second; // at first its 0
        if(num == 0) {
            if(newFishiesMap.count(8) == 0) {
                newFishiesMap.insert(pair<int, long long>(8, fishCount));
            } else {
                newFishiesMap[8] += fishCount;
            }
                if (newFishiesMap.count(6) == 0) {
                    newFishiesMap.insert(pair<int, long long>(6, fishCount));
                } else {
                    newFishiesMap[6] += fishCount;
                }
        } else {
            if (newFishiesMap.count(num - 1) == 0) {
                newFishiesMap.insert(pair<int, long long>(num - 1, fishCount));
            } else {
                newFishiesMap[num - 1] += fishCount;
            }
        }
    }
    return newFishiesMap;
}

long long getFishiesCount(map<int, long long> fishiesMap) {
    long long sum = 0;
    for (const auto &x : fishiesMap) {
        sum += x.second;
    } 
    return sum;
}

int main() {
    string line;
    vector<string> lines;
    vector<int> fishies;
    map<int, long long> fishiesMap;
    ifstream myfile("data/6.txt");
    cout << fishies.max_size() << "\n";
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            fishies = parse_line(line);
            for(int i = 0; i < fishies.size(); i++) {
                if(fishiesMap.count(fishies[i]) == 0) {
                    fishiesMap.insert(pair<int, long long>(fishies[i], 1));
                }
                else {
                    fishiesMap[fishies[i]]++;
                }
            }
        }
        for (int i = 0; i < 256; i++) {
            fishiesMap = getNewFishiesMap(fishiesMap);
        }
        long long fishiesCount = getFishiesCount(fishiesMap);
        cout << "so many fishies " << fishiesCount << "\n";
    }
    else cout << "fooey\n";

    return 0; 

}


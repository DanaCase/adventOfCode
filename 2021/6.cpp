#include <string>
#include <fstream>
#include <iostream>
#include<sstream>
#include <vector>

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

int print_fishies(vector<int> &fishies) {
    for (int i = 0; i < fishies.size(); i ++) {
        cout << fishies[i] << ' ';
    }
    cout << "\n";
    return 0;
}

int main() {
    string line;
    vector<string> lines;
    vector<int> fishies;
    ifstream myfile("data/6-test");
    cout << fishies.max_size() << "\n";
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
              fishies = parse_line(line);
        }
        for (int i = 0; i < 256; i++) {
            int noNewFishies = fishies.size();
            for(int j = 0; j < noNewFishies; j++) {
                if(fishies[j] == 0) {
                    fishies[j] = 6;
                    fishies.push_back(8);
                }
                else {
                    fishies[j]--;
                }
            }
            //print_fishies(fishies);
        }
        cout << "so many fishies " << fishies.size() << "\n";
    }
    else cout << "fooey\n";

    return 0; 

}


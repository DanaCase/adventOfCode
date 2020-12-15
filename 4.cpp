#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct passport {
    string byr;
    string iyr;
    string eyr;
    string hyt;
    string hcl;
    string ecl;
    string pid;
    string cid;
};

bool isValid(passport pass) {
    return true;
}

passport getPassport(vector<string> collected) {
    cout << "get passport ";
    for(int i = 0; i < collected.size(); i++)
    {
        cout << collected.at(i) <<  ' ';
    }

    cout << "\n";
    passport pass;
    pass.byr = "";
    return pass;
}

vector<string> split(const string& s, const char& c ) {
    string buff{""};
    vector<string> v;
    for(int i = 0; i != s.size(); i++)
    {
        char n = s.at(i);
        if(n != c) 
        {
            buff+=n;
            //cout << buff << "\n";

        } else if(n == c && buff != "")
        {
            v.push_back(buff); buff = "";
        }

    }
    if(buff != "")
    {
        v.push_back(buff);
    }
    return v;
}

int main() {
    string line;
    vector<string> collected{};
    int validCount = 0;

    ifstream myfile( "4testinput.txt");
    if (myfile) 
    {
        while (getline( myfile, line)) 
        {
            if (line != "") 
            {
                vector<string> tmp = split(line, ' ');
                collected.insert(collected.end(), tmp.begin(), tmp.end());
                continue;
            }
            passport pass = getPassport(collected);
            if (isValid(pass)) {
                validCount++; 
            }
            collected.clear();
        }
        passport pass = getPassport(collected);
        if (isValid(pass)) {
            validCount++; 
        }
        myfile.close();
        cout << validCount;
    }
    else cout << "fooey\n";

    return 0; 

}

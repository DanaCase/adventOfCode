#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<string> necessaryKeys{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

int countDigit(long long n)
{
    int count = 0;
    while (n != 0) 
    {
        n = n / 10;
        ++count;
    }
    return count;
}
bool byr(string s) {
    try {
        int i = stoi(s);
        if(countDigit(i) == 4 && i >= 1920 && i <= 2002) {
            return true;
        }
        return false;
    } catch (const exception& e) {
        cout << e.what() << '\n';
        return false;
    }
}  
bool iyr(string s) {
    try {
        int i = stoi(s);
        if(countDigit(i) == 4 && i >= 2010 && i <= 2020) {
            return true;
        }
        return false;
    } catch (const exception& e) {
        cout << e.what() << '\n';
        return false;
    }
}
bool eyr(string s) {
    try {
        int i = stoi(s);
        if(countDigit(i) == 4 && i >= 2020 && i <= 2030) {
            return true;
        }
        return false;
    } catch (const exception& e) {
        cout << e.what() << '\n';
        return false;
    }
}
bool hgt(string s) {
    try {
        string buff;
        for (int i =0; i != s.size(); i++) {
            char n = s.at(i);
            if (n != 'c' && n != 'i') {
                buff+=n;
            } else if (n == 'c') {
                int num = stoi(buff);
                return num <= 193 && num >=150;
            } else if (n == 'i') {
                int num = stoi(buff);
                return num <= 76 && num >=59;
            }
        }
        return false;

    } catch (const exception& e) {
        cout << e.what() << '\n';
        return false;
    }
}

bool hcl(string s) {
    try {
        for (int i =0; i != s.size(); i++) {
            char n = s.at(i);
            if(i == 0 && n != '#') {
                cout << "wrong start \n";
                return false;
            }
            if(i > 6) {
                cout << "hcl too long \n";
                return false;
            }
            if((n >= 'a' && n<= 'f') || (n >= '0' && n <= '9')) {
                continue;
            }
        }
        return true;
    } catch (exception& e) {
        cout << e.what() << '\n';
        return false;
    }
}

bool ecl(string s) {
    vector<string> valid{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    for(auto& v:valid) {
        if(s == v) {
            return true;
        }
    }
    cout << "eye color not found " << s << "\n";
    return false;
}

bool pid(string s) {
    try {
        if (s.size() != 9) {
            cout << "pid wrong length \n";
            return false;
        }
        for(int i = 0; i != s.size(); i++) {
            int n = stoi(s);
        }
        return true;
    } catch (exception& e) {
        cout << e.what() << "\n";
        return false;
    }
}

bool isValid(map<string, string> pass, map<string, function<bool(string)>> funcMap) {
    for(auto& s:necessaryKeys) {
        //cout << s << " \n";
        //cout << pass[s] << " \n";
        if(pass.find(s) != pass.end()) {
            if(funcMap.find(s) != funcMap.end()) {
                if (!funcMap[s](pass[s])) {
                    return false;
                }
            }
            continue;
        } else {
            cout << s << " " << pass[s] << "not found\n";
            return false;
        }
    }
    return true;
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


map<string, string> getPassport(vector<string> collected) {
    map<string, string> pass;
    for(int i = 0; i != collected.size(); i ++)
    {
        vector<string> kv = split(collected.at(i), ':');
        //pass.insert(pair<string, string>(kv[0], kv[1]));
        //cout << kv[1];
        pass[kv[0]] = kv[1];
    }
    return pass;
}

int main() {
    string line;
    vector<string> collected{};
    int validCount = 0;
    map<string, function<bool(string)>>  funcMap =
         {
            {"byr" , byr},
            {"iyr" , iyr},
            {"eyr" , eyr},
            {"hgt" , hgt},
            {"hcl" , hcl},
            {"ecl" , ecl},
            {"pid" , pid}
         };

    ifstream myfile( "4input.txt");
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
            map<string, string> pass = getPassport(collected);
            if (isValid(pass, funcMap)) {
                validCount++; 
            }
            collected.clear();
        }
        map<string, string> pass = getPassport(collected);
        if (isValid(pass, funcMap)) {
            validCount++; 
        }
        myfile.close();
        cout << validCount;
    }
    else cout << "fooey\n";

    return 0; 

}

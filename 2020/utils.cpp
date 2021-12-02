#include <string>
#include <vector>

using namespace std;

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

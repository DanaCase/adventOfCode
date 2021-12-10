#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;


void printStack(stack<int> s)
{
    if (s.empty())
        return;
    int x = s.top();
    s.pop();
    cout << x << ' ';
    printStack(s);
    s.push(x);
}

long long parse_line(string line) {
    stack <char> cstack;

    for(int i = 0; i < line.size(); i++){
        if(line[i] == '[') {
            cstack.push('[');
        }
        else if(line[i] == ']') {
            char it = cstack.top();
            cstack.pop();
            if (it != '[') {
                //part1
                //cout << it << "expected ]" << "\n";
                //return 57;
                return 0;
            }
        }
        else if(line[i] == '{') {
            cstack.push('{');
        }
        else if(line[i] == '}') {
                char it = cstack.top();
                cstack.pop();
                if (it != '{') {
                    //part 1
                    //cout << it << "expected }" << "\n";
                    //return 1197;
                    return 0;
                }
        }
        else if(line[i] == '(') {
            cstack.push('(');
        }
        else if(line[i] == ')') {
                char it = cstack.top();
                cstack.pop();
                if (it != '(') {
                    //part1
                    //cout << it << "expected )" << "\n";
                    //return 3;
                    return 0;
                }
        }
        else if(line[i] == '<') {
            cstack.push('<');
        }
        else if(line[i] == '>') {
                char it = cstack.top();
                cstack.pop();
                if (it != '<') {
                    //part1
                    //cout << it << "expected <" << "\n";
                    //return 25137;
                    return 0;
                }
        }
    }
    //cout << "the size is " << cstack.size() << "\n";
    long long count = 0;
    while (!cstack.empty()){
        cout<<cstack.top()<<" ";
        count = count * 5;
        if (cstack.top() == '(') {
            count += 1;
        }
        if (cstack.top() == '[') {
            count += 2;
        }
        if (cstack.top() == '{') {
            count += 3;
        }
        if (cstack.top() == '<') {
            count += 4;
        }
        cstack.pop();
        //cout << count << "\n";
    }
    cout << "\n";
    return count;
}


int main() {
    string line;
    int count = 0;
    vector<long long> v;
    ifstream myfile("data/10.txt");
    if (myfile)  
    {
        while (getline( myfile, line)) {
            //cout << line << "\n";
            //part1
            //count += parse_line(line); 
            //part2
            long long score = parse_line(line);
            if(score != 0) {
                cout << score << "\n";
                v.push_back(score);
            }
        }
        //part 1
        //cout << count << "\n";

        sort(v.begin(), v.end());

        //for(auto &x : v) {
            //cout << x << "\n";
        //}

        int pos = v.size() / 2;
        cout << "middle is " << v[pos] << "\n";
    }
    else cout << "fooey\n";

    return 0; 

}


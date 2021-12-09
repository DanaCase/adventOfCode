#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include<sstream>
#include <typeinfo>
#include <set>

using namespace std;

vector<string> getCalls(string str) {
    vector<string> v;
    stringstream ss(str);
 
    while (ss.good()) {
        string substr;
        getline(ss, substr, ',');
        v.push_back(substr);
    }
    return v; 
}

vector<string> getBingoLine(string str) {
    vector<string> v;
    stringstream ss(str);

    while(ss.good()) {
        string substr;
        getline(ss, substr, ' ');
        v.push_back(substr);
    }
    return v;
}

int printLastPosCalls(vector<vector<bool>> &lastPosCalls) {
    for(int j=0;j<lastPosCalls.size();j++)
    {
        for(int k=0;k<lastPosCalls[j].size();k++)
        {
            cout<<lastPosCalls[j][k]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}

int printBingoCard(vector<vector<string>> &card, vector<vector<bool>> &posCalls) {
    for(int j=0;j<card.size();j++)
    {
        for(int k=0;k<card[j].size();k++)
        {
            string start = "";
            string end = "";
            string space = "";
            if(card[j][k].size() == 1) {
                space = " ";
            }
            if(posCalls[j][k]) {
                start = "\e[1m";
                end = "\e[0m";
            } 
            cout<<start<<card[j][k]<<end<<space<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return 0;
}

bool checkForBingoShallow(vector<vector<bool>> &x, vector<vector<string>> &y) {
    int foo[5] = {0,0,0,0,0};
    //check horiz
    for (int j = 0; j < 5; j++) {
        int countHoriz = 0;
        for (int k = 0; k < 5; ++k) {
            if (x[j][k] == 1) {
                //cout << "k is " << k << "\n";
                //cout << "positive found at " <<  j << ' ' << k << "\n" << "value is " << y[j][k] << "\n";
                //cout << x[j][k] << " ";
                countHoriz++;
                foo[k]++;
                if(countHoriz == 5) {
                    return 1;
                }
                if(foo[k] == 5) {
                    return 1;
                }
            }
        }
        //cout << "\n";
    }
    return 0;
}

bool checkForBingo(vector<vector<vector<bool>>> &x, vector<vector<vector<string>>> &y) {
    for(int i = 0; i < x.size(); i++) {
        if (checkForBingoShallow(x[i], y[i])) {
            return 1;
        }
    }
    return 0;
}

int getUnmarkedNumbersSum(vector<vector<bool>> &x, vector<vector<string>> &y) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if(x[i][j] == 0) {
                sum += stoi(y[i][j]);
            }
        }
    }
    return sum;
}

int main() {
    string line;
    //bingo card line count
    int i = 0;
    vector<string> calls;
    //internal bingo card line counter
    int j = 0;
    vector<vector<vector<string>>> bingoCards;
    ifstream myfile("data/4.txt");
    if (myfile)  // same as: if (myfile.good())
    {
        while (getline( myfile, line)) {
            //cout << line << "\n";
            if(i == 0) {
                calls = getCalls(line);
                i++;
            }
            else if(line == ""){
                bingoCards.push_back(vector<vector<string>>());
                i++;
                j = 0;
                continue;
            }
            else {
                bingoCards[i - 2].push_back(vector<string>());
                stringstream ss(line);

                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ' ');
                    if (substr != "") {
                        bingoCards[i - 2][j].push_back(substr);
                    }
                }
                j++;
            }
        }
        
        //make another vector of positive calls
        vector<vector<vector<bool>>> posCalls(bingoCards.size(), vector<vector<bool>>(5, vector<bool>(5, 0)));
            
        //for part 2
        for(int c = 0; c < calls.size(); c++) {
            //its at this point I realize I should have made a map of all the numbers and their positions in the bingo cards womp womp
            //for now I will be lame
            string call = calls[c];
            cout << "call is " << call << "\n";
            for(int ii = 0; ii < bingoCards.size(); ii++){
                for (int jj = 0; jj < bingoCards[0].size(); jj++) {
                    for (int kk = 0; kk < bingoCards[0][0].size(); kk++) {
                        if(bingoCards[ii][jj][kk] == call) {
                            posCalls[ii][jj][kk] = 1;

                            //printLastPosCalls(posCalls[ii]);
                            //printBingoCard(bingoCards[ii], posCalls[ii]);
                            bool bingo = checkForBingo(posCalls, bingoCards);
                            if(bingo) {
                                cout << "BINGO!" << "\n";
                                //int sum = getUnmarkedNumbersSum(posCalls[ii], bingoCards[ii]);
                                //cout << sum * stoi(call) << "\n";
                                //uncomment this out for part 1
                                //return 0;

                                printBingoCard(bingoCards[ii], posCalls[ii]);

                                cout << "winning board is " << ii <<  " at call " << call << "\n";
                                int sum = getUnmarkedNumbersSum(posCalls[ii], bingoCards[ii]);
                                cout << "last called num " << call << "\n";
                                cout << "sum is " << sum << "\n";
                                cout << sum * stoi(call) << "\n";

                                bingoCards.erase(bingoCards.begin() + ii);
                                posCalls.erase(posCalls.begin() + ii);
                        }
                    }
                }

                }
            }
        }
    }
    else cout << "fooey\n";

    return 0; 

}

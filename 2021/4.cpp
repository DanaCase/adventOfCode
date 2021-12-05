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

bool checkForBingoShallow(vector<vector<bool>> &x, vector<vector<string>> &y) {
    int foo[5] = {0,0,0,0,0};
    //check horiz
    for (int j = 0; j < 5; j++) {
        int countHoriz = 0;
        for (int k = 0; k < 5; ++k) {
            if (x[j][k] == 1) {
                //cout << "k is " << k << "\n";
                //cout << "positive found at " <<  j << ' ' << k << "\n" << "value is " << y[j][k] << "\n";
                cout << x[j][k] << " ";
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
        cout << "\n";
    }
    return 0;
}

bool checkForBingo(vector<vector<vector<bool>>> &x, vector<vector<vector<string>>> &y) {
    for(int i = 0; i < x.size(); i++) {
        //vert vector
        int foo[5] = {0,0,0,0,0};
        //check horiz
        for (int j = 0; j < 5; j++) {
            int countHoriz = 0;
            for (int k = 0; k < 5; ++k) {
                if (x[i][j][k] == 1) {
                    //cout << "k is " << k << "\n";
                    //cout << "positive found at " << i << " " << j << ' ' << k << "\n" << "value is " << y[i][j][k] << "\n";
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
                //cout << "first call " << calls[0] << "\n";
                i++;
            }
            else if(line == ""){
                //cout << "new card" << "\n";
                
                //vector<vector<string>> v2d(5);
                bingoCards.push_back(vector<vector<string>>());
                i++;
                j = 0;
                continue;
            }
            else {
                //cout << "first num in bingo line " << getBingoLine(line)[0] << "\n";
                //cout << i << " " << j << "\n";
                // ok why do I seg fault here the second time?
                bingoCards[i - 2].push_back(vector<string>());
                stringstream ss(line);

                while (ss.good()) {
                    string substr;
                    getline(ss, substr, ' ');
                    if (substr != "") {
                        //cout << "substr is " << substr << "\n";
                        bingoCards[i - 2][j].push_back(substr);
                    }
                }
                j++;
                //bingoCards[i].push_back(v);
            }
        }
        //cout <<  "made it " << "\n";
        //cout << bingoCards[0][0][0] << "\n";
        
        //make another vector of positive calls
        vector<vector<vector<bool>>> posCalls(bingoCards.size(), vector<vector<bool>>(5, vector<bool>(5, 0)));
            
        //for part 2
        //pair is board
        set<int> winningBoardsSet;
        vector<int> winningBoards;
        for(int c = 0; c < calls.size(); c++) {
            //its at this point I realize I should have made a map of all the numbers and their positions in the bingo cards womp womp
            //for now I will be lame
            string call = calls[c];
            //cout << bingoCards.size() << "\n";
            for(int ii = 0; ii < bingoCards.size(); ii++){
                for (int jj = 0; jj < bingoCards[0].size(); jj++) {
                    //cout << bingoCards[0][0].size();
                    //cout << "checking bingo  card value " << bingoCards[ii][jj][0] << "\n";
                    for (int kk = 0; kk < bingoCards[0][0].size(); kk++) {
                        if(bingoCards[ii][jj][kk] == call) {
                            //cout << "thats a good sign " << bingoCards[ii][jj][kk] << " matches call " << call << "at" << ii << jj << kk << "\n";
                            posCalls[ii][jj][kk] = 1;
                            bool bingo = checkForBingo(posCalls, bingoCards);
                            if(bingo) {
                                cout << "BINGO!" << "\n";
                                int sum = getUnmarkedNumbersSum(posCalls[ii], bingoCards[ii]);
                                cout << sum * stoi(call) << "\n";
                                //uncomment this out for part 1
                                //return 0;
                                
                                //if the winning board is not yet recorded, add it to the vector so its position is reccorded
                                //check for existance
                                if (winningBoardsSet.count(ii) == 0) {
                                    winningBoards.push_back(ii);
                                    cout << "winning board is " << ii << "\n";
                                }
                                winningBoardsSet.insert(ii);
                            }
                        }
                    }
                }
            }
        }
            // last winning board is
            cout << "winning boards set sise " << winningBoardsSet.size() << "\n";
            cout << "winning boards vector size "  << winningBoards.size() << "\n";
            for (int a=0; a < winningBoards.size(); a++) {
                cout << winningBoards[a] << "\n";
                // this is a weird hack because I dont understand the below segfault
                if (a == winningBoards.size() -1 ) {
                    cout << "last board to win is " << winningBoards[a] << "\n";
                    int winningBoardPos = winningBoards[a];
                     //ok now recalculate what the uncalled numbers would be
                    vector<vector<bool>> lastPosCalls(5, vector<bool>(5, 0));
                    printLastPosCalls(lastPosCalls);
                    for(int cc = 0; cc < calls.size(); cc++) {
                        string ccall = calls[cc];
                        for (int iii = 0; iii < 5; iii++) {
                            for (int jjj = 0; jjj < 5; jjj++) {
                                if(bingoCards[winningBoardPos][iii][jjj] == ccall) {
                                    cout << ccall << " matches " << bingoCards[winningBoardPos][iii][jjj] << "\n";
                                    lastPosCalls[iii][jjj] = 1;
                                    printLastPosCalls(lastPosCalls);
                                    bool bingo = checkForBingoShallow(lastPosCalls, bingoCards[winningBoardPos]);
                                    if(bingo) {
                                        cout << "LAST BINGO!" << "\n";
                                        int sum = getUnmarkedNumbersSum(lastPosCalls, bingoCards[winningBoardPos]);
                                        cout << "last ccalled num " << ccall << "\n";
                                        cout << sum * stoi(ccall) << "\n";
                                        return 0;
                                    }
                                }
                            } 
                        }
                    }

                }
            }
            //why on earth does this segfault when the above doesnt?
            int size = winningBoards.size();
            //cout << winningBoards.size();
            //cout << size << "\n";
            //cout << "why does this seg fault? " << winningBoards[size -1] << "\n";
            
            //ok now recalculate what the uncalled numbers would be
            //vector<vector<bool>> lastPosCalls(5, vector<bool>(5, 0));
            //for(int cc = 0; cc < calls.size(); cc++) {
                //string call = calls[cc];
                //for (int iii = 0; iii < 5; iii++) {
                    //for (int jjj = 0; jjj < 5; jjj++) {
                        //if(bingoCards[it][iii][jjj] == call) {
                            //lastPosCalls[iii][jjj] = 1;
                            //bool bingo = checkForBingoShallow(lastPosCalls, bingoCards[it]);
                            //if(bingo) {
                                //cout << "LAST BINGO!" << "\n";
                                //int sum = getUnmarkedNumbersSum(lastPosCalls, bingoCards[it]);
                                //cout << "last called num " << call << "\n";
                                //cout << sum * stoi(call) << "\n";
                                //return 0;
                            //}
                        //}
                    //} 
                //}
            //}
        //}
    }
    else cout << "fooey\n";

    return 0; 

}

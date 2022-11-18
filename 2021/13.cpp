#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;
using std::map;

int largestx = 0;
int largesty = 0;
vector<pair<int, int> > coords;

vector<pair<string, int> > instructions;

void handleFold(string instruction) {
    int xpos = instruction.find("x");
    int ypos = instruction.find("y");
    if(string::npos != instruction.find("x") ) {
        int x = stoi(instruction.substr(xpos+2));
        //cout << x << "\n";
        instructions.push_back(pair<string, int> ("x", x));
    }
    if(string::npos != instruction.find("y") ) {
        int y = stoi(instruction.substr(ypos+2));
        cout << "y: " << y << "\n";
        instructions.push_back(pair<string, int> ("y", y));
    }
}

void parse_line(string line) {
    stringstream ss(line);
    vector<int> coord;
    while (ss.good()) {
        try {
            string substr;
            getline(ss, substr, ',');
            //cout << substr << "\n";
            int i = stoi(substr);
            coord.push_back(i);
        }
        catch (exception &err) {
            handleFold(line);
        }
    }
    if (coord.size() == 2) {
        //cout << "x coord: " << coord[0] << "\n";
        coords.push_back(pair<int, int>(coord[0], coord[1]));
        if(coord[0] > largestx) {
            largestx = coord[0];
        }
        if(coord[1] > largesty) {
            largesty = coord[1];
        }
    }
}

void countDots(vector<vector<int> >& sheet) {
    int count = 0;
    //print each line...that is each member of y for a given x
    for(int y = 0; y < sheet[0].size(); y++) {
        for(int x = 0; x < sheet.size(); x++)
            //cout << x ;
            if(sheet[x][y] == 1){
                cout << '#';
                count++;
            }
            else {
                cout << '.';
            }
        cout << "\n";
    }
    cout << "dots found: " << count << "\n";
}

vector<vector<int> > fold(vector<vector<int> > sheet, pair<string, int> instruction) {
    if(instruction.first == "x") {
        int workingx = largestx - instruction.second - 1;
        vector<vector<int> > newSheet(workingx, vector<int>(largesty, 0));
        for(int i=0; i < workingx; i++) {
            newSheet[i] = sheet[i];
            vector<int> insert = sheet[sheet.size() - 1 - i];
            for(int j = 0; j < insert.size(); j++) {
                if (insert[j] == 1) {
                    newSheet[i][j] = 1;
                }
            }
        }
        largestx = workingx;
        return newSheet;
    }
    
    if(instruction.first == "y") {
        int workingy = largesty - instruction.second - 1;
        vector<vector<int> > newSheet(largestx, vector<int>(workingy, 0));
        for(int i=0; i < largestx; i++) {
            vector<int> insert(workingy);
            for(int j=0; j <= workingy; j++) {
                //extra -1 because of the fold
                if (sheet[i][j] == 1 || sheet[i][largesty - 1 - j] == 1) {
                    newSheet[i][j] = 1;
                }
            }
        }
        largesty = workingy;
        return newSheet;
    }
}


int main() {
    string line;
    ifstream myfile( "data/13.txt");
    if (myfile)
    {
        while (getline( myfile, line)) {
            parse_line(line); 
        }
        myfile.close();

        largestx++;
        largesty++;
        
        vector<vector<int> > sheet(largestx, vector<int>(largesty, 0));

        for (pair<int, int> i : coords) {
            sheet[i.first][i.second] = 1;
        }
        
        //sheet[0][6] = 1;
    
        countDots(sheet);

        sheet = fold(sheet, instructions[0]);

        countDots(sheet);

        //sheet = fold(sheet, instructions[1]);

        //countDots(sheet);
        
    }
    else cout << "fooey\n";

    return 0; 
}

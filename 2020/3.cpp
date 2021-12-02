#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int countTrees(string line, int i, int slopea, int slopeb, int linelength) {
    int count = 0;
    int j = 0;
    char test{'#'};

    j = ((i / slopeb) * slopea) % (linelength + 1);
    if(slopeb == 2) {
        cout << "j " << j << " i " << i << "\n";
    }
    if(line.at(j) == test) {
        count++;
    }

    return count;
}

int main() {
    int i = 0;
    string line;
    ifstream file( "3input.txt");
    unsigned long long c1 = 0;
    unsigned long long c2 = 0;
    unsigned long long c3 = 0;
    unsigned long long c4 = 0;
    unsigned long long c5 = 0;
    unsigned long long output;
    if (file)
    {
        while (getline(file, line)) {
            if(i == 0) {
                i ++;
                continue;
            }
            c1 += countTrees(line, i, 1, 1, 30);
            c2 += countTrees(line, i, 3, 1, 30);
            c3 += countTrees(line, i, 5, 1, 30);
            c4 += countTrees(line, i, 7, 1, 30);
            if (i % 2 == 0) {
                c5 += countTrees(line, i, 1, 2, 30);
                cout << c5 << "\n";
            }
            i++;
        }
        output = c1 * c2 * c3 * c4 * c5;
        cout << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << "\n";
        cout << output <<  "\n";
        cout << to_string(output) << "\n";
        file.close();
    }
    else cout << "fooey\n";

    return 0; 

}

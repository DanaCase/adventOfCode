#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;
using std::map;

typedef struct {
    string name;
    bool visited;
    bool small;
} enode;

//adjacency list
map<string, vector<enode> > adj;


void addEdge(map<string, vector<enode> >& adj, string u, string v, bool smallu, bool smallv)
{
    enode nodev = {name: v, visited: false, small: smallv };
    enode nodeu = {name: u, visited: false, small: smallu };
    adj[u].push_back(nodev);
    adj[v].push_back(nodeu);
}

bool isSmall(string s) {
    if (s == "start" || s == "end") {
        return true;
    }
    if (islower(s[0])) {
        return true;
    }
    return false;
}

void parse_line(string line) {
    stringstream ss(line);
    vector<string> edge;
    while (ss.good()) {
        string substr;
        getline(ss, substr, '-');
        edge.push_back(substr);
    }
    bool smallu = isSmall(edge[0]);
    bool smallv = isSmall(edge[1]);

    addEdge(adj, edge[0], edge[1], smallu, smallv);
}

void search(enode node, map<string, bool> m, vector<enode> path, vector<vector<enode> >& paths) {
    cout << "working on node: " << node.name << "\n";
    path.push_back(node);
    cout << "current path size: " << path.size() << "\n";
    if (node.small) {
        m[node.name] = true;
    }
    if (node.name == "end"){
        paths.push_back(path);
        cout << path.size() << "\n";
        return;
    }
    for(int i = 0; i < adj[node.name].size(); ++i) {
       //cout << node.name;
        cout << adj[node.name].size();
        enode checknode = adj[node.name][i];
        //not over visited
        if (!m[checknode.name]) {
            search(checknode, m, path, paths);
        }
    }
}

int main() {
    string line;
    ifstream myfile( "data/12.txt");
    if (myfile)
    {
        while (getline( myfile, line)) {
            parse_line(line); 
        }
        myfile.close();

        cout << adj.size() << "\n";

        vector<vector<enode> > paths;
        map<string, bool> visited;

        enode start = {.name = "start", .visited = true, .small = true};
        vector<enode> path;

        search(start, visited, path, paths);
        
        cout << "paths size: " << paths.size() << "\n";

    }
    else cout << "fooey\n";

    return 0; 
}

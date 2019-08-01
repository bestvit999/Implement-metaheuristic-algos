#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> getfile(string path_to_file){
    ifstream input;
    string line;
    vector<int> file;
    input.open(path_to_file);
    while(!input.eof()){
        input >> line;
        file.push_back(stoi(line));
    }
    return file;
}
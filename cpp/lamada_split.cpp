#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string teststr="abc def ghi jkl";
    char blank = ' ';
    vector<string> result;
    auto split = [&]{
       string::size_type pos1, pos2;
        pos2 = teststr.find(blank);
        pos1 = 0;
        while(string::npos != pos2){
            result.push_back(teststr.substr(pos1, pos2-pos1));
            pos1 = pos2 + 1;
            pos2 = teststr.find(blank, pos1);
        }
        result.push_back(teststr.substr(pos1));
    };
    split();
    for(int i =0; i<result.size(); ++i)
        cout<< result[i] << endl;
    return 0;
}

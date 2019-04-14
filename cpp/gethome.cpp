#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

int main(){

    const char* homeDir = getenv("HOME");
    std::cout << homeDir << std::endl;
    std::string file("hax");
    std::stringstream ss;
    ss << homeDir << "/Pictures/path_"<<file<<".png";
    std::string dir;
    ss >> dir;
    std::cout << dir << std::endl;
    return 0;
}

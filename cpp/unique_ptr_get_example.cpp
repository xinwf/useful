#include <iostream>
#include <string>
#include <memory>

void change(std::string * s){
    *s = "content has been modified!";
}
 
int main()
{
    std::unique_ptr<std::string> s_p(new std::string("Hello, world!"));
    change(s_p.get());
    std::string *s = s_p.get();
    std::cout << *s << '\n';
}

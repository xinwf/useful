#include <iostream>
#include <chrono>
#include <thread>

int main(){
    auto start = std::chrono::system_clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end = std::chrono::system_clock::now();
    auto int_s = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout<<int_s.count()<<std::endl;
    
}

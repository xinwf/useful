#include <iostream>
#include <vector>

using namespace std;

/*
给定一个正整数，检查他是否为交替位二进制数：换句话说，
就是他的二进制数相邻的两个位数永不相等。
*/
bool hasAlternatingBits(int n){
    std::string str1;
    str1 = n % 2;
    while(n!=0){
        n = n >> 1;
        str1 += std::to_string(n%2);
    }
    std::string str2 = str1.substr(0, str1.size()-1);
    std::string str3;
    for(int i=0; i<str1.size(); ++i){
        if(i%2==0)
            str3 += str1[i];
        else
            str3 += str2[i-1];
    }
    if(str3.find('0') ==std::string::npos) 
        return true;
    else    
        return false;
}

/*
给定一个整数数组和一个整数k，你需要找到该数组中和为 k 的连续的子数组的个数。
*/
int subarraySum(vector<int>& nums, int k) {

}

int main()
{
    return 0;
}
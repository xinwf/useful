#include <iostream>
#include <vector>

using namespace std;

// bubble sort
void bubble(vector<int> vec)
{
    int temp;
    for(int i = 0; i < vec.size(); ++i){
        for(int j = 0; j < vec.size() - i -1; ++j){
            if(vec[j]>vec[j+1]){
                temp = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = temp;
            }
        }
    }
    cout << "sorted(bubble): ";
    for(int i=0; i<vec.size();++i) cout << vec[i] <<" ";
    cout <<"\n";
}

// selection sort
void selection(vector<int> vec)
{
    vector<int> sorted;
    int index = 0, max = 0;
    while(vec.size()>0){
        max = 0;
        index = 0;
        for(int i=0; i<vec.size(); ++i){
            if(vec[i]>max){
                max = vec[i];
                index = i;
            }
        }
        sorted.insert(sorted.begin(), max);
        vec.erase(vec.begin()+index);
    }
    cout << "sorted(selection): ";
    for(int i=0; i<sorted.size();++i) cout << sorted[i] <<" ";
    cout <<"\n";
}

// insertion sort
void insertion(vector<int> vec)
{
    for(int i=1; i<vec.size(); ++i){
        int j = i - 1;
        int current = vec[i];
        while (j>=0 && vec[j]>current)
        {
            vec[j+1] = vec[j];
            j = j - 1;
        }
        vec[j+1] = current;
    }
    cout << "sorted(insertion): ";
    for(int i=0; i<vec.size();++i) cout << vec[i] <<" ";
    cout <<"\n";
}

int main()
{

    std::vector<int> intv1 {2, 32, 45, 12, 24, 8, 19, 36};
    // std::vector<int> intv2(intv1);
    
    cout << "origin: ";
    for(int i=0; i<intv1.size();++i) cout << intv1[i] <<" ";
    cout <<"\n";

    bubble(intv1);
    selection(intv1);
    insertion(intv1);
    return 0;
}
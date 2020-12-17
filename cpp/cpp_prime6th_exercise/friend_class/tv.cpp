#include "tv.h"

#include <iostream>

bool Tv::Volup()
{
    if (volume_ < MaxVal){
        volume_ ++;
        return true;
    }else{
        return false;
    }
    
}

bool Tv::Voldown()
{
    if (volume_ > MinVal){
        volume_ --;
        return true;
    }else{
        return false;
    }
}

void Tv::Chanup()
{
    if (channel_ < maxChannel_)
        channel_ ++;
    else
        channel_ = 1;
}

void Tv::Chandown()
{
    if (channel_ > 1)
        channel_ --;
    else
        channel_ = maxChannel_;
}

void Tv::Settings() const
{
    using std::cout;
    using std::endl;

    cout << "TV is " << (state_ == Off? "Off" : "On") << endl;
    if (state_ == On){
        cout << "Volume setting = " << volume_ << endl;
        cout << "Channel setting = " << channel_ << endl;
        cout << "Mode = " << (mode_ == Antenna? "Antenna": "Cable") << endl;
        cout << "Input = " << (input_ == TV? "TV" : "DVD") << endl;
    }
}
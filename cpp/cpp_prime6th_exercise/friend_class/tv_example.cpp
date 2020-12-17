#include "tv.h"

#include <iostream>

int main()
{
    using std::cout;
    Tv s42;
    cout << "Initial settings for 42\" TV: \n";
    s42.Settings();
    s42.OnOff();
    s42.Chanup();
    cout << "\nAdjusted settings for 42\" TV: \n";
    s42.Chanup();
    cout << "\nAdjusted settings for 42\" TV: \n";
    s42.Settings();

    Remote grey;
    grey.SetChan(s42, 10);
    grey.Volup(s42);
    grey.Volup(s42);
    cout << "\n42\" settings after using remote:\n";
    s42.Settings();

    Tv s58(Tv::On);
    s58.SetMode();
    grey.SetChan(s58, 28);
    cout << "\n58\" settings:\n";
    s58.Settings();
    return 0;
}
#ifndef TV_H_
#define TV_H_
class Tv
{

public:
    friend class Remote;
    enum {Off, On};
    enum {MinVal, MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};
    Tv(int s = Off, int mc = 125) : state_(s), volume_(5),
        maxChannel_(mc), channel_(2), mode_(Cable), input_(TV) {}
    
    void OnOff() {state_ = (state_ == On)? Off : On;}
    bool IsOn() const {return state_ == On;}
    bool Volup();
    bool Voldown();
    void Chanup();
    void Chandown();
    void SetMode() {mode_ = (mode_ == Antenna)? Cable : Antenna;}
    void SetInput() {input_ = (input_ == TV)? DVD : TV;}
    void Settings() const;
private:
    int state_;
    int volume_;
    int maxChannel_;
    int channel_;
    int mode_;
    int input_;
};

class Remote
{

public:
    Remote(int m = Tv::TV) : mode_(m) {}
    bool Volup(Tv &t) {return t.Volup();}
    bool Voldown(Tv &t) {return t.Voldown();}
    void OnOff(Tv &t) {t.OnOff();}
    void Chanup(Tv &t) {t.Chanup();}
    void Chandown(Tv &t) {t.Chandown();}
    void SetChan(Tv &t, int c) {t.channel_ = c;}
    void SetMode(Tv &t) {t.SetMode();}
    void SetInput(Tv &t) {t.SetInput();}
private:
    int mode_;
};

#endif
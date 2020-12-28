#include <iostream>
#include <cstdio>
#include <cstring>

/*
 * This example is used to show the conception of bitwise constness and logical constness.
 * 
 * bitwise constness: 
 */

class TextBlock
{

public:
    TextBlock(/* args */);
    TextBlock(const char *data);
    char* getData() const;
    ~TextBlock();
private:
    char *pText_;
};

TextBlock::TextBlock(/* args */)
{
}

TextBlock::TextBlock(const char *data)
{
    pText_ = new char [sizeof(*data)];
    strcpy(pText_, data);
}

TextBlock::~TextBlock()
{
    delete [] pText_;
    pText_ = nullptr;
}

char* TextBlock::getData() const
{
    if(pText_ == nullptr)
        return nullptr;
    else{
        char *tmp = &pText_[0];
        *tmp = 'J';
        return pText_;
    }
}

int main()
{
    TextBlock tb("Hello world");
    std::cout << tb.getData() << std::endl;;
    return 0;
}
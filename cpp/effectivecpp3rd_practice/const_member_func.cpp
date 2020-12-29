#include <iostream>
#include <cstdio>
#include <cstring>

/*
 * This example is used to show the conception of bitwise constness and logical constness.
 * 
 * bitwise constness: This camp believes that a member function if and only if
 * it dosen't modify any of the object's data(excluding those that are static) members,
 * if it dosen't modify any of the bits inside the object.
 * 
 * logical constness: A const member function might modify some of the bits in object on 
 * which it's invoked, but only in ways that clients cannot detect.
 * 
 * The function getData in class TextBlock is only to expound this problem, length function
 * is used to expound the logical constness, data can be modified in const member function
 * with mutable keyword.
 * 
 * Subsequently, we use the operator[] to provide data access functions for const and non-
 * const objects without duplicated codes.
 */

class TextBlock
{

public:
    TextBlock(/* args */);
    TextBlock(const char *data);
    char* getData() const;
    ~TextBlock();
    std::size_t length() const;
    const char& operator[] (std::size_t pos) const;
    char& operator[] (std::size_t pos);
private:
    char *pText_;
    mutable std::size_t textLength_;
    mutable bool lengthIsValid_;
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

const char& TextBlock::operator[] (std::size_t pos) const
{
    std::cout << "const []\n";
    if (pos<0 || pos>(std::strlen(pText_)-1)) return '*';
    return pText_[pos];
}

char& TextBlock::operator[] (std::size_t pos)
{
    std::cout << "normal []\n";
    return const_cast<char&>(
        static_cast<const TextBlock&>(*this)[pos]
    );
}

std::size_t TextBlock::length() const
{
    if (!lengthIsValid_){
        textLength_ = std::strlen(pText_);
        lengthIsValid_ = true;
    }
    return textLength_;
}

int main()
{
    TextBlock tb("Hello world");
    std::cout << tb.getData() << std::endl;
    std::cout << "Data length: " << tb.length() << "\n";
    std::cout << tb[3] << "\n";
    const TextBlock ctb("Jennie.");
    std::cout << ctb[3] << "\n";
    return 0;
}
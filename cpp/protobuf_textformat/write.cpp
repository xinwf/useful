#include "test.pb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <cstdio>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
 
using namespace std;
int main(int argc, char** argv){
    if (argc <2){
        printf("programe savefile\n");
        exit(1);
    }
 
    //声明一个class结构
    classes c;
    c.set_name("Communication 2004");
    //添加学生
    student* t = c.add_member();
    t->set_name("flyan338");
    t->set_age(26);
    t->set_addr("china");
    
    t = c.add_member();
    t->set_name("likeliu");
    t->set_age(25);
    t->set_addr("china");
 
    t = c.add_member();
    t->set_name("gaoy");
    t->set_age(24);
    t->set_addr("American");
 
 
    //首先将protobuf输出到一个string中
    std::string p;
    google::protobuf::TextFormat::PrintToString(c,&p);
    
    //输出到文件中
    ofstream fout;
    fout.open(argv[1], ios::out| ios_base::ate);
    if (!fout.is_open()){
        fprintf(stderr, "open %s fail\n", argv[1]);
        return -1;
    }
    fout <<p<<endl;
    fout.flush();
    fout.close();
 
    return 0;
}


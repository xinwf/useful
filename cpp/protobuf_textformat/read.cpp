#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fcntl.h>
#include <fstream>
#include <cstdio>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "test.pb.h"
 
using namespace std;
int main(int argc, char** argv){
    if (argc <2){
        printf("programe reloadfile\n");
        exit(1);
    }
 
    classes c;
    int fileDescriptor = open(argv[1], O_RDONLY);
    if( fileDescriptor < 0 ){
        return -1;
    }
    google::protobuf::io::FileInputStream fileInput(fileDescriptor);
    fileInput.SetCloseOnDelete( true );
    if (!google::protobuf::TextFormat::Parse(&fileInput, &c)){
        return -2;
    }
    cout<<"classes name:" <<c.name() <<endl;
    cout<<"student number:"<<c.member_size()<<endl;
    for (int i = 0 ; i < c.member_size(); i++){
        cout <<"student name:"<<c.member(i).name()<<endl;
        cout <<"student age:" << c.member(i).age()<<endl;
        cout <<"student addr:" << c.member(i).addr() <<endl;
    }
    return 0;
}
 


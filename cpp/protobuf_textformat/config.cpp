#include <stdlib.h>  
#include <stdio.h>  
#include <errno.h>
#include <string.h>  
#include <iostream>  
#include <fcntl.h>  
#include <fstream>  
#include <cstdio>  
#include <google/protobuf/text_format.h>  
#include <google/protobuf/io/zero_copy_stream_impl.h>
 
#include "config.pb.h"

using namespace std;
 
void save_config(string &file_name, string &contect)
{
    ofstream fout;
    fout.open(file_name.c_str(), ios::out| ios_base::ate);
 
    if (!fout.is_open()) {
        fprintf(stderr, "open config.cfg fail\n");
        exit(-1);
    }
 
    fout << contect <<endl;
    fout.flush();
    fout.close(); 
}
 
void load_config(string &file_name, config::Configure &config)
{
    int fd = open("config.cfg", O_RDONLY);
 
    if (fd < 0) {
        printf("open config.cfg failure:%s \n",strerror(errno));
        exit(-1);
    }
 
    google::protobuf::io::FileInputStream fileInput(fd);
    fileInput.SetCloseOnDelete(true);
    google::protobuf::TextFormat::Parse(&fileInput, &config);  
}
 
int main(void)
{
    config::Configure config;
    config.set_host("127.0.0.1");
    config.set_port(8080);
 
    string contect;
    google::protobuf::TextFormat::PrintToString(config, &contect);
    
    string file_name = "config.cfg";
    save_config(file_name, contect);    
 
    cout << "\n---------Save config done.-----------\n" << endl;
 
    config::Configure config2;
    load_config(file_name, config2);
 
    cout << "host: " << config2.host() << endl;
    cout << "port: " << config2.port() << endl;
 
    cout << "\n---------Load config done.-----------\n" << endl;
    return 0;
}

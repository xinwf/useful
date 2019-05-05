#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>  
 
using namespace std;   
using namespace cv;  
 
int main(int argc,char *argv[])    
{ 
    Mat A=Mat::ones(2,3,CV_32FC1);
    Mat B=Mat::ones(3,2,CV_32FC1);
    Mat C=Mat::ones(2,3,CV_32FC1);
    Mat D=Mat::ones(3,1,CV_32FC1);
    Mat AB;
    Mat CD;
 
    A.at<float>(0,0)=1;
    A.at<float>(0,1)=2;
    A.at<float>(0,2)=3;
    A.at<float>(1,0)=4;
    A.at<float>(1,1)=5;
    A.at<float>(1,2)=6;
 
    B.at<float>(0,0)=1;
    B.at<float>(0,1)=2;
    B.at<float>(1,0)=3;
    B.at<float>(1,1)=4;
    B.at<float>(2,0)=5;
    B.at<float>(2,1)=6;
 
    AB=A*B;
 
    cout<<"A=\n"<<A<<endl<<endl;
    cout<<"B=\n"<<B<<endl<<endl;
    cout<<"AB=\n"<<AB<<endl<<endl;

    C.at<float>(0,0)=0.06867806607502848;
    C.at<float>(0,1)=0.9976388741624868;
    C.at<float>(0,2)=-50.42805649738955;
    C.at<float>(1,0)=-0.9976388741624868;
    C.at<float>(1,1)=0.06867806607502848;
    C.at<float>(1,2)=543.973370526209;

    D.at<float>(0,0)=244;
    D.at<float>(1,0)=277;
    D.at<float>(2,0)=1;

    CD=C*D;
 
    cout<<"C=\n"<<C<<endl<<endl;
    cout<<"D=\n"<<D<<endl<<endl;
    cout<<"CD=\n"<<CD<<endl<<endl;

}

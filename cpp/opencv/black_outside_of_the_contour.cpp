#include <string>
#include <iostream>    
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;    
int main(int argc, char* argv[])
{
    cv::Mat im_source_non_square = cv::imread("/home/mate/Pictures/3.png", CV_LOAD_IMAGE_COLOR);
    cv::namedWindow("Image",CV_WINDOW_FREERATIO);
    cv::imshow("Image", im_source_non_square);
    Mat im_source_square;
    int m_nCenterX=220;
    int m_nCenterY=280;
    int m_nRadius=40;
    
    Mat im_mask=im_source_non_square.clone();
    im_mask.setTo(cv::Scalar(0,0,0));
    circle( im_mask, cv::Point(m_nCenterX,m_nCenterY), m_nRadius, cv::Scalar(255,255,255), -3, 8, 0 );
    cv::namedWindow("Mask image",CV_WINDOW_FREERATIO);
    cv::imshow("Mask image", im_mask);
    Mat im_source_circle;
    cv::bitwise_and(im_source_non_square,im_mask,im_source_circle);
    cv::namedWindow("Combined image",CV_WINDOW_FREERATIO);
    cv::imshow("Combined image", im_source_circle);

    cv::vector<Point> myContour;
    myContour.push_back(Point(140, 180));
    myContour.push_back(Point(180, 180));
    myContour.push_back(Point(180, 220));
    myContour.push_back(Point(140, 220));
    cv::Rect rect(140,180,150,150);
    // Mat mask=cv::Mat::zeros(im_source_non_square.size(), CV_8UC1);
    // cv::drawContours(mask, myContour, 0, Scalar(255), CV_FILLED);
    Mat mask=im_source_non_square.clone();
    mask.setTo(cv::Scalar(0,0,0));

    cv::rectangle(mask, rect, Scalar(255,255,255), CV_FILLED);
    cv::bitwise_and(im_source_non_square,mask, im_source_square);
    cv::namedWindow("Combined image2",CV_WINDOW_FREERATIO);
    cv::imshow("Combined image2", im_source_square);
    
    cv::waitKey(0);
    return 0;
}
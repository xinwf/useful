#include <cv.h>
#include <highgui.h>
int main()
{
    cv::Mat input = cv::imread("rotateObjects_input.png");

    std::vector<cv::Point> myContour;
    myContour.push_back(cv::Point(100,100));
    myContour.push_back(cv::Point(150,100));
    myContour.push_back(cv::Point(150,300));
    myContour.push_back(cv::Point(100,300));

    cv::Point2f cog(0,0);
    for(unsigned int i=0; i<myContour.size(); ++i)
    {
        cog = cog + cv::Point2f(myContour[i].x, myContour[i].y);
    }
    cog = 1.0f/(float)myContour.size()*cog;

    std::cout << "center of gravity: " << cog << std::endl;


    // create and draw mask
    cv::Mat mask = cv::Mat::zeros(input.size(), CV_8UC1);
    cv::fillConvexPoly(mask,myContour,255);

    // create rotation mat
    float angleDEG = 45;
    cv::Mat transformation = cv::getRotationMatrix2D(cog,angleDEG,1);
    std::cout << transformation << std::endl;

    // rotated mask holds the object position after rotation
    cv::Mat rotatedMask;
    cv::warpAffine(mask,rotatedMask,transformation,input.size());
    cv::Mat rotatedInput;
    cv::warpAffine(input,rotatedInput,transformation, input.size());

    cv::imshow("input",input);
    //cv::imshow("rotated input",rotatedInput);
    //cv::imshow("rotated mask",rotatedMask);

    // copy rotated object to original image:
    cv::Mat output = input.clone();
    rotatedInput.copyTo(output, rotatedMask);

    //cv::imwrite("rotateObjects_beforeHolefilling.png", output);

    // now there are pixel left from the old object position.
    cv::Mat holePixelMask = mask & (255-rotatedMask);
    // we have to fill those pixel with some kind of background...
    cv::Mat legalBackground = (255-mask);
    //cv::erode(legalBackground,)

    // fill holes. here you could try to find some better background color by averaging in neighborhood or sth.
    cv::Vec3b lastLegalPixel(0,0,0);
    for(unsigned int j=0; j<mask.rows; ++j)
        for(unsigned int i=0; i<mask.cols; ++i)
        {
            if(holePixelMask.at<unsigned char>(j,i))
            {
                output.at<cv::Vec3b>(j,i) = lastLegalPixel;
            }
            else
            {
                if(legalBackground.at<unsigned char>(j,i))
                    lastLegalPixel = input.at<cv::Vec3b>(j,i);
            }
        }



    //cv::imshow("holes before filling", holePixelMask);
    //cv::imshow("legal background", legalBackground);

    cv::imshow("result", output);
    cv::imwrite("result.png", output);

    cv::waitKey(-1);
    return 0;
}

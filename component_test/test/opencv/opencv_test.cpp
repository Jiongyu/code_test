#include<opencv2/features2d/features2d.hpp>  
#include<opencv2/opencv.hpp>
 
using namespace cv;
 
int main( int argc, char** argv )
{
    Mat image;
    image = imread("../1.png", 1);
 
    if( argc != 2 || !image.data )
    {
        printf( "No image data \n" );
        return -1;
    }

    // imshow( "Display Image", image );
    // waitKey(0);
 
    return 0;
}
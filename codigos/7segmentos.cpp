#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int top_slider = 10;
int top_slider_max = 200;

char TrackbarName[50];
CvPoint p;
Mat image, thres, element, dilated;

int main(int argc, char**argv){
  int width, height;
  element = getStructuringElement(MORPH_ELLIPSE, Size(4,4));

  //  element = getStructuringElement( MORPH_ELLIPSE, Size( 5,5 ), Point( 2, 2 ) );

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  imshow("cinza", image);
  waitKey(0);
  width=image.size().width;
  height=image.size().height;
  threshold(image,thres,1,255,THRESH_OTSU+THRESH_BINARY_INV);
  p.x=0;
  p.y=0;
  floodFill(thres,p,255);
  imshow("binario", thres);
  waitKey(0);

  dilate(thres,dilated,element);
  //imshow("erode", dilated);
  //waitKey(0);
  //erode(dilated,dilated,element);
  erode(dilated,dilated,element);
  //imshow("dilated1", dilated);
  //waitKey(0);
  erode(dilated,dilated,element);
  //imshow("dilated2", dilated);
  //waitKey(0);
  erode(dilated,dilated,element);
  //imshow("dilated3", dilated);
  //waitKey(0);
  erode(dilated,dilated,element);
  //imshow("dilated4", dilated);
  //waitKey(0);

  dilate(dilated,dilated,element);
  //imshow("erode1", dilated);
  //waitKey(0);
  dilate(dilated,dilated,element);
  //imshow("erode2", dilated);
  //waitKey(0);
  dilate(dilated,dilated,element);
  imshow("final", dilated);
  waitKey(0);

  return 0;
}

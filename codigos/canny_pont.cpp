#include <iostream>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace cv;

#define STEP 5
#define JITTER 3

float gauss[] = {1,2,1,
                 2,4,2,
                 1,2,1};

int main(int argc, char** argv){
  vector<int> yrange;
  vector<int> xrange;
  Mat mask(3,3,CV_32F), mask1;

  Mat image, frame, points, blur, border;

  int width, height, gray;
  int x, y;

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  image.copyTo(blur);
  mask = Mat(3, 3, CV_32F, gauss);
  scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;
  filter2D(image, blur, image.depth(), mask, Point(1,1), 0);
  filter2D(blur, blur, blur.depth(), mask, Point(1,1), 0);
  filter2D(blur, blur, blur.depth(), mask, Point(1,1), 0);
  filter2D(blur, blur, blur.depth(), mask, Point(1,1), 0);

  srand(time(0));

  if(!image.data){
	  cout << "nao abriu" << argv[1] << endl;
    cout << argv[0] << " imagem.jpg";
    exit(0);
  }

  width=image.size().width;
  height=image.size().height;
  xrange.resize(height/STEP);
  yrange.resize(width/STEP);

  iota(xrange.begin(), xrange.end(), 0);
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  blur.copyTo(points);
  random_shuffle(xrange.begin(), xrange.end());

  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      gray = image.at<uchar>(x,y);
      circle(points,cv::Point(y,x),5,CV_RGB(gray,gray,gray),-1,CV_AA);
    }
  }

  waitKey();
  for(int h=1;h<=4;h++){
  Canny(image, border, 50*h, 150*h);
     for(int i=0; i<height; i++ ){
        for(int j=0; j<width; j++){
     	   if(border.at<uchar>(i,j)>0){
     	      gray = image.at<uchar>(i,j);
     	      circle(points, cv::Point(j,i),5-h,CV_RGB(gray,gray,gray),-1,CV_AA);
     	   }
        }
     }
  }

  imshow("saida_canny_pont",points);
  waitKey();

  imwrite("saida_canny_pont.jpg", points);
  return 0;
}

#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, newimage;
  int p1i,p1j,p2i,p2j;
  Vec3b val;
  int width, height;

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu biel.png" << endl;

  width=image.size().width;
  height=image.size().height;

  Mat imgRect1(image, Rect(0,0,width/2-1,height/2-1));
  Mat imgRect2(image, Rect(width/2,0,width-1,height/2-1));
  //Mat imgRect3(image, Rect(height/2,0,height-1,width/2-1));
  //Mat imgRect4(image, Rect(height/2,width/2,height-1,width-1));
  // for(int i=0; i<height; i++){
  //   for(int j=0; j<width; j++){
  //     if(i <=height/2-1 || j<=width/2-1 ){
	//        image.at<uchar>(i,j) = imgRect4.at<uchar>(i,j);
  //     }
  //   }
  // }
  newimage = image.clone();
  imgRect1.copyTo(newimage(Rect(width/2+1,0,imgRect1.size().height,imgRect1.size().width)));
  // imgRect2.copyTo(image);
  namedWindow("Original",WINDOW_AUTOSIZE);
  imshow("Original", imgRect2);
  waitKey();
  namedWindow("Original",WINDOW_AUTOSIZE);
  imshow("Original", imgRect1);
  waitKey();
  namedWindow("Original",WINDOW_AUTOSIZE);
  imshow("Original", newimage);
  waitKey();
  return 0;
}

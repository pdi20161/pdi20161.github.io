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

  Mat imgRect1(image, Rect(0,0,width/2,height/2));
  Mat imgRect2(image, Rect(width/2-1,0,width/2,height/2));
  Mat imgRect3(image, Rect(0,height/2-1,width/2,height/2));
  Mat imgRect4(image, Rect(width/2-1,height/2-1,height/2,width/2));
  newimage = image.clone();

  

  imgRect1.copyTo(newimage(Rect(width/2,0,imgRect1.size().height,imgRect1.size().width)));
  imgRect2.copyTo(newimage(Rect(width/2,height/2,imgRect2.size().height,imgRect2.size().width)));
  imgRect3.copyTo(newimage(Rect(0,height/2,imgRect3.size().height,imgRect3.size().width)));
  imgRect4.copyTo(newimage(Rect(0,0,imgRect4.size().height,imgRect4.size().width)));
  // imgRect2.copyTo(image);
  namedWindow("Original",WINDOW_AUTOSIZE);
  imshow("Original", image);
  namedWindow("rect1",WINDOW_AUTOSIZE);
  imshow("rect1", imgRect1);
  namedWindow("rect2",WINDOW_AUTOSIZE);
  imshow("rect2", imgRect2);
  namedWindow("rect3",WINDOW_AUTOSIZE);
  imshow("rect3", imgRect3);
  namedWindow("rect4",WINDOW_AUTOSIZE);
  imshow("rect4", imgRect4);
  namedWindow("Saida",WINDOW_AUTOSIZE);
  imshow("Saida", newimage);
  waitKey();
  return 0;
}

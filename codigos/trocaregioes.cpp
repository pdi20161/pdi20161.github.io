#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>
#include <chrono>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, newimage;
  Rect alea[4];
  int aleint[4],i=0;
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

  alea[0]=Rect(width/2,0,height/2,width/2);
  alea[1]=Rect(width/2,height/2,height/2,width/2);
  alea[2]=Rect(0,height/2,height/2,width/2);
  alea[3]=Rect(0,0,height/2,width/2);

  std::array<int,4> foo {0,1,2,3};

  // obtain a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));

  std::cout << "shuffled elements:";
  for (int& x: foo){
    aleint[i] = x;
    i++;
  }

    imgRect1.copyTo(newimage(alea[aleint[0]]));
    imgRect2.copyTo(newimage(alea[aleint[1]]));
    imgRect3.copyTo(newimage(alea[aleint[2]]));
    imgRect4.copyTo(newimage(alea[aleint[3]]));

  namedWindow("Saida",WINDOW_AUTOSIZE);
  imshow("Saida", newimage);
  waitKey();
  return 0;
}

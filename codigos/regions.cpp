#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  int p1x, p1y, p2x, p2y;

  cout << "Entre com as coordenadas (x y) do ponto 1: ";
  cin >> p1x >> p1y;

  cout << "Entre com as coordenadas (x y) do ponto 2: ";
  cin >> p2x >> p2y;

  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu biel.png" << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);

  for(int i=p1x;i<p2x;i++){
    for(int j=p1y;j<p2y;j++){
      image.at<uchar>(i,j) = 255 - image.at<uchar>(i,j);
    }
  }

  imshow("janela", image);
  waitKey();
  return 0;
}

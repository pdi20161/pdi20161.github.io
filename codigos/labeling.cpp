#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace cv;
using namespace std;
int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects, nobjecthole;

  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  imshow("original", image);
  waitKey();
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(i == 0 || j == 0 || i== height-1 || j == width-1){
		// achou um objeto
	image.at<uchar>(i,j) = 255;
      }
    }
  }
  imshow("com bordas", image);
  floodFill(image,p,0);
  floodFill(image,p,1);
  // busca objetos com buracos presentes
  nobjects=1;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
		// achou um objeto
		nobjects++;
		p.x=j;
		p.y=i;
		floodFill(image,p,nobjects);
	  }
	}
  }
  imshow("objetos", image);
  imwrite("objetos.png", image);
  waitKey();
  nobjecthole = 0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 0 ){
       	if(image.at<uchar>(i,j-1) != 1){	
       		nobjecthole++;
		p.x=j-1;
		p.y=i;
		floodFill(image,p,1);
		p.x=j;
		p.y=i;
		floodFill(image,p,1);
	 }
       }
     }
  }
  cout<<"Numero de objetos = "<<nobjects-1<<endl;
  cout<<"Numero de objetos com furo = "<<nobjecthole<<endl;
  imshow("furo", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}

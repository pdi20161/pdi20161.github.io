#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double alfa;
int alfa_slider = 0;
int alfa_slider_max = 100;

int width, height;

float gauss[] = {1,2,1,
                 2,4,2,
                 1,2,1};

int center_slider;
int center_slider_max ;

int vertical_slider;
int vertical_slider_max ;

Mat original, desfocada, blended;
Mat desf_cpy;

char TrackbarName[50];
Mat increase_colour_saturation(Mat image)
{
    vector<Mat> planes;
    Mat hsv;
    cvtColor(image, hsv, CV_BGR2HSV);
    Vec3b val;
    for(int i=0;i<hsv.rows;i++){
      for(int j=0;j<hsv.cols;j++){
        int v = hsv.at<Vec3b>(i,j)[1] + 20;
        if(v>255) v= 255;
      	else if(v<0) v= 0;
          hsv.at<Vec3b>(i,j)[1] = v;
      }
    }
    cvtColor(hsv, image, CV_HSV2BGR);
    return image;
}
void on_trackbar_blend(int, void*){
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted(desf_cpy , alfa, original, 1-alfa, 0.0, blended);
 imshow("addweighted", blended);
}

void on_trackbar_vert(int, void*){
  desfocada.copyTo(desf_cpy);
int limit_v = vertical_slider;
  int limit_c = center_slider;
  if(limit_v > 0 && limit_c > 0 && limit_c/2+limit_v<=height && (height-limit_c)/2-(height/2-limit_v)>=0){
    if(limit_v <=height/2){
      Mat tmp = original(Rect(0, (height-limit_c)/2-(height/2-limit_v),width,limit_c));
      
  	  tmp.copyTo(desf_cpy(Rect(0, (height-limit_c)/2-(height/2-limit_v),width,limit_c)));

    }
    else if(limit_v > height/2){
      Mat tmp = original(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c));
      
  	  tmp.copyTo(desf_cpy(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c)));
    }
      on_trackbar_blend(alfa_slider,0);
  }

}

void on_trackbar_center(int, void*){
  desfocada.copyTo(desf_cpy);
    int limit_v = vertical_slider;
  int limit_c = center_slider;
  if(limit_c > 0 && limit_v > 0 && limit_c/2+limit_v<=height && (height-limit_c)/2-(height/2-limit_v)>=0){
    if(limit_v <= height/2){
      Mat tmp = original(Rect(0, (height-limit_c)/2-(height/2-limit_v),width,limit_c));

      tmp.copyTo(desf_cpy(Rect(0, (height-limit_c)/2-(height/2-limit_v),width,limit_c)));

    }
    else if(limit_v > height/2){
      Mat tmp = original(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c));

      tmp.copyTo(desf_cpy(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c)));
    }
    on_trackbar_blend(alfa_slider,0);
  }

}


int main(int argvc, char** argv){
  Mat mask(3,3,CV_32F), mask1;
  original = imread("tiltshift_entrada3.jpg");
  mask = Mat(3, 3, CV_32F, gauss);
  scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;
  filter2D(original, desfocada, original.depth(), mask, Point(1,1), 0);
  filter2D(desfocada, desfocada, desfocada.depth(), mask, Point(1,1), 0);
  filter2D(desfocada, desfocada, desfocada.depth(), mask, Point(1,1), 0);
  desfocada.copyTo(desf_cpy);
  width = original.size().width;
  height = original.size().height;
  original = increase_colour_saturation(original);
  vertical_slider = height/2;
  vertical_slider_max = height;
  center_slider = 0;
  center_slider_max = height;
  namedWindow("addweighted", 1);

  sprintf( TrackbarName, "Alpha x %d", alfa_slider_max );
  createTrackbar( TrackbarName, "addweighted",
				  &alfa_slider,
				  alfa_slider_max,
				  on_trackbar_blend );
  on_trackbar_blend(alfa_slider, 0 );

  sprintf( TrackbarName, "DistCenter x %d", center_slider_max );
  createTrackbar( TrackbarName, "addweighted",
				  &center_slider,
				  center_slider_max,
				  on_trackbar_center );
  on_trackbar_center(center_slider, 0 );

  sprintf( TrackbarName, "VertPosi x %d", vertical_slider_max );
  createTrackbar( TrackbarName, "addweighted",
          &vertical_slider,
          vertical_slider_max,
          on_trackbar_vert );
  on_trackbar_vert(vertical_slider, 0 );

  waitKey(0);
  imwrite("tiltshift_saida.png", blended);
  return 0;
}

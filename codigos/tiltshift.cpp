#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

double alfa;
int alfa_slider = 0;
int alfa_slider_max = 100;

int width, height;

int center_slider;
int center_slider_max ;

int vertical_slider;
int vertical_slider_max ;

Mat original, desfocada, blended;
Mat desf_cpy;

char TrackbarName[50];

void on_trackbar_blend(int, void*){
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted( original, alfa, desf_cpy, 1-alfa, 0.0, blended);
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
      cout<<(height-limit_c)/2-(height/2-limit_v)<<"\n";

    }
    else if(limit_v > height/2){
      Mat tmp = original(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c));
  	  tmp.copyTo(desf_cpy(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c)));
      cout<<limit_c<<" "<<limit_v<<"\n";
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
      cout<<(height-limit_c)/2-(height/2-limit_v)<<"\n";
      tmp.copyTo(desf_cpy(Rect(0, (height-limit_c)/2-(height/2-limit_v),width,limit_c)));
      cout<<limit_c<<" "<<limit_v<<"\n";

    }
    else if(limit_v > height/2){
      Mat tmp = original(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c));
      tmp.copyTo(desf_cpy(Rect(0, (height-limit_c)/2+(limit_v-height/2),width,limit_c)));
      cout<<limit_c<<" "<<limit_v<<"\n";
    }
    on_trackbar_blend(alfa_slider,0);
  }

}

int main(int argvc, char** argv){
  original = imread("blend1.jpg");
  desfocada = imread("blend2.jpg");
  desfocada.copyTo(desf_cpy);
  width = original.size().width;
  height = original.size().height;
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
  return 0;
}

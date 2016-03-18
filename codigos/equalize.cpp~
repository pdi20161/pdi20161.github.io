#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image, equalize;
  int width, height;
  VideoCapture cap;
  vector<Mat> planes, channels;
  Mat histR, histG, histB;
  int nbins = 64;
  float range[] = {0, 256};
  const float *histrange = { range };
  bool uniform = true;
  bool acummulate = false;

  cap.open(1);

  if(!cap.isOpened()){
    cout << "cameras indisponiveis";
    return -1;
  }

  width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

  cout << "largura = " << width << endl;
  cout << "altura  = " << height << endl;

  int histw = nbins, histh = nbins/2;
  Mat histImgR(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgG(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgB(histh, histw, CV_8UC3, Scalar(0,0,0));

  Mat histImgReq(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgGeq(histh, histw, CV_8UC3, Scalar(0,0,0));
  Mat histImgBeq(histh, histw, CV_8UC3, Scalar(0,0,0));

  while(1){
    cap >> image;
    split(image,planes);
    calcHist(&planes[0], 1, 0, Mat(), histR, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[1], 1, 0, Mat(), histG, 1,
             &nbins, &histrange,
             uniform, acummulate);
    calcHist(&planes[2], 1, 0, Mat(), histB, 1,
             &nbins, &histrange,
             uniform, acummulate);

    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histB, histB, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

    histImgR.setTo(Scalar(0));
    histImgG.setTo(Scalar(0));
    histImgB.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histImgR, Point(i, histh),Point(i, cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
      line(histImgG, Point(i, histh),Point(i, cvRound(histG.at<float>(i))),
           Scalar(0, 255, 0), 1, 8, 0);
      line(histImgB, Point(i, histh),Point(i, cvRound(histB.at<float>(i))),
           Scalar(255, 0, 0), 1, 8, 0);
    }
    //equalize
    split (image, channels);
    equalizeHist(channels[0], channels[0]); 
    equalizeHist(channels[1], channels[1]);
    equalizeHist(channels[2], channels[2]);
    merge(channels,equalize);

    calcHist(&channels[0], 1, 0, Mat(), histR, 1,&nbins, &histrange,
             uniform, acummulate);
    calcHist(&channels[1], 1, 0, Mat(), histG, 1,&nbins, &histrange,
             uniform, acummulate);
    calcHist(&channels[2], 1, 0, Mat(), histB, 1,&nbins, &histrange,
             uniform, acummulate);

    normalize(histR, histR, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histG, histG, 0, histImgR.rows, NORM_MINMAX, -1, Mat());
    normalize(histB, histB, 0, histImgR.rows, NORM_MINMAX, -1, Mat());

    histImgReq.setTo(Scalar(0));
    histImgGeq.setTo(Scalar(0));
    histImgBeq.setTo(Scalar(0));

    for(int i=0; i<nbins; i++){
      line(histImgReq, Point(i, histh), Point(i, cvRound(histR.at<float>(i))),
           Scalar(0, 0, 255), 1, 8, 0);
      line(histImgGeq, Point(i, histh), Point(i, cvRound(histG.at<float>(i))),
           Scalar(0, 255, 0), 1, 8, 0);
      line(histImgBeq, Point(i, histh), Point(i, cvRound(histB.at<float>(i))),
           Scalar(255, 0, 0), 1, 8, 0);
    }

    histImgR.copyTo(image(Rect(0, 0       ,nbins, histh)));
    histImgG.copyTo(image(Rect(0, histh   ,nbins, histh)));
    histImgB.copyTo(image(Rect(0, 2*histh ,nbins, histh)));
    imshow("image", image);

    histImgReq.copyTo(equalize(Rect(0, 0       ,nbins, histh)));
    histImgGeq.copyTo(equalize(Rect(0, histh   ,nbins, histh)));
    histImgBeq.copyTo(equalize(Rect(0, 2*histh ,nbins, histh)));
    imshow("equalize", equalize);
    if(waitKey(30) >= 0) break;
  }
  return 0;
}

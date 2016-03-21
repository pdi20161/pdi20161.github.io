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

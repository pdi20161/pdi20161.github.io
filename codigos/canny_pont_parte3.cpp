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

  imwrite("saida_canny_pont.jpg", points)

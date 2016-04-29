  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  image.copyTo(blur);
  mask = Mat(3, 3, CV_32F, gauss);
  scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;
  filter2D(image, blur, image.depth(), mask, Point(1,1), 0);
  filter2D(blur, blur, blur.depth(), mask, Point(1,1), 0);
  filter2D(blur, blur, blur.depth(), mask, Point(1,1), 0);
  filter2D(blur, blur, blur.depth(), mask, Point(1,1), 0);

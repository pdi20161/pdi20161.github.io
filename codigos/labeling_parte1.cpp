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
floodFill(image,p,0);

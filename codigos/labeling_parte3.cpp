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

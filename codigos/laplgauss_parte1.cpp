if(isLoG){
      mask = Mat(3, 3, CV_32F, gauss);
      scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
      mask = mask1;
      filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
      mask = Mat(3, 3, CV_32F, laplacian);
      filter2D(frameFiltered, frameFiltered2, frameFiltered.depth(), mask, Point(1,1), 0);
      if(absolut){
        frameFiltered2=abs(frameFiltered2);
      }
      frameFiltered2.convertTo(result1, CV_8U);
      imshow("filtroespacial", result1);
    }
    else{
      filter2D(frame32f, frameFiltered, frame32f.depth(), mask, Point(1,1), 0);
      if(absolut){
        frameFiltered=abs(frameFiltered);
      }
      frameFiltered.convertTo(result, CV_8U);
      imshow("filtroespacial", result);
    }

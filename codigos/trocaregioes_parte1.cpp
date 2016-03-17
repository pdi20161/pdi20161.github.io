Mat imgRect1(image, Rect(0,0,width/2,height/2));
Mat imgRect2(image, Rect(width/2-1,0,width/2,height/2)); 
Mat imgRect3(image, Rect(0,height/2-1,width/2,height/2));
Mat imgRect4(image, Rect(width/2-1,height/2-1,height/2,width/2));
newimage = image.clone();

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

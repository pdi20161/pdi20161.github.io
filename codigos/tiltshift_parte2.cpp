void on_trackbar_blend(int, void*){
 alfa = (double) alfa_slider/alfa_slider_max ;
 addWeighted(desf_cpy , alfa, original, 1-alfa, 0.0, blended);
 imshow("addweighted", blended);
}

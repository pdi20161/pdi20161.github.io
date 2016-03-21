int main(int argvc, char** argv){
  Mat mask(3,3,CV_32F), mask1;
  original = imread("tiltshift_entrada3.jpg");
  mask = Mat(3, 3, CV_32F, gauss);
  scaleAdd(mask, 1/16.0, Mat::zeros(3,3,CV_32F), mask1);
  mask = mask1;
  filter2D(original, desfocada, original.depth(), mask, Point(1,1), 0);
  filter2D(desfocada, desfocada, desfocada.depth(), mask, Point(1,1), 0);
  filter2D(desfocada, desfocada, desfocada.depth(), mask, Point(1,1), 0);
  desfocada.copyTo(desf_cpy);
  width = original.size().width;
  height = original.size().height;
  original = increase_colour_saturation(original);
  vertical_slider = height/2;
  vertical_slider_max = height;
  center_slider = 0;
  center_slider_max = height;
  namedWindow("addweighted", 1);

  sprintf( TrackbarName, "Alpha x %d", alfa_slider_max );
  createTrackbar( TrackbarName, "addweighted",
				  &alfa_slider,
				  alfa_slider_max,
				  on_trackbar_blend );
  on_trackbar_blend(alfa_slider, 0 );

  sprintf( TrackbarName, "DistCenter x %d", center_slider_max );
  createTrackbar( TrackbarName, "addweighted",
				  &center_slider,
				  center_slider_max,
				  on_trackbar_center );
  on_trackbar_center(center_slider, 0 );

  sprintf( TrackbarName, "VertPosi x %d", vertical_slider_max );
  createTrackbar( TrackbarName, "addweighted",
          &vertical_slider,
          vertical_slider_max,
          on_trackbar_vert );
  on_trackbar_vert(vertical_slider, 0 );

  waitKey(0);
  imwrite("tiltshift_saida.png", blended);
  return 0;
}

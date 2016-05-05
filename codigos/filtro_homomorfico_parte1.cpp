Mat filterHomomorfico( int M, int N){
  Mat H = Mat(M, N, CV_32F), filter;
		for(int i=0; i<M ;i++){
			for(int j=0; j<N ;j++){
					float D2 = pow((float)i-M/2.0, 2) + pow((float)j-N/2.0, 2);
					H.at<float>(i,j) = (gama_h-gama_l)*(1.0-exp(-1.0*(float)c*(D2/pow(d0,2))))+ gama_l;
			}
		}
		Mat comps[]= {H, H};
		merge(comps, 2, filter);
		return filter;
}


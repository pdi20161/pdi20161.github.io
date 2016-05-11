#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>

#define RADIUS 20

using namespace cv;
using namespace std;


double gama_h;
int gama_h_slider = 0;
int gama_h_slider_max = 100;

double gama_l;
int gama_l_slider = 0;
int gama_l_slider_max = 100;

double c;
int c_slider = 0;
int c_slider_max = 100;

double d0;
int d0_slider = 0;
int d0_slider_max = 100;

char TrackbarName[50];

void on_trackbar_gama_h(int, void*){
 gama_h = (double) gama_h_slider ;
}

void on_trackbar_gama_l(int, void*){
 gama_l = (double) gama_l_slider  ;
}

void on_trackbar_c(int, void*){
 c = (double) c_slider  ;
}

void on_trackbar_d0(int, void*){
 d0 = (double) d0_slider ;
}

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

// troca os quadrantes da imagem da DFT
void deslocaDFT(Mat& image ){
  Mat tmp, A, B, C, D;

  // se a imagem tiver tamanho impar, recorta a regiao para
  // evitar cópias de tamanho desigual
  image = image(Rect(0, 0, image.cols & -2, image.rows & -2));
  int cx = image.cols/2;
  int cy = image.rows/2;

  // reorganiza os quadrantes da transformada
  // A B   ->  D C
  // C D       B A
  A = image(Rect(0, 0, cx, cy));
  B = image(Rect(cx, 0, cx, cy));
  C = image(Rect(0, cy, cx, cy));
  D = image(Rect(cx, cy, cx, cy));

  // A <-> D
  A.copyTo(tmp);  D.copyTo(A);  tmp.copyTo(D);

  // C <-> B
  C.copyTo(tmp);  B.copyTo(C);  tmp.copyTo(B);
}

int main(int , char**){
  VideoCapture cap;
  Mat image, imaginaryInput, complexImage, multsp;
  Mat padded, filter, mag;
  Mat imagegray, tmp;
  Mat_<float> realInput, zeros;
  vector<Mat> planos;
  char key;
	namedWindow("original", 1);

  sprintf( TrackbarName, "Gama H: ");
    createTrackbar( TrackbarName, "original",
  				  &gama_h_slider,
  				  gama_h_slider_max,
  				  on_trackbar_gama_h );
    on_trackbar_gama_h(gama_h_slider, 0 );

    sprintf( TrackbarName, "Gama L: ");
      createTrackbar( TrackbarName, "original",
    				  &gama_l_slider,
    				  gama_l_slider_max,
    				  on_trackbar_gama_l );
      on_trackbar_gama_l(gama_l_slider, 0 );

      sprintf( TrackbarName, "C: ");
        createTrackbar( TrackbarName, "original",
      				  &c_slider,
      				  c_slider_max,
      				  on_trackbar_c );
        on_trackbar_c(c_slider, 0 );

        sprintf( TrackbarName, "D0: ");
          createTrackbar( TrackbarName, "original",
        				  &d0_slider,
        				  d0_slider_max,
        				  on_trackbar_d0 );
          on_trackbar_d0(d0_slider, 0 );

  // valores ideais dos tamanhos da imagem
  // para calculo da DFT
  int dft_M, dft_N;

  // abre a câmera default
  //cap.open(0);
  //if(!cap.isOpened())
   // return -1;

  // captura uma imagem para recuperar as
  // informacoes de gravação
  //cap >> image;
  image = imread("filtro_homomofico_entrada.jpg");
  // identifica os tamanhos otimos para
  // calculo do FFT
  dft_M = getOptimalDFTSize(image.rows);
  dft_N = getOptimalDFTSize(image.cols);

 // realiza o padding da imagem
  copyMakeBorder(image, padded, 0,
                 dft_M - image.rows, 0,
                 dft_N - image.cols,
                 BORDER_CONSTANT, Scalar::all(0));

  // parte imaginaria da matriz complexa (preenchida com zeros)
  zeros = Mat_<float>::zeros(padded.size());

  // prepara a matriz complexa para ser preenchida
  complexImage = Mat(padded.size(), CV_32FC2, Scalar(0));

  // a função de transferência (filtro frequencial) deve ter o
  // mesmo tamanho e tipo da matriz complexa
  filter = complexImage.clone();

  // cria uma matriz temporária para criar as componentes real
  // e imaginaria do filtro ideal
  tmp = Mat(dft_M, dft_N, CV_32F);

  // cria a matriz com as componentes do filtro e junta
  // ambas em uma matriz multicanal complexa
  Mat comps[]= {tmp, tmp};
  merge(comps, 2, filter);

  for(;;){
    //cap >> image;
    image = imread("filtro_homomofico_entrada.jpg");
    cvtColor(image, imagegray, CV_BGR2GRAY);
    imshow("original", imagegray);

    // realiza o padding da imagem
    copyMakeBorder(imagegray, padded, 0,
                   dft_M - image.rows, 0,
                   dft_N - image.cols,
                   BORDER_CONSTANT, Scalar::all(0));

    // limpa o array de matrizes que vao compor a
    // imagem complexa
    planos.clear();
    // cria a compoente real
    realInput = Mat_<float>(padded);
    // insere as duas componentes no array de matrizes
    planos.push_back(realInput);
    planos.push_back(zeros);

    // combina o array de matrizes em uma unica
    // componente complexa
    merge(planos, complexImage);

    //add(complexImage, 1.0, complexImage);
    //log(complexImage,complexImage);

    // calcula o dft
    dft(complexImage, complexImage);

    // realiza a troca de quadrantes
    deslocaDFT(complexImage);

    filter = filterHomomorfico(dft_M,dft_N);

    //cout << "H: "<< H << "\n";

    // aplica o filtro frequencial
    mulSpectrums(complexImage,filter,complexImage,0);

    // limpa o array de planos
    planos.clear();
    // separa as partes real e imaginaria para modifica-las
    split(complexImage, planos);

    // recompoe os planos em uma unica matriz complexa
    merge(planos, complexImage);

    // troca novamente os quadrantes
    deslocaDFT(complexImage);

    // calcula a DFT inversa
    idft(complexImage, complexImage);

    //normalize(complexImage, complexImage, 0, 1, CV_MINMAX);
    //exp(complexImage,complexImage);

    // limpa o array de planos
    planos.clear();

    // separa as partes real e imaginaria da
    // imagem filtrada
    split(complexImage, planos);

    // normaliza a parte real para exibicao
    normalize(planos[0], planos[0], 0, 1, CV_MINMAX);

    imshow("filtrada", planos[0]);

    key = (char) waitKey(10);
    if( key == 27 ) break; // esc pressed!
  }
  return 0;
}

for(int i = 0; i<histh; i++){
   for(int j = 0; j<histw; j++){
     somaatual = somaatual + histImgR.at<uchar>(i,j);
     somaanterior = somaanterior+histImgBufR.at<uchar>(i,j);
   }
}
mediaatual = somaatual/(histh*histw);
mediaanterior = somaanterior/(histh*histw);
if(abs(mediaatual - mediaanterior)>=2 && ruidoinicial>=30){
   cout<<"Movimento Detectado\n";
   ruidoinicial = 31;
}

#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
using namespace std;
using namespace cv;

 
int main(int argc,char **argv){
  time_t timer_begin,timer_end;
  raspicam::RaspiCam_Cv Camera;
  Mat src_img;
  int nCount=100;
  //set camera params
  Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
  Camera.set( CV_CAP_PROP_FRAME_WIDTH, 640);
  Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 480);
  

  namedWindow("capture",CV_WINDOW_AUTOSIZE);
  
  //Open camera
  if (!Camera.open()){
    cerr<<"Error opening the camera"<<endl;
    return -1;
  }
  
  time ( &timer_begin );
  for ( int i=0; i<nCount; i++ ) {
    Camera.grab();
    Camera.retrieve(src_img);
    imshow("capture",src_img);
    if (cvWaitKey(1) >= 0){
      break;
    }
  }
  Camera.release();
  cvDestroyWindow("capture");

  time ( &timer_end );
  double secondsElapsed = difftime ( timer_end,timer_begin );
  cout<<  ( float ) ( ( float ) ( nCount ) /secondsElapsed ) <<endl;
  return 0;
}

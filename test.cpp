#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <pca9685.h>
#include <wiringPi.h>
#include <unistd.h>

using namespace std;
using namespace cv;

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50
#define PIN0 300
#define PIN1 301

int deg_to_value(int deg);
 
int main(int argc,char **argv){

  //camera setting
  raspicam::RaspiCam_Cv Camera;
  Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
  Camera.set( CV_CAP_PROP_FRAME_WIDTH, 640);
  Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 480);

  //
  CascadeClassifier cascade;
  cascade.load("haarcascades/haarcascade_frontalface_alt.xml");
  vector<Rect> faces;
  Mat src_img;

  //
  int nCount=100;
  time_t timer_begin,timer_end;

  //
  wiringPiSetup();
  int fd = pca9685Setup(PIN_BASE, 0x40,HERTZ);
  
  //Open camera
  if (!Camera.open()){
    cerr << "Error opening the camera" << endl;
    return -1;
  }

  //
  if(fd < 0){
    cerr << "Error setting up the motor" << endl;
  }

  pca9685PWMReset(fd);
  namedWindow("capture",CV_WINDOW_AUTOSIZE);
  time (&timer_begin);

  int degree = 0;
  
  for ( int i=0; i<nCount; i++ ) {
    //capture
    Camera.grab();
    Camera.retrieve(src_img);

    //face detection
    cascade.detectMultiScale(src_img,faces,1.1,3,0,Size(80,80));


    
    //when no faces are detected
    if(faces.size() == 0){
      cout << "searching for faces..." << endl;
      //degree = 0;
      //pwmWrite(PIN0,deg_to_value(degree));
    }
    //when faces are detected
    else{
      //choose the biggest face
      int face_id=0;
      int face_size=0;
      for(int j=0;j<faces.size();j++){
	if(faces[j].width*faces[j].height > face_size){
	  face_id = j;
	}
      }
      
      int center_x = faces[face_id].x + faces[face_id].width/2;
      int center_y = faces[face_id].y + faces[face_id].height/2;
      cout << center_x << " " << center_y << "     ";

      float Kp = -0.05;
      degree = int(Kp*(320 - center_x) + degree);
      if(degree > 90){
	degree = 90;
      }else if(degree < -90){
	degree = -90;
      }
      cout << degree << endl;
      pwmWrite(PIN0,deg_to_value(degree));
      
      rectangle(src_img,Point(faces[face_id].x,faces[face_id].y),Point(faces[face_id].x+faces[face_id].width,faces[face_id].y+faces[face_id].height),Scalar(0,0,255),3,CV_AA);
      
    }
    imshow("capture",src_img);
    
    if (cvWaitKey(1) >= 0){
      break;
    }
  }
  Camera.release();
  cvDestroyWindow("capture");

  time (&timer_end);
  double secondsElapsed = difftime ( timer_end,timer_begin );
  cout<<  ( float ) ( ( float ) ( nCount ) /secondsElapsed ) <<endl;
  return 0;
}



int deg_to_value(int deg){
  float y = -83.0/36 * (deg - 90) + 105;
  return (int)y;
}

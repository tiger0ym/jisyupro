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

#define target_x 320
#define target_y 240

#define KP_x -0.05
#define KD_x -0.005
#define KP_y 0.05
#define KD_y 0.01
#define delta_t 0.2

int deg_to_value(int deg);
 
int main(int argc,char **argv){

  //camera setting
  raspicam::RaspiCam_Cv Camera;
  Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
  Camera.set( CV_CAP_PROP_FRAME_WIDTH, 640);
  Camera.set( CV_CAP_PROP_FRAME_HEIGHT, 480);
  Camera.setRotation(2);

  //
  CascadeClassifier cascade;
  cascade.load("haarcascades/haarcascade_frontalface_alt.xml");
  vector<Rect> faces;
  Mat src_img;

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
    return -1;
  }

  int degree_x = 0;
  int diff0_x = 0;
  int diff1_x = 0;

  int degree_y = 0;
  int diff0_y = 0;
  int diff1_y = 0;
  
  while(true) {
    //capture
    Camera.grab();
    Camera.retrieve(src_img);

    Point2f center = Point2f(static_cast<float>(src_img.cols/2),static_cast<float>(src_img.rows/2));
    Mat affine;

    //face detection
    cascade.detectMultiScale(src_img,faces,1.1,3,0,Size(80,80));

    if(faces.size() == 0){
      getRotationMatrix2D(center,10,1).copyTo(affine);
      warpAffine(src_img,src_img,affine,src_img.size(),INTER_CUBIC);
    
      //face detection
      cascade.detectMultiScale(src_img,faces,1.1,3,0,Size(80,80));

      if(faces.size() == 0){
	getRotationMatrix2D(center,-20,1).copyTo(affine);
	warpAffine(src_img,src_img,affine,src_img.size(),INTER_CUBIC);
    
	//face detection
	cascade.detectMultiScale(src_img,faces,1.1,3,0,Size(80,80));
      }
    }
    
    //when no faces are detected
    if(faces.size() == 0){
      //cout << "searching for faces..." << endl;
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
      //cout << center_x << " " << center_y << endl;

      
      
      //PD control
      diff0_x = diff1_x;
      diff1_x = target_x - center_x;
      degree_x = int(KP_x*diff1_x + KD_x*(diff1_x-diff0_x)/delta_t + degree_x);

      diff0_y = diff1_y;
      diff1_y = target_y - center_y;
      degree_y = int(KP_y*diff1_y + KD_y*(diff1_y-diff0_y)/delta_t + degree_y);

      //keep degrees in [-90, 90]
      if(degree_x > 90){
	degree_x = 90;
      }else if(degree_x < -90){
	degree_x = -90;
      }
      if(degree_y > 90){
	degree_y = 90;
      }else if(degree_y < -90){
	degree_y = -90;
      }
      pwmWrite(PIN0,deg_to_value(degree_x));
      pwmWrite(PIN1,deg_to_value(degree_y));
      
      
    }
    
    if (cvWaitKey(1) >= 0){
      break;
    }
  }
  Camera.release();
  pca9685PWMReset(fd);

  return 0;
}



int deg_to_value(int deg){
  float y = -83.0/36 * (deg - 90) + 105;
  return (int)y;
}

#include <ctime>
#include <iostream>
#include <raspicam/raspicam_cv.h>
#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

 
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

  
  //Open camera
  if (!Camera.open()){
    cerr<<"Error opening the camera"<<endl;
    return -1;
  }
  
  namedWindow("capture",CV_WINDOW_AUTOSIZE);
  time (&timer_begin);
  
  for ( int i=0; i<nCount; i++ ) {
    //capture
    Camera.grab();
    Camera.retrieve(src_img);

    //face detection
    cascade.detectMultiScale(src_img,faces,1.1,3,0,Size(80,80));

    //when no faces are detected
    if(faces.size() == 0){
      cout << "searching for faces..." << endl;
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
      
      rectangle(src_img,Point(faces[face_id].x,faces[face_id].y),Point(faces[face_id].x+faces[face_id].width,faces[face_id].y+faces[face_id].height),Scalar(0,0,255),3,CV_AA);
      cout << center_x << " " << center_y << endl;
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

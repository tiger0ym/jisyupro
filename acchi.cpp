#include <pca9685.h>
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>
#include <random>

using namespace std;

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50
#define PIN0 300
#define PIN1 301

int deg_to_value(int deg){
  float y = -83.0/36 * (deg - 90) + 105;
  return (int)y;
}


int main(void){
  
  int s;
  srand(time(NULL));
  s = rand() % 4 ;
  cout << s << endl;

  wiringPiSetup();
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);

  if(fd < 0){
    cout << "Error in setup" << endl;
    return -1;
  }

 
  
  pca9685PWMReset(fd);

  if(s == 0){
    pwmWrite(PIN0,deg_to_value(-45));
    pwmWrite(PIN1,deg_to_value(0));
  }else if(s == 1){
    pwmWrite(PIN0,deg_to_value(45));
    pwmWrite(PIN1,deg_to_value(0));
  }else if(s == 2){
    pwmWrite(PIN0,deg_to_value(0));
    pwmWrite(PIN1,deg_to_value(-45));
  }else{
    pwmWrite(PIN0,deg_to_value(0));
    pwmWrite(PIN1,deg_to_value(45));
  }

  sleep(1);
  
  pwmWrite(PIN0,deg_to_value(0));
  pwmWrite(PIN1,deg_to_value(0));
  pca9685PWMReset(fd);
  return 0;

}

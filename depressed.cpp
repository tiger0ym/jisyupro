#include <pca9685.h>
#include <wiringPi.h>
#include <iostream>
#include <unistd.h>

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

  wiringPiSetup();
  int fd = pca9685Setup(PIN_BASE, 0x40, HERTZ);

  if(fd < 0){
    cout << "Error in setup" << endl;
    return -1;
  }

  pca9685PWMReset(fd);
  
  pwmWrite(PIN1,deg_to_value(-45));
  return 0;
}
   

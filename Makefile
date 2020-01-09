all: acchi demo test depressed

acchi: acchi.cpp
	g++ $^ -o $@ -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685

demo: demo.cpp
	g++ $^ -o $@ `pkg-config --libs --cflags opencv` -lraspicam_cv -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685

test: test.cpp
	g++ $^ -o $@ `pkg-config --libs --cflags opencv` -lraspicam_cv -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685

depressed: depressed.cpp
	g++ $^ -o $@ -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685

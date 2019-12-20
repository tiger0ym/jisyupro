test: test.cpp
	g++ test.cpp -o test `pkg-config --libs --cflags opencv` -lraspicam_cv -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685

# You need to "sudo apt-get install libgtkmm-3.0-dev" to build the demo_3d binary

all: collect_data

HDRS = helper_3dmath.h I2Cdev.h MPU6050_6Axis_MotionApps20.h MPU6050.h packager.h
CMN_OBJS = I2Cdev.o MPU6050.o
CLD_OBJS = collect_data.o packager.o

IMU_OBJS = IMU_zero.o 
# Set DMP FIFO rate to 100Hz.  See comments in
# MPU6050_6Axis_MotionApps20.h for details.

CXXFLAGS = -DDMP_FIFO_RATE=1 -Wall -g -O2 `pkg-config gtkmm-3.0 --cflags --libs`

 $(CMN_OBJS) $(CLD_OBJS) $(IMU_OBJS): $(HDRS)

collect_data: $(CMN_OBJS) $(CLD_OBJS)
	@ echo "Compiled data collection program"
	@ $(CXX) -o $@ $^ -l wiringPi -lm

IMU_zero: $(CMN_OBJS) $(IMU_OBJS)
	@ echo "Compiled IMU Callibration program"
	@ $(CXX) -o $@ $^ -lm

clean:
	@ echo "Ahh clean!"
	@ rm -f $(CMN_OBJS) $(CLD_OBJS) $(IMU_OBJS) collect_data IMU_zero

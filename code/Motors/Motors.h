#ifndef MOTORS_H
#define MOTORS_H
#define PI 3.14159265358979323846

class Motors {
    protected:
        PwmOut pwm1;
        PwmOut pwm2;// CONNECT TO PIN 3 & 6, JP1a respectively. pwm1 and pwm2 objects to interact with MDB.
        DigitalOut control1, control2, enable; //Digital pins to interact with MDB.
        float frequency, period, speed_A, speed_B;
    public:
        Motors(PinName PWM1, PinName PWM2, PinName ctrl1, PinName ctrl2, PinName ena) : pwm1(PWM1), pwm2(PWM2), control1(ctrl1), control2(ctrl2), enable(ena) { //Constructor to create a bipolar Motor object with specified pins.
            control1 = 1; //Set to Bipolar Mode of operation.
            control2 = 1;
            enable = 1;
            pwm1.write(0.5);
            pwm2.write(0.5);
        }
        void setFreq(float freq) {
            frequency = freq;
            period = 1/frequency;
             pwm1.period(period);
             pwm2.period(period);
        }  
        void setSpeed(float dr1, float dr2) {
           
            pwm1.write(dr1);
            
            pwm2.write(dr2);
        }
};

#endif
#include <iostream>
#include <string>
#include <WashingCycle.hpp>

///Testing a pull request with this
// Normally these would output phsyiscall instead of to the terminal. Also the sheet should be noted that all the Tub functions on the class diagram now only that WashingCycle as input
class Tub{
private:
    Motor motor;
    Heater heater;
    Bleach bleach;
public:
    void spin(const WashingCycle& cycle) {
        int speed = cycle.getSpeed();
        motor.setSpeedSetPoint(speed);
        std::cout << "The Tub is spinning at " << speed << " RPM." << std::endl;
     }
    void stop(){
        motor.setSpeedSetPoint(0);
        std::cout <<"The Tub has stopped spinning." <<std::endl;
    }
    void drain(const WashingCycle& cycle){
         int drainSpeed = cycle.getSpeed()* 0.5;
        std::cout <<"The Tub is draining." << std::endl;
    }
    void bleachRelease(const WashingCycle& cycle){
       if (cycle.getBleach()) {
            bleach.setRelease(true);
            std::cout << "The Tub is releasing bleach." << std::endl;
        } else {
            std::cout << "No bleach release required." << std::endl;
        }
    }
    void fill(std::string temp){
        if (temp == "hot"){
            heater.setHeaterTempSetPoint(140);
            std::cout <<"The Tub is filling with hot water. And it will be kept hot." << std::endl;
        }
        heater.setHeaterTempSetPoint(0);
        std::cout <<"The Tub is filling with " + temp + " water." << std::endl;
    }
};

class Motor{ //When additional hardware info is gathered next revision, connection will go here
    private:
        int speedSetPoint;

    public:
        void setSpeedSetPoint(int newSpeedSetPoint){
            speedSetPoint =newSpeedSetPoint;
        }
};

class Heater{ //As planned this will turn on heat thru a hardware interface
    private:
        int heaterTempSetPoint;
        int heaterTempCurrent;
    public:
        void setHeaterTempSetPoint(int newHeaterTempSetPoint){
            heaterTempSetPoint =newHeaterTempSetPoint;
        }
        int getHeaterTempSetPoint(){
            return heaterTempCurrent;
        }
};

class Bleach {
private:
    bool release; //When release is true, bleach enters system

public:
    Bleach() : release(false) {}

    void setRelease(bool newRelease){
        release = newRelease;
    }
};
// The logic for filling the tub is something I have been basing my head on a wall about
class fillLevel{

};

class DrainValve{
    protected:
        bool status; // When status is true, tub is draining
    public:
        DrainValve() : status(false) {};

        void (bool newStatus){
            status= newStatus;
        }
};

class FillValve{
    protected:
        std::string tempSetPoint 
        bool status; // When status is true, tub is filling. This is only used in the closing function
    public:
        FillValve() : status(false) {};

        void setStatus(bool temp){
            status= newStatus;
        }
};
// Example of classes and obect interaction for group project in CSC 300. 
//Authored by the group "Digital Destroyerz" composed of Moe Rahimi, Hugo Schroeder, Kamelish Candelaria Velez, Keith Askew.

#include <iostream>
#include <chrono>
#include "WashingCycle.hpp"

#include <gpio_library> //would be specific to microcontoller used. Pin and port numbers are arbitrary since there is no defined board. *Loosely* based on Arduino GPIO functions.
#define LID_SENSOR 1 //pin to lid sensor for open or closed state
#define GUI_BACKLIGHT 2 //pin or port on the microcontroller to tell the GUI to wake up
#define GUI_RX 3 //port which the microcontroller recieves data from the GUI
#define GUI_TX 4 //port which the microcontroller sends data to the GUI
#define TUB_RX 5 //port which the microcontroller recieves data from the tub
#define TUB_TX 6 //port which the microcontroller sends data to the tub

void initializeLidSensor(){
    SerialPin(LID_SENSOR, INPUT, bool LidClosed)//pull sensor info and stores it in a bool for open or closed state
}
void GUIpower(){
    bool LightOn = LidClosed; 
    SerialPin(GUI_BACKLIGHT, OUTPUT, LightOn);//push the power state to the GUI display based on the lid state
}
char GUIinput(){
    SerialPin(GUI_RX, INPUT, char GUIselection); //read the button selection from the GUI
    return GUIselection;
}
void GUICommand(const string command){
    SerialPin(GUI_TX, OUTPUT, command);//send commands to the tub module
}
void TubState(){
    SerialPin(TUB_RX, INPUT, char TubFull);//read when the tub is full or empty
}
void TubCommand(const string command){
    SerialPin(TUB_TX, OUTPUT, command);//send commands to the tub module
}
//pause functions moved and adjusted from header file
void pauseTimer() {
	auto pauseTime = std::chrono::steady_clock::now()- start;
}
void resumeTimer() {
	auto start = std::chrono::steady_clock::now() - pauseTime;
}

int main() {

    initializeLidSensor();

    while (!LidClosed){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

        LightOn();
        char Selection = GUIinput();
        switch (Selection)
        {
        case "M"://Runs manual cycle
            ManualCyce();//Instance of manual cycle
            setWashTemp(GUIinput());
            SetRinseTemp(GUIinput())
            setSpeed(GUIinput());
            setBleach(GUIinput());
            setDuration(GUIinput());
            //move the following up to the break to be after the switch statement
        
            break;

        case "Q"://Runs quick cycle
            QuickCycle();
            break;

        case "D";//Runs dark cycle
            DarkCycle();
            break;

        case "S";// Runs sanitation cycle
            SanitationCycle();
            break;

        case "H";//Runs heavy cycle
            HeavyCycle();
            break;

        default:
            std::cout << "ERROR: invalid selection"
        }

    auto start = std::chrono::steady_clock::now();
	auto finish = start + std::chrono::minutes(getDuration());
	auto rinse = finish - std::chrono::minutes(25);//time until rinse cycle
    GUICommand(getDuration());//sends time back to GUI for confirmation and display. This lets the GUI count down on its own.
            
    TubCommand(getWashTemp());//fills the tub with the designated temperature of water.
    while (TubFull =! "F"){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }//waits until the tub declares it is full. Tub shuts itself off to prevent overfilling.
    TubCommand(getSpeed());
    while (std::chrono::steady_clock::now()< rinse){
		std::this_thread::sleep_for(std::chrono::minutes(1));
	    } //countdown until beginning of rinse cycle
    TubCommand(drain);//sends command to drain the tub
    while (TubFull =! "E"){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }//waits until the tub declares it is empty

    TubCommand(getRinseTemp()); //begin the rinse cycle
    while (TubFull =! "F"){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }//waits until the tub declares it is full. Tub shuts itself off to prevent overfilling.
    TubCommand(getSpeed());
    while (std::chrono::steady_clock::now()< finish){
		std::this_thread::sleep_for(std::chrono::minutes(1));
		} //countdown until end of rinse cycle
    TubCommand(drain);//sends command to drain the tub
    while (TubFull =! "E"){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }//waits until the tub declares it is empty
    GUICommand(alarm);//send "done" notificatoin to GUI

    return 0;
}

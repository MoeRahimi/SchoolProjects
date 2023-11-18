// Example of classes and obect interaction for group project in CSC 300. 
//Authored by the group "Digital Destroyerz" composed of Moe Rahimi, Hugo Schroeder, Kamelish Candelaria Velez, Keith Askew.
// Does this comitt work?
#include <iostream>
#include "WashingCycle.h"

#include <gpio_library> //would be specific to microcontoller used
#define LID_SENSOR 1 //would be the actual pin number on the microcontroller
#define GUI_BACKLIGHT 2 //would be the actual pin or port on the microcontroller to tell the GUI to wake up
#define GUI_INPUT 4 //would be the actual data port to the GUI display
void initializeLidSensor(){
    SerialPin(LID_SENSOR, INPUT, bool LidOpen)//pull sensor info and stores it in a bool for open or closed state
}
void GUIpower(){
    bool LightOn =! LidOpen; 
    SerialPin(GUI_BACKLIGHT, OUTPUT, LightOn);//push the power state to the GUI display based on teh lid state
}
char GUIinput(){
    SerialPin(GUI_INPUT, INPUT, char GUIselection); //read the button selection from the GUI
    return GUIselection;
}

main

int main() {

    initializeLidSensor();
    while (LidOpen){
        LightOn();
        char Selection = GUI_INPUT();
        switch (Selection)
        {
        case "M"://Runs manual cycle
            setTemp(GUI_INPUT);
            setSpeed(GUI_INPUT);
            setBleach(GUI_INPUT);
            ManualCyce();//Runs manual cycle
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
    }

    return 0;
}

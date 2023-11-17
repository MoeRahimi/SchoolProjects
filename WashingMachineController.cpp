// Example of classes and obect interaction for group project in CSC 300. 
//Authored by the group "Digital Destroyerz" composed of Moe Rahimi, Hugo Schroeder, Kamelish Candelaria Velez, Keith Askew.

#include <iostream>

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


int main() {

    initializeLidSensor();
    while (LidOpen){
        LightOn();
        
    }

    return 0;
}

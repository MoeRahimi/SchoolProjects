#include <chrono>
#include <string>

//Currently 1 second is acting as 1 minute 

class WashingCycle {
protected:
	std::string temp;  //changed to string type, aka hot, temperate, cold?
	int speed;
	bool bleach;

	std::chrono::seconds duration; // This was changed from int to seconds and renamed from time to reduce confusion
	//int heaterTemp; // I think this should be scrapped from the class diagram, as in the sequence diagram the heater was linked to the temp

	//These parameters are only for the Timer function
	std::chrono::steady_clock::time_point startTime; // The pause function will either need to remove lasped time, or likely restart the time from the paus point

	bool timerRunning; // Variable added to make the clock work
	std::chrono::steady_clock::time_point pauseTime; //Time point when paused
public:
	//Getters

	std::string getWashTemp() const { return washTemp; }
	std::string getRinseTemp() const { return rinseTemp; }
	int getSpeed() const { return speed; }
	bool getBleach() const { return bleach; }

	std::chrono::seconds getDuration() const { return duration; }
	bool isTimerRunning() const { return timerRunning; } // This will return current state of the timer
	std::chrono::seconds getElapsedTime() const {
		if (timerRunning) {
			auto currentTime = std::chrono::steady_clock::now();
			auto elapsed = currentTime - startTime;
			return std::chrono::duration_cast<std::chrono::seconds>(elapsed);

		}
		return std::chrono::seconds(0); // Return zero if the timer is not running
	}

	//Setters have been moved to only be in the manual cycle

	//Moving the timer functions to the controller
};


class ManualCycle : public WashingCycle {
public:
	//I am still not certian if we need all these setters...

	void setWashTemp(std::string newWashTemp) { washTemp = newWashTemp; } // Do we want a guard so that temp can only be a few things?
	void setRinseTemp(std::string newRinseTemp) { rinseTemp = newRinseTemp; }
	void setSpeed(int newSpeed) { speed = newSpeed; }
	void setBleach(bool newBleach) { bleach = newBleach; }
	void setDuration(std::chrono::seconds newDuration) { duration = newDuration; }
	ManualCycle(std::string manWashTemp, std::string manRinseTemp, int manSpeed, bool manBleach, std::chrono::seconds manDuration) {
		washTemp = manWashTemp;
		rinseTemp = manRinseTemp
		speed = manSpeed;
		bleach = manBleach;
		duration = manDuration;
	}
};

class QuickCycle : public WashingCycle {
public:
	QuickCycle() {

		washTemp = "cold";
		rinseTemp = "cold";
		speed = 1600;
		bleach = false;
		duration = std::chrono::seconds(50);
	}
};

class DarkCycle : public WashingCycle {
public:
	DarkCycle() {
		washTemp = "cold";
		rinseTemp = "cold";
		speed = 1000;
		bleach = false;
		duration = std::chrono::seconds(76);
	}
};

class SanitationCycle : public WashingCycle {
public:
	SanitationCycle() {
		washTemp = "hot";
		rinseTemp = "cold";
		speed = 1600;
		bleach = false;
		duration = std::chrono::seconds(80);
	}
};

class HeavyCycle : public WashingCycle {
public:
	HeavyCycle() { //This has a seperate temp for rinse... and I don't love that currently it is just a fucntion call to change that...
		washTemp = "hot";
		rinseTemp = "hot";
		speed = 1600;
		bleach = true;
		duration = std::chrono::seconds(80);
	}
	void rinseTemp() {
		temp = "cold";
	}
};


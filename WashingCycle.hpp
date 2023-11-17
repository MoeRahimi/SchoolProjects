#include <chrono>
#include <string>
#ifndef WASHINGCYCLE_HPP
#define WASHINGCYCLE_HPP
//Currently 1 second is acting as 1 minute 

class WashingCycle {
protected:
	std::string temp;  //changed to string type, aka hot, temperate, cold?
	int speed;
	bool bleach;
	std::chrono::seconds duration;
	
	//These parameters are only for the Timer function
	std::chrono::steady_clock::time_point startTime; // Where the math for the run time begins at
	bool timerRunning; // Variable added to make the clock work
	std::chrono::steady_clock::time_point pauseTime; //Time point when paused
public:
	//Getters
	std::string getTemp() const { return temp; }
	int getSpeed() const { return speed; }
	bool getBleach() const { return bleach; }
	std::chrono::seconds getDuration() const { return duration; }
	bool isTimerRunning() const { return timerRunning; } // This will return current state of the timer
	std::chrono::seconds getElapsedTime() const {
		if (timerRunning) {
			auto currentTime = std::chrono::steady_clock::now();
			auto elapsed = currentTime - startTime;
			return std::chrono::duration_cast<std::chrono::seconds>(elapsed);
		} else if (startTime != std::chrono::steady_clock::now()) { //Return if Timer is paused
			auto elapsed = pauseTime - startTime;
			return std::chrono::duration_cast<std::chrono::seconds>(elapsed);
		}
		return std::chrono::seconds(0); // Return zero if the timer is not running
	}

	//Setters have been moved to only be in the manual cycle
	void setDuration(std::chrono::seconds newDuration) { duration = newDuration; }
	void startTimer() { //This is in place of a getter for the timer
		if (!timerRunning) {
			std::chrono::steady_clock::now();
			timerRunning = true;
		}
	}

	//Other functions
	void pauseTimer() {
		pauseTime = std::chrono::steady_clock::now();
		timerRunning = false;
	}
	void resumeTimer() { //NB every time the resume is run, the startTime is adjusted for the pause
		auto currentTime = std::chrono::steady_clock::now();
		startTime += (currentTime - pauseTime);
		timerRunning = true;
	}
};


class ManualCycle : public WashingCycle {
public:
	//I am still not certian if we need all these setters...
	void setTemp(std::string newTemp) { temp = newTemp; } // Do we want a guard so that temp can only be a few things?
	void setSpeed(int newSpeed) { speed = newSpeed; }
	void setBleach(bool newBleach) { bleach = newBleach; }
	ManualCycle(std::string manTemp, int manSpeed, bool manBleach, std::chrono::seconds manDuration) {
		temp = manTemp;
		speed = manSpeed;
		bleach = manBleach;
		duration = manDuration;
	}
};

class QuickCycle : public WashingCycle {
public:
	QuickCycle() {
		temp = "cold";
		speed = 1600;
		bleach = false;
		duration = std::chrono::seconds(50);
	}
};

class DarkCycle : public WashingCycle {
public:
	DarkCycle() {
		temp = "cold";
		speed = 1000;
		bleach = false;
		duration = std::chrono::seconds(76);
	}
};

class SanitationCycle : public WashingCycle {
public:
	SanitationCycle() {
		temp = "cold";
		speed = 1600;
		bleach = false;
		duration = std::chrono::seconds(80);
	}
};

class HeavyCycle : public WashingCycle {
public:
	HeavyCycle() { //This has a seperate temp for rinse... and I don't love that currently it is just a fucntion call to change that...
		temp = "hot";
		speed = 1600;
		bleach = true;
		duration = std::chrono::seconds(80);
	}
	void rinseTemp() {
		temp = "cold";
	}
};

#endif


#pragma config(Sensor, in1,    otherBattery,   sensorAnalog)
#pragma config(Sensor, dgtl12, blockPneumatics, sensorDigitalOut)
#pragma config(Motor,  port1,           rtLift,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           lfDrive,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           lbDrive,       tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port4,           llLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rfDrive,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           rbDrive,       tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port7,           rlLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rmLift,        tmotorVex393_MC29, openLoop, reversed, encoderPort, None)
#pragma config(Motor,  port9,           ltLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          lmLift,        tmotorVex393_HBridge, openLoop, encoderPort, None)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
This file is the main link of the program, it has the button controls and specific autonomous instructions
*/

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#pragma platform(VEX)
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"
//Uncomment the next line(s) when programming the autonomous code
#include "autonomous.h"
//#include "selection.h"
#include "battery.h"
void lift(int power);
void clearLCD();
void print(const char* lineOne, const char* lineTwo);
void stopDrive();
void waitForPress();
void waitForRelease();
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
int count = 0;
void pre_auton(){
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options
		switch(count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Red");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				count++;
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Blue");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton){
				waitForRelease();
				count++;
			}
			break;
		default:
			count = 0;
			break;
		}
	}
}
task autonomous(){
		//Red Drive
	//Switch Case that actually runs the user choice
	switch(count){
	case 0:
		//If count = 0, run the code correspoinding with choice 1
		displayLCDCenteredString(0, "Red");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(250);
		SensorValue[blockPneumatics] = false;
		lift(-127);
		wait1Msec(2500);
		lift(0);
		basicDrive(0, 127);
		wait1Msec(850);
		stopDrive();
		SensorValue[blockPneumatics] = true;
		lift(-127);
		wait1Msec(500);
		lift(0);
		basicDrive(-70, -70);
		wait1Msec(1000);
		stopDrive();
		break;
	case 1:
	//Blue Drive
		//If count = 1, run the code correspoinding with choice 2
		displayLCDCenteredString(0, "Blue");
		displayLCDCenteredString(1, "is running!");
		wait1Msec(250);
		SensorValue[blockPneumatics] = false;
		lift(-127);
		wait1Msec(2500);
		lift(0);
		basicDrive(127, 0);
		wait1Msec(850);
		stopDrive();
		SensorValue[blockPneumatics] = true;
		lift(-127);
		wait1Msec(500);
		lift(0);
		basicDrive(-70, -70);
		wait1Msec(1000);
		stopDrive();
		break;
	default:
		displayLCDCenteredString(0, "No valid choice");
		displayLCDCenteredString(1, "was made!");
		break;
	}
}

task usercontrol(){
	// User control code here, inside the loop
	clearLCD();
	int origBattery = nImmediateBatteryLevel;
	int origBackBattery = SensorValue[otherBattery];
	displayLCDVoltageString(0);
	displayLCDCenteredString(0, "2616F");
	bool leftDriveShouldStop;
	bool rightDriveShouldStop;
	while(true){
		if(nImmediateBatteryLevel != origBattery || SensorValue[otherBattery] != origBackBattery){
			displayLCDVoltageString(1);
		}
		//Bogdan Drive
		if(abs(vexRT[Ch3]) <= 30){
			leftDriveShouldStop = true;
		}
		else{
			leftDriveShouldStop = false;
		}
		if(abs(vexRT[Ch2]) <= 30){
			rightDriveShouldStop = true;
		}
		else{
			rightDriveShouldStop = false;
		}
		if(leftDriveShouldStop){
			motor[lfDrive] = motor[lbDrive] = 0;
		}
		else{
			motor[lfDrive] = motor[lbDrive] = vexRT[Ch3];
		}
		if(rightDriveShouldStop){
			motor[rfDrive] = motor[rbDrive] = 0;
		}
		else{
			motor[rfDrive] = motor[rbDrive] = vexRT[Ch2];
		}
		//Lift
		if(vexRT[Btn6D]){//using the lift function, this says run at full speed when 6U is pressed
			lift(127);
		}
		else if (vexRT[Btn6U]){//Reverse direction
			lift(-127);
		}
		else{//If neither button is pressed it won't move, it must be set to zero or it'll keep going after being pressed
			lift(0);
		}
		//Pneumatics
		if(vexRT[Btn5U]){
			SensorValue[blockPneumatics] = true;
		}
		if(vexRT[Btn5D]){
			SensorValue[blockPneumatics] = false;
		}
	}
}
void lift(int power){
	motor[ltLift] = motor[lmLift] = motor[llLift] = motor[rtLift] = motor[rmLift] = motor[rlLift] = power;
}
void clearLCD(){
	clearLCDLine(0);
	clearLCDLine(1);
}
void print(const char* lineOne, const char* lineTwo){
	clearLCDLine(0);
	displayLCDPos(0, 0);
	displayNextLCDString(lineOne);
	if(lineTwo != NULL){
		clearLCDLine(1);
		displayLCDPos(1, 0);
		displayNextLCDString(lineTwo);
	}
}
void stopDrive(){
	motor[rfDrive] = motor[rbDrive] = motor[lfDrive] = motor[lbDrive] = 0;
}
void waitForPress(){
	while(nLCDButtons == 0){/*We just have to wait a while*/}
	wait1Msec(5);
}
void waitForRelease(){
	while(nLCDButtons != 0){/*We just have to wait a while*/}
	wait1Msec(5);
}

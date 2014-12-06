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
#include "enumerations.h"
//Uncomment the next line(s) when programming the autonomous code
#include "autonomous.h"
#include "lcd.h"
void lift(int power);
void stopDrive();
MHAutonMode selection = MHAutonModeNoneSelected;
MHTeamColor color = MHTeamColorNone;
void pre_auton(){
	//Up here is the old pre_auton. This is here incase the new one using my lcd.h doesn't work out in time
	/*
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	bool selected = false;
	while(!selected){
		//Switch case that allows the user to choose from 4 different options
		switch(count){
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "Red");
			displayLCDCenteredString(1, "<		 Enter		>");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == MHLCDButtonLeft){
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == MHLCDButtonRight){
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
			if(nLCDButtons == MHLCDButtonLeft){
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == MHLCDButtonRight){
				waitForRelease();
				count++;
			}
			break;
		default:
			count = 0;
			break;
		}
	}
	*/
	string current = "main";
	screenForScreenStyle(MHLCDScreenStyleMain, &liveScreen);
	displayScreen(liveScreen);
	//Everything needs to be stuffed in a loop, just to allow graceful back functionality without causing a stackoverflow
	while(selection == MHAutonModeNoneSelected){
		//I'm not sure if the break and continue procs will apply to a nested switch statement, so until I find out, I'm using ifs
		if(current == "main"){
			waitForPress();
			if(nLCDButtons == MHLCDButtonLeft){
				//Display the Point Selection screen, keep track of the color (red), restart the loop
				waitForRelease();
				color = MHTeamColorRed;
				screenForScreenStyle(MHLCDScreenStylePointSelection, &nextScreen);
				displayNextScreen();
				current = "point";
				continue;
			}
			else if(nLCDButtons == MHLCDButtonCenter){
				//End the loop, specify no auton, go to voltage screen
				waitForRelease();
				color = MHTeamColorAny;
				selection = MHAutonModeNoAuton;
				screenForScreenStyle(MHLCDScreenStyleVoltage, &nextScreen);
				displayNextScreen();
				current = "volt";
				break;
			}
			else if(nLCDButtons == MHLCDButtonRight){
				//Display the Point Selection screen, keep track of the color (blue), restart the loop
				waitForRelease();
				color = MHTeamColorBlue;
				screenForScreenStyle(MHLCDScreenStylePointSelection, &nextScreen);
				displayNextScreen();
				current = "point";
				continue;
			}
			/*else if(nLCDButtons == MHLCDButtonAll){
				//Display the voltage screen for 5 seconds, reinstate the main screen, restart the loop
				waitForRelease();
				flashScreenStyle(MHLCDScreenStyleVoltage);
				continue;
			}*/
			else{
				waitForRelease();
				print("Invalid", "selection");
				wait1Msec(MHTimeOneSecond * 2);
				displayScreen(liveScreen);
			}
		}
		else if(current == "point"){
			waitForPress();
			if(nLCDButtons == MHLCDButtonLeft){
				//Set the proper 3 point auton, display voltage screen, end the loop
				waitForRelease();
				if(color == MHTeamColorBlue){
					selection = MHAutonModeBlue3;
					screenForScreenStyle(MHLCDScreenStyleVoltage, &nextScreen);
					displayNextScreen();
					current = "volt";
					break;
				}
				else if(color == MHTeamColorRed){
					selection = MHAutonModeRed3;
					screenForScreenStyle(MHLCDScreenStyleVoltage, &nextScreen);
					displayNextScreen();
					current = "volt";
					break;
				}
			}
			else if(nLCDButtons == MHLCDButtonCenter){
				//Clear the team color selection, go back to the main screen, restart the loop
				waitForRelease();
				color = MHTeamColorNone;
				displayLastScreen();
				current = "main";
				continue;
			}
			else if(nLCDButtons == MHLCDButtonRight){
				//Set the proper 5 point auton, display the voltage screen, end the loop
				waitForRelease();
				if(color == MHTeamColorBlue){
					selection = MHAutonModeBlue5;
					screenForScreenStyle(MHLCDScreenStyleVoltage, &nextScreen);
					displayNextScreen();
					current = "volt";
					break;
				}
				else if(color == MHTeamColorRed){
					selection = MHAutonModeRed5;
					screenForScreenStyle(MHLCDScreenStyleVoltage, &nextScreen);
					displayNextScreen();
					current = "volt";
				}
			}
			/*else if(nLCDButtons == MHLCDButtonAll){
				//Display the voltage screen for 5 seconds, reinstate the Point Selection screen, restart the loop
				waitForRelease();
				flashScreenStyle(MHLCDScreenStyleVoltage);
				continue;
			}*/
			else{
				waitForRelease();
				print("Invalid", "Point");
			}
		}
	}
}
task autonomous(){
//All the green you see beyond this point is the old autonomous. Keep this and the old pre_auton, and you're safe for an untested competition
/*
	//Red Drive
	//Switch Case that actually runs the user choice
	switch(selection){
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
	*/









	switch(selection){
		case MHAutonModeNoAuton:
			//Since there's no autonomous, we can wait for the usercontrol;
			return;
		case MHAutonModeRed3:
			//Here's the tried and true red 3 pointer
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
			//Auton over
			return;
		case MHAutonModeBlue3:
			//Here's the battle-tested blue 3 pointer
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
			//Auton over
			return;
		case MHAutonModeBlue5:
			//The 5 point blue auton
			print("Blue 5 Point", "Coming Soon");
			SensorValue[blockPneumatics] = false;
			lift(-127);
			wait1Msec(MHTimeHalfSecond);
			basicDrive(MHMotorPowerMax, MHMotorPowerMax);
			wait1Msec(MHTimeOneSecond);
			stopDrive();
			lift(MHMotorPowerStop);
			wait1Msec(MHTimeOneMillisecond * 5);
			lift(MHMotorPowerMax);
			wait1Msec(MHTimeOneSecond + MHTimeTenthSecond * 1.5);
			lift(MHMotorPowerStop);
			wait1Msec(MHTimeOneMillisecond * 5);
			lift(-127);
			wait1Msec(MHTimeOneSecond * 5 + MHTimeHalfSecond);
			lift(MHMotorPowerStop);
			basicDrive(MHMotorPowerHalf, MHMotorPowerHalf);
			wait1Msec(MHTimeHalfSecond);
			stopDrive();
			wait1Msec(MHTimeOneMillisecond * 5);
			basicDrive(-MHMotorPowerHalf, MHMotorPowerHalf);
			wait1Msec(MHTimeOneSecond - MHTimeTenthSecond);
			stopDrive();
			wait1Msec(MHTimeOneMillisecond * 5);
			basicDrive(MHMotorPowerMax, MHMotorPowerMax);
			wait1Msec(MHTimeTenthSecond * 3);
			stopDrive();
			lift(MHMotorPowerMax);
			wait1Msec(MHTimeTenthSecond);
			lift(MHMotorPowerStop);
			wait1Msec(MHTimeHalfSecond);
			SensorValue[blockPneumatics] = true;
			wait1Msec(MHTimeOneSecond);
			basicDrive(-MHMotorPowerMax, -MHMotorPowerMax);
			lift(MHMotorPowerMax);
			wait1Msec(MHTimeHalfSecond);
			stopDrive();
			wait1Msec(MHTimeOneSecond * 3.5);
			lift(MHMotorPowerStop);
			//Auton over
			return;
		case MHAutonModeRed5:
			//The 5 point red auton will go here when it's written
			print("Red 5 Point", "Coming Soon");
			SensorValue[blockPneumatics] = false;
			lift(-127);
			wait1Msec(MHTimeHalfSecond);
			basicDrive(MHMotorPowerMax, MHMotorPowerMax);
			wait1Msec(MHTimeOneSecond);
			stopDrive();
			lift(MHMotorPowerStop);
			wait1Msec(MHTimeOneMillisecond * 5);
			lift(MHMotorPowerMax);
			wait1Msec(MHTimeOneSecond + MHTimeTenthSecond * 1.5);
			lift(MHMotorPowerStop);
			wait1Msec(MHTimeOneMillisecond * 5);
			lift(-127);
			wait1Msec(MHTimeOneSecond * 5 + MHTimeHalfSecond);
			lift(MHMotorPowerStop);
			basicDrive(MHMotorPowerHalf, MHMotorPowerHalf);
			wait1Msec(MHTimeHalfSecond);
			stopDrive();
			wait1Msec(MHTimeOneMillisecond * 5);
			basicDrive(MHMotorPowerHalf, -MHMotorPowerHalf);
			wait1Msec(MHTimeOneSecond - MHTimeTenthSecond);
			stopDrive();
			wait1Msec(MHTimeOneMillisecond * 5);
			basicDrive(MHMotorPowerMax, MHMotorPowerMax);
			wait1Msec(MHTimeTenthSecond * 3);
			stopDrive();
			lift(MHMotorPowerMax);
			wait1Msec(MHTimeTenthSecond);
			lift(MHMotorPowerStop);
			wait1Msec(MHTimeHalfSecond);
			SensorValue[blockPneumatics] = true;
			wait1Msec(MHTimeOneSecond);
			basicDrive(-MHMotorPowerMax, -MHMotorPowerMax);
			lift(MHMotorPowerMax);
			wait1Msec(MHTimeHalfSecond);
			stopDrive();
			wait1Msec(MHTimeOneSecond * 3.5);
			lift(MHMotorPowerStop);
			//Auton over
			return;
	}
}
task usercontrol(){
	// User control code here, inside the loop
	clearLCD();
	int origBattery = nImmediateBatteryLevel;
	int origBackBattery = SensorValue[otherBattery];
	displayLCDVoltageString(1);
	displayLCDCenteredString(0, "2616F");
	bool leftDriveShouldStop;
	bool rightDriveShouldStop;
	while(true){
		if(nImmediateBatteryLevel != origBattery || SensorValue[otherBattery] != origBackBattery){
			//displayLCDVoltageString(1);
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
void stopDrive(){
	motor[rfDrive] = motor[rbDrive] = motor[lfDrive] = motor[lbDrive] = MHMotorPowerStop;
}

#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    otherBattery,   sensorAnalog)
#pragma config(Sensor, in2,    turningGyro,    sensorGyro)
#pragma config(Sensor, in7,    lLiftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, in8,    rLiftPotentiometer, sensorPotentiometer)
#pragma config(Sensor, dgtl1,  cubeIntake,     sensorDigitalOut)
#pragma config(Sensor, dgtl2,  skyriseClaw,    sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           rbLift,        tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           lfDrive,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           lbDrive,       tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port4,           ltLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           rDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           lbLift,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rtLift,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rmLift,        tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port9,           lmLift,        tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)
#include "Vex_Competition_Includes.h"
#include "enumerations.h"
#include "autonomous.h"
#ifndef LCD
//This file depends on lcd.h, but some other #includes might, too
#include "lcd.h"
#endif
MHAutonStyle roundAuton = MHAutonStyleNoAuton;
void pre_auton(){
	displayScreenStyle(MHLCDScreenStyleVoltage);
	waitForPressOfButton(MHLCDButtonCenter);
	//Set up the style selection screen
	bLCDBacklight = true;
	displayLCDCenteredString(1, "Cube Skill Skyrs");
	while(true){
		if(nLCDButtons == MHLCDButtonLeft){
			//Cube auton chosen
			waitForRelease();
			roundAuton = MHAutonStyleCubeAuton;
			break;
		}
		else if(nLCDButtons == MHLCDButtonCenter){
			//Time for programminng skills
			waitForRelease();
			initAutonomousWithTeamColor(MHTeamColorRed);
			roundAuton = MHAutonStyleSkills;
			displayScreenStyle(MHLCDScreenStyleVoltage);
			break;
		}
		else if(nLCDButtons == MHLCDButtonRight){
			//Skyrise auton chosen
			waitForRelease();
			roundAuton = MHAutonStyleSkyriseAuton;
			break;
		}
	}
	//If it's not the skills, we continue
	if(roundAuton != MHAutonStyleSkills && roundAuton != MHAutonStyleCubeAuton){
		displayLCDCenteredString(1, "Red         Blue");
		while(true){
			if(nLCDButtons == MHLCDButtonLeft){
				//We're on the red side
				waitForRelease();
				initAutonomousWithTeamColor(MHTeamColorRed);
				break;
			}
			else if(nLCDButtons == MHLCDButtonRight){
				//We're on the blue side
				waitForRelease();
				initAutonomousWithTeamColor(MHTeamColorBlue);
				break;
			}
		}
	}
	//If it's the cube auton, we ask if we want a 3 or 1 point
	if(roundAuton == MHAutonStyleCubeAuton){
		displayLCDCenteredString(1, "Red          Blue");
		while(true){
			if(nLCDButtons == MHLCDButtonRight){
				waitForRelease();
				initAutonomousWithTeamColor(MHTeamColorBlue);
				break;
			}
			else if(nLCDButtons == MHLCDButtonLeft){
				waitForRelease();
				initAutonomousWithTeamColor(MHTeamColorRed);
				break;
			}
		}
	}
	//Reconfigure the gyroscope
	displayLCDCenteredString(0, "Configuring Gyro");
	displayLCDCenteredString(1, "Keep Robot Still");
	SensorType[turningGyro] = sensorNone;
	wait1Msec(MHTimeOneSecond);
	SensorType[turningGyro] = sensorGyro;
	wait1Msec(MHTimeOneSecond * 2);
}
task autonomous(){
	displayScreenStyle(MHLCDScreenStyleVoltage);
	bLCDBacklight = false;
	float startBattery = nImmediateBatteryLevel;
	float startOther = SensorValue[otherBattery];
	//Auton running here
	//runAutonomousStyleForTeamColor(roundColor, roundAuton);
	liftToPosition(MHLiftPositionBottom / 2);
	if(startBattery != nImmediateBatteryLevel || startOther != SensorValue[otherBattery]){
		displayLCDVoltageString(1);
	}
}
task usercontrol(){
	//Drive control
	displayScreenStyle(MHLCDScreenStyleVoltage);
	bLCDBacklight = false;
	float startBattery = nImmediateBatteryLevel;
	float startOther = SensorValue[otherBattery];
	//int frontDirection = 1;
	bool shouldToggle = true;
	while(true){
		if(startBattery != nImmediateBatteryLevel || startOther != SensorValue[otherBattery]){
			displayLCDVoltageString(1);
			startBattery = nImmediateBatteryLevel;
			startOther = SensorValue[otherBattery];
		}
		//string top;
		//string bottom;
		//sprintf(top, "%d", SensorValue[turningGyro]);
		//sprintf(bottom, "%d", SensorValue[rLiftPotentiometer]);
		//displayLCDCenteredString(0, top);
		//displayLCDCenteredString(1, bottom);
		if(abs(vexRT[Ch2]) <= 30){
			stopDriveSide(MHRobotSideRight);
		}
		else{
			motor[rDrive] = vexRT[Ch2] /* frontDirection*/;
		}
		if(abs(vexRT[Ch3]) <= 30){
			stopDriveSide(MHRobotSideLeft);
		}
		else{
			motor[lfDrive] = motor[lbDrive] = vexRT[Ch3] /* frontDirection*/;
		}
		//Lift control
		if(vexRT[Btn6U]){
			lift(MHMotorPowerMax, MHLiftDirectionUp);
		}
		else if(vexRT[Btn6D]){
			lift(MHMotorPowerMax, MHLiftDirectionDown);
		}
		//If neither button is pressed, the lift must be stopped, or it will keep going
		else{
			lift(MHMotorPowerStop, MHLiftDirectionStop);
		}
		//Skyrise Intake
		if(vexRT[Btn8D]){
			SensorValue[skyriseClaw] = MHPneumaticPositionOpen;
		}
		else if(vexRT[Btn8R]){
			SensorValue[skyriseClaw] = MHPneumaticPositionClosed;
		}
		if(vexRT[Btn5U] || vexRT[Btn5D]){
			resetEncoders();
		}
		else if(vexRT[Btn7D]){
			SensorValue[cubeIntake] = MHPneumaticPositionOpen;
			time = MHTimeOneSecond * 2;
			if(!cubeResetTaskRunning){
				startTask(resetCubeIntake);
			}
		}
		else if(vexRT[Btn7U]){
			if(shouldToggle){
				SensorValue[cubeIntake] = !SensorValue[cubeIntake];
				shouldToggle = false;
			}
		}
		if(!vexRT[Btn7U]){
			shouldToggle = true;
		}
		//Auton fixer
		//if(vexRT[Btn7U]){
		//	frontDirection *= -1;
		//}
		abortTimeslice();
	}
}

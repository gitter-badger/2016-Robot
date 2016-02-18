// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

std::shared_ptr<DriveSubsystem> Robot::driveSubsystem;
std::shared_ptr<ControlSS> Robot::controlSS;
std::unique_ptr<OI> Robot::oi;

void Robot::RobotInit() {
	RobotMap::init();
    driveSubsystem.reset(new DriveSubsystem());
    controlSS.reset(new ControlSS());
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	//setting up position SC
		posSC = new SendableChooser();
		//adding all options to choose to posSC
		posSC->AddDefault("Left 1 (Default)", new Pos1());
		posSC->AddObject("Left/Middle 2", new Pos2());
		posSC->AddObject("Middle 3", new Pos3());
		posSC->AddObject("Right/Middle 4", new Pos4());
		posSC->AddObject("Right 5", new Pos5());
		/**/

		//make options viewable on dash
		SmartDashboard::PutData("Positions", posSC);

		//setting up defense SC
		defSC = new SendableChooser();
		//adding all options to choose to defSC
		defSC->AddDefault("Low bar 1 (Default)", new Def1());
		defSC->AddObject("Portcullis 2", new Def2());
		defSC->AddObject("Cheval de Frise 3", new Def3());
		defSC->AddObject("Moat 4", new Def4());
		defSC->AddObject("Ramparts 5", new Def5());
		defSC->AddObject("Drawbridge 6", new Def6());
		defSC->AddObject("Sally Port 7", new Def7());
		defSC->AddObject("Rock Wall 8", new Def8());
		defSC->AddObject("Rough Terrain 9", new Def9());
		//make defSC viewable on dash
		SmartDashboard::PutData("Defense", defSC);

	// instantiate the command used for the autonomous period
	autonomousCommand.reset(new AutonomousCommand());
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

void Robot::DisabledPeriodic() {
	Robot::controlSS->time->Reset();

	Robot::controlSS->updateShooter();
	SmartDashboard::PutNumber("Shooter PSI", Robot::controlSS->shooterPSI);
	SmartDashboard::PutBoolean("Can use shooter?", Robot::controlSS->shooterUse);
	Robot::controlSS->updateArm();
	SmartDashboard::PutNumber("Arm PSI", Robot::controlSS->armPSI);
	SmartDashboard::PutBoolean("Can use arm?", Robot::controlSS->armUse);
}

void Robot::AutonomousInit() {
	//create Command objects to get options selected by SCs
	Command* temp = (Command*) posSC->GetSelected();
	Command* temp2 = (Command*) defSC->GetSelected();
	//run both commands that were chosen
	temp->Run();
	temp2->Run();
	//show on dash what numbers were chosen
	SmartDashboard::PutNumber("Position selected:", Robot::controlSS->posNum);
	SmartDashboard::PutNumber("Defense selected:", Robot::controlSS->defNum);

	Robot::controlSS->updateShooter();
	SmartDashboard::PutNumber("Shooter PSI", Robot::controlSS->shooterPSI);
	SmartDashboard::PutBoolean("Can use shooter?", Robot::controlSS->shooterUse);
	Robot::controlSS->updateArm();
	SmartDashboard::PutNumber("Arm PSI", Robot::controlSS->armPSI);
	SmartDashboard::PutBoolean("Can use arm?", Robot::controlSS->armUse);

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

	//create Command objects to get options selected by SCs
	Command* temp = (Command*) posSC->GetSelected();
	Command* temp2 = (Command*) defSC->GetSelected();
	//run both commands that were chosen
	temp->Run();
	temp2->Run();
	//show on dash what numbers were chosen
	SmartDashboard::PutNumber("Position selected:", Robot::controlSS->posNum);
	SmartDashboard::PutNumber("Defense selected:", Robot::controlSS->defNum);

	SmartDashboard::PutNumber("Auto Time", Robot::controlSS->time->Get());

	Robot::controlSS->updateShooter();
	SmartDashboard::PutNumber("Shooter PSI", Robot::controlSS->shooterPSI);
	SmartDashboard::PutBoolean("Can use shooter?", Robot::controlSS->shooterUse);
	Robot::controlSS->updateArm();
	SmartDashboard::PutNumber("Arm PSI", Robot::controlSS->armPSI);
	SmartDashboard::PutBoolean("Can use arm?", Robot::controlSS->armUse);
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();

	Robot::controlSS->updateShooter();
	SmartDashboard::PutNumber("Shooter PSI", Robot::controlSS->shooterPSI);
	SmartDashboard::PutBoolean("Can use shooter?", Robot::controlSS->shooterUse);
	Robot::controlSS->updateArm();
	SmartDashboard::PutNumber("Arm PSI", Robot::controlSS->armPSI);
	SmartDashboard::PutBoolean("Can use arm?", Robot::controlSS->armUse);
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();

	SmartDashboard::PutNumber("Teleop Time", Robot::controlSS->time->Get());

	Robot::controlSS->updateShooter();
	SmartDashboard::PutNumber("Shooter PSI", Robot::controlSS->shooterPSI);
	SmartDashboard::PutBoolean("Can use shooter?", Robot::controlSS->shooterUse);
	Robot::controlSS->updateArm();
	SmartDashboard::PutNumber("Arm PSI", Robot::controlSS->armPSI);
	SmartDashboard::PutBoolean("Can use arm?", Robot::controlSS->armUse);
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);


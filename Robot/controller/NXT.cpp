#include "NXT.h"

NXT::NXT(int port)
{
	bluetoothPort_ = port;
}

NXT::~NXT()
{
	delete connection_;
	delete brick_;
	delete motorA_;
	delete motorB_;
	delete motorC_;
	delete lSensorL_;
	delete lSensorR_;
}

bool NXT::Connect()
{
	connection_ = new Bluetooth();
	brick_ = new Brick(connection_);
	motorA_ = new Motor(OUT_A, connection_);
	motorB_ = new Motor(OUT_B, connection_);
	motorC_ = new Motor(OUT_C, connection_);
	lSensorL_ = new Light(IN_3, connection_, LED_OFF);
	lSensorR_ = new Light(IN_2, connection_, LED_OFF);

	try
	{
		connection_->connect(bluetoothPort_);
	}
	catch (Nxt_exception& e)
	{
		connection_->disconnect();
		return false;
	}

	return true;
}

void NXT::Disconnect()
{
	lSensorL_->set(LED_OFF);
	lSensorR_->set(LED_OFF);

	motorA_->stop();
	motorB_->stop();
	motorC_->stop();

	StopPrograms();

	connection_->disconnect();
}

void NXT::SendMessage(string message)
{
	brick_->write_msg(message, OUT_MAILBOX, false);
}

string NXT::ReadMessage()
{
	return brick_->read_msg(IN_MAILBOX, true); 
}

void NXT::StartProgram(string name)
{
	brick_->start_program(name, false);
}

void NXT::StopPrograms()
{
	brick_->stop_programs(false);
}

void NXT::SetPort(int port)
{
	bluetoothPort_ = port;
}
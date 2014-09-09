#pragma once

#ifndef SERIAL_COMMUNICATOR_H
#define SERIAL_COMMUNICATOR_H


#include "CameraBase.h"

using namespace FlyCapture2;

#define BASE 0X70000
#define START 0x55000000
#define STOP 0x56000000

class SerialCommunicator
{
public:
	SerialCommunicator();
	SerialCommunicator(CameraBase* camera);
	virtual ~SerialCommunicator();

	void SetCamera(CameraBase* camera);
	void SerialTransmit(unsigned int val);

private:
	void InitSerialTransmit();

protected:
	CameraBase* camera;
};



#endif
#include "stdafx.h"
#include "SerialCommunicator.h"


SerialCommunicator::SerialCommunicator()
{
	this->camera = NULL;
}

SerialCommunicator::SerialCommunicator(CameraBase* camera)
{
	this->camera = camera;
	InitSerialTransmit();
}


SerialCommunicator::~SerialCommunicator()
{
}


void SerialCommunicator::InitSerialTransmit()
{
	// Enable serial output
	camera->WriteRegister(BASE+0x004,0x40000000);
	
	// Verify transmit buffer is ready
	unsigned int register_val;
	camera->ReadRegister(BASE+0x004, &register_val);
	if (register_val != 0x40800000) {
		MessageBox(NULL, (LPCSTR)L"Transmit buffer not ready",(LPCSTR)L"SerialTransmit Error",MB_OK);
	}

	// Set baud rate, or use default 19200?
}


void SerialCommunicator::SetCamera(CameraBase* camera)
{
	this->camera = camera;
	InitSerialTransmit();
}


void SerialCommunicator::SerialTransmit(unsigned int val)
{
	if (camera == NULL) {
		return;
	}

	unsigned int register_val;
	FlyCapture2::Error err;
	
	// Verify transmit buffer is ready
	err = camera->ReadRegister(BASE+0x004, &register_val);
	if (err != PGRERROR_OK) {
		MessageBox(NULL, "Error when verifying transmit buffer", "SerialTransmit Error", MB_OK);
	}
	if (register_val != 0x40800000) {
		MessageBox(NULL, "Transmit buffer not ready", "SerialTransmit Error", MB_OK);
		return;
	}

	// Store value in transmit buffer
	err = camera->WriteRegister(BASE+0x0100, val);
	if (err != PGRERROR_OK) {
		MessageBox(NULL, "Error when writing transmit buffer", "SerialTransmit Error", MB_OK);
	}

	// Verify transmit buffer is storing 4 bytes
	err = camera->ReadRegister(BASE+0x000c, &register_val);
	if (err != PGRERROR_OK) {
		MessageBox(NULL, "Error when verifying transmit buffer is stored", "SerialTransmit Error", MB_OK);
	}
	if (register_val != 0xff040000) {
		MessageBox(NULL, "Transmit buffer not stored","SerialTransmit Error",MB_OK);
		return;
	}

	// Send byte
	camera->WriteRegister(BASE+0x000c,0xFF010000);
}
/*=========================================================================

Program:
Module:    $RCSfile: $
Language:  C++
Date:      $Date: $
Version:   $Revision: $

Copyright (c) Canon Inc. All rights reserved.

=========================================================================*/

#include "SlicerSnakeTCPIPComm4Demo.h"

int SlicerSnakeReceiveMsg(igtl::Socket * socket){

	//------------------------------------------------------------
	// Create a message buffer to receive header
	igtl::MessageHeader::Pointer headerMsg;
	headerMsg = igtl::MessageHeader::New();

	//------------------------------------------------------------
	// Allocate a time stamp 
	igtl::TimeStamp::Pointer ts;
	ts = igtl::TimeStamp::New();

	// Initialize receive buffer
	headerMsg->InitPack();

	// Receive generic header from the socket
	int r = socket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
	if (r == 0)
	{
		socket->CloseSocket();
		exit(0);
	}
	if (r != headerMsg->GetPackSize())
	{
		return SLIER_SNAKE_COMM_ERROR;
	}


	// Deserialize the header
	headerMsg->Unpack();

	// Get time stamp
	igtlUint32 sec;
	igtlUint32 nanosec;

	headerMsg->GetTimeStamp(ts);
	ts->GetTimeStamp(&sec, &nanosec);

	/*
	std::cerr << "Time stamp: "
		<< sec << "." << std::setw(9) << std::setfill('0')
		<< nanosec << std::endl;
	*/

	// Check data type and receive data body
	if (strcmp(headerMsg->GetDeviceType(), "TRANSFORM") == 0)
	{
		ReceiveTransform(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "POSITION") == 0)
	{
		ReceivePosition(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "IMAGE") == 0)
	{
		ReceiveImage(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "STATUS") == 0)
	{
		ReceiveStatus(socket, headerMsg);
	}
#if OpenIGTLink_PROTOCOL_VERSION >= 2
	else if (strcmp(headerMsg->GetDeviceType(), "POINT") == 0)
	{
		ReceivePoint(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "TRAJ") == 0)
	{
		ReceiveTrajectory(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "STRING") == 0)
	{
		ReceiveString(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "TDATA") == 0)
	{
		// ReceiveTrackingData(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "QTDATA") == 0)
	{
		// ReceiveQuaternionTrackingData(socket, headerMsg);
	}
	else if (strcmp(headerMsg->GetDeviceType(), "CAPABILITY") == 0)
	{
		ReceiveCapability(socket, headerMsg);;
	}
#endif //OpenIGTLink_PROTOCOL_VERSION >= 2
	else
	{
		std::cerr << "Receiving : " << headerMsg->GetDeviceType() << std::endl;
		socket->Skip(headerMsg->GetBodySizeToRead(), 0);
	}

	return 0;

}

int ReceiveTransform(igtl::Socket * socket, igtl::MessageHeader::Pointer& header)
{
	std::cerr << std::endl << "Receiving TRANSFORM data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::TransformMessage::Pointer transMsg;
	transMsg = igtl::TransformMessage::New();
	transMsg->SetMessageHeader(header);
	transMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(transMsg->GetPackBodyPointer(), transMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = transMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		// Retrive the transform data
		igtl::Matrix4x4 matrix;
		transMsg->GetMatrix(matrix);
		igtl::PrintMatrix(matrix);
		std::cerr << std::endl;

		if (runstate::Globals::RunType == ___TLANSLATOR){
			
			double matrix3x3[3][3];

			for (int i = 0; i < 3; i++){
				for (int j = 0; j < 3; j++){
					matrix3x3[i][j] = (double)matrix[i][j];
				}
			}

			runstate::Globals::SetTransformMatrix3x3(matrix3x3);
		}

		return 1;
	}

	return 0;
}

int ReceivePosition(igtl::Socket * socket, igtl::MessageHeader::Pointer& header)
{
	std::cerr << "Receiving POSITION data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::PositionMessage::Pointer positionMsg;
	positionMsg = igtl::PositionMessage::New();
	positionMsg->SetMessageHeader(header);
	positionMsg->AllocatePack();

	// Receive position position data from the socket
	socket->Receive(positionMsg->GetPackBodyPointer(), positionMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = positionMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		// Retrive the transform data
		float position[3];
		float quaternion[4];

		positionMsg->GetPosition(position);
		positionMsg->GetQuaternion(quaternion);

		std::cerr << "position   = (" << position[0] << ", " << position[1] << ", " << position[2] << ")" << std::endl;
		std::cerr << "quaternion = (" << quaternion[0] << ", " << quaternion[1] << ", "
			<< quaternion[2] << ", " << quaternion[3] << ")" << std::endl << std::endl;

		return 1;
	}

	return 0;
}

int ReceiveImage(igtl::Socket * socket, igtl::MessageHeader::Pointer& header)
{
	std::cerr << "Receiving IMAGE data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::ImageMessage::Pointer imgMsg;
	imgMsg = igtl::ImageMessage::New();
	imgMsg->SetMessageHeader(header);
	imgMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(imgMsg->GetPackBodyPointer(), imgMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = imgMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		// Retrive the image data
		int   size[3];          // image dimension
		float spacing[3];       // spacing (mm/pixel)
		int   svsize[3];        // sub-volume size
		int   svoffset[3];      // sub-volume offset
		int   scalarType;       // scalar type

		scalarType = imgMsg->GetScalarType();
		imgMsg->GetDimensions(size);
		imgMsg->GetSpacing(spacing);
		imgMsg->GetSubVolume(svsize, svoffset);

		std::cerr << "Device Name           : " << imgMsg->GetDeviceName() << std::endl;
		std::cerr << "Scalar Type           : " << scalarType << std::endl;
		std::cerr << "Dimensions            : ("
			<< size[0] << ", " << size[1] << ", " << size[2] << ")" << std::endl;
		std::cerr << "Spacing               : ("
			<< spacing[0] << ", " << spacing[1] << ", " << spacing[2] << ")" << std::endl;
		std::cerr << "Sub-Volume dimensions : ("
			<< svsize[0] << ", " << svsize[1] << ", " << svsize[2] << ")" << std::endl;
		std::cerr << "Sub-Volume offset     : ("
			<< svoffset[0] << ", " << svoffset[1] << ", " << svoffset[2] << ")" << std::endl << std::endl;
		return 1;
	}

	return 0;

}


int ReceiveStatus(igtl::Socket * socket, igtl::MessageHeader::Pointer& header)
{

	std::cerr << "Receiving STATUS data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::StatusMessage::Pointer statusMsg;
	statusMsg = igtl::StatusMessage::New();
	statusMsg->SetMessageHeader(header);
	statusMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(statusMsg->GetPackBodyPointer(), statusMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = statusMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		std::cerr << "========== STATUS ==========" << std::endl;
		std::cerr << " Code      : " << statusMsg->GetCode() << std::endl;
		std::cerr << " SubCode   : " << statusMsg->GetSubCode() << std::endl;
		std::cerr << " Error Name: " << statusMsg->GetErrorName() << std::endl;
		std::cerr << " Status    : " << statusMsg->GetStatusString() << std::endl;
		std::cerr << "============================" << std::endl << std::endl;
	}

	return 0;

}

#if OpenIGTLink_PROTOCOL_VERSION >= 2
int ReceivePoint(igtl::Socket * socket, igtl::MessageHeader::Pointer& header)
{

	std::cerr << "Receiving POINT data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::PointMessage::Pointer pointMsg;
	pointMsg = igtl::PointMessage::New();
	pointMsg->SetMessageHeader(header);
	pointMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(pointMsg->GetPackBodyPointer(), pointMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = pointMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{

		if (runstate::Globals::RunType == ___TLANSLATOR){
			// Determine the pre-defined pathway number (1-3) based on the message name
			runstate::Globals::PathwayNumber = 0;
			if (strcmp(pointMsg->GetDeviceName(), "Pathway_1") == 0) {
				runstate::Globals::PathwayNumber = 1;
			} else if (strcmp(pointMsg->GetDeviceName(), "Pathway_2") == 0) {
				runstate::Globals::PathwayNumber = 2;
			} else if (strcmp(pointMsg->GetDeviceName(), "Pathway_3") == 0) {
				runstate::Globals::PathwayNumber = 3;
			}
                }

		double _zb;
		vector<double> _x;
		vector<double> _z;

		int nElements = pointMsg->GetNumberOfPointElement();
		for (int i = 0; i < nElements; i++)
		{

			igtl::PointElement::Pointer pointElement;
			pointMsg->GetPointElement(i, pointElement);

			igtlUint8 rgba[4];
			pointElement->GetRGBA(rgba);

			igtlFloat32 pos[3];
			pointElement->GetPosition(pos);

			if (!strcmp(pointElement->GetName(), "zb")){ 
				_zb = (double)pos[2]; 
			}
			else if (!strcmp(pointElement->GetName(), "coordinate")){
				_x.push_back((double)pos[0]); 
				_z.push_back((double)pos[2]); 
			}

			std::cerr << "========== Element #" << i << " ==========" << std::endl;
			std::cerr << " Name      : " << pointElement->GetName() << std::endl;
			std::cerr << " GroupName : " << pointElement->GetGroupName() << std::endl;
			std::cerr << " RGBA      : ( " << (int)rgba[0] << ", " << (int)rgba[1] << ", " << (int)rgba[2] << ", " << (int)rgba[3] << " )" << std::endl;
			std::cerr << " Position  : ( " << std::fixed << pos[0] << ", " << pos[1] << ", " << pos[2] << " )" << std::endl;
			std::cerr << " Radius    : " << std::fixed << pointElement->GetRadius() << std::endl;
			std::cerr << " Owner     : " << pointElement->GetOwner() << std::endl;
			std::cerr << "================================" << std::endl << std::endl;

		}

		if (runstate::Globals::RunType == ___SLICER){
			runstate::Globals::Log4Matlab(_zb, _x, _z);
		} else if (runstate::Globals::RunType == ___TLANSLATOR){
			runstate::Globals::ad7011_zb.clear();
			runstate::Globals::LoadPresetPathwayData(runstate::Globals::PathwayNumber);
                }

	}

	return 1;
}

int ReceiveTrajectory(igtl::Socket * socket, igtl::MessageHeader::Pointer& header)
{

	std::cerr << "Receiving TRAJECTORY data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::TrajectoryMessage::Pointer trajectoryMsg;
	trajectoryMsg = igtl::TrajectoryMessage::New();
	trajectoryMsg->SetMessageHeader(header);
	trajectoryMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(trajectoryMsg->GetPackBodyPointer(), trajectoryMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = trajectoryMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		int nElements = trajectoryMsg->GetNumberOfTrajectoryElement();
		for (int i = 0; i < nElements; i++)
		{
			igtl::TrajectoryElement::Pointer trajectoryElement;
			trajectoryMsg->GetTrajectoryElement(i, trajectoryElement);

			igtlUint8 rgba[4];
			trajectoryElement->GetRGBA(rgba);

			igtlFloat32 entry[3];
			igtlFloat32 target[3];
			trajectoryElement->GetEntryPosition(entry);
			trajectoryElement->GetTargetPosition(target);

			std::cerr << "========== Element #" << i << " ==========" << std::endl;
			std::cerr << " Name      : " << trajectoryElement->GetName() << std::endl;
			std::cerr << " GroupName : " << trajectoryElement->GetGroupName() << std::endl;
			std::cerr << " RGBA      : ( " << (int)rgba[0] << ", " << (int)rgba[1] << ", " << (int)rgba[2] << ", " << (int)rgba[3] << " )" << std::endl;
			std::cerr << " Entry Pt  : ( " << std::fixed << entry[0] << ", " << entry[1] << ", " << entry[2] << " )" << std::endl;
			std::cerr << " Target Pt : ( " << std::fixed << target[0] << ", " << target[1] << ", " << target[2] << " )" << std::endl;
			std::cerr << " Radius    : " << std::fixed << trajectoryElement->GetRadius() << std::endl;
			std::cerr << " Owner     : " << trajectoryElement->GetOwner() << std::endl;
			std::cerr << "================================" << std::endl << std::endl;
		}
	}

	return 1;
}

int ReceiveString(igtl::Socket * socket, igtl::MessageHeader::Pointer& header)
{

	std::cerr << "Receiving STRING data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::StringMessage::Pointer stringMsg;
	stringMsg = igtl::StringMessage::New();
	stringMsg->SetMessageHeader(header);
	stringMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(stringMsg->GetPackBodyPointer(), stringMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = stringMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		std::cerr << "Encoding: " << stringMsg->GetEncoding() << "; "
			<< "String: " << stringMsg->GetString() << std::endl << std::endl;
	}

	if (runstate::Globals::RunType == ___TLANSLATOR){
		assert(atoi(stringMsg->GetString()) > 0 && atoi(stringMsg->GetString()) < 4);
		runstate::Globals::PathwayNumber = atoi(stringMsg->GetString());
		runstate::Globals::ad7011_zb.clear();
		runstate::Globals::LoadPresetPathwayData(runstate::Globals::PathwayNumber);
	}

	if (strcmp(stringMsg->GetString(), "Recieve end from the translator.") == 0){
		runstate::Globals::isRecvEnd = RECIEVE_END_FROM_TRANSLATOR;
	}

	return 1;
}

int ReceiveTrackingData(igtl::ClientSocket::Pointer& socket, igtl::MessageHeader::Pointer& header)
{
	std::cerr << "Receiving TDATA data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::TrackingDataMessage::Pointer trackingData;
	trackingData = igtl::TrackingDataMessage::New();
	trackingData->SetMessageHeader(header);
	trackingData->AllocatePack();

	// Receive body from the socket
	socket->Receive(trackingData->GetPackBodyPointer(), trackingData->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = trackingData->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		int nElements = trackingData->GetNumberOfTrackingDataElements();
		for (int i = 0; i < nElements; i++)
		{
			igtl::TrackingDataElement::Pointer trackingElement;
			trackingData->GetTrackingDataElement(i, trackingElement);

			igtl::Matrix4x4 matrix;
			trackingElement->GetMatrix(matrix);


			std::cerr << "========== Element #" << i << " ==========" << std::endl;
			std::cerr << " Name       : " << trackingElement->GetName() << std::endl;
			std::cerr << " Type       : " << (int)trackingElement->GetType() << std::endl;
			std::cerr << " Matrix : " << std::endl;
			igtl::PrintMatrix(matrix);
			std::cerr << "================================" << std::endl << std::endl;
		}
		return 1;
	}
	return 0;
}

int ReceiveQuaternionTrackingData(igtl::ClientSocket::Pointer& socket, igtl::MessageHeader::Pointer& header)
{
	std::cerr << "Receiving QTDATA data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::QuaternionTrackingDataMessage::Pointer quaternionTrackingData;
	quaternionTrackingData = igtl::QuaternionTrackingDataMessage::New();
	quaternionTrackingData->SetMessageHeader(header);
	quaternionTrackingData->AllocatePack();

	// Receive body from the socket
	socket->Receive(quaternionTrackingData->GetPackBodyPointer(), quaternionTrackingData->GetPackBodySize());

	// Deserialize position and quaternion (orientation) data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = quaternionTrackingData->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		int nElements = quaternionTrackingData->GetNumberOfQuaternionTrackingDataElements();
		for (int i = 0; i < nElements; i++)
		{
			igtl::QuaternionTrackingDataElement::Pointer quaternionTrackingElement;
			quaternionTrackingData->GetQuaternionTrackingDataElement(i, quaternionTrackingElement);

			float position[3];
			float quaternion[4];
			quaternionTrackingElement->GetPosition(position);
			quaternionTrackingElement->GetQuaternion(quaternion);

			std::cerr << "========== Element #" << i << " ==========" << std::endl;
			std::cerr << " Name       : " << quaternionTrackingElement->GetName() << std::endl;
			std::cerr << " Type       : " << (int)quaternionTrackingElement->GetType() << std::endl;
			std::cerr << " Position   : "; igtl::PrintVector3(position);
			std::cerr << " Quaternion : "; igtl::PrintVector4(quaternion);
			std::cerr << "================================" << std::endl << std::endl;
		}
		return 1;
	}
	return 0;
}

int ReceiveCapability(igtl::Socket * socket, igtl::MessageHeader * header)
{

	std::cerr << "Receiving CAPABILITY data type." << std::endl;

	// Create a message buffer to receive transform data
	igtl::CapabilityMessage::Pointer capabilMsg;
	capabilMsg = igtl::CapabilityMessage::New();
	capabilMsg->SetMessageHeader(header);
	capabilMsg->AllocatePack();

	// Receive transform data from the socket
	socket->Receive(capabilMsg->GetPackBodyPointer(), capabilMsg->GetPackBodySize());

	// Deserialize the transform data
	// If you want to skip CRC check, call Unpack() without argument.
	int c = capabilMsg->Unpack(1);

	if (c & igtl::MessageHeader::UNPACK_BODY) // if CRC check is OK
	{
		int nTypes = capabilMsg->GetNumberOfTypes();
		for (int i = 0; i < nTypes; i++)
		{
			std::cerr << "Typename #" << i << ": " << capabilMsg->GetType(i) << std::endl;
		}
	}

	return 1;

}

int SendToSlicer(igtl::Socket *socket){

	assert(runstate::Globals::re_x.size() == SEATH_CELL);
	assert(runstate::Globals::re_x.size() == runstate::Globals::re_z.size());


	// Send the 60 coordinate data and zb to the slicer
	// Response data is 61 set.
	// Position[0] : zb data (0, 0, zb)
	// Position[1] : coordinate data (x1, 0, z1)
	// ...
	// Position[60]: coordinate data (x60, 0, z60) 

	// Create point data to response to the client
	igtl::PointElement::Pointer re_pointElement_zb;
	re_pointElement_zb = igtl::PointElement::New();

	// Create re_pointMsg to response to the client
	igtl::PointMessage::Pointer re_pointMsg;
	re_pointMsg = igtl::PointMessage::New();

	vector<double> re_zb(3, 0); // initialized (0, 0, 0)
	vector<double> re_RAS_zb(3, 0); // initialized (0, 0, 0)

	re_zb[2] = runstate::Globals::re_zb;

	assert(re_zb.size() == 3);

	runstate::Globals::ConvertXYZToRAS(re_zb, runstate::Globals::TransformMatrix, re_RAS_zb);

	assert(re_RAS_zb.size() == 3);

	re_pointElement_zb->SetName("zb");
	re_pointElement_zb->SetPosition(0, 0, re_RAS_zb[2]);

	re_pointMsg->AddPointElement(re_pointElement_zb);
	re_pointMsg->Pack();

	for (int i = 0; i < (int)runstate::Globals::re_x.size(); i++){

		// Create point data to response to the client
		igtl::PointElement::Pointer re_pointElement_ras;
		re_pointElement_ras = igtl::PointElement::New();
		
		vector<double> re_XYZ(3, 0); // initialized (0, 0, 0)
		vector<double> re_RAS(3, 0); // initialized (0, 0, 0)

		re_XYZ[0] = runstate::Globals::re_x[i];
		re_XYZ[2] = runstate::Globals::re_z[i];

		assert(re_XYZ.size() == 3);

		runstate::Globals::ConvertXYZToRAS(re_XYZ, runstate::Globals::TransformMatrix, re_RAS);

		assert(re_RAS.size() == 3);

		re_pointElement_ras->SetName("coordinate");
		re_pointElement_ras->SetPosition(re_RAS[0], re_RAS[1], re_RAS[2]);

		re_pointMsg->AddPointElement(re_pointElement_ras);
		re_pointMsg->Pack();

	}

	socket->Send(re_pointMsg->GetPackPointer(), re_pointMsg->GetPackSize());

	return 0;

}

#endif //OpenIGTLink_PROTOCOL_VERSION >= 2

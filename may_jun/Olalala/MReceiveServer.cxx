#include "MReceiveServer.h"
#include "MConnectorWindow.h"


// -------------------- Class MReceiveServer -------------------- //
MReceiveServer::MReceiveServer(int port)
{
 std::cerr << "into MRS" << std::endl;

  // Prepare the server and client socket
  ////  igtl::ServerSocket::Pointer serverSocket;
  serverSocket = igtl::ServerSocket::New();
  serverSocket->CreateServer(port);

  ////  igtl::Socket::Pointer clientSocket;
  while(1)
  {
    // Wait for connection
    clientSocket = serverSocket->WaitForConnection(10000);  // 10 seconds

    if (clientSocket.IsNotNull())  // if client connected
    {
      //// igtl::MessageHeader::Pointer headerMsg;
      headerMsg = igtl::MessageHeader::New();
  
      // looping
      for(int i = 0; i<100; i++)
      {
        headerMsg->InitPack();
        int r = clientSocket->Receive(headerMsg->GetPackPointer(), headerMsg->GetPackSize());
        headerMsg->Unpack();

        if(strcmp(headerMsg->GetDeviceType(), "TRANSFORM") == 0)
        {
	  // Message body handler for TRANSFORM
          MReceiveServer::ReceiveTransform(clientSocket, headerMsg);
        }
      }
    }    // endif client connected 
  }

  clientSocket->CloseSocket();

  //////  delete[] receiveData;

}


//
// Private functions
//// double *MReceiveServer::ReceiveTransform(igtl::Socket *clientSocket, igtl::MessageHeader *header)
//

int MReceiveServer::ReceiveTransform(igtl::Socket *clientSocket, igtl::MessageHeader *header)
{
  //// igtl::TransformMessage::Pointer transMsg;
  transMsg = igtl::TransformMessage::New();

  // Put the header information to the transform message
  transMsg->SetMessageHeader(header);
  transMsg->AllocatePack();

  // Receive the message body
  clientSocket->Receive(transMsg->GetPackBodyPointer(), transMsg->GetPackBodySize());

  // Unpack the message body
  int c = transMsg->Unpack(1);
  if (c & igtl::MessageHeader::UNPACK_BODY)   // if Cyclic redundancy check is ok, read transform data.
  {
    // Retrive the transform data
    igtl::Matrix4x4 mat4x4;
    transMsg->GetMatrix(mat4x4);
    //////    igtl::PrintMatrix(matrix);

    //////  matData = new double[15];
    matData[0] = mat4x4[0][0];
    matData[1] = mat4x4[0][1];
    matData[2] = mat4x4[0][2];
    matData[3] = mat4x4[0][3];


    matData[4] = mat4x4[1][0];
    matData[5] = mat4x4[1][1];
    matData[6] = mat4x4[1][2];
    matData[7] = mat4x4[1][3];

    matData[8] = mat4x4[2][0];
    matData[9] = mat4x4[2][1];
    matData[10] = mat4x4[2][2];
    matData[11] = mat4x4[2][3];

    matData[12] = mat4x4[3][0];
    matData[13] = mat4x4[3][1];
    matData[14] = mat4x4[3][2];
    matData[15] = mat4x4[3][3];
  }
  //// return matData;
  return 1;
}


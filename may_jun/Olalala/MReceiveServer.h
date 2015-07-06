#ifndef _MReceiveServer_h
#define _MReceiveServer_h

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>

#include "igtlOSUtil.h"
#include "igtlMessageHeader.h"
#include "igtlTransformMessage.h"
#include "igtlImageMessage.h"
#include "igtlServerSocket.h"
#include "igtlStatusMessage.h"
#include "igtlPositionMessage.h"


class MReceiveServer {

  protected:
    MReceiveServer(){};

 public:
    MReceiveServer(int port);
    virtual ~MReceiveServer(){};

// --------------------  -------------------- //
  private:
    igtl::ServerSocket::Pointer        serverSocket;
    igtl::Socket::Pointer              clientSocket;   
    igtl::MessageHeader::Pointer       headerMsg;
    igtl::TransformMessage::Pointer    transMsg;
    igtl::Matrix4x4                    matrix;

    ////  double        *ReceiveTransform(igtl::Socket *clientSocket, igtl::MessageHeader *header);

    int        ReceiveTransform(igtl::Socket *clientSocket, igtl::MessageHeader *header); 

    
  public:
    double         matData[];
    

};    // end class

 

#endif

/* client.cpp
 *
 * tcp client connects to mwars MCU server
 *
*/

#include "console.h"
#include "ui_consoleForm.h"


//--------------------------------------------------------------------------------------
// sendScannerMssg(cmdMssg cmd, ushort x, ushort y)
//		callers: a) sendScanCmd(void) of form
//                      sendScannerMssg(CMD_SLEW, scannerState.XPos, scannerState.YPos);
//
//               b) scannerOn(), scannerOff(), laserOn(), laserOff() of form:
//                      sendScannerMssg( CMD_LASER_OFF, 0, 0);
//
//                  ALSO listener()  for UDP stream from openCV
//
//--------------------------------------------------------------------------------------
void Mwars::sendScannerMssg(ushort cmd, ushort x, ushort y) {

    struct clientMssg mssg;


    qDebug ("sendScannerMssg(), sent: %d %d %d", x, y, cmd);


     // send a message in disconnected state crashes system
     if (tcpConnected == false)  {
         ui->notificationLabel->setText("Not Connected to Server");
         return;
     }

   //  if (verbose)
    //         qDebug("A sent : %d", x);

 //  NOTE THIS!!!! IT'S BOUND TO FUCK SOMETHING UP
     // scanner direction is backwards.
     // Reverse it, but only for slew commands, else e.g. laserOff has x=0 and
     // sets x = 0xA000
     // note console.cpp line 65 re-inverts for display
  //   if (cmd == CMD_SLEW){
        y = SCANNER_DAC_LIMIT - y;
        x = SCANNER_DAC_LIMIT - x;
 //    }

    if (verbose)
            qDebug("client sent : %d %d %d", x, y, cmd);

    // convert words from host to network order & construct mssg
    mssg.info =   htons(cmd);
    mssg.XPos = htons(x);
    mssg.YPos = htons(y);

    clientSocket.write( (char*)&mssg, qint64(sizeof (mssg)));
    clientSocket.flush();
}


//--------------------------------------------------------------------------------------
// OnReadyRead()
//
//		signals:	readyRead() emitted by udp & tcp sockets when new data available

//  both tcp and udp sockets emit readyRead() signal when data is received
//  this routine invoked on readyRead signal, wher QObject sigsender is used to identify
//  if it was the tcp or udp socket   
//
// readyRead() is not emitted recursively; if you reenter the event loop or call waitForReadyRead()
// inside a slot connected to the readyRead() signal, the signal will not be reemitted
// This places the handler in a while loop to resolve as per http://qt-project.org/forums/viewthread/10184
//--------------------------------------------------------------------------------------
void Mwars::OnReadyRead(void) {

    QObject *sigsender=sender();  // sigsender identifies origin of the signal
    QHostAddress sender;          // readDatagram saves the sender's host address and port in *address and *port
  //  quint16 senderPort;

  //  static int count;
   // struct opencvMssg mssg;

   // qDebug() << "entered OnScannerReadyRead()" << count++;

   // qDebug() << "Message from: " << sender.toString();
   // qDebug() << "Message port: " << senderPort;

    //http://www.qtcentre.org/archive/index.php/t-31700.html
    //QIODevice *dev = qobject_cast<QIODevice*>(sender());
    //if (!dev) return;
    //qDebug() << dev->readAll();

 /*   if (sigsender) {
        qDebug() << " signal call objn: " << sigsender->objectName() << " clasn: " << sigsender->metaObject()->className();
    } else {
        qDebug() << " direct call";
        return;
    }
*/
 //   QString sQUdpSocket = "QUdpSocket";
 //   QString sQTcpSocket = "QTcpSocket";

    // a) ----------------------   UDP socket has data ------------------------------
    
    if (sigsender->metaObject()->className() == QString("QUdpSocket")) {

    //qDebug() << "UDP readyRead()" << count++;

    while (listenSocket->hasPendingDatagrams()) {

        // read and process UDP data packets
        listener();
        }       // while
    }           // if UDP socket
    
    // b) ----------------------    tcp socket has data ------------------------------   
    else if (sigsender->metaObject()->className() == QString("QTcpSocket")) {

       //  qDebug() << "TCP readyRead() " << count++;

        int iBytesAvailable = clientSocket.bytesAvailable();

        while(iBytesAvailable > 0) {
            if(clientSocket.isValid())
               //  console.cpp; readScannerResponse reads, processess data at tcp socket
               readScannerResponse();  
            else {
               qDebug("Warning. Socket is not valid to read data from");
               break;
            }
        iBytesAvailable = clientSocket.bytesAvailable();
        }   // while
     }
  return;
 }


//--------------------------------------------------------------------------------------
// connectToScanner(void)
//		signals:	connectScanner() in Constructor
//					pushButtonConnect(clicked)
//
// clientSocket: client socket sends stream to scanner
//--------------------------------------------------------------------------------------
void Mwars::connectToScanner(void) {
    qDebug() << "started connectToScanner";
    clientSocket.abort();
    clientSocket.connectToHost(QString(SCANNERADDRESS), int(SCANNERPORT));
    return;
     }


//--------------------------------------------------------------------------------------
// clientSocketState( QAbstractSocket::SocketState state)
//		signals:	SocketState state 		emitted by clientSocket
//					(also avail:  void bytesWritten(qint64 bytes)
//
// clientSocket: client socket sends stream to scanner
//--------------------------------------------------------------------------------------
void Mwars::clientSocketState( QAbstractSocket::SocketState state)  {

    QString stateMssg;

    ui->pushButtonConnect->setEnabled(true);		// disable Connect button
    ui->notificationLabel->setText("");             // clear any previous notification

     switch(state) 	 {
        case QAbstractSocket::UnconnectedState: stateMssg = "UnconnectedState"; break;
        case QAbstractSocket::HostLookupState:  stateMssg = "HostLookupState"; break;
        case QAbstractSocket::ConnectingState:  stateMssg = "ConnectingState"; break;
        case QAbstractSocket::ConnectedState:   stateMssg = "ConnectedState"; break;
        case QAbstractSocket::ListeningState:   stateMssg = "ListeningState"; break;
        case QAbstractSocket::ClosingState:     stateMssg = "ClosingState"; break;
     }
    ui->tcpStateLabel->setText(stateMssg);

    if( state == QAbstractSocket::ConnectedState ) {		// CONNECTED
        tcpConnected = true;
        ui->tcpStateLabel->setStyleSheet("color: rgb(0, 0, 0)");	// display tcpState in black
 //       ui->pushButtonConnect->setText("RE-CONNECT");
        ui->notificationLabel->setText("");
        enableWidgets();

        laserOff();         // this also updates serverState
        scannerOff();
        verboseOff();

    //    cameraDataEnableFlag = false;
        serverReady = true; // ready for data reception
        qDebug()<< "Server is Ready";
    }
    else {													// NOT CONNECTED
        tcpConnected = false;
        serverReady = false;
    //    cameraDataEnableFlag = false;
        ui->tcpStateLabel->setStyleSheet("color: rgb(255, 0, 0)");	// display tcpState in red
      //  ui->pushButtonConnect->setText("CONNECT");
        ui->pushButtonConnect->setDefault(true);			// default button

#ifdef FORCE_ENABLE_WIDGETS
    enableWidgets();
#else
     disableWidgets();				// control widgets get enabled when connected
#endif

    }
}


//--------------------------------------------------------------------------------------
// clientSocketError( QAbstractSocket::SocketError error)
//		signals:	SocketError error 		emitted by clientSocket
//
// clientSocket: client socket sends stream to scanner
//--------------------------------------------------------------------------------------
void Mwars::clientSocketError( QAbstractSocket::SocketError socketError) {

    serverReady = false;
  //  cameraDataEnableFlag = false;

    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("scannerClient"),
            tr("The host was not found. Check host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("scannerClient"),
            tr("The connection was refused by the peer.Check scanner server is running, "
               "and check that the host name and port settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("scannerClient"),
             tr("The following error occurred: %1.").arg(clientSocket.errorString()));
    }

    ui->notificationLabel->setStyleSheet("color: rgb(255, 0, 0)");
    ui->notificationLabel->setText(QString(tr("TCP error: %1").arg( clientSocket.errorString() ) ));
    ui->pushButtonConnect->setDefault(true);						// default button

    }

//--------------------------------------------------------------------------------------
// scanner clientSocketError( QAbstractSocket::disconnected())
//		signals:	disconnected()		emitted by clientSocket
//
// clientSocket: client socket sends stream to scanner
//--------------------------------------------------------------------------------------
// I would like to use this to detect when the server becomes disconnected
void Mwars::disconnectedz(void) {

  //  cameraDataEnableFlag = false;
    qDebug() << "entered disconnected";
}


//--------------------------------------------------------------------------------------
// void MWars::keepServerAlive(void)
//		signals:	keepServerAliveTimer timeout()
//
// this receives a timeout signal every 1/2 second and sends KEEP_ALIVE message
// needed to get a response to update the Console
//-------------------------------------------------------------------------------------
void Mwars::keepServerAlive(void) {
   if (serverReady)
      sendScannerMssg(CMD_NULL_MSSG, 0, 0);
}



//--------------------------------------------------------------------------------------
// readScannerResponse(void)
//		called from OnReadyRead() to read tcp data from scanner unit
//--------------------------------------------------------------------------------------
void Mwars::readScannerResponse(void) {

    clientSocket.read((char*)&serverMssg, qint64(sizeof(serverMssg)));

    // note these are co-ords not angles. Change?
    //serverMssg.info = ntohs(serverMssg.info);           //contains count sent back from server for test
    //serverMssg.XPos = ntohs(serverMssg.XPos);
    //serverMssg.YPos = ntohs(serverMssg.YPos);

    // update scannerState with values returned from server
    // scannerState.status = serverMssg.status;
    //scannerState.XPos = serverMssg.XPos;
    //scannerState.YPos = serverMssg.YPos;

    // update scannerState with values returned from server
    // note these are co-ords not angles. Change?
    scannerState.status = serverMssg.status;
    serverMssg.info = ntohs(serverMssg.info);           //contains count sent back from server for test
    scannerState.XPos = ntohs(serverMssg.XPos);
    scannerState.YPos = ntohs(serverMssg.YPos);


    // show it
    // client.cpp reverses scanner direction at line 43.
    // this reverses the values echoed back for display
    ui->lcdNumberX->display(SCANNER_DAC_LIMIT - scannerState.XPos);
    ui->lcdNumberY->display(SCANNER_DAC_LIMIT - scannerState.YPos);

/*    if (verbose)
        qDebug("recv from scan: %d %d %d %d %d %d %d %d %d %d %x %x",
            serverMssg.status.serverFault, serverMssg.status.laserFault,          //0, 1
            serverMssg.status.scanXFault, serverMssg.status.scanYFault,           //2, 3
            serverMssg.status.unknownScannerFault, serverMssg.status.hwStartFail, //4, 5
            serverMssg.status.laserPower,serverMssg.status.XShutDown,             //6, 7
            serverMssg.status.YShutDown, serverMssg.status.spiError,              //8, 9
            scannerState.XPos, scannerState.YPos);                            // angles
*/
    //   if (verbose)
//        qDebug("recv from scan: %x %x", scannerState.XPos, scannerState.YPos);


    //  display fault notifications ======================

/*
DISABLED DUE TO BAD FAULT STATUS REPORTING FROM SCANNER

    // serverFault is set when any of the following are set
    if 	(scannerState.status.serverFault) {
        ui->labelScannerStateFault->setText("FAULT");
        ui->labelScannerStateFault->setStyleSheet("color: rgb(255, 0, 0)");

        ui->notificationLabel->setStyleSheet("color: rgb(255, 0, 0)");   // red for error
        ui->notificationLabel->setText("Server fault");

        // clear any previous error
        ui->notificationLabel->setText("");

       if ( scannerState.status.hwStartFail)
           ui->notificationLabel->setText("hwStartFail, server HW interrupts are disabled");
       if ( scannerState.status.scanXFault)
            ui->notificationLabel->setText("scanXFault, server HW interrupts are disabled");
       if ( scannerState.status.scanYFault)
            ui->notificationLabel->setText("scanYFault, server HW interrupts are disabled");
       if ( scannerState.status.unknownScannerFault)
            ui->notificationLabel->setText("unknownScannerFault, server HW interrupts are disabled");
        if ( scannerState.status.spiError)
            ui->notificationLabel->setText("spiError");
   }
   else  {
       ui->labelScannerStateFault->setText("OK");
       ui->labelScannerStateFault->setStyleSheet("color: rgb(0, 255, 0)");

       ui->notificationLabel->setStyleSheet("color: rgb(0, 0, 0)");   // clear
       ui->notificationLabel->setText("");
    }
 */

    //================  display server status ======================
    if 	(scannerState.status.XShutDown) {
        ui->labelScanXPwr->setText("ON");
        ui->labelScanXPwr->setStyleSheet("color: rgb(0, 255, 0)");  }
        else {
        ui->labelScanXPwr->setText("OFF");
        ui->labelScanXPwr->setStyleSheet("color: rgb(100, 100, 100)");
    }
    if 	(scannerState.status.YShutDown) {
        ui->labelScanYPwr->setText("ON");
        ui->labelScanYPwr->setStyleSheet("color: rgb(0, 255, 0)");  }
        else {
        ui->labelScanYPwr->setText("OFF");
        ui->labelScanYPwr->setStyleSheet("color: rgb(100, 100, 100)");
    }
    if 	(scannerState.status.laserPower) {
        ui->labelLaserPwr->setText("ON");
        ui->labelLaserPwr->setStyleSheet("color: rgb(0, 255, 0)");  }
        else {
        ui->labelLaserPwr->setText("OFF");
        ui->labelLaserPwr->setStyleSheet("color: rgb(100, 100, 100)");
    }

    if 	(scannerState.status.scanXFault) {
         ui->labelScanXFlt->setText("FAULT");
         ui->labelScanXFlt->setStyleSheet("color: rgb(255, 0, 0)");  }
        else {
         ui->labelScanXFlt->setText("");
         ui->labelScanXFlt->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if 	(scannerState.status.scanYFault) {
         ui->labelScanYFlt->setText("FAULT");
         ui->labelScanYFlt->setStyleSheet("color: rgb(255, 0, 0)");  }
        else {
         ui->labelScanYFlt->setText("");
         ui->labelScanYFlt->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if 	(scannerState.status.laserFault) {
         ui->labelLaserFlt->setText("FAULT");
         ui->labelLaserFlt->setStyleSheet("color: rgb(255, 0, 0)");  }
        else {
         ui->labelLaserFlt->setText("");
         ui->labelLaserFlt->setStyleSheet("color: rgb(0, 0, 0)");
    }
    if 	(scannerState.status.hwStartFail) {
         ui->labelHWStartFault->setText("Hardware Start Failure");
         ui->labelHWStartFault->setStyleSheet("color: rgb(255, 0, 0)");  }
        else {
         ui->labelHWStartFault->setText("OK");
         ui->labelHWStartFault->setStyleSheet("color: rgb(0, 255, 0)");
    }
}














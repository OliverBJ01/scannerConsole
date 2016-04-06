#ifndef MWARS_H
#define MWARS_H

//#define FORCE_ENABLE_WIDGETS      // sets all widgets active for testing



#include "scannerDraw.h"

#include <QMainWindow>
#include <QThread>
#include <QTimer>
#include <QtCore/qstring.h>
#include <QMessageBox>
#include <qiodevice.h>               // for tcp state
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <QXmlStreamWriter>

#include <iostream>
#include "/usr/include/arpa/inet.h"  // for htons()
#include "/usr/include/math.h"

#define SCANNERPORT 1000            // TCP scanner port
#define SCANNERADDRESS "10.1.1.99"  // scanner IP address

#define OPENCVPORT 9988             // UDP port to receive from openCV
// own address

// status word bits
#define SW_NO_FAULT		false
#define SW_FAULT		true
#define SW_POWER_ON		0		//~logic
#define SW_POWER_OFF	1

#define FAULT		true
#define NO_FAULT  	false

// used only to reverse direction in sendScannerMssg()
#define SCANNER_DAC_LIMIT 65535


// scanner frame size is theoretically 0 to 65535 both x and y set by scanner DAC range
// However, this is the practical frame size as scanner board trips outside these values
#define DAC_X_MIN 512
#define DAC_X_MAX 65024
#define DAC_Y_MIN 512
#define DAC_Y_MAX 65024

// ------- logitech cam -----------
// --------------------------------
// a. logitech camera frame size in pixels
#define CAMERA_X_PIXELS 640    //1280
#define CAMERA_Y_PIXELS 480    //960


// globals    Probably should be a structure
// calibration variables read on startup to align and scale camera FOV to scanner FOV
// maintained in XML file
extern unsigned int g_xScanFOVOrigin_su, g_yScanFOVOrigin_su;   // corresponds to camera FOV 0,0
extern unsigned int g_xScanFOVMax_su, g_yScanFOVMax_su;         // corresponds to camera FOV xmax, ymax

extern int g_xCamtoScanOffset_mm;     // measured x offset from cam to scanner in direction away from origin at TLHC (mm)
extern int g_yCamtoScanOffset_mm;
//extern int g_xCamTrim;            //  trim applied to correct for cam offset from testing
//extern int g_yCamTrim;

extern int g_xLenWallFOV_mm;     // measured width, x axis, of FOV at target distance = range (mm)
extern int g_yLenWallFOV_mm;
extern int range_mm;            // measured range cam to target (mm)




// ------------- maintains the current scanner state ----------------------
struct statusWord {
    ushort	serverFault		:	1;	// server has fault
    ushort 	laserFault		:	1;	// server fault
    ushort	scanXFault		:	1;	// server fault
    ushort	scanYFault		:	1;	// server fault
    ushort	unknownScannerFault	:	1;	// server fault
    ushort 	hwStartFail		:	1;	// server hardware didn't start
    ushort 	laserPower		: 	1;	// client command
    ushort	XShutDown       :	1;	// client command
    ushort	YShutDown       :	1;	// client command
    ushort	badClientMssg	:	1;	// client command
    ushort	spiError		:	1;	// server sets on excessive spi errors
    ushort	verbose			:	1;	// client command
} ;

struct   scannerState {
    ushort XPos;
    ushort YPos;
    ushort info;            // passes cmdMssg to server,
    struct statusWord status;
}  ;

// ------------------ message structures and content ----------------------
// 1.  UDP message from openCV client to (this) server
struct opencvMssg {
    ushort XPos;        //scanner X value
    ushort YPos;
    bool laserOn;       // turn laser on
};

// 2. TCP message: (this) client scanner console to server in scanner device
struct clientMssg {
    ushort XPos;       //scanner X value
    ushort YPos;
    ushort info;		// send data client to server & vice versa
} ;

// 3. TCP message: server in scanner device to (this) client scanner console
struct serverMssg {      // message back from server
    ushort XPos;         //scanner X value
    ushort YPos;
    ushort info;
    struct statusWord status;
};

// (this) client's commands to server
enum cmdMssg {CMD_LASER_OFF, CMD_LASER_ON,
            CMD_SCANXPWR_OFF, CMD_SCANXPWR_ON,
            CMD_SCANYPWR_OFF, CMD_SCANYPWR_ON,
        //	CMD_DAC_RESET_OFF, CMD_DAC_RESET_ON,
            CMD_SLEW, CMD_VERBOSE_ON, CMD_VERBOSE_OFF,
            CMD_NULL_MSSG, CMD_RESET } ;

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
namespace Ui {
class mwarsForm;
}

//--------------------------------------------------------------------------------------
// class Mwars
//--------------------------------------------------------------------------------------
class Mwars : public QMainWindow  {
    Q_OBJECT

public:
    explicit Mwars(QWidget *parent = 0);
    ~Mwars();


    QTcpSocket clientSocket;   // client socket the MCU scanner's server
    QUdpSocket *listenSocket;  // socket for UDP stream from OpenCV


private:
     Ui::mwarsForm *ui;


    QThread *workerThread;  // Thread object which will let us manipulate the running thread
    ScannerDraw *scannerDraw; // Object which contains methods that should be run in another thread
    bool rectangleIsRunning;
    // can do scannerDraw->Bresenham(...)


    QXmlStreamReader Rxml;

     // 'global' structures and flags
     struct scannerState scannerState;   // client copy of the scanner's state
     struct serverMssg serverMssg;       // servers response message

    bool verbose;               // verbose OFF
    bool laserDisableFlag;
    bool laserOnFlag;
    bool scannerOnFlag;
    bool verboseEnableFlag;
    bool testDataEnableFlag;    // set by Enable Test Data button to turn on test data stream
    bool cameraDataEnableFlag;  // set by Enable Camera Data button to turn on camera ata stream
    bool tcpConnected;          // tcp connected
    bool serverReady;
    bool calibrateFlag;



signals:
    void connectScanner(void);

public slots:
    void sendScannerMssg(ushort cmd, ushort x, ushort y);
    void scannerOn(void);
    void scannerOff(void);
    void laserOn(void);
    void laserOff(void);

private slots:
    // client.cpp
    void clientSocketState(QAbstractSocket::SocketState state);
    void clientSocketError(QAbstractSocket::SocketError error);
    void OnReadyRead(void);
    void connectToScanner(void);
    void disconnectedz(void);
    void keepServerAlive(void);

    //console.cpp
    void readScannerResponse(void);
    void laserDisableToggle(void);
    void sendScanCmd(void);
    void scannerToggle(void);
    void on_pbLaserToggle_clicked(void);
    void resetScanner(void);
    void verboseOn(void);
    void verboseOff(void);
    void clearStateWidets(void);
    //void testSignal(void);

    void testDataToggle(void);
    void enableTestData(void);
    void disableTestData(void);

    void cameraDataToggle(void);
    void enableCameraData(void);
    void disableCameraData(void);

    void disableWidgets(void);
    void enableWidgets(void);
    void centre_scanner(void);

    // listener.cpp
    void listener(void);

    // calibration stuff
    void calibrateToggle();
    void calibrateOn();
    void calibrateOff();

    int readXMLFile(void);
    int writeXMLFile(void);
    void calSetULHC(void);
    void calSetLRHC(void);
    void ReadCamElements(void);
    int calFullFrame(void);
    int calHalfFrame(void);
    void xCamTrim(void);
    void yCamTrim(void);
    int camTrimOffset(void);

    void xCamOffset(void);
    void yCamOffset(void);
    int  camScanOffset(void);

    void alignBoresight(void);

    void translateTargetCoords(ushort &x_p, ushort &y_p);

    // for scannerDraw bresenham
    void on_pbRectangle_clicked();
    void rectangleFinished(void);
    void stopRectangle();

    void disableCalibrationWidgets(void);
};

#endif //MWARS_H


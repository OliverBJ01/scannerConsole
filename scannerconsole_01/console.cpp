////  NOTE
/*	System Calibration
 *      a. measure range to target plane (wall)
 *      b. projecte a line onto a 1m rule on the wall, adjust line length to ruler length, recored delta scanner units.
 *          derives the mm to scanunit scale factor
 *      c. measure laser to camera offsets
 *
 *      d. using calibration tool
 *          align scanner rectangle over full or 1/2 frame rectangle drawn on camera sensor
 *              derives the pixels to scanunit scale factor
 *
 * Qtimer timer;
    timer.setInterval(50);
    connect(&timer, ..
        or
    QTimer *timer = new QTimer(this);
    timer->start(500);
    connect(timer, */


#include "console.h"
#include "ui_consoleForm.h"


// stored in calibration file fred.
// calibration camera FOV to scanner FOV values in XML file
unsigned int g_xScanFOVOrigin_su, g_yScanFOVOrigin_su;
unsigned int g_xScanFOVMax_su, g_yScanFOVMax_su;
float g_xSF_pixelTomm;
float g_ySF_pixelTomm;


int g_xLenWallFOV_mm;       // measured width, x axis, of FOV at target distance = range (mm)
int g_yLenWallFOV_mm;
int range_mm;                // measured range cam to target (mm)



//--------------------------------------------------------------------------------------
// sendScanCmd(void)
//
// deal with X and Y from the sliders
//
//		signals: 	xSlider, SIGNAL(valueChanged(int))
//					ySlider, SIGNAL(valueChanged(int))
//--------------------------------------------------------------------------------------
void Mwars::sendScanCmd(void)  		{

    sendScannerMssg(CMD_SLEW, ui->xSlider->value(), ui->ySlider->value());
    // these are echoed back from scanner and displayed in LCDs
    }

//--------------------------------------------------------------------------------------
// void Mwars::laserDisableToggle(void)
//		signals:	pushButtonLaserEnableToggle(clicked)
// Enable Scanner button signal comes here
//
// This clears laser
//-------------------------------------------------------------------------------------
void Mwars::laserDisableToggle(void) {

   if (laserDisableFlag)    {     // Is disabled, clear the flag

      ui->labelLaser_3->setText("ENABLED");
      ui->pushButtonLaserDisableToggle->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(75, 75, 75)");

      // enable other buttons
      ui->pbLaserToggle->setEnabled(true);        // enable the laser button
      ui->pushButtonCameraDataToggle->setEnabled(true);
      ui->pushButtonTestDataToggle->setEnabled(true);

      laserDisableFlag = false;
      ui->notificationLabel->setText("LASER ENABLED");

      ui->pushButtonTestDataToggle->setEnabled(true);     // enable test data button
   }
   else   {                   // not disabled, turn it off, disable it
       laserOff();
       ui->pbLaserToggle->setEnabled(false);  // disable the laser button
       ui->labelLaser_3->setText("DISABLED");
       ui->pushButtonLaserDisableToggle->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(75, 75, 75)");

       disableCameraData();
       ui->pushButtonCameraDataToggle->setEnabled(false);     // and disable its button

       disableTestData();
       ui->pushButtonTestDataToggle->setEnabled(false);     // and disable its button

       laserDisableFlag = true;
       ui->notificationLabel->setText("LASER DISABLED");
    }
}



//--------------------------------------------------------------------------------------
// void Mwars::laserToggle(void)
//		signals:	pbLaserToggle(clicked)
// Enable Scanner button signal comes here
// Note: a toggle
//-------------------------------------------------------------------------------------
void Mwars::on_pbLaserToggle_clicked(void) {
//void Mwars::laserToggle(void) {

   if (laserOnFlag)        // Is ON; turn off scanner
      laserOff();
   else                      // Is OFF, turn on
      laserOn();
}

//--------------------------------------------------------------------------------------
// void Mwars::laserOn(void)
//-------------------------------------------------------------------------------------
void Mwars::laserOn(void) 		{
    sendScannerMssg( CMD_LASER_ON, 0, 0);

    ui->pbLaserToggle->setStyleSheet("background-color: rgb(255, 255, 150); color: rgb(75, 75, 75)");

    ui->labelLaser_2->setText("ON");
    ui->labelLaser_2->setStyleSheet("color: rgb(255, 0, 0)");

    scannerState.status.laserPower = true;
    laserOnFlag = true;
}

//--------------------------------------------------------------------------------------
// void Mwars::laserOff(void)
//-------------------------------------------------------------------------------------
void Mwars::laserOff(void) 		{
    sendScannerMssg( CMD_LASER_OFF, 0, 0);

    ui->pbLaserToggle->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(75, 75, 75)");

    ui->labelLaser_2->setText("OFF");
    ui->labelLaser_2->setStyleSheet("color: rgb(75, 75, 75)");

    scannerState.status.laserPower = false;
    laserOnFlag = false;
}

//--------------------------------------------------------------------------------------
// void Mwars::scannerToggle(void)
//		signals:	pushButtonscannerToggle(clicked)
// Enable Scanner button signal comes here
// Note: a toggle
//-------------------------------------------------------------------------------------
void Mwars::scannerToggle(void) {

    if (scannerOnFlag) {    // Is ON; turn off scanner
       centre_scanner();    // leave scanner centred
       scannerOff();
    }
    else                    // Is OFF, turn on
       scannerOn();
}

//--------------------------------------------------------------------------------------
// void Mwars::scannerOn(void)
//-------------------------------------------------------------------------------------
void Mwars::scannerOn(void) 	{
    sendScannerMssg( CMD_SCANXPWR_ON, 0, 0);
    sendScannerMssg( CMD_SCANYPWR_ON, 0, 0);

    ui->labelScanner->setText("ON");
    //ui->pushButtonScannerToggle->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(75, 75, 75)");

    scannerState.status.XShutDown = true;
    scannerState.status.YShutDown = true;
    scannerOnFlag = true;
}

//--------------------------------------------------------------------------------------
// void Mwars::scannerOff(void)
//-------------------------------------------------------------------------------------
void Mwars::scannerOff(void) 	{
    sendScannerMssg( CMD_SCANXPWR_OFF, 0, 0);
    sendScannerMssg( CMD_SCANYPWR_OFF, 0, 0);

    ui->labelScanner->setText("OFF");
  //  ui->pushButtonScannerToggle->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(75, 75, 75)");

    scannerState.status.XShutDown = false;
    scannerState.status.YShutDown = false;
    scannerOnFlag = false;
}

//--------------------------------------------------------------------------------------
// void Mwars::centre_scanner(void)
//		centres the scanner in current frame
//      changing slider sends its position to scanner
//-------------------------------------------------------------------------------------
void Mwars::centre_scanner(void) {
        ui->xSlider->setValue((g_xScanFOVMax_su-g_xScanFOVOrigin_su)/2 + g_xScanFOVOrigin_su);
        ui->ySlider->setValue((g_yScanFOVMax_su-g_yScanFOVOrigin_su)/2 + g_yScanFOVOrigin_su);
}


//--------------------------------------------------------------------------------------
// void Mwars::cameraDataToggle(void)
//		signals:	pushButtonCameraDataToggle(clicked)
//-------------------------------------------------------------------------------------
void Mwars::cameraDataToggle(void) {

   if (cameraDataEnableFlag)         // Is ON; turn off opencv stream
      disableCameraData();
   else                              // Is OFF, turn on
      enableCameraData();
}


//--------------------------------------------------------------------------------------
// void Mwars::enableCameraData(void)
//-------------------------------------------------------------------------------------
void Mwars::enableCameraData(void) {

    laserOff();                 // opencv data stream will turn laser on / off

    disableTestData();          // turn off test data (if on)
    calibrateOff();             //
    centre_scanner();
    scannerOn();

    // and turn on camera data
    ui->pushButtonCameraDataToggle->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(75, 75, 75)");
    cameraDataEnableFlag = true;
}

//--------------------------------------------------------------------------------------
// void Mwars::disableCameraData(void)
//-------------------------------------------------------------------------------------
void Mwars::disableCameraData(void) {

    laserOff();
    centre_scanner();        // leave scanner centred
    scannerOff();

    ui->pushButtonCameraDataToggle->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(75, 75, 75)");
    cameraDataEnableFlag = false;
}

//--------------------------------------------------------------------------------------
// void Mwars::resetScanner(void)
//		signals:	pushButtonresetScanner(clicked)
//--------------------------------------------------------------------------------------
void Mwars::resetScanner(void) {

    laserOff();
    serverReady = false;
    testDataEnableFlag   = false;             // turn off data stream
    cameraDataEnableFlag = false;             // turn off data stream

    centre_scanner();
    scannerOff();

    ui->pushButtonTestDataToggle->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(75, 75, 75)");
    ui->pushButtonCameraDataToggle->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(75, 75, 75)");

    sendScannerMssg(CMD_RESET, 0, 0);
    qDebug() << "Reset server cmd sent";
    }

//--------------------------------------------------------------------------------------
// void Mwars::verboseOn(void)
//		signals:	radioButtonVerboseOn(clicked)
//--------------------------------------------------------------------------------------
void Mwars::verboseOn(void) {
    sendScannerMssg(CMD_VERBOSE_ON, 0, 0);
    verbose = true;
    qDebug() << "server verbose is on";
    }

//--------------------------------------------------------------------------------------
// void Mwars::server verboseOff(void)
//		signals:	radioButtonVerboseOn(clicked)
//--------------------------------------------------------------------------------------
void Mwars::verboseOff(void) {
    sendScannerMssg(CMD_VERBOSE_OFF, 0, 0);
    verbose = false;
    qDebug() << "server verbose is off";
    }

//--------- void Mwars::disableWidgets(void) ------------------
//--------------------------------------------------------------
void Mwars::disableWidgets(void){
    ui->pbLaserToggle->setEnabled(false);
    ui->pushButtonScannerToggle->setEnabled(false);
    ui->radioButtonVerboseOn->setEnabled(false);
    ui->radioButtonVerboseOff->setEnabled(false);
    ui->xSlider->setEnabled(false);
    ui->ySlider->setEnabled(false);
    ui->xSpinBox->setEnabled(false);
    ui->ySpinBox->setEnabled(false);
    ui->pushButtonTestDataToggle->setEnabled(false);
    ui->pushButtonCameraDataToggle->setEnabled(false);

    ui->pbCalibrateToggle->setEnabled(false);
    disableCalibrationWidgets();

}


//----------- void Mwars::enableWidgets(void) -----------------
//--------------------------------------------------------------
void Mwars::enableWidgets(void){
    ui->pbLaserToggle->setEnabled(true);
    ui->pushButtonLaserDisableToggle->setEnabled(true);
    ui->pushButtonScannerToggle->setEnabled(true);
    ui->radioButtonVerboseOn->setEnabled(true);
    ui->radioButtonVerboseOff->setEnabled(true);
    ui->xSlider->setEnabled(true);
    ui->ySlider->setEnabled(true);
    ui->xSpinBox->setEnabled(true);
    ui->ySpinBox->setEnabled(true);
    ui->pushButtonTestDataToggle->setEnabled(true);
    ui->pushButtonCameraDataToggle->setEnabled(true);

    ui->pbCalibrateToggle->setEnabled(true);    // enable only master calibration button
}

//------------ void Mwars::clearStateWidgets() -------------
//--------------------------------------------------------------
void Mwars::clearStateWidets(void) {
    ui->labelScanXPwr->setText("");
    ui->labelScanYPwr->setText("");
    ui->labelLaserPwr->setText("");
    ui->labelScanXFlt->setText("");
    ui->labelScanYFlt->setText("");
    ui->labelLaserFlt->setText("");
    ui->labelScannerStateFault->setText("");
    ui->labelHWStartFault->setText("");
    }

//	if (QString::compare(ui.pushButtonVerbose->text(), "Verbose On"))  { // a match



//--------------------------------------------------------------------------------------
// Mwars::Mwars()
// the Constructor
//--------------------------------------------------------------------------------------
Mwars::Mwars(QWidget *parent) : QMainWindow(parent), ui(new Ui::mwarsForm)  {

    ui->setupUi(this);  // Ui:mwarsForm ui

    //*********** two timers
    QTimer *keepServerAliveTimer = new QTimer(this);  // instantiate timer
    QTimer *testTimer = new QTimer(this);


    // a. TCP stream to scanner server
    // clientSocket: client socket sends stream to scanner. clientSocket already exists
    // Q_SIGNALS signals emitted by socket  unimplemented: void hostFound() void connected()
    connect( &clientSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(clientSocketError(QAbstractSocket::SocketError)) );
    connect( &clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(clientSocketState(QAbstractSocket::SocketState)) );

    connect( &clientSocket, SIGNAL(readyRead()),this, SLOT(OnReadyRead()) );
    connect( &clientSocket, SIGNAL(disconnected()), this, SLOT(disconnectedz()) );

    // b. UDP stream from opencv / camera
    listenSocket = new QUdpSocket ( this );
    listenSocket->bind(9988 );
    connect( listenSocket, SIGNAL(readyRead()),this, SLOT(OnReadyRead()) );

    //signals from within code
    connect( this, SIGNAL(connectScanner()), this, SLOT(connectToScanner()));  // Constructor
    connect( keepServerAliveTimer, SIGNAL(timeout()), this, SLOT(keepServerAlive()));

//    connect( testTimer, SIGNAL(timeout()), this, SLOT(testSignal()));

    // signals from ui
    connect( ui->xSlider, SIGNAL(valueChanged(int)), this, SLOT(sendScanCmd()));
    connect( ui->ySlider, SIGNAL(valueChanged(int)), this, SLOT(sendScanCmd()));
    connect( ui->spinboxXCamTrim, SIGNAL(valueChanged(int)), this, SLOT(sendScanCmd()));
    connect( ui->spinboxYCamTrim, SIGNAL(valueChanged(int)), this, SLOT(sendScanCmd()));

    //connect( ui->pbLaserToggle, SIGNAL(clicked()), this, SLOT(laserToggle()));
    connect( ui->pushButtonLaserDisableToggle, SIGNAL(clicked()), this, SLOT(laserDisableToggle()));
    connect( ui->pushButtonScannerToggle, SIGNAL(clicked()), this, SLOT(scannerToggle()));
    connect( ui->pushButtonConnect, SIGNAL(clicked()), this, SLOT(connectToScanner()));
    connect( ui->radioButtonVerboseOn, SIGNAL(clicked()), this, SLOT(verboseOn()));
    connect( ui->radioButtonVerboseOff, SIGNAL(clicked()), this, SLOT(verboseOff()));
    connect( ui->pushButtonResetScanner, SIGNAL(clicked()), this, SLOT(resetScanner()));
    connect( ui->pushButtonCameraDataToggle, SIGNAL(clicked()), this, SLOT(cameraDataToggle()));
    connect( ui->pushButtonTestDataToggle, SIGNAL(clicked()), this, SLOT(testDataToggle()));
    //connect( ui->pbAlignBS, SIGNAL(clicked()), this, SLOT(alignBoresight()));

    connect( ui->pbCalibrateToggle, SIGNAL(clicked()), this, SLOT(calibrateToggle()));
    connect( ui->pbCalSetULHC, SIGNAL(clicked()), this, SLOT(calSetULHC()));
    connect( ui->pbCalSetLRHC, SIGNAL(clicked()), this, SLOT(calSetLRHC()));
    connect( ui->pbCalFullFrame, SIGNAL(clicked()), this, SLOT(calFullFrame()));
    connect( ui->pbCalHalfFrame, SIGNAL(clicked()), this, SLOT(calHalfFrame()));

    connect( ui->spinboxXCamTrim, SIGNAL(valueChanged(int)), this, SLOT(xCamTrim()));
    connect( ui->spinboxYCamTrim, SIGNAL(valueChanged(int)), this, SLOT(yCamTrim()));
    connect( ui->pbCamTrimOffset, SIGNAL(clicked()), this, SLOT(camTrimOffset()));

    connect( ui->sbXCamOffset, SIGNAL(valueChanged(int)), this, SLOT(xCamOffset()));
    connect( ui->sbYCamOffset, SIGNAL(valueChanged(int)), this, SLOT(yCamOffset()));
    connect( ui->pbCamOffset, SIGNAL(clicked()), this, SLOT(camScanOffset()));

    connect( ui->pbCalLaserBsight, SIGNAL(clicked()), this, SLOT(alignBoresight()));
    //connect( this, SIGNAL (testSignal()), this, SLOT (testSignal()));


    // temporary stuff to test parallax offset
    g_xLenWallFOV_mm = (1310 * 2);  // measured width, x axis, of FOV at target distance = range (mm)
    g_yLenWallFOV_mm = (975 * 2);
    g_xSF_pixelTomm =  (float)g_xLenWallFOV_mm / CAMERA_X_PIXELS;
    g_ySF_pixelTomm =  (float)g_yLenWallFOV_mm / CAMERA_Y_PIXELS;
    range_mm         = 2750;          // measured range cam to target (mm)


    //overwritten when cam file is read
    g_xScanFOVOrigin_su = DAC_X_MIN;		// scanner origin corresponding to x_camFOVOrigin (scan units)
    g_xScanFOVMax_su    = DAC_X_MAX;		// scanner max x corresponding to x_camFOVMax (scan units)

    // read camera to scanner calibration file. This reads the calibration parameters
    // and sets main slider and spin box values
    readXMLFile();

    ui->spinboxXCamTrim->setRange(-5000, +5000);
    ui->spinboxYCamTrim->setRange(-5000, +5000);
    ui->radioButtonVerboseOff->setChecked(true);

    clearStateWidets();				// clear Server State widget text

#ifdef FORCE_ENABLE_WIDGETS
    enableWidgets();
#else
     disableWidgets();				// control widgets get enabled when connected
#endif

    verbose = false;                // verbose OFF
    laserOnFlag = false;
    testDataEnableFlag = false;     // set by TestData button to turn on test data stream
    cameraDataEnableFlag = false;   // set by Camera Data button to turn on OpenCVcamera data stream
    laserDisableFlag = false;       // set by Laser On/Off button
    scannerOnFlag = false;          // set by Scanner On/Off button
    tcpConnected = false;           // tcp connected
    serverReady = false;
    calibrateFlag = false;

    setWindowTitle(tr("MWARS SCANNER CONSOLE"));



    // =================== start scannerserver comms ===============================
    //  a) UDP stream of co-ords and laser command from OpenCV Project mwars
    //  b) TCP connection to server in the scanner unit

    // 1. connect to the TCP server in the laser scanner unit
    emit connectScanner();              //runs connectToScanner


    // ==================== timers ==================================
    // start the keep alivetimer. Used to get response to update Console
    keepServerAliveTimer->start(1000);  //1000 = 1 sec

    //start the test signal timer for testSignal()
    // 1000 = 1 sec, 1 = 1mS
    //testTimer->start(100);             // 5 Hz
    //testTimer->start(10);              // 50 Hz
    //testTimer->start(20);              // 25 Hz
    // testTimer->start(60);              //  8 Hz
    // testTimer->start(50);              //  10 Hz

    sendScanCmd();     // init scanner, slew to slider values

    rectangleIsRunning = false;
}


//--------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------
Mwars::~Mwars()  {

   // scannerDraw->abort();
    workerThread->wait();
    qDebug()<<"Deleting thread and scannerDraw in Thread "<<this->QObject::thread()->currentThreadId();
    delete workerThread;
    delete scannerDraw;
    delete ui;
}



//--------------------------------------------------------------------------------------
//  void Mwars::on_pbRectangle_clicked()
//
//  void drawRectangle (Mwars *mwars, pt1, pt2, pt3, pt4)
//--------------------------------------------------------------------------------------

void Mwars::on_pbRectangle_clicked()
{
    if(rectangleIsRunning) {
        QMessageBox::critical(this, "Error", "Rectangle is already running");
        return;
    }

    workerThread = new QThread();            // instantiates ScannerDraw class and the QThread
    scannerDraw = new ScannerDraw(this, 33, 44);   // on heap

    scannerDraw->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), scannerDraw, SLOT(drawRectangle()));

    connect(scannerDraw, SIGNAL(finished()), workerThread, SLOT(quit()), Qt::DirectConnection);
    connect(scannerDraw, SIGNAL(finished()), scannerDraw, SLOT(deleteLater()));
    connect(scannerDraw, SIGNAL(finished()), workerThread, SLOT(deleteLater()));

    connect(workerThread, SIGNAL(finished()), this, SLOT(rectangleFinished()));

    connect(ui->pbStopRectangle, SIGNAL(clicked()), this, SLOT(stopRectangle()));

    // need these signals cause can't call sockets across threads
    connect(scannerDraw, SIGNAL(sendScannerMssg (ushort, ushort, ushort)), this, SLOT(sendScannerMssg(ushort, ushort, ushort)));
    connect(scannerDraw, SIGNAL (laserOn()), this, SLOT(laserOn()));
    connect(scannerDraw, SIGNAL (laserOff()), this, SLOT(laserOff()));
    connect(scannerDraw, SIGNAL (scannerOn()), this, SLOT(scannerOn()));
    connect(scannerDraw, SIGNAL (scannerOff()), this, SLOT(scannerOff()));

    workerThread->start();

    rectangleIsRunning = true;
    ui->pbStopRectangle->setEnabled(true);
}

//--------------------------------------------------------------------------------------
//  void Mwars::stopRectangle()

//  signal finished from workerThread
//--------------------------------------------------------------------------------------
void Mwars::stopRectangle(){

    if (workerThread != 0 && rectangleIsRunning ) {
        workerThread->requestInterruption();
        workerThread->wait();
    }

    qDebug()<<"exiting stopRectangle in Thread "<<thread()->currentThreadId();
}


//--------------------------------------------------------------------------------------
//  void Mwars::rectangleFinished()

//  signal finished from workerThread
//--------------------------------------------------------------------------------------
void Mwars::rectangleFinished() {

    rectangleIsRunning = false;
    ui->pbStopRectangle->setEnabled(false);
}


/*    // To avoid having two threads running simultaneously, the previous thread is aborted.
   // scannerDraw->abort();
   // workerThread->wait(); // If the thread is not running, this will immediately return.



    // **** for thread that runs scannerDraw routines  *******
    // 1. The constructor will instantiate both the Worker and the QThread.
    QThread *workerThread = new QThread();            // instantiates ScannerDraw class and the QThread
    ScannerDraw *scannerDraw = new ScannerDraw();



    // worker->setPath("~/Desktop");   can pass stuff the the class before it is sent to thread
    // refer: http://forum.qt.io/topic/32578/qthread-relation-between-quit-finished-and-deletelater

    // 2. The worker is moved to the thread. That will give ownership of this worker to the
    //  other thread which will be able to freely manipulate it.
    scannerDraw->moveToThread(workerThread);
    //connect( ui->pbRectangle, SIGNAL(clicked()), this, SLOT(on_pbRectangle_clicked()));
    // 4. The workRequested() signal of the Worker is connected to the start() function of the thread
    //    which means that the thread will start when requestWork() is called.
    connect(scannerDraw, SIGNAL(workRequested()), workerThread, SLOT(start()));
    // 5. The started() signal of the thread is connected to the doWork() function of the worker which
    //    means that as soon as the thread starts, the doWork() function is called.
    connect(workerThread, SIGNAL(started()), scannerDraw, SLOT(drawRectangle()));
    // 6. Then we connect the finished() signal of the worker to the quit() slot of the thread,
    // ensuring that the thread will stop when the work is done.
    connect(scannerDraw, SIGNAL(finished()), workerThread, SLOT(quit()), Qt::DirectConnection);

    //workerThread->start();
    //scannerDraw->requestWork();

    //  3. Then we connect the Worker::valueChanged() signal to update display.
    //  connect(scannerDraw, SIGNAL(valueChanged(QString)), ui->label, SLOT(setText(QString)));





*/











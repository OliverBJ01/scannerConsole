/*   Class ScannerDraw
 *
 * app to use scanner to 'draw' lines on the wall using thread
 * event driven implementation of Bresenham line algorithm
 *
 *  refer: https://fabienpn.wordpress.com/2013/05/01/qt-thread-simple-and-stable-with-sources
 *  https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/
 *  http://doc.qt.io/qt-5/qthread.html#details
 *
 *
    1. The constructor will instantiate both the Worker and the QThread.
    2. Then, the worker is moved to the thread. That will give ownership of this worker to the
        other thread which will be able to freely manipulate it.
    3. Then we connect the Worker::valueChanged() signal to update display.
    4. The workRequested() signal of the Worker is connected to the start() function of the thread
        which means that the thread will start when requestWork() is called.
    5. The started() signal of the thread is connected to the doWork() function of the worker which
        means that as soon as the thread starts, the doWork() function is called.
    6. Then we connect the finished() signal of the worker to the quit() slot of the thread,
        ensuring that the thread will stop when the work is done.
 *
*/


//Another option would be to use "QtConcurrent::run()"
//:http://qt-project.org/doc/qt-4.8/qtconcurrentrun.html for your dirSize(QString path) function.
// This way you don't need QThread and its easy to "cancel execution":
// http://qt-project.org/doc/qt-4.8/qfuture.html#cancel .

#include "scannerDraw.h"
#include "console.h"
#include <QThread>
#include <QApplication>


// calibration camera FOV to scanner FOV values in XML file
extern unsigned int g_xScanFOVOrigin_su, g_yScanFOVOrigin_su;
extern unsigned int g_xScanFOVMax_su, g_yScanFOVMax_su;


//--------------------------------------------------------------------------------------
// Constructor
//--------------------------------------------------------------------------------------
ScannerDraw::ScannerDraw(Mwars *m, int start, int end) {

    mwars = m;
    m_isRunning = false;
    m_start = start;
    m_end = end;
}



//--------------------------------------------------------------------------------------
// void ScannerDraw::drawRectangle(void)
//
//  draws the 1/2 frame that corresponds with the OpenCV 1/2 frame
//-------------------------------------------------------------------------------------
void ScannerDraw::drawRectangle() {

    m_isRunning = true;
    emit scannerOn();
    emit laserOn();

    unsigned int xLen = g_xScanFOVMax_su-g_xScanFOVOrigin_su;
    unsigned int yLen = g_yScanFOVMax_su-g_yScanFOVOrigin_su;
    unsigned int xOrg = g_xScanFOVOrigin_su + xLen/4;
    unsigned int yOrg = g_yScanFOVOrigin_su + yLen/4;
    unsigned int xMax = g_xScanFOVOrigin_su + xLen/4 * 3;
    unsigned int yMax = g_yScanFOVOrigin_su + yLen/4 * 3;

    qDebug()<<"Starting drawRectangle() process in Thread "<<thread()->currentThreadId();

    for (;;) {

        // m_isRunning is cleared in Bresenham when stop signal received
        Bresenham (xOrg, yOrg, xMax, yOrg);
        if (!m_isRunning)  return;
        Bresenham (xMax, yOrg, xMax, yMax);
        if (!m_isRunning)  return;
        Bresenham (xMax, yMax, xOrg, yMax);
        if (!m_isRunning)  return;
        Bresenham (xOrg, yMax, xOrg, yOrg);

     /*   // m_isRunning is cleared in Bresenham when stop signal received
        Bresenham (20000, 10000, 40000, 10000);
        if (!m_isRunning)  return;
        Bresenham (40000, 10000, 40000, 20000);
        if (!m_isRunning)  return;
        Bresenham (40000, 20000, 20000, 20000);
        if (!m_isRunning)  return;
        Bresenham (20000, 20000, 20000, 10000); */
    }

     qDebug()<<"Bresenham process finished in Thread "<<thread()->currentThreadId();
     emit scannerOff();
     emit laserOff();

     emit finished();
}



//--------------------------------------------------------------------------------------
//
// Bresenham's line algorithm
//
//--------------------------------------------------------------------------------------
void ScannerDraw::Bresenham(int x1, int y1, int x2, int y2)  {

    #define bScale 50       // step 50 scanner units instead of 1
    #define bdelay 400      // needed to stop the UDP pipe from overflowing
                            // microseconds

    x1 = x1/bScale; x2 = x2/bScale; y1 = y1/bScale; y2 = y2/bScale;

    qDebug()<<"Starting Bresenham process in Thread "<<thread()->currentThreadId();

    if ( QThread::currentThread()->isInterruptionRequested()){
        qDebug()<<"isInterruptionRequested in Bresenhan. Thread: "<<thread()->currentThreadId();
        emit scannerOff();
        emit laserOff();
        m_isRunning = false;
        emit finished();
        return;
    }

    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    emit sendScannerMssg (CMD_SLEW, x1*bScale, y1*bScale);
    QThread::usleep(bdelay);   // microseconds

    if (delta_x >= delta_y)       {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2)          {

            if ((error >= 0) && (error || (ix > 0))) {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;

            QThread::usleep(bdelay);   // microseconds
            emit sendScannerMssg (CMD_SLEW, x1*bScale, y1*bScale);
        }
    }
    else      {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)          {
            if ((error >= 0) && (error || (iy > 0))) {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;

            QThread::usleep(bdelay);   // microseconds
            emit sendScannerMssg (CMD_SLEW, x1*bScale, y1*bScale);
        }
    }
}


//--------------------------------------------------------------------------------------
// Destructor
//--------------------------------------------------------------------------------------
ScannerDraw::~ScannerDraw()  {

  //  scannerDraw->abort();
  //  workerThread->wait();
    qDebug()<<"Deleting thread and scannerDraw in Thread "<<this->QObject::thread()->currentThreadId();
  //  delete workerThread;
  //  delete scannerDraw;
}


/*//--------------------------------------------------------------------------------------
//  void ScannerDraw::requestWork()
//
//  called from on_pbRectangle_clicked()
//
//  4. The workRequested() signal of the Worker is connected to the start() function of the thread
//      which means that the thread will start when requestWork() is called.
//--------------------------------------------------------------------------------------
void ScannerDraw::requestWork()
{
    mutex.lock();
    _working = true;
    _abort = false;
    qDebug()<<"Request worker start in Thread "; //<<thread()->currentThreadId();
    mutex.unlock();

    emit workRequested();  // connected to thread, SLOT(start())
}

//--------------------------------------------------------------------------------------
//  void ScannerDraw::abort()
//
//  Requests the process to abort
//--------------------------------------------------------------------------------------
void ScannerDraw::abort()
{
    mutex.lock();

    if (_working) {
        _abort = true;
        qDebug()<<"Request worker aborting in Thread "<<thread()->currentThreadId();
    }
    mutex.unlock();
}
/--------------------------------------------------------------------------------------
// void ScannerDraw::drawRectangle(void)
//
//  5. The started() signal of the thread is connected to the doWork() function of the worker which
//      means that as soon as the thread starts, the doWork() function is called.
//-------------------------------------------------------------------------------------
void ScannerDraw::drawRectangle(void) {
//void ScannerDraw::drawRectangle(Mwars *mwars) {
     qDebug()<<"Starting drawRectangle() process in Thread "<<thread()->currentThreadId();

       // for (;;) {
            Bresenham (20000, 10000, 40000, 10000);
            Bresenham (40000, 10000, 40000, 20000);
            Bresenham (40000, 20000, 20000, 20000);
            Bresenham (20000, 20000, 20000, 10000);

            Bresenham ( 20000, 10000, 20500, 10000);
            Bresenham ( 20500, 10000, 20500, 10500);
            Bresenham ( 20500, 10010, 20000, 10500);
            Bresenham ( 20000, 10500, 20000, 10000);
      //  }

        // Set _working to false, meaning the process can't be aborted anymore.
        mutex.lock();
        _working = false;
        mutex.unlock();

        qDebug()<<"Bresenham process finished in Thread "<<thread()->currentThreadId();

        emit finished();
}





//--------------------------------------------------------------------------------------
// void ScannerDraw::stopDrawRectangle(void)
//-------------------------------------------------------------------------------------
 void ScannerDraw::stopDrawRectangle(void) {

     mwars->scannerOff();
     mwars->laserOff();
     qDebug() <<"stopDrawRectangle() process in Thread "<<thread()->currentThreadId();
     m_isRunning = false;
 }
*/


















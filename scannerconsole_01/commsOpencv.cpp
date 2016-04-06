/*   listener.cpp
 *
 * .listens for UDP messages from OpenCV
 *
 * sends any messages to scanner pane
 *
 * robust; the sender can start & stop and this picks up
 * */

#include <console.h>
#include "math.h"

#define PI 3.14159265

#include "ui_consoleForm.h"


// calibration camera FOV to scanner FOV values in XML file
extern unsigned int g_xScanFOVOrigin_su, g_yScanFOVOrigin_su;
extern unsigned int g_xScanFOVMax_su,    g_yScanFOVMax_su;
extern float g_xSF_PixelToSU;
extern float g_ySF_PixelToSU;
extern float g_xSF_pixelTomm;
extern float g_ySF_pixelTomm;

extern int g_xLenWallFOV_mm;        // measured width, x axis, of FOV at target distance = range (mm)
extern int g_yLenWallFOV_mm;
extern int g_xCamtoScanOffset_mm;   // measured offset between cam and scanner (mm)
extern int g_yCamToScanOffset_mm;
extern int g_xCamTrim;              //  trim applied to correct for cam offset from testing
extern int g_yCamTrim;

extern int range_mm;                // measured range cam to target (mm)


//--------------------------------------------------------
// void Mwars::Listener::listener()
//		signals:	readyRead()
//
// Receives pointing stream, laser commands from Project mwars02, udpSender.cpp
//  port 9988

// listenSocket bound to port 9988 in console.cpp line 350
//
// http://www.bogotobogo.com/Qt/Qt5_QUdpSocket.php
//
// Calibration:  maps the camera FOV into the scanner FOV.
// The calibrate() routine is used to direct laser to camera FOV corners:
//  TLHC: (camera: 0,0) and saved at
//BRHC (e.g. 640, 48) to the scanner co-ordes, and these values
// are saved in the camera XML file. This file is read on start-up and is used to scale the
// camera FOV into the scanner FOV, for a given distance.

// Also, off set adjustment is provided that allow the scanner co-ords to be offset to allow
// for changes in camera orientration wrt scanner after calibration.

//
//-------------------------------------------------------
void Mwars::listener(void) {

    struct opencvMssg mssg;     // message structure received from openCV

    // readDatagram saves the sender's host address and port in *address and *port
    QHostAddress sender;
    quint16 senderPort;

    qDebug() << "listener:Message from: " << sender.toString() << " Message port: " << senderPort;

    listenSocket->readDatagram( ( char*) &mssg, sizeof(mssg), &sender, &senderPort );

    // when calibrating, send mssg without scaling
    if (calibrateFlag) {
        mssg.XPos = DAC_X_MIN + ui->xSpinBox->value() + mssg.XPos;
        mssg.YPos = DAC_Y_MIN + ui->xSpinBox->value() + mssg.YPos;
        return;
    }

   // process the packet only if camera stream enabled
   if (cameraDataEnableFlag) {            // from the Enable Camera data button on console

       //  convert to host format
        mssg.XPos = ntohs(mssg.XPos);
        mssg.YPos = ntohs(mssg.YPos);

        if (verbose)
                qDebug ("listener A: %d %d %d", mssg.XPos, mssg.YPos, mssg.laserOn);

//#define PARALLAX_CORR       // enable camera / scanner parallax correction
#ifdef PARALLAX_CORR
        // translate the target's pixel co-ords into corresponding scan units for scanner
        // and  adjust for parallax error and apply the trim adjustment

        //qDebug() << "Precall  mssg.XPos " << mssg.XPos << " mssg.YPos " << mssg.YPos << endl;
        int xx = g_xScanFOVOrigin_su + (mssg.XPos * g_xSF_PixelToSU) + g_xCamTrim;
        //int yy = g_yScanFOVOrigin_su + mssg.YPos * g_ySF_PixelToSU + g_yCamTrim;

        translateTargetCoords (mssg.XPos, mssg.YPos);

        //************tempory until Y imlemented ***************8
        //************tempory until Y imlemented ***************8
        mssg.YPos = g_yScanFOVOrigin_su + mssg.YPos * g_ySF_PixelToSU + g_yCamTrim;


        qDebug() << "listener(), xx: " << xx << " mssg.XPos: " << mssg.XPos;

#else   // ignore parallax adjustment
        float x_mmTosu = g_xSF_PixelToSU / g_xSF_pixelTomm;
        float y_mmTosu = g_ySF_PixelToSU / g_ySF_pixelTomm;

        mssg.XPos = g_xScanFOVOrigin_su + (mssg.XPos * g_xSF_PixelToSU) + (g_xCamtoScanOffset_mm / x_mmTosu) + g_xCamTrim;
        mssg.YPos = g_yScanFOVOrigin_su + (mssg.YPos * g_ySF_PixelToSU) + (g_yCamtoScanOffset_mm / y_mmTosu) + g_yCamTrim;
#endif
        if (verbose)
            qDebug ("listener B: %d %d %d", mssg.XPos, mssg.YPos, mssg.laserOn);

           //if laser state changed, then toggle laser state
           if (mssg.laserOn != scannerState.status.laserPower) {
                 if (mssg.laserOn) // laser on
                    laserOn();
                 else
                    laserOff();
            }

           sendScannerMssg(CMD_SLEW, mssg.XPos, mssg.YPos);
            //printf ("listener: sendScannerMssg()\n")
        }  // enable flag
}




/*------------------------------------------------------
    void Mwars::translateTargetCoords(ushort &x_p, ushort &y_p)

    Receives reference to x_p y_p in pixels, and updates to scan units
    adjusted for camera intrinics and target range

    a) receives reference x_p y_p; target co-ords from openCV in pixels
    b) adjusts for parallax error
    c) converts to scanner units
    d) offsets co-ords by: offset to scanner origin, trim adjustment
    -------------------------------------------------------
*/

void Mwars::translateTargetCoords(ushort &x_p, ushort &y_p)  {

        float alpha, beta, theta;

    float g_xSF_pixelTomm =  (float)(g_xLenWallFOV_mm / CAMERA_X_PIXELS);                     // SF pixels to mm projected on wall
    float g_xSF_mmTosu = (float)(g_xScanFOVMax_su - g_xScanFOVOrigin_su) / g_xLenWallFOV_mm;  // SF mm projected on wall to su

    // x_p is the target co-ordinate from opencv in pixels
    //for (float x_p1 = 0;   x_p1 < 650;   x_p1 = x_p1+20) {
    //    float x_p = x_p1;

        // work in projected image units mm, because we measure range and image width and offset in mm
        float x_mm = g_xSF_pixelTomm * x_p;                         // pixels to mm at target pos mm
        float norm_mm = abs((int) (x_mm - (g_xLenWallFOV_mm/2)) );  // abs about centre / boresight mm

        alpha = atan (norm_mm/range_mm);

        if (x_p <320) {
            beta = atan ((norm_mm + g_xCamtoScanOffset_mm)/range_mm);
            theta = beta-alpha;
           }
        else  {
            beta = atan ((norm_mm - g_xCamtoScanOffset_mm)/range_mm);
            theta = beta-alpha;
            }

         float xCam_mm =  tan (alpha)*(range_mm);
         float xScan_mm = tan (beta)*(range_mm-g_xCamtoScanOffset_mm);

         if (x_p <320)
             xScan_mm = abs(xScan_mm - g_xLenWallFOV_mm/2);
        else
             xScan_mm = xScan_mm +  g_xLenWallFOV_mm/2;

         // convert mm to scan units
         float x_su = xScan_mm * g_xSF_mmTosu + g_xScanFOVOrigin_su + g_xCamTrim;

        //qDebug() << x_p  << " " << norm_mm  << " a " << alpha*180/PI  << " b " << beta*180/PI << " a-b " << alpha-beta
         //        << " su_mm "  <<su_mm;

         qDebug() << x_p  << " " << norm_mm  << " xCam_mm " << xCam_mm  << " xScan_mm " << xScan_mm
                  << " x_su " << x_su;

        x_p = x_su;

return;
}




/*
 *     float alpha, beta, theta;

    float g_xSF_pixelTomm =  (float) g_xLenWallFOV_mm / CAMERA_X_PIXELS;                  // sfactor pixels to mm projected on wall
    float g_xSF_mmTosu = (float) (g_xScanFOVMax_su - g_xScanFOVOrigin_su) / g_xLenWallFOV_mm;  // sfactor mm to su

    // x_p is the target co-ordinate from opencv in pixels
    //for (float x_p1 = 0;   x_p1 < 650;   x_p1 = x_p1+20) {
    //    float x_p = x_p1;

        // work in projected image units mm, because we measure range and image width and offset in mm
        float x_mm = g_xSF_pixelTomm * x_p;                         // pixels to mm at target pos mm
        float norm_mm = abs((int) (x_mm - (g_xLenWallFOV_mm/2)) );  	// abs about centre / boresight mm

        alpha = atan (norm_mm/range_mm);

        if (x_p <320) {
            beta = atan ((norm_mm + g_xCamToScanOffset_mm)/range_mm);
            theta = beta-alpha;
            beta = alpha+theta;
           }
        else  {
            beta = atan ((norm_mm - g_xCamToScanOffset_mm)/range_mm);
            theta = beta-alpha;
            beta = alpha + theta;
            }

         float xCam_mm =  tan (alpha)*(range_mm);
         float xScan_mm = tan (beta)*(range_mm-g_xCamToScanOffset_mm);

         if (x_p <320)
             xScan_mm = abs(xScan_mm - g_xLenWallFOV_mm/2);
        else
             xScan_mm =xScan_mm +  g_xLenWallFOV_mm/2;

         // convert mm to scan units
         float x_su = xScan_mm * g_xSF_mmTosu + g_xScanFOVOrigin_su + g_xCamTrim;

        //qDebug() << x_p  << " " << norm_mm  << " a " << alpha*180/PI  << " b " << beta*180/PI << " a-b " << alpha-beta
         //        << " su_mm "  <<su_mm;

         qDebug() << x_p  << " " << norm_mm  << " xCam_mm " << xCam_mm  << " xScan_mm " << xScan_mm
                  << " x_su " << x_su;

        x_p = x_su;

return;
}


 *
 *
 *
 *
 *
 *
 *
 *
 *
 *     // x_p is the target co-ordinate from opencv in pixels
    for (float x_p1 = 0;   x_p1 < 650;   x_p1 = x_p1+20) {
        float x_p = x_p1;

        // work in projected image units mm, because we measure range and image width and offset in mm
        float x_mm = g_xSF_pixelTomm * x_p;                           // pixels to mm at target pos mm
        float norm_mm = abs((int) (x_mm - (g_xLenWallFOV_mm/2)) );  	// abs about centre / boresight mm

        float srxScan_mm, srxCam_mm;

        srxCam_mm = sqrt( pow(norm_mm, 2) + pow(range_mm, 2) );	// slant range from scan: 0-320

        if (x_p <320)
            srxScan_mm = sqrt(pow (norm_mm + g_xCamToScanOffset_mm, 2) + pow(range_mm, 2) );	// slant range from scan: 0-320p
        else
            srxScan_mm = sqrt(pow (norm_mm - g_xCamToScanOffset_mm, 2) + pow(range_mm, 2) );	// slant range from scan: 0-320p

        float delta_mm = abs (srxCam_mm - srxScan_mm);

        float alpha = atan(norm_mm/range_mm);

        //float gamma = PI/2 - alpha;
        float plax_mm = delta_mm * tan(alpha);


        // convert coord from pixels to scan units, add scan origin offset, add plax (converted to scan units), add the manual tr
        //x_p = x_mm*g_xSF_mmTosu + g_xScanFOVOrigin_su + g_xCamTrim + plax_mm*g_xSF_mmTosu;
   //     qDebug() << "Out  x_p " <<  x_p << endl;

        qDebug() << x_p  << " " << norm_mm << srxCam_mm << " " << srxScan_mm << " delta " << delta_mm
                 << " a " << alpha*180/PI << " p " << plax_mm;
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *void Mwars::translateTargetCoords(ushort &x_p, ushort &y_p)  {

    float g_xSF_pixelTomm =   (float) g_xLenWallFOV_mm / CAMERA_X_PIXELS;                  // sfactor pixels to mm projected on wall
    float g_xSF_mmTosu = (float) (g_xScanFOVMax_su - g_xScanFOVOrigin_su) / g_xLenWallFOV_mm;  // sfactor mm to su

     //       qDebug() << "In  x_p " <<  x_p << endl;

    // x_p is the target co-ordinate from opencv in pixels
    //for (float x_p1 = 0;   x_p1 < 650;   x_p1 = x_p1+20) {
    //    float x_p = x_p1;

        // work in projected image units mm, because we measure range and image width and offset in mm
        float x_mm = g_xSF_pixelTomm * x_p;                        // pixels to mm at target pos mm

        // parallax reduces either side boresight, so we calculate
        //parallax in mm symetrically about the boresight
        float x_norm_mm = abs((int) (x_mm - (g_xLenWallFOV_mm/2)) );  	// abs about centre / boresight mm

        float x_srScan = sqrt(pow (x_norm_mm + g_xCamToScanOffset_mm, 2) + pow(range_mm, 2) );	// slant range from scan: 0-320p
        if (x_p >320)
            x_srScan = sqrt(pow (x_norm_mm - g_xCamToScanOffset_mm, 2) + pow(range_mm, 2) );	// slant range from scan: 0-320p

        //float x_srCam = sqrt(pow (x_norm_mm, 2) + pow(range_mm, 2) );	// slant range from camera  //NOT NEEDED
        //float x_delta = abs(x_srScan-x_srCam);        //NOT NEEDED

        float x_beta = acos(range_mm/x_srScan);       //NOT NEEDED
        //float gamma = PI/2 - x_beta;            // 90-beta
        float x_plax_mm = g_xCamToScanOffset_mm * sin(PI/2 - x_beta);

      //  if (x_p >320) x_plax_mm = -x_plax_mm;

        // convert coord from pixels to scan units, add scan origin offset, add plax (converted to scan units), add the manual tr
        x_p = x_mm*g_xSF_mmTosu + g_xScanFOVOrigin_su + g_xCamTrim + x_plax_mm*g_xSF_mmTosu;
   //     qDebug() << "Out  x_p " <<  x_p << endl;

        //qDebug() << " x_p " << x_p  << " gamma " << gamma*180/PI  << " delta " << x_delta  << " plax " << x_plax_mm << endl;

    //}
return;
}*/

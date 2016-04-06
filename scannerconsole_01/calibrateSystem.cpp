/*

  Calibration.

  Required to translate the target position co-ordinated from the camera / opencv into the
  equivalent scanner dac cordinates

Calibration consists of:
a) initial calibration: mapping the camera FOV into the scanner FOV.
    The calibration function directs the laser to the TLHC and BRHC of the camera FOV,
    and saves the result in the camCalFile.

TLHC, camera (0,0) is saved as g_xScanFOVOrigin_su, g_yScanFOVOrigin_su   (in scanner units)
BRHC, camera (640, 480 for this camera) is saved as g_xScanFOVMax_su, g_yScanFOVMax_su  (in scanner units)

b) in use: translating the target co-ordinate from opencv (CamPos)that is in camera
    units to the target coords in scanner's units (ScanPos).
    The project reads the camCalFile on start up, and then uses this data to scale the
    target co-ordinates from opencv (in camera units) to scanner units.

xScanPos = g_xScanFOVOrigin_su + xCamPos * (g_xScanFOVMax_su-g_xScanFOVOrigin_su)/640
yScanPos = g_yScanFOVOrigin_su + yCamPos * (g_yScanFOVMax_su-g_yScanFOVOrigin_su)/480

When setting camera to scanner offsets (in mm):
 the offset is derived: origin to camera to scanner, for origin at TLHC
 for camera above scanner, and to the left looking at it front-on; x = -70 and y = 50

*/

#include <QFileSystemModel>
#include "ui_consoleForm.h"
#include "console.h"

#include <iostream>
#define READNEXT Rxml.readNext()

//void ReadRoomElement(void);

QString calFilename = "fred.txt";


// calibration camera FOV to scanner FOV values in XML file (su: scanner units)
extern unsigned int g_xScanFOVOrigin_su, g_yScanFOVOrigin_su;
extern unsigned int g_xScanFOVMax_su, g_yScanFOVMax_su;
extern float g_xSF_pixelTomm;
extern float g_ySF_pixelTomm;
extern int g_xLenWallFOV_mm;        // measured width, x axis, of FOV at target distance = range (mm)
extern int g_yLenWallFOV_mm;
extern int range_mm;                // measured range cam to target (mm)

int g_xCamtoScanOffset_mm;   // measured offset between cam sensor and scanner mirror centroid (mm)
int g_yCamtoScanOffset_mm;
int g_xCamTrim;             //  trim applied to correct for cam offset from testing
int g_yCamTrim;

float g_xSF_PixelToSU;
float g_ySF_PixelToSU;

//--------------------------------------------------------------------------------------
// void Mwars::alignBoresight(void)
//		signal: pbCalLaserBsight (clicked)
//
//  this just enables the calibration buttons
//--------------------------------------------------------------------------------------
void Mwars::alignBoresight(void) {

    scannerOn();
    centre_scanner();   // this also send the centering message to scanner
    laserOn();
}


//--------------------------------------------------------------------------------------
// void Mwars::calibrateToggle(void)
//		signal: pbCalibrateToggle (clicked)
//
//  this just enables the calibration buttons
//--------------------------------------------------------------------------------------
void Mwars::calibrateToggle(void) {
    if (calibrateFlag)
        calibrateOff();
    else
        calibrateOn();
}

//--------------------------------------------------------------------------------------
// void Mwars::calibrateOn(void)
//
// Enables calibation buttons. Actual calibration occurs when they are pressed
//--------------------------------------------------------------------------------------
void Mwars::calibrateOn(void) {

    laserOff();
    centre_scanner();
    scannerOff();
    disableTestData();
    disableCameraData();

    // init slider & spinbox ranges to the max extents that scanner can slew
    ui->xSlider->setRange(DAC_X_MIN, DAC_X_MAX);
    ui->ySlider->setRange(DAC_Y_MIN, DAC_Y_MAX);
    ui->xSpinBox->setRange(DAC_X_MIN, DAC_X_MAX);
    ui->ySpinBox->setRange(DAC_Y_MIN, DAC_Y_MAX);

    // centre sliders
    ui->xSlider->setValue((DAC_X_MAX-DAC_X_MIN)/2 + DAC_X_MIN);
    ui->ySlider->setValue((DAC_Y_MAX-DAC_Y_MIN)/2 + DAC_Y_MIN);

   // enable calibration buttons
    ui->pbCalSetULHC->setEnabled(true);
    ui->pbCalSetLRHC->setEnabled(true);
    ui->pbCalFullFrame->setEnabled(true);
    ui->pbCalHalfFrame->setEnabled(true);
    ui->pbCamTrimOffset->setEnabled(true);
    ui->spinboxXCamTrim->setEnabled(true);
    ui->spinboxYCamTrim->setEnabled(true);
    ui->pbCamTrimOffset->setEnabled(true);
    ui->pbCalLaserBsight->setEnabled(true);
    ui->sbXCamOffset->setEnabled(true);
    ui->sbYCamOffset->setEnabled(true);
    ui->pbCamOffset->setEnabled(true);

    ui->pbRectangle->setEnabled(true);

    ui->notificationLabelCal->setText("Ready to calibrate");
    calibrateFlag = true;
}



//--------------------------------------------------------------------------------------
// void Mwars::calibrateOff(void)
//--------------------------------------------------------------------------------------
void Mwars::disableCalibrationWidgets(void) {

    // disable calibration buttons
    ui->pbCalSetULHC->setEnabled(false);
    ui->pbCalSetLRHC->setEnabled(false);
    ui->pbCalFullFrame->setEnabled(false);
    ui->pbCalHalfFrame->setEnabled(false);
    ui->pbCamTrimOffset->setEnabled(false);
    ui->spinboxXCamTrim->setEnabled(false);
    ui->spinboxYCamTrim->setEnabled(false);
    ui->pbCamTrimOffset->setEnabled(false);
    ui->pbCalLaserBsight->setEnabled(false);
    ui->sbXCamOffset->setEnabled(false);
    ui->sbYCamOffset->setEnabled(false);
    ui->pbCamOffset->setEnabled(false);

    ui->pbRectangle->setEnabled(false);
    ui->pbStopRectangle->setEnabled(false);
}

//--------------------------------------------------------------------------------------
// void Mwars::calibrateOff(void)
//--------------------------------------------------------------------------------------
void Mwars::calibrateOff(void) {

    // we come here when calibration is complete (including calib file updated)

    disableCalibrationWidgets();

   // init slider & spinbox ranges to the scanner values corresponding
   // to the camera view extents 0,0 to 640, 480 pixels
    ui->xSlider->setRange(g_xScanFOVOrigin_su, g_xScanFOVMax_su);
    ui->ySlider->setRange(g_yScanFOVOrigin_su, g_yScanFOVMax_su);

    laserOff();
    centre_scanner();
    scannerOff();

    ui->notificationLabelCal->setText("");
    calibrateFlag = false;


   /* qDebug("xOffset: %d yOffset: %d xMax: %d, yMax: %d \n"
           " xDelta: %d yDelta: %d, xScale: %d yScale: %d\n"
           " g_xCamTrim %d  g_yCamTrim %d",
        g_xScanFOVOrigin_su, g_yScanFOVOrigin_su, g_xScanFOVMax_su, g_yScanFOVMax_su,
        (g_xScanFOVMax_su-g_xScanFOVOrigin_su), (g_yScanFOVMax_su-g_yScanFOVOrigin_su),
            g_xSF_PixelToSU, g_ySF_PixelToSU, g_xCamTrim,g_yCamTrim);  */
}



//--------------------------------------------------------------------------------------
// int Mwars::calFullframe(void)
//		signal: pbCalFullFrame (clicked)
//--------------------------------------------------------------------------------------
int Mwars::calFullFrame(void) {

 //   if ((g_xScanFOVMax_su == 0) || (g_xScanFOVOrigin_su == 0)) {
 //       ui->notificationLabelCal->setText("Error: Either ULHC or LRHC not entered");
//        return 1;
//    }

    g_xSF_PixelToSU = ((float)(g_xScanFOVMax_su-g_xScanFOVOrigin_su)) / CAMERA_X_PIXELS;
    g_ySF_PixelToSU = ((float)(g_yScanFOVMax_su-g_yScanFOVOrigin_su)) / CAMERA_Y_PIXELS;

   if (!writeXMLFile()) {           // good write return 1 i.e. false
        ui->notificationLabelCal->setText("Full Frame Cal Complete");
        calibrateOff();

        // display values
        ui->labelCalScalex->setText(QString::number(g_xSF_PixelToSU));
        ui->labelCalScaley->setText(QString::number(g_ySF_PixelToSU));
        ui->labelCalOffsetx->setText(QString::number(g_xScanFOVOrigin_su));
        ui->labelCalOffsety->setText(QString::number(g_yScanFOVOrigin_su));

        return 0;
   }
   else         // retains error message posted by writeXMLFile
       return 1;
}
//--------------------------------------------------------------------------------------
// int Mwars::calHalfFrame(void)
//		signal: pbHalfFrame (clicked)
//--------------------------------------------------------------------------------------
int Mwars::calHalfFrame(void) {

    // must scale by 4 for half frame measurement.
    // If full frame with co-ords 0,0 to 640,480, we are now measuring half frame co-ords
    // 160,140 to 480,360. So we set g_xScanFOVOrigin_su = 0, and scale g_xScanFOVMax_su by 4/3

 //   if ((g_xScanFOVMax_su == 0) || (g_xScanFOVOrigin_su == 0)) {
 //       ui->notificationLabelCal->setText("Error: Either ULHC or LRHC not entered");
 //       return 1;
 //   }

    // we measured scanner frame extents corresponding to 1/2 camera frame
    // derive the scaling factor
    g_xSF_PixelToSU = (g_xScanFOVMax_su-g_xScanFOVOrigin_su) / (CAMERA_X_PIXELS/2);
    g_ySF_PixelToSU = (g_yScanFOVMax_su-g_yScanFOVOrigin_su) / (CAMERA_Y_PIXELS/2);

    // we measured scanner offset to 1/2 camera frame i.e. 160,120. Calculate the
    // scanner offset to camera 0,0
    g_xScanFOVOrigin_su = g_xScanFOVOrigin_su - CAMERA_X_PIXELS/4 * g_xSF_PixelToSU;
    g_yScanFOVOrigin_su = g_yScanFOVOrigin_su - CAMERA_Y_PIXELS/4 * g_ySF_PixelToSU;

    // confirm we are not exceeding the practical DAC extents
    if (g_xScanFOVOrigin_su < DAC_X_MIN)  {
          ui->notificationLabelCal->setText("Origin < DAX_X_MIN");
          return -1;
          }
    if (g_yScanFOVOrigin_su < DAC_Y_MIN) {
          ui->notificationLabelCal->setText("Origin < DAX_Y_MIN");
          return -1;
          }

    // we measured scanner offset to 1/2 camera frame i.e. 450,360. Calculate the scanner offset
    // to full frame i.e. 640, 480
    g_xScanFOVMax_su = g_xScanFOVMax_su + CAMERA_X_PIXELS/4 * g_xSF_PixelToSU;
    g_yScanFOVMax_su = g_yScanFOVMax_su + CAMERA_Y_PIXELS/4 * g_ySF_PixelToSU;

    // confirm we are not exceeding the practical DAC extents
    if (g_xScanFOVMax_su > DAC_X_MAX)  {
          ui->notificationLabelCal->setText("x > DAC_X_MAX");
          return -1;
          }
    if (g_yScanFOVMax_su > DAC_Y_MAX) {
          ui->notificationLabelCal->setText("x > DAC_Y_MAX");
          return -1;
          }

    if (!writeXMLFile()) {
         ui->notificationLabelCal->setText("Half Frame Cal Complete");
         calibrateOff();            // toggles off cal function

         // display values
         ui->labelCalScalex->setText(QString::number(g_xSF_PixelToSU));
         ui->labelCalScaley->setText(QString::number(g_ySF_PixelToSU));
         ui->labelCalOffsetx->setText(QString::number(g_xScanFOVOrigin_su));
         ui->labelCalOffsety->setText(QString::number(g_yScanFOVOrigin_su));

         /*qDebug("xOffset: %d yOffset: %d xMax: %d, yMax: %d \n"
                " xDelta: %d yDelta: %d, xScale: %d yScale: %d",
             g_xScanFOVOrigin_su, g_yScanFOVOrigin_su, g_xScanFOVMax_su, g_yScanFOVMax_su,
             (g_xScanFOVMax_su-g_xScanFOVOrigin_su), (g_yScanFOVMax_su-g_yScanFOVOrigin_su),
             g_xSF_PixelToSU, g_ySF_PixelToSU);  */

         return 0;
    }
    else         // retains error mesage posted by writeXMLFile
        return 1;
}


//--------------------------------------------------------------------------------------
// void calSetULHC(void)
//		signal: pbcalSetULHC (clicked)
//--------------------------------------------------------------------------------------

void Mwars::calSetULHC(void) {

    g_xScanFOVOrigin_su = ui->xSpinBox->value();
    g_yScanFOVOrigin_su = ui->ySpinBox->value();

    scannerOff();
    laserOff();

    ui->notificationLabelCal->setText("ULHC recorded");
}

//--------------------------------------------------------------------------------------
// void calSetLRHC(void)
//		signal: pbcalSetLRHC (clicked)
//--------------------------------------------------------------------------------------

void Mwars::calSetLRHC(void) {

    g_xScanFOVMax_su = ui->xSpinBox->value();
    g_yScanFOVMax_su = ui->ySpinBox->value();

    scannerOff();
    laserOff();

    ui->notificationLabelCal->setText("LRHC recorded");
}

//--------------------------------------------------------------------------------------
// int Mwars::writeXMLFile(void)
//-------------------------------------------------------------------------------------
int Mwars::writeXMLFile(void)   {

    QFile file(calFilename);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(0, "Error!", "Error opening file");
        return 1;
     }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("CamPoints");

    xmlWriter.writeTextElement("g_xScanFOVOrigin_su", QString::number(g_xScanFOVOrigin_su) );
    xmlWriter.writeTextElement("g_yScanFOVOrigin_su", QString::number(g_yScanFOVOrigin_su) );
    xmlWriter.writeTextElement("g_xScanFOVMax_su", QString::number(g_xScanFOVMax_su) );
    xmlWriter.writeTextElement("g_yScanFOVMax_su", QString::number(g_yScanFOVMax_su) );
    xmlWriter.writeTextElement("g_xSF_PixelToSU", QString::number(g_xSF_PixelToSU) );
    xmlWriter.writeTextElement("g_ySF_PixelToSU", QString::number(g_ySF_PixelToSU) );
    xmlWriter.writeTextElement("g_xCamTrim", QString::number(g_xCamTrim) );
    xmlWriter.writeTextElement("g_yCamTrim", QString::number(g_yCamTrim) );

    xmlWriter.writeTextElement("g_xLenWallFOV_mm", QString::number(g_xLenWallFOV_mm) );
    xmlWriter.writeTextElement("g_yLenWallFOV_mm", QString::number(g_yLenWallFOV_mm) );
    xmlWriter.writeTextElement("g_xCamtoScanOffset_mm", QString::number(g_xCamtoScanOffset_mm) );
    xmlWriter.writeTextElement("g_yCamtoScanOffset_mm", QString::number(g_yCamtoScanOffset_mm) );
    xmlWriter.writeTextElement("range", QString::number(range_mm) );

    xmlWriter.writeEndElement();

    file.close();
    //ui->notificationLabel->setText("Xml Saved to: " calFilename);

    return 0;   //ok
}


//--------------------------------------------------------------------------------------
// int Mwars::ReadXMLFile()
//-------------------------------------------------------------------------------------
int Mwars::readXMLFile()  {

    //QXmlStreamReader Rxml;

    QFile file(calFilename);
    if (!file.open(QFile::ReadOnly | QFile::Text))  	{
        std::cerr << "Error: Cannot read file " << qPrintable(calFilename)
              << ": " << qPrintable(file.errorString())
              << std::endl;
            qDebug() <<"COULD NOT READ CAMERA CALIBRATION FILE";
        ui->notificationLabelCal->setText("BAD CAL FILE");
        return 1;
    }

    Rxml.setDevice(&file);
    Rxml.readNext();

    while(!Rxml.atEnd()) {
        if(Rxml.isStartElement()) {

            if(Rxml.name() == "CamPoints") {
                ReadCamElements();
            }
            else if(Rxml.name() == "Dummy") {
                //ReadDummyElements();
                //Rxml.readNext();        // i hope this skips over
            }
            else  {
                Rxml.raiseError(QObject::tr("Valid Param"));
            }
        }
        else
            Rxml.readNext();
    }  // while

    file.close();

    // init slider & spinbox ranges to the scanner values corresponding
    // to the camera view extents 0,0 to 640, 480 pixels from the file parameters
     ui->xSlider->setRange(g_xScanFOVOrigin_su, g_xScanFOVMax_su);
     ui->ySlider->setRange(g_yScanFOVOrigin_su, g_yScanFOVMax_su);
     ui->xSpinBox->setRange(g_xScanFOVOrigin_su, g_xScanFOVMax_su);
     ui->ySpinBox->setRange(g_yScanFOVOrigin_su, g_yScanFOVMax_su);
     ui->xSlider->setValue((g_xScanFOVMax_su-g_xScanFOVOrigin_su)/2 + g_xScanFOVOrigin_su);
     ui->ySlider->setValue((g_yScanFOVMax_su-g_yScanFOVOrigin_su)/2 + g_yScanFOVOrigin_su);

    ui->notificationLabelCal->setText("Read cal. file");
    qDebug() <<"read camera calibration file OK";

    // update parameters into the GUI labels
    ui->labelCalScalex->setText(QString::number(g_xSF_PixelToSU));
    ui->labelCalScaley->setText(QString::number(g_ySF_PixelToSU));
    ui->labelCalOffsetx->setText(QString::number(g_xScanFOVOrigin_su));
    ui->labelCalOffsety->setText(QString::number(g_yScanFOVOrigin_su));
    ui->spinboxXCamTrim->setValue(g_xCamTrim);
    ui->spinboxYCamTrim->setValue(g_yCamTrim);
    ui->sbXCamOffset->setValue(g_xCamtoScanOffset_mm);
    ui->sbYCamOffset->setValue(g_yCamtoScanOffset_mm);

    if (Rxml.hasError())  {
        std::cerr << "Error: Failed to parse file "
             << qPrintable(calFilename) << ": "
             << qPrintable(Rxml.errorString()) << std::endl;
        return 1;
    }
    else if (file.error() != QFile::NoError) {
        std::cerr << "Error: Cannot read file " << qPrintable(calFilename)
              << ": " << qPrintable(file.errorString())
              << std::endl;
        return 1;
    }
    return 0;
}

//--------------------------------------------------------------------------------------
// void Mwars::ReadCamElements(void)
//-------------------------------------------------------------------------------------
void Mwars::ReadCamElements(void) {

    bool ok;

    while(!Rxml.atEnd())      {
        if(Rxml.isEndElement()) {
            Rxml.readNext();
            break;
        }
        else if(Rxml.isCharacters())
            Rxml.readNext();

        else if(Rxml.isStartElement()) 	{

            if(Rxml.name() == "g_xScanFOVOrigin_su")
                g_xScanFOVOrigin_su = (Rxml.readElementText()).toUInt (&ok, 10);
            else if(Rxml.name() == "g_yScanFOVOrigin_su")
                g_yScanFOVOrigin_su = (Rxml.readElementText()).toUInt (&ok, 10);

            else if(Rxml.name() == "g_xScanFOVMax_su")
                g_xScanFOVMax_su = (Rxml.readElementText()).toUInt (&ok, 10);
            else if(Rxml.name() == "g_yScanFOVMax_su")
                g_yScanFOVMax_su = (Rxml.readElementText()).toUInt (&ok, 10);

            else if(Rxml.name() == "g_xSF_PixelToSU")
                g_xSF_PixelToSU = (Rxml.readElementText()).toFloat (&ok);
            else if(Rxml.name() == "g_ySF_PixelToSU")
                g_ySF_PixelToSU = (Rxml.readElementText()).toFloat (&ok);

            else if(Rxml.name() == "g_xCamTrim")
                g_xCamTrim = (Rxml.readElementText()).toInt (&ok, 10);
            else if(Rxml.name() == "g_yCamTrim")
                g_yCamTrim = (Rxml.readElementText()).toInt (&ok, 10);

            else if(Rxml.name() == "g_xLenWallFOV_mm")
                g_xLenWallFOV_mm = (Rxml.readElementText()).toInt (&ok, 10);
            else if(Rxml.name() == "g_yLenWallFOV_mm")
                g_yLenWallFOV_mm = (Rxml.readElementText()).toInt (&ok, 10);

            else if(Rxml.name() == "g_xCamtoScanOffset_mm")
                g_xCamtoScanOffset_mm = (Rxml.readElementText()).toInt (&ok, 10);
            else if(Rxml.name() == "g_yCamtoScanOffset_mm")
                g_yCamtoScanOffset_mm = (Rxml.readElementText()).toInt (&ok, 10);

            else if(Rxml.name() == "range_mm")
                range_mm = (Rxml.readElementText()).toInt (&ok, 10);

            Rxml.readNext();
        }
        else
            Rxml.readNext();
    }
}



//--------------------------------------------------------------------------------------
// int Mwars::camTrimOffset(void)
//		signal: pbCamTrimOffset (clicked)
//--------------------------------------------------------------------------------------
int Mwars::camTrimOffset(void) {

    if (!writeXMLFile()) {           // good write return 1 i.e. false
        ui->notificationLabelCal->setText("Trim Complete");
         calibrateOff();

         return 0;
    }
    else         // retains error mesage posted by writeXMLFile
        return 1;
}


//--------------------------------------------------------------------------------------
// void Mwars::g_xCamTrim(void)
//		signal: spinboxXCamTrim (valueChanged)
//--------------------------------------------------------------------------------------
void Mwars::xCamTrim(void) {
    g_xCamTrim = ui->spinboxXCamTrim->value();
}

//--------------------------------------------------------------------------------------
// void Mwars::g_yCamTrim(void)
//		signal: spinboxXYCamTrim (valueChanged)
//--------------------------------------------------------------------------------------
void Mwars::yCamTrim(void) {
    g_yCamTrim = ui->spinboxYCamTrim->value();
}

//--------------------------------------------------------------------------------------
// int Mwars::camScanOffset(void)
//		signal: pbCamOffset (clicked)
//--------------------------------------------------------------------------------------
int Mwars::camScanOffset(void) {

    if (!writeXMLFile()) {           // good write return 1 i.e. false
        ui->notificationLabelCal->setText("Trim Complete");
         calibrateOff();

         return 0;
    }
    else         // retains error mesage posted by writeXMLFile
        return 1;
}


//--------------------------------------------------------------------------------------
// void Mwars::xCamOffset(void)
//		signal: sbXCamOffset (valueChanged)
//--------------------------------------------------------------------------------------
void Mwars::xCamOffset(void) {
    g_xCamtoScanOffset_mm = ui->sbXCamOffset->value();
}

//--------------------------------------------------------------------------------------
// void Mwars::yCamOffset(void)
//		signal: sbYCamOffset (valueChanged)
//--------------------------------------------------------------------------------------
void Mwars::yCamOffset(void) {
    g_yCamtoScanOffset_mm = ui->sbYCamOffset->value();
}

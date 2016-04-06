#include "console.h"
#include "math.h"

#include "ui_consoleForm.h"

//--------------------------------------------------------------------------------------
// void Mwars::testDataToggle(void)
//		signals:	pushButtonTestDataToggle(clicked)
// Enable Scanner button signal comes here
// Note: a toggle
//-------------------------------------------------------------------------------------
void Mwars::testDataToggle(void) {

   if (testDataEnableFlag)         // Is ON; turn off scanner
      disableTestData();
   else                      // Is OFF, turn on
      enableTestData();
}

//--------------------------------------------------------------------------------------
// void Mwars::enableTestData(void)
//-------------------------------------------------------------------------------------
void Mwars::enableTestData(void) {

   disableCameraData();     // turn off, if on
   calibrateOff();

   centre_scanner();
   scannerOn();
   laserOn();

   // turn on test data
   ui->pushButtonTestDataToggle->setStyleSheet("background-color: rgb(255, 255, 0); color: rgb(75, 75, 75)");
   testDataEnableFlag = true;

   //emit testSignal();

 //  testSignal();

   laserOff();

}

//--------------------------------------------------------------------------------------
// void Mwars::disableTestData(void)
//-------------------------------------------------------------------------------------
void Mwars::disableTestData(void) {

       laserOff();
       centre_scanner();        // leave scanner centred
       scannerOff();

       ui->pushButtonTestDataToggle->setStyleSheet("background-color: rgb(255, 255, 255); color: rgb(75, 75, 75)");
       testDataEnableFlag = false;

}






// ***************************** SHONKY GLOBAL VARIABLE DECLARATIONS **************************************
    float angle = 0;  // start at 30 degrees
    bool  fred;
  //  int count = 0;




   /* if (testDataEnableFlag, ){
        if (count == 0)
            sendScannerMssg(CMD_SLEW, 2*g_xScanFOVOrigin_su, 2*g_yScanFOVOrigin_su);
        else if (count == 1)
                sendScannerMssg(CMD_SLEW, 2*g_xScanFOVOrigin_su, g_yScanFOVMax_su/2);
        else if (count == 2)
                sendScannerMssg(CMD_SLEW, g_xScanFOVMax_su/2, g_yScanFOVMax_su/2);
        else
                sendScannerMssg(CMD_SLEW, g_xScanFOVMax_su/2, 2*g_yScanFOVOrigin_su);

        count++;
        if (count == 4)  count = 0;
    }*/



    /*
    void Mwars::testSignal(void) {
    quint16 x;
    quint16 y;

    float deltaAngle = 20;
    //float amplitude = 0xfffe;       // DAC goes 0x0000 -> -10V, 0xffff -> +10V
    float amplitude = 0xfffe/10;
    float offset = 0xfffe/2;

    // angle declared outside function as a global var

# define PI 3.1415

    if (testDataEnable){

        y = offset + amplitude/2 * sin((angle+90) * float (PI / 180));
        x = offset + amplitude/2 * sin((angle) * float (PI / 180));
        // a. does not update spinbox & slider (which is slow slow)
        sendScannerMssg(CMD_SLEW, x, y);
        //OR
        //  B. writes to spinbox, which updates slider, which sends sendScanCmd sending CMD_SLEW with slider values
        // ui->xSpinBox->setValue(x);
        // ui->ySpinBox->setValue(y);

        angle += deltaAngle;            // degrees of increment
    }
}
*/
/*

void Mwars::testSignal(void) {
    quint16 x;
    quint16 y;
    //float amplitude = 0xfffe/1.1;    // ~10V 0 to peak
    float amplitude = 0xfffe/2;      // ~2 V 0-p

    float offset = 0xfffe/2;

    if (testDataEnable){
        fred = !fred;
        if (fred) {
                y = offset + amplitude/2;
                x = offset - amplitude/2;
        }
        else {
                y = offset - amplitude/2;
                x = offset + amplitude/2;
        }
        sendScannerMssg(CMD_SLEW, x, y);
    }
}

*/




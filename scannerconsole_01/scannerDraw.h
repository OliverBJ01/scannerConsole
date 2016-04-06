#ifndef SCANNERDRAW_H
#define SCANNERDRAW_H

#include <QObject>

class Mwars;            //must add a forwarding class declaration to your class
                        // to invoke this classes objects
//--------------------------------------------------------------------------------------
//
// class ScannerDraw
//
//--------------------------------------------------------------------------------------
class ScannerDraw : public QObject {
    Q_OBJECT

public:
    ScannerDraw(Mwars *mwars, int start, int end);
    ~ScannerDraw();

public slots:
    void drawRectangle();
    void Bresenham (int x1, int y1, int x2, int y2);

signals:
    void finished();        //This signal is emitted when process is finished or aborted
    void sendScannerMssg (ushort cmd, ushort x1, ushort y1);
    void laserOn();
    void laserOff();
    void scannerOn();
    void scannerOff();

 private:
    Mwars *mwars;
    int m_start;
    int m_end;

 public:
    bool m_isRunning;
};

#endif // SCANNERDRAW_H



/*
//--------------------------------------------------------------------------------------
//
// class ScannerDraw
//
//--------------------------------------------------------------------------------------
class ScannerDraw : public QObject {
    Q_OBJECT

public:
    explicit ScannerDraw(QObject *parent = 0);
//    ~ScannerDraw();

    // thread safe as it uses #mutex to protect access to #_working variable
    void requestWork();       // Requests the process to start

    // thread safe as it uses #mutex to protect access to #_abort variable
    void abort();           //Requests the process to abort

private:
    //bool _working;          // Process is aborted when @em true
    //bool _abort;            // @em true when Worker is doing work
    //QMutex mutex;           // Protects access to #_abort


signals:
    void workRequested();   //This signal is emitted when the Worker request to Work
    //void valueChanged(const QString &value); //This signal is emitted when counted value is changed (every sec)
    void finished();        //This signal is emitted when process is finished or aborted)
    //void error(QString err);


public slots:
    void drawRectangle(void);
    void Bresenham (int x1, int y1, int const x2, int const y2);

};  */

#ifndef GPSCONFIGURE_H
#define GPSCONFIGURE_H

#include <QObject>
#include <QGeoPositionInfoSource>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QTimer>

#include "gps.h"
#include "math.h"

#define SET_TIMER_CHECK_GPS 200 // 0.5s
#define SET_TIMER_GET_GPS 200 // 0.5s

#define SET_TIME_GPSD_DATA 5000 // 5s

#define pathGpsData "/dev/ttyAMA0"

class gpsconfigure : public QObject
{
    Q_OBJECT
public:
    explicit gpsconfigure(gps_data_t *const gpsData,
                          int *const returnGpsDataStatus,
                          bool *const gpsRunningFlag);

    ~gpsconfigure();

    // Ket noi port data cua gps voi gpsd
    bool ConnectGpsPort(bool OpenGpsPortData = false);

    // Chuong trinh main chay gps
    void startTimerCheckGps();

    // Khoi tao timer kiem tra port Gps
    void initilizeTimerCheckGps(int setTimer);

    // Khoi tao timer upload new data Gps
    void initilizeTimerGetDataGps(int setTimer);

    // Ket noi cac signal va slot can thiet
    void ConnectFunction();

signals:
    // Tin hieu dung de goi chuong trinh khoi dong lai khi co bat cu issue nao xay ra voi Gps
    void callInitializeGpsSignalWhenIssueHappened();

    // Tin hieu dung de thong bao da co data GPS moi duoc cap nhap
    void getDataGpsUpdated(const QGeoPositionInfo &info);

private slots:
    // Chuong trinh nay de cap nhap du lieu gps moi vao bien info
    void getDataGpsChanged();

    // Chuong trinh upgrade data gps.
    void gpsDataRequested();

    // Chuong trinh kiem tra port Gps khi bi mat tinh hieu
    void InitializeGpsSignalWhenIssueHappened();

    // Chuong trinh khoi tao tin hieu GPS
    void InitializeGpsSignal();

private:
    gps_data_t *const getGpsData;

    int *const getReturnGpsDataStatus;

    bool *const getGpsRunningFlag;

    QTimer* _timerCheckGpsPort;
    QTimer* _timerGetDataGps;

    QGeoPositionInfo info;

enum returnGpsDataStatus
    {
        HAVE_DATA_GPS = 0,
        NO_DATA_GPS = 1,
        NO_SIGNAL_GPS = 2,
        GPS_MODULE_RESETED = 3,
        HAVE_PROBLEM = 4
};

    friend class GpsDataSend;
};

#endif // GPSCONFIGURE_H

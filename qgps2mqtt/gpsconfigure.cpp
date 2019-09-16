#include "gpsconfigure.h"

gpsconfigure::gpsconfigure(gps_data_t *const gpsData,
                           int *const returnGpsDataStatus,
                           bool *const gpsRunningFlag)
    : getGpsData(gpsData),
      getReturnGpsDataStatus(returnGpsDataStatus),
      getGpsRunningFlag(gpsRunningFlag)
{
    _timerGetDataGps = new QTimer(this);
    _timerCheckGpsPort = new QTimer(this);

    initilizeTimerCheckGps(SET_TIMER_CHECK_GPS);
    initilizeTimerGetDataGps(SET_TIMER_GET_GPS);

    // Connect signal and slot
    ConnectFunction();
}

gpsconfigure::~gpsconfigure()
{

}

void gpsconfigure::initilizeTimerCheckGps(int setTimer)
{
    //     Khoi tao Timer kiem tra port Gps
    // Dung hoat dong cuar TImer der configue lai
    _timerCheckGpsPort->stop();

    if((nullptr != _timerCheckGpsPort)
       && (true != _timerCheckGpsPort->isActive()))
    {
        _timerCheckGpsPort->setInterval(setTimer);

        connect(_timerCheckGpsPort, SIGNAL(timeout()),
                this, SLOT(InitializeGpsSignal()));

    }
}

void gpsconfigure::initilizeTimerGetDataGps(int setTimer)
{
    //     Khoi tao Timer kiem tra port Gps
    // Dung hoat dong cuar TImer der configue lai
    _timerGetDataGps->stop();

    if((nullptr != _timerGetDataGps)
       && (true != _timerGetDataGps->isActive()))
    {
        _timerGetDataGps->setInterval(setTimer);

        connect(_timerGetDataGps, SIGNAL(timeout()),
                this, SLOT(getDataGpsChanged()));

        _timerGetDataGps->start();
    }
}

void gpsconfigure::InitializeGpsSignal()
{
    if(false == QFileInfo(pathGpsData).exists())
    {
#ifdef DEBUG_LOCATION_GPS
        qDebug() << "Waiting for InitializeGpsSignal\n";
#endif
        *getReturnGpsDataStatus = HAVE_PROBLEM;

        *getGpsRunningFlag = false;
    }

    else if(true == QFileInfo(pathGpsData).exists())
    {

        // Ket noi voi port du lieu GPS voi GPSD
        if(true == ConnectGpsPort(true))
        {
#ifdef DEBUG_LOCATION_GPS
            qDebug() << "StartGpsSignal successed!!!";
#endif
            // Stop Timer
#ifdef DEBUG_LOCATION_GPS
            qDebug() << "GPS Program Started!!!\n"<<
                        "Stop Timer on gpsconfigure class\n";
#endif
            // Ngung timer kiem tra port Gps
            _timerCheckGpsPort->stop();

            // Khoi dong timer upload Gps data
            _timerGetDataGps->start();
        }

        else
        {
            // Khong the ket noi Gps duoc
            qDebug() << "StartGpsSignal failed!!!";

        }
    }

}

bool gpsconfigure::ConnectGpsPort(bool OpenGpsPortData)
{
    try
    {
        if(-1 == gps_open("localhost", "2947", getGpsData))
        {
#ifdef DEBUG_LOCATION_GPS
            qDebug() << "ConnectGpsPort failed!!!";
#endif

            // Khong the ket noi voi Gps port data
            *getReturnGpsDataStatus = HAVE_PROBLEM;
            *getGpsRunningFlag = false;
        }

        else if((true == OpenGpsPortData) &&
                (-1 != gps_open("localhost", "2947", getGpsData)))
        {
            // Doc du lieu tu Gps port
            gps_stream(getGpsData, WATCH_ENABLE, nullptr);

            // Da ket noi duoc voi Gps port
            *getGpsRunningFlag = true;
            *getReturnGpsDataStatus = NO_DATA_GPS;
        }

    }
    catch (...)
    {
        // Su dung ham try catch nay de tranh truong hop loi xay ra:
        // - Gps port mat ket noi khi gps_read dang doc.
        *getReturnGpsDataStatus = HAVE_PROBLEM;

        *getGpsRunningFlag = false;
        // Thong bao loi da xay ra
    }
    return *getGpsRunningFlag;
}

void gpsconfigure::startTimerCheckGps()
{
    // Start Timer
    _timerCheckGpsPort->start();
}

void gpsconfigure::ConnectFunction()
{
#ifdef DEBUG_LOCATION_GPS
    qDebug() << "Connect Function!!!";
#endif
    connect(this, SIGNAL(callInitializeGpsSignalWhenIssueHappened()),
            this, SLOT(InitializeGpsSignalWhenIssueHappened()));

}

// Chuong trinh nay dung de goi lay du lieu tu ben ngoai nhu MQTT, hay gi do, tuy ...
void gpsconfigure::getDataGpsChanged()
{
    try
    {
        // Kiem tra trang thai hoat dong cua Gps Module thong qua gpsRunningFlag xem co du lieu moi cap nhap hay khoong thong qua ham gps_waiting(), thoi gian cho la 5s
        if((true == *getGpsRunningFlag)
           &&(true == gps_waiting(getGpsData, SET_TIME_GPSD_DATA)))
        {
            if(-1 == gps_read(getGpsData))
            {
#ifdef DEBUG_LOCATION_GPS
                qDebug() << "getDataGpsChanged failed!!!";
#endif
                // Xay ra loi voi port Gps Data
                *getReturnGpsDataStatus = HAVE_PROBLEM;

                // Thong bao chuong trinh gap loi
                emit callInitializeGpsSignalWhenIssueHappened();
            }

            else
            {
                /*
                 * Kiem tra xem du lieu Gps co bi sai hay khong
                 * - Kiem tra hai du lieu latitude va longitude cos phai la so hay khong
                 * */
                if ((STATUS_FIX == getGpsData->status)
                     &&!isnan(getGpsData->fix.latitude)
                     &&!isnan(getGpsData->fix.longitude))
                {
#ifdef DEBUG_LOCATION_GPS
                    qDebug("latitude: %f, longitude: %f, speed: %f, timestamp: %lf\n", getGpsData->fix.latitude, getGpsData->fix.longitude, getGpsData->fix.speed, getGpsData->fix.time);
#endif
                    // Thong bao co du lieu moi
                    *getReturnGpsDataStatus = HAVE_DATA_GPS;

                    // Gui thong bao cap nhap du lieu
                    info.setCoordinate(QGeoCoordinate(getGpsData->fix.latitude,
                                                      getGpsData->fix.longitude,
                                                      getGpsData->fix.altitude
                                                      ));

                    info.setAttribute(QGeoPositionInfo::GroundSpeed,
                                      getGpsData->fix.speed);

                }

                else
                {
                    // Du lieu tra ve bi loi
                    *getReturnGpsDataStatus = NO_DATA_GPS;
#ifdef DEBUG_LOCATION_GPS
                    qDebug() << "No updated data!!!";
#endif
                }
            }
        }

        else if((true == *getGpsRunningFlag)
                && (false == gps_waiting(getGpsData, SET_TIME_GPSD_DATA))
                && (false == QFileInfo(pathGpsData).exists()))
        {
            /* Truong hop nay xay ra khi Gps khong hoat dong (gpsRunningFlag = false) hoac khong co du lieu Gps duoc day len trong 5s
             * Goi chuong tirnh khoi dong lai gps
             */

#ifdef DEBUG_LOCATION_GPS
            qDebug() << "GPS module was reseted!!!";
#endif
            // Thong bao Module GPS da bi reset
            emit callInitializeGpsSignalWhenIssueHappened();
        }

        else if((true == *getGpsRunningFlag)
                && (false == gps_waiting(getGpsData, SET_TIME_GPSD_DATA))
                && (true == QFileInfo(pathGpsData).exists()))
        {
            /*
             * Truong hop nay xay ra khi bi mat tinh hieu GPS
             */
#ifdef DEBUG_LOCATION_GPS
            qDebug() << "GPS signal lost!!!";
#endif
            *getReturnGpsDataStatus = NO_SIGNAL_GPS;
        }
    }

    catch (...)
    {
#ifdef DEBUG_LOCATION_GPS
    qDebug() << "Co loi xay ra voi port du lieu Gps!!!";
#endif
    *getReturnGpsDataStatus = HAVE_PROBLEM;
    *getGpsRunningFlag = true;
    // Gui yeu cau khoi dong lai Gps Module
    emit callInitializeGpsSignalWhenIssueHappened();
    }
}

void gpsconfigure::gpsDataRequested()
{
    if(false == isnan(info.coordinate().latitude())
       && false == isnan(info.coordinate().longitude()))
    {
        // Gui du lieu Gps len khi duoc yeu cau
        emit getDataGpsUpdated(info);
    }
}

void gpsconfigure::InitializeGpsSignalWhenIssueHappened()
{
    *getGpsRunningFlag = false;

    // Ngung chuong trinh upload data Gps
    _timerGetDataGps->stop();

    // Khoi dong chuong trinh kiem tra port Gps
    _timerCheckGpsPort->start();
}

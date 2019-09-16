#include "locationdetect.h"

/**
 * @brief LocationDetect::LocationDetect
 * @param parent
 */
GpsDataSend::GpsDataSend(gps_data_t *const gpsData,
                         int *const ReturnGpsDataStatus,
                         bool *const GpsRunningFlag)
{
#ifdef DEBUG_LOCATION_GPS
    qDebug() << "Khoi dong GPS";
#endif

    _gpsconfigure = new gpsconfigure(gpsData,
                                     ReturnGpsDataStatus,
                                     GpsRunningFlag);

    // Ket noi tin hieu getDataGpsUpdated() va function positionUpdated()
    connect(_gpsconfigure, SIGNAL(getDataGpsUpdated(QGeoPositionInfo)),
            this, SLOT(positionUpdated(QGeoPositionInfo)));

    // Khoi dong Gps va ket noi port data
    _gpsconfigure->startTimerCheckGps();

    // Ket noi timerRequestGetDataGps va tin hieu Timer
    _timerRequestGetDataGps = new QTimer(this);
    if((nullptr != _timerRequestGetDataGps)
       && (true != _timerRequestGetDataGps->isActive()))
    {
        _timerRequestGetDataGps->setInterval(SET_TIME_GETGPS);

        connect(_timerRequestGetDataGps, SIGNAL(timeout()),
                _gpsconfigure, SLOT(gpsDataRequested()));

        _timerRequestGetDataGps->start();
    }
}

GpsDataSend::~GpsDataSend()
{
    // Xoa vung cap bo nho cua class nay khi khong can thiet nua, no chi hoat dong khi duoc goi
    delete _gpsconfigure;
}

void GpsDataSend::positionUpdated(const QGeoPositionInfo &info)
{
#ifdef DEBUG_LOCATION_GPS
#endif
    qDebug() << "Position updated:" << info;
    if (_lastPos != info)
    {
        _lastPos = info;
        emit positionChanged(info);
    }
}



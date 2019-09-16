#include "mainmodel.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>

mainModel::mainModel(QObject *parent) : QObject(parent)
{

}

void mainModel::start()
{

    ConfigSetting& settings = ConfigSetting::getInstance();

    // Lay pointer chi toi noi luu tru du lieu cho chuong trinh lay du lieu Gps
    gps_data_t *const gpsData = settings.getPointerToGpsData();
    int *const returnGpsDataStatus = settings.getGpsDataStatus();
    bool *const gpsRunningFlag = settings.getGpsRunningStatus();

    m_gld = new GpsDataSend(gpsData,
                            returnGpsDataStatus,
                            gpsRunningFlag);

    connect(m_gld, SIGNAL(positionChanged(QGeoPositionInfo)),
            this, SLOT(updatePosition(QGeoPositionInfo)));

    QString topic = settings.getMqttTopic();
    QString host = settings.getMqttHost();
    int port = settings.getMqttPort();

    m_sender = new MqttSender(host, port);
    m_sender->setDefaultTopic(topic);

}

void mainModel::updatePosition(const QGeoPositionInfo &info)
{
    QJsonObject jsonObj;
    jsonObj["gps_location"] = 1;
    jsonObj["latitude"] = QString::number(info.coordinate().latitude(), 'g', 12);
    jsonObj["longitude"] = QString::number(info.coordinate().longitude(), 'g', 12);
    jsonObj["speed"] = QString::number(info.attribute(QGeoPositionInfo::GroundSpeed));

    QJsonDocument jsonDoc(jsonObj);
    if (m_sender)
    {
        this->m_sender->send(jsonDoc.toJson().data(), jsonDoc.toJson().size());
    }
}


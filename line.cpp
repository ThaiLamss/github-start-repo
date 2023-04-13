#include "line.h"


Line::Line(QObject *parent) : QObject(parent)
{

}

void Line::writeJson(QJsonObject &json) const
{
    json["lineId"] = m_lineId;
    json["productionModel"] = m_productionModel;
    m_productionLine.writeJson(json);
    m_wipLine.writeJson(json);
    m_agv.writeJson(json);
}

void Line::readJson(const QJsonObject &json)
{
    m_lineId = json["lineId"].toInt();
    m_productionModel = json["productionModel"].toString();
    if(m_productionLine.readJson(json)) emit productionLineChanged();
    if(m_wipLine.readJson(json)) emit wipLineChanged();
    if(m_agv.readJson(json)) emit agvChanged();
}

int Line::lineId() const
{
    return m_lineId;
}

void Line::setLineId(int lineId)
{
    if (m_lineId == lineId)
        return;
    m_lineId = lineId;
    emit lineIdChanged();
}


const QString &Line::productionModel() const
{
    return m_productionModel;
}

void Line::setProductionModel(const QString &newProductionModel)
{
    if (m_productionModel == newProductionModel)
        return;
    m_productionModel = newProductionModel;
    emit productionModelChanged();
}

void Line::setLineStatus(ProductionLine::LineStatus newStatus)
{
    if(m_productionLine.updateStatus(newStatus))
    {
        emit productionLineChanged();
    }
}

void Line::setWipStatus(WipLine::LineStatus newStatus)
{
    if(m_wipLine.updateStatus(newStatus))
    {
        emit wipLineChanged();
    }
}

void Line::setAGVStatus(AGV::AGVStatus newStatus)
{
    if(m_agv.updateStatus(newStatus))
    {
        emit agvChanged();
    }
}

QVariantMap Line::getProductionLineData()
{
    QVariantMap productionLineData;

    // Lấy thông tin của ProductionLine
    QString status;
    QDateTime currentTime = QDateTime::currentDateTime();
    int iElapsedSec = m_productionLine.timeUpdated.secsTo(currentTime);
    QString elapsedTime = QDateTime::fromSecsSinceEpoch(iElapsedSec,Qt::TimeSpec::UTC).toString("hh:mm:ss");

    // Chuyển đổi enum LineStatus thành QString
    switch (m_productionLine.status) {
    case ProductionLine::LineStatus::Full:
        status = "Full";
        break;
    case ProductionLine::LineStatus::Call:
        status = "Call";
        break;
    default:
        status = "unknown";
        break;
    }

    // Thêm dữ liệu vào QVariantMap
    productionLineData.insert("status", status);
    productionLineData.insert("timeUpdated", m_productionLine.timeUpdated.toString("hh:mm:ss"));
    productionLineData.insert("elapsedTime", elapsedTime);

    return productionLineData;
}

QVariantMap Line::getWipLineData()
{
    QVariantMap wipLineData;

    // Lấy thông tin của ProductionLine
    QString status;
    QDateTime currentTime = QDateTime::currentDateTime();
    int iElapsedSec = m_wipLine.timeUpdated.secsTo(currentTime);
    QString elapsedTime = QDateTime::fromSecsSinceEpoch(iElapsedSec,Qt::TimeSpec::UTC).toString("hh:mm:ss");

    // Chuyển đổi enum LineStatus thành QString
    switch (m_wipLine.status) {
    case Line::WipLine::Empty:
        status = "Empty";
        break;
    case Line::WipLine::Confirmed:
        status = "Confirmed";
        break;
    default:
        status = "unknown";
        break;
    }

    // Thêm dữ liệu vào QVariantMap
    wipLineData.insert("status", status);
    wipLineData.insert("timeUpdated", m_wipLine.timeUpdated.toString("hh:mm:ss"));
    wipLineData.insert("elapsedTime", elapsedTime);

    return wipLineData;
}

QVariant Line::getAgvData()
{
    QVariantMap agvData;

    // Lấy thông tin của ProductionLine
    QString status;
    int agvID = m_agv.agvID;
    QDateTime currentTime = QDateTime::currentDateTime();
    int iElapsedSec = m_agv.timeUpdated.secsTo(currentTime);
    QString elapsedTime = QDateTime::fromSecsSinceEpoch(iElapsedSec,Qt::TimeSpec::UTC).toString("hh:mm:ss");

    // Chuyển đổi enum LineStatus thành QString
    switch (m_agv.status) {
    case Line::AGV::Idle:
        status = "Idle";
        break;
    case Line::AGV::Call:
        status = "Call";
        break;
    case Line::AGV::Carried:
        status = "Carried";
        break;
    default:
        status = "unknown";
        break;
    }

    // Thêm dữ liệu vào QVariantMap
    agvData.insert("status", status);
    agvData.insert("agvID", agvID);
    agvData.insert("timeUpdated", m_agv.timeUpdated.toString("hh:mm:ss"));
    agvData.insert("elapsedTime", elapsedTime);

    return agvData;
}

bool Line::ProductionLine::updateStatus(LineStatus newStatus)
{
    if (status != newStatus)
    {
        status = newStatus;
        timeUpdated = QDateTime::currentDateTime();
        return true;
    }
    return false;
}

void Line::ProductionLine::writeJson(QJsonObject &json) const
{
    QJsonObject lineObj;
    lineObj["status"] = status;
    lineObj["timeUpdate"] = timeUpdated.toString("yy-MM-dd hh:mm:ss");
    json["productionLine"] = lineObj;
}

bool Line::ProductionLine::readJson(const QJsonObject &json)
{
    if(json.contains("productionLine")&&json["productionLine"].isObject())
    {
        QJsonObject lineObj = json["productionLine"].toObject();
        status = LineStatus(lineObj["status"].toInt());
        timeUpdated = QDateTime::fromString(lineObj["timeUpdate"].toString(),"yy-MM-dd hh:mm:ss");
        return true;
    }
    return false;
}

bool Line::WipLine::updateStatus(LineStatus newStatus)
{
    if (status != newStatus)
    {
        status = newStatus;
        timeUpdated = QDateTime::currentDateTime();
        return true;
    }
    return false;
}

void Line::WipLine::writeJson(QJsonObject &json) const
{
    QJsonObject wipObject;
    wipObject["status"] = status;
    wipObject["timeUpdate"] = timeUpdated.toString("yy-MM-dd hh:mm:ss");
    json["wipLine"] = wipObject;
}


bool Line::WipLine::readJson(const QJsonObject &json)
{
    if(json.contains("wipLine")&&json["wipLine"].isObject())
    {
        QJsonObject wipObj = json["wipLine"].toObject();
        status = LineStatus(wipObj["status"].toInt());
        timeUpdated = QDateTime::fromString(wipObj["timeUpdate"].toString(),"yy-MM-dd hh:mm:ss");
        return true;
    }
    return false;
}

bool Line::AGV::updateStatus(AGVStatus newStatus)
{
    if (status != newStatus)
    {
        status = newStatus;
        timeUpdated = QDateTime::currentDateTime();
        return true;
    }
    return false;
}

void Line::AGV::writeJson(QJsonObject &json) const
{
    QJsonObject agvObj;
    agvObj["status"] = status;
    agvObj["agvID"] = agvID;
    agvObj["timeUpdate"] = timeUpdated.toString("yy-MM-dd hh:mm:ss");
    json["agv"] = agvObj;
}

bool Line::AGV::readJson(const QJsonObject &json)
{
    if(json.contains("agv")&&json["agv"].isObject())
    {
        QJsonObject agvObj = json["agv"].toObject();
        status = AGVStatus(agvObj["status"].toInt());
        agvID = agvObj["agvID"].toInt();
        timeUpdated = QDateTime::fromString(agvObj["timeUpdate"].toString(),"yy-MM-dd hh:mm:ss");
        return true;
    }
    return false;
}

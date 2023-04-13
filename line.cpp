#include "line.h"


Line::Line(QObject *parent) : QObject(parent)
{

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

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

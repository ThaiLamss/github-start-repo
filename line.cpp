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

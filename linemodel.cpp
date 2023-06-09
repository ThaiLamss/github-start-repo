#include "linemodel.h"


LineModel::LineModel(QObject *parent) : QAbstractListModel(parent)
{

}

void LineModel::writeJson(QJsonObject &json) const
{
//    QList<Line*> m_lines; // Danh sách các đối tượng Line
//    QStringList m_productionModels;
    QJsonArray productionModelArray = QJsonArray::fromStringList(m_productionModels);
    QJsonArray lineArray;
    foreach(Line* line, m_lines)
    {
        QJsonObject lineObj;
        line->writeJson(lineObj);
        lineArray.append(lineObj);
    }
    json["productionModelArray"] = productionModelArray;
    json["lineArray"] = lineArray;

}

void LineModel::readJson(const QJsonObject &json)
{
    if(json.contains("productionModelArray")&&json["productionModelArray"].isArray())
    {
        QJsonArray productionModelArray = json["productionModelArray"].toArray();
        m_productionModels.clear();
        foreach (QVariant model, productionModelArray.toVariantList())
        {
            m_productionModels.append(model.toString());
        }
    }
    if(json.contains("lineArray")&&json["lineArray"].isArray())
    {
        QJsonArray lineArray = json["LineData"].toArray();
        m_lines.clear();

        for(int lineIndex=0; lineIndex < lineArray.size();++lineIndex)
        {
            QJsonObject lineObj = lineArray[lineIndex].toObject();
            Line *line = new Line(this);
            line->readJson(lineObj);
        }
    }
}

const QStringList &LineModel::productionModels() const
{
    return m_productionModels;
}

void LineModel::setProductionModels(const QStringList &newProductionModels)
{
    if (m_productionModels == newProductionModels)
        return;
    m_productionModels = newProductionModels;
    emit productionModelsChanged();
}

void LineModel::addLine(Line *line)
{
    // Bắt đầu thêm dữ liệu vào danh sách
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    // Thêm đối tượng Line vào danh sách
    m_lines.append(line);

    // Kết thúc thêm dữ liệu vào danh sách
    endInsertRows();
}


int LineModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_lines.length();
}

QVariant LineModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    // Lấy dòng (Line) tương ứng với index
    Line* line = m_lines.at(index.row());

    // Kiểm tra role và trả về dữ liệu tương ứng
    switch (role) {
    case LineIdRole:
        return line->lineId();
    case ProductionModelsRole:
        return productionModels();
    case ProductionLineRole:
    {
        return line->getProductionLineData();

    }
    case WipLineRole:
    {
        return line->getWipLineData();
    }
    case AgvRole:
    {
        return line->getAgvData();
    }
    default:
        return QVariant();
    }
}

bool LineModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
            return false;
        }

    Line* line = m_lines.at(index.row());
    switch (role) {
    case LineIdRole:
        line->setLineId(value.toInt());
        emit dataChanged(index, index, { role });
        return true;
    default:
        return false;
    }

}

QHash<int, QByteArray> LineModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[LineIdRole] = "lineId";
    roles[ProductionModelsRole] = "productionModel";
    roles[ProductionLineRole] = "productionLine";
    roles[WipLineRole] = "wipLineRole";
    roles[AgvRole] = "agvRole";

    return roles;
}

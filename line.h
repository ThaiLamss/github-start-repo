#ifndef LINE_H
#define LINE_H


#include <QObject>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QVariantMap>
#include <QJsonObject>

class Line : public QObject
{
    Q_OBJECT
public:
    explicit Line(QObject *parent = nullptr);

    struct ProductionLine
    {
        enum LineStatus { Full, Call };
        LineStatus status;
        QDateTime timeUpdated;

        bool updateStatus(LineStatus newStatus);
        void writeJson(QJsonObject &json) const;
        bool readJson(const QJsonObject &json);

    };
    struct WipLine
    {
        enum LineStatus { Empty, Confirmed };
        LineStatus status;
        QDateTime timeUpdated;

        bool updateStatus(LineStatus newStatus);
        void writeJson(QJsonObject &json) const;
        bool readJson(const QJsonObject &json);
    };
    struct AGV
    {
        int agvID;
        enum AGVStatus { Idle, Call, Carried };
        AGVStatus status;
        QDateTime timeUpdated;

        bool updateStatus(AGVStatus newStatus);
        void writeJson(QJsonObject &json) const;
        bool readJson(const QJsonObject &json);
    };

    Q_PROPERTY(int lineId READ lineId WRITE setLineId NOTIFY lineIdChanged)
    Q_PROPERTY(QString productionModel READ productionModel WRITE setProductionModel NOTIFY productionModelChanged)

    void writeJson(QJsonObject &json) const;
    void readJson(const QJsonObject &json);

    int lineId() const;
    void setLineId(int lineId);

    const QString &productionModel() const;
    void setProductionModel(const QString &newProductionModel);
    void setLineStatus(ProductionLine::LineStatus newStatus);
    void setWipStatus(WipLine::LineStatus newStatus);
    void setAGVStatus(AGV::AGVStatus newStatus);
    QVariantMap getProductionLineData();
    QVariantMap getWipLineData();
    QVariant getAgvData();

signals:
    void lineIdChanged();
    void productionLineChanged();
    void wipLineChanged();
    void agvChanged();
    void productionModelChanged();

private:
    int m_lineId;
    QString m_productionModel;
    ProductionLine m_productionLine;
    WipLine m_wipLine;
    AGV m_agv;

};


#endif // LINE_H

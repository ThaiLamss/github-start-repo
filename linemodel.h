#ifndef LINEMODEL_H
#define LINEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "line.h"

class LineModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList productionModels READ productionModels WRITE setProductionModels NOTIFY productionModelsChanged)
public:
    explicit LineModel(QObject *parent = nullptr);

    // Role enum để định nghĩa các role sử dụng trong QML
    enum LineModelRoles {
        LineIdRole = Qt::UserRole + 1,
        ProductionModelsRole,
        ProductionLineRole,
        WipLineRole,
        AgvRole
    };

    const QStringList &productionModels() const;
    void setProductionModels(const QStringList &newProductionModels);


    void addLine(Line *line);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

signals:
    void productionModelsChanged();

protected:
    // Khởi tạo mapping giữa role và tên role
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Line*> m_lines; // Danh sách các đối tượng Line
    QStringList m_productionModels;

};

#endif // LINEMODEL_H

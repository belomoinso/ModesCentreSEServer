#ifndef MODESCENTREMODEL_H
#define MODESCENTREMODEL_H

#include <QAbstractListModel>

struct HourValue
{
    double value = 0;
    bool checked = true;
};

class ModesCentreModel : public QAbstractListModel
{
    Q_OBJECT

    enum ModesCentreRoles
    {
        YesterdayRole = Qt::UserRole,
        TodayRole,
        TomorrowRole,
        HourRole,
        YesterdayCheckRole,
        TodayCheckRole,
        TomorrowCheckRole,
    };

public:
    explicit ModesCentreModel(QObject* parent = nullptr);

    Q_INVOKABLE void generateValues();

    QVariant data(const QModelIndex& index, int role) const final;
    QHash<int, QByteArray> roleNames() const final;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVector<HourValue>& yesterdayValuesRef() { return m_yesterdayValues; }
    QVector<HourValue>& todayValuesRef() { return m_todayValues; }
    QVector<HourValue>& tomorrowValuesRef() { return m_tomorrowValues; }

private:
    QVector<HourValue> m_yesterdayValues;
    QVector<HourValue> m_todayValues;
    QVector<HourValue> m_tomorrowValues;
};

#endif // MODESCENTREMODEL_H

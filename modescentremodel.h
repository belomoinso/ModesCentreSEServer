#ifndef MODESCENTREMODEL_H
#define MODESCENTREMODEL_H

#include <QAbstractListModel>

class ModesCentreModel : public QAbstractListModel
{
    Q_OBJECT

    enum ModesCentreRoles
    {
        TodayRole = Qt::UserRole,
        TomorrowRole,
        HourRole
    };

public:
    explicit ModesCentreModel(QObject* parent = nullptr);

    Q_INVOKABLE void generateValues();

    QVariant data(const QModelIndex& index, int role) const final;
    QHash<int, QByteArray> roleNames() const final;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVector<double>& todayValuesRef() { return m_todayValues; }
    QVector<double>& tomorrowValuesRef() { return m_tomorrowValues; }

private:
    QVector<double> m_todayValues;
    QVector<double> m_tomorrowValues;
};

#endif // MODESCENTREMODEL_H

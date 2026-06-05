#include "modescentremodel.h"
#include <QDateTime>
#include <QDebug>

ModesCentreModel::ModesCentreModel(QObject* parent) :
    QAbstractListModel(parent)
{
    m_yesterdayValues.resize(24);
    m_todayValues.resize(24);
    m_tomorrowValues.resize(24);

    generateValues();
}

void ModesCentreModel::generateValues()
{
    std::srand(QDateTime::currentMSecsSinceEpoch());
    for (int i = 0; i < 24; ++i)
    {
        m_yesterdayValues[i].value = (static_cast<double>(std::rand() % 10001)) / 100;
        m_todayValues[i].value = (static_cast<double>(std::rand() % 10001)) / 100;
        m_tomorrowValues[i].value = (static_cast<double>(std::rand() % 10001)) / 100;
    }
    emit dataChanged(index(0), index(rowCount() - 1), { YesterdayRole, TodayRole, TomorrowRole });
}

QHash<int, QByteArray> ModesCentreModel::roleNames() const
{
    const static QHash<int, QByteArray> rnames = {
        { YesterdayRole, QByteArrayLiteral("yesterday") },
        { TodayRole, QByteArrayLiteral("today") },
        { TomorrowRole, QByteArrayLiteral("tomorrow") },
        { HourRole, QByteArrayLiteral("hour") },
        { YesterdayCheckRole, QByteArrayLiteral("yesterdayChecked") },
        { TodayCheckRole, QByteArrayLiteral("todayChecked") },
        { TomorrowCheckRole, QByteArrayLiteral("tomorrowChecked") },
    };
    return rnames;
}

int ModesCentreModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 24;
}

QVariant ModesCentreModel::data(const QModelIndex& index, int role) const
{
    Q_ASSERT(index.isValid());
    const auto row = index.row();

    switch (role)
    {
    case YesterdayRole:
        return QString::number(m_yesterdayValues.at(row).value, 'f', 2);
    case TodayRole:
        return QString::number(m_todayValues.at(row).value, 'f', 2);
    case TomorrowRole:
        return QString::number(m_tomorrowValues.at(row).value, 'f', 2);
    case HourRole:
        return QString("%1:00").arg(row + 1, 2, 10, QLatin1Char('0'));
    case YesterdayCheckRole:
        return m_yesterdayValues.at(row).checked;
    case TodayCheckRole:
        return m_todayValues.at(row).checked;
    case TomorrowCheckRole:
        return m_tomorrowValues.at(row).checked;
    }
    return QVariant();
}

bool ModesCentreModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    const auto row = index.row();
    bool ok = false;
    switch (role)
    {
    case YesterdayRole:
        m_yesterdayValues[row].value = value.toDouble(&ok);
        emit dataChanged(index, index, { YesterdayRole });
        break;
    case TodayRole:
        m_todayValues[row].value = value.toDouble(&ok);
        emit dataChanged(index, index, { TodayRole });
        break;
    case TomorrowRole:
        m_tomorrowValues[row].value = value.toDouble(&ok);
        break;
    case YesterdayCheckRole:
    {
        const auto val = value.toBool();
        if (m_yesterdayValues[row].checked == val)
            return true;
        m_yesterdayValues[row].checked = value.toBool();
        emit dataChanged(index, index, { YesterdayCheckRole });
        return true;
    }
    case TodayCheckRole:
    {
        const auto val = value.toBool();
        if (m_todayValues[row].checked == val)
            return true;
        m_todayValues[row].checked = value.toBool();
        emit dataChanged(index, index, { TodayCheckRole });
        return true;
    }
    case TomorrowCheckRole:
    {
        const auto val = value.toBool();
        if (m_tomorrowValues[row].checked == val)
            return true;
        m_tomorrowValues[row].checked = value.toBool();
        emit dataChanged(index, index, { TomorrowCheckRole });
        return true;
    }
    }
    return ok;
}

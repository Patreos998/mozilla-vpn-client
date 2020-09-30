#ifndef SERVERCOUNTRYMODEL_H
#define SERVERCOUNTRYMODEL_H

#include "servercountry.h"

#include <QAbstractListModel>
#include <QByteArray>
#include <QObject>
#include <QPointer>

class SettingsHolder;
class ServerData;

class ServerCountryModel final : public QAbstractListModel
{
public:
    enum ServerCountryRoles {
        NameRole = Qt::UserRole + 1,
        CodeRole,
        CitiesRole,
    };

    ServerCountryModel() = default;

    bool fromSettings(SettingsHolder &settingsHolder);

    void fromJson(const QByteArray &data);

    void pickRandom(ServerData &data);

    const QList<Server> getServers(const ServerData &data) const;

    // QAbstractListModel methods

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &) const override { return m_countries.length(); }

    QVariant data(const QModelIndex &index, int role) const override;

private:
    void fromJsonInternal();

private:
    QByteArray m_rawJson;

    QList<ServerCountry> m_countries;
};

#endif // SERVERCOUNTRYMODEL_H

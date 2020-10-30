/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef NETWORKREQUEST_H
#define NETWORKREQUEST_H

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>

class MozillaVPN;
class QNetworkAccessManager;

class NetworkRequest final : public QObject
{
    Q_OBJECT

public:
    ~NetworkRequest() = default;

    // This object deletes itself at the end of the operation.

    static NetworkRequest *createForAuthenticationVerification(QObject *parent,
                                                               MozillaVPN *vpn,
                                                               const QString &pkceCodeSuccess,
                                                               const QString &pkceCodeVerifier);

    static NetworkRequest *createForDeviceCreation(QObject *parent,
                                                   MozillaVPN *vpn,
                                                   const QString &deviceName,
                                                   const QString &pubKey);

    static NetworkRequest *createForDeviceRemoval(QObject *parent,
                                                  MozillaVPN *vpn,
                                                  const QString &pubKey);

    static NetworkRequest *createForServers(QObject *parent, MozillaVPN *vpn);

    static NetworkRequest *createForAccount(QObject *parent, MozillaVPN *vpn);

    static NetworkRequest *createForVersions(QObject *parent, MozillaVPN *vpn);

    static NetworkRequest *createForIpInfo(QObject *parent, MozillaVPN *vpn);

    static NetworkRequest *createForCaptivePortalDetection(QObject *parent);

    static NetworkRequest *createForDOH(QObject *parent,
                                        const QUrl &dohUrl,
                                        const QByteArray &dohHost);

#ifdef IOS_INTEGRATION
    static NetworkRequest *createForIOSProducts(QObject *parent, MozillaVPN *vpn);

    static NetworkRequest *createForIOSPurchase(QObject *parent,
                                                MozillaVPN *vpn,
                                                const QString &orderId);
#endif

private:
    NetworkRequest(QObject *parent);

    void deleteRequest();
    void getRequest();
    void postRequest(const QByteArray &body);

    void handleReply(QNetworkReply *reply);

private slots:
    void replyFinished();

signals:
    void requestFailed(QNetworkReply::NetworkError error);
    void requestCompleted(const QByteArray &data);

private:
    QNetworkRequest m_request;
    QNetworkReply *m_reply = nullptr;
};

#endif // NETWORKREQUEST_H

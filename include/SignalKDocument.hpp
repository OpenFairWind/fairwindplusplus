//
// Created by Raffaele Montella on 18/04/21.
//

#ifndef FAIRWIND_SIGNALKDOCUMENT_HPP
#define FAIRWIND_SIGNALKDOCUMENT_HPP


#include <QJsonDocument>

class SignalKDocument: public QObject {
    Q_OBJECT

public:
    explicit SignalKDocument();
    ~SignalKDocument();

    void save(QString fileName);
    void load(QString fileName);

    void update(QJsonObject &jsonObjectUpdate);
    void insert(const QString& path, const QJsonValue& newValue);
    QJsonObject subtree(const QString& path);

    QString getSelf();
    QString getVersion();

signals:
    void updated(const QString path);
    void updatedNavigationPosition();

private:
    QJsonDocument m_jsonDocument;

    void modifyJsonValue(QJsonObject& obj, const QString& path, const QJsonValue& newValue);

};


#endif //FAIRWIND_SIGNALKDOCUMENT_HPP

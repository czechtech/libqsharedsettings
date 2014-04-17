#ifndef QSHAREDSETTINGS_H
#define QSHAREDSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QVariant>
#include <QMap>
#include <QStringList>
#include <QTimer>
#include <QDebug>

using namespace std;

class QSharedSettings : public QSettings
{
	Q_OBJECT

public:
	 QSharedSettings(const QString &organization, const QString &application = QString(), QObject *parent = 0);
	 QSharedSettings(Scope scope, const QString &organization, const QString &application = QString(), QObject *parent = 0);
	 QSharedSettings(Format format, Scope scope, const QString &organization, const QString &application = QString(), QObject *parent = 0);
	 QSharedSettings(const QString &fileName, Format format, QObject *parent = 0);
	 QSharedSettings(QObject * parent = 0);
	~QSharedSettings();

protected:
	//

private:
	void initialize();
	QTimer m_pollingTimer;
	QVariantMap m_storedSettings; // typedef QMap<QString, QVariant>

public:
	//

public slots:
	//

private slots:
	void checkSettings();

signals:
	void settingChanged(QString key);

};

#endif // QSHAREDSETTINGS_H

#include "qsharedsettings.h"

QSharedSettings::QSharedSettings(const QString &organization, const QString &application, QObject *parent)
	: QSettings(organization, application, parent)
{
	initialize();
}

QSharedSettings::QSharedSettings(Scope scope, const QString &organization, const QString &application, QObject *parent)
	: QSettings(scope, organization, application, parent)
{
	initialize();
}

QSharedSettings::QSharedSettings(Format format, Scope scope, const QString &organization, const QString &application, QObject *parent)
	: QSettings(format, scope, organization, application, parent)
{
	initialize();
}

QSharedSettings::QSharedSettings(const QString &fileName, Format format, QObject *parent)
	: QSettings(fileName, format, parent)
{
	initialize();
}

QSharedSettings::QSharedSettings(QObject *parent)
	: QSettings(parent)
{
	initialize();
}


void QSharedSettings::initialize()
{
	// initialize the qmap
	checkSettings();
	
    connect(&m_pollingTimer, SIGNAL(timeout()), this, SLOT(checkSettings()) );

	// start the polling timer
	m_pollingTimer.start(1000);
}


QSharedSettings::~QSharedSettings()
{
	// end the polling timer?
	m_pollingTimer.stop();

	// free the qmap?
}

// private slot
void QSharedSettings::checkSettings()
{
	sync();

	QStringList changedKeys = allKeys();

	// Check each stored key,value
	for(QList<QString> storedKeys = m_storedSettings.keys(); storedKeys.size() > 0; storedKeys.removeFirst()) {
		QString k = storedKeys.first();
		if(!changedKeys.contains(k)) {
			// it's been removed
			changedKeys.append(k);
			m_storedSettings.remove(k);
		}
		else if(m_storedSettings.value(k) == value(k) ) {
			// it's not been changed
			changedKeys.removeAll(k);
		}
		else {
			// update the stored value
			m_storedSettings[k] = value(k);
		}

	}
	
	// Store any new settings
	for(int i = 0; i < changedKeys.size(); i++) {
		QString k = changedKeys[i];
		if(!m_storedSettings.contains(k) && contains(k)) {
			m_storedSettings[k] = value(k);
		}
	}

	if(changedKeys.size() > 0) {
		emit settingsChanged(changedKeys);
	}
}

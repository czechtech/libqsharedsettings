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
	QStringList currentKeys = allKeys();
	
	int currentSize = currentKeys.size();
	int storedSize  = m_storedSettings.keys().size();
	
	// FIX ME: This is not a robust method of making sure the key lists are identical
	
	// check for removed key,value pairs:
	if(currentSize < storedSize) {
		QStringList storedKeys = m_storedSettings.keys();
		for(int i = 0; i < currentSize; i++) {
			int index = storedKeys.indexOf(currentKeys[i]);
			if(index != -1) {
				storedKeys.removeAt(index);
			} else {
				emit settingChanged(currentKeys[i]);
			}
		}
	}
	
	// check for new key,value pairs:
	if(currentSize > storedSize) {
		QStringList storedKeys = m_storedSettings.keys();
		for(int i = 0; i < storedSize; i++) {
			int index = currentKeys.indexOf(storedKeys[i]);
			if(index != -1) {
				currentKeys.removeAt(index);
			} else {
				emit settingChanged(storedKeys[i]);
			}
		}
		currentKeys = allKeys();
	}
	
	// check values:
	for (int i = 0; i < currentKeys.size(); i++) {
		QString key = currentKeys[i];
		if(m_storedSettings.value(key) != value(key) ) {
			emit settingChanged(key);
			m_storedSettings[key] = value(key);
		}
	}
}

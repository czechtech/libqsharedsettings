#include <iostream>
#include <csignal>
#include <QCoreApplication>
#include <QTime>
#include <QDebug>
#include "../qsharedsettings.h"

using namespace std;

QCoreApplication *a;

void signalHandler(int signum) { cerr << "Terminating\n"; a->exit(0); }

class TestClass: public QObject
{
    Q_OBJECT
public slots:
	void onChangedSettings(QStringList keys)  {
		QSettings s("CzechTech", "QSharedSettingsDemo");
		for(int i = 0; i < keys.size(); i++) {
			QString  key   = keys.at(i);
			QVariant value = s.value(key);
			if(!s.contains(key)) { value = "(removed)"; }
			qDebug() << "CHANGE:" << key << " is now " << value;
		}
	}
};


int main(int argc, char *argv[])
{
  a = new QCoreApplication(argc, argv);
  signal(SIGINT,  signalHandler); signal(SIGTERM, signalHandler);

  TestClass t;
  QSharedSettings s("CzechTech", "QSharedSettingsDemo");

  QObject::connect(&s, SIGNAL(settingsChanged(QStringList)), &t, SLOT(onChangedSettings(QStringList)));

  qDebug() << "RandomNumber is currently: " << s.value("RandomNumber");

  qDebug() << "Changing RandonNumber value now...";
  QTime now = QTime::currentTime();
  s.setValue("RandomNumber", now.msec());
  
  return a->exec();
}

#include "test.moc" //http://stackoverflow.com/questions/5854626/qt-signals-and-slots-error-undefined-reference-to-vtable-for
#include <iostream>
#include <csignal>
#include <QCoreApplication>
#include <QTime>
#include <QDebug>
#include <QTest>
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

  // Display All Settings
  qDebug() << "Current Settings:";
  QStringList keylist = s.allKeys();
  for(int i = 0; i < keylist.size(); i++) {
    qDebug() << "Key: " << keylist[i] << "Value:" << s.value(keylist[i]);
  }
  
  QTest::qWait(1000);
  
  // Add A New Setting
  qDebug() << "Adding New Setting...";;
  QString add1 = "Rand" + QString::number(QTime::currentTime().msec());
  int val1 = QTime::currentTime().msec();
  s.setValue(add1, val1);

  QTest::qWait(1000);

  // Remove 2 Settings
  if(s.allKeys().size() > 2) {
    qDebug() << "Deleting 2 Settings...";
    QString delKey1 = s.allKeys()[0];
    QString delKey2 = s.allKeys()[1];
    s.remove(delKey1);
    s.remove(delKey2);
  }

  QTest::qWait(1000);

  // Add A New Setting
  qDebug() << "Adding Another New Setting...";
  QString add2 = "Rand" + QString::number(QTime::currentTime().msec());
  int val2 = QTime::currentTime().msec();
  s.setValue(add2, val2);
  
  QTest::qWait(1000);

  // Change 1 Setting
  if(s.allKeys().size() > 0) {
    qDebug() << "Changing A Setting...";
    s.setValue(s.allKeys()[0], QTime::currentTime().msec());
  }
  
  return a->exec();
}

#include "test.moc" //http://stackoverflow.com/questions/5854626/qt-signals-and-slots-error-undefined-reference-to-vtable-for
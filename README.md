QSharedSettings Library - libqsharedsettings
============================================

Enhance QSettings for dynamic settings changes.

Typically, a QSettings object is instantiated for only two brief moments during a program's execution:
- At the launch of an application to read it's previous state, and then
- At the close of the application to save it's current state.

QSharedSettings is designed to have a persistent settings object that alerts the application whenever it's settings have been adjusted. These adjustments can be made internally by itself, or, more radically, by an external source such as a system-wide settings application or another cooperative application.

It helps to have an understanding of [QSettings](http://qt-project.org/doc/qt-4.8/qsettings.html) to fully understand the purpose of this library.


Installation
------------

Download, compile, and install:

    wget https://github.com/czechtech/libqsharedsettings/archive/master.zip
    gunzip master.zip
    cd libqsharedsettings-master
    qmake && make && su -c 'make install'
    cd ..
    rm master.zip


Usage
-----

Include QSharedSettings header file:

    #include <qsharedsetting.h>

Add a persistent QSharedSettings member to the main class definition.

    QSharedSettings m_settings;

Declare and define an appropriate slot.

    void onChangedSettings(QStringList keys)  { ... }

Connect the signal/slot in the constructor of your main class.

    connect(&m_settings, SIGNAL(settingsChanged(QStringList)), this, SLOT(onChangedSettings(QStringList)));

Now, whenever a setting or settings are changed, the settingsChanged(...) signal is added to the event queue with the keys of the settings which have changed.  The onChangedSettings(...) slot is called, and the application can respond appropriately.

Notes
-----

Before changing any settings internally, it sometimes makes sense to disconnect the signal/slot.  Example: While saving the current state upon exit.

QSharedSettings creates another mechanism of inter-process communication.  But, keep in mind, access to QSettings is restricted based on the [QSettings Fallback Mechanism](qt-project.org/doc/qt-4.8/qsettings.html#fallback-mechanism)


Test Program
------------

Included with the library is a demonstration.

    cd libqsharedsettings-master/test
    qmake && make

To see the demonstration, launch the test program.

    ./test

When "test" is executed it adds some settings, changes a setting, and removes a couple settings.  The screen output occurs within Qt's main event loop.  To truely appreciate what QSharedSettings can do, launch (and leave executing) the test program from two different terminals.  Ctrl-C interrupts the program to exit.


To Do
-----

- Get away from the internal manual polling!
- Consider a mechanism to control which settings are shared, which are not.

The code functions well, but it could use some enhancements and bullet-proofing.


Uses
----

- [tvscontrol](https://code.google.com/p/tvscontrol/)
- [QSettingsWebEditor](https://github.com/czechtech/QSettingsWebEditor)
- [ProPresentTextDisplay]()

If you use this in a project, drop a line to have your project linked here.

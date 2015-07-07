#ifndef TST_CONTROLLERAIRCRAFTTEST
#define TST_CONTROLLERAIRCRAFTTEST

#include <QtTest>

class ControlledAircraftTest : public QObject
{
    Q_OBJECT

public:
    ControlledAircraftTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void readConfig1();
    void readConfig2();
    void runParameters1();
    void runParameters2();
    void runParameters3();
};

#endif // TST_CONTROLLERAIRCRAFTTEST


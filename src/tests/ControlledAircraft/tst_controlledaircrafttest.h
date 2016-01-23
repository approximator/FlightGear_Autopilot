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
};

#endif /* TST_CONTROLLERAIRCRAFTTEST */

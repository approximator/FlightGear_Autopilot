#ifndef TST_CONTROLLERAIRCRAFTTEST
#define TST_CONTROLLERAIRCRAFTTEST

#include <QtTest>

class MathTest : public QObject
{
    Q_OBJECT

public:
    MathTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void normalizeAngle_360();
    void normalizeAngle_180();
    void headingOffset1();
};

#endif // TST_CONTROLLERAIRCRAFTTEST


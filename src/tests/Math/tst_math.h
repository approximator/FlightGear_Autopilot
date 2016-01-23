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
    void distance_data();
    void distance();

    void degToMinSec_data();
    void degToMinSec();

    void headingTo_data();
    void headingTo();
};

#endif // TST_CONTROLLERAIRCRAFTTEST

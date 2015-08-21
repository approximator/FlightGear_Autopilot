
#include "../../FlightController/FgMath.h"
#include "tst_math.h"

MathTest::MathTest()
{
}

void MathTest::initTestCase()
{
}

void MathTest::cleanupTestCase()
{
}

void MathTest::normalizeAngle_360()
{
    using fgap::math::normalizeAngle_360;
    QCOMPARE(normalizeAngle_360(0), 0.0);
    QCOMPARE(normalizeAngle_360(10), 10.0);
    QCOMPARE(normalizeAngle_360(45), 45.0);
    QCOMPARE(normalizeAngle_360(90), 90.0);
    QCOMPARE(normalizeAngle_360(100), 100.0);
    QCOMPARE(normalizeAngle_360(180), 180.0);
    QCOMPARE(normalizeAngle_360(200), 200.0);
    QCOMPARE(normalizeAngle_360(270), 270.0);
    QCOMPARE(normalizeAngle_360(300), 300.0);
    QCOMPARE(normalizeAngle_360(359), 359.0);
    QCOMPARE(normalizeAngle_360(360), 0.0);
    QCOMPARE(normalizeAngle_360(72184.3), 184.3);
    QCOMPARE(normalizeAngle_360(-1), 359.0);
    QCOMPARE(normalizeAngle_360(-90), 270.0);
    QCOMPARE(normalizeAngle_360(-31050), 270.0);
    QCOMPARE(normalizeAngle_360(-584083), 197.0);
}

void MathTest::normalizeAngle_180()
{
    using fgap::math::normalizeAngle_180;
    QCOMPARE(normalizeAngle_180(0), 0.0);
    QCOMPARE(normalizeAngle_180(10), 10.0);
    QCOMPARE(normalizeAngle_180(45), 45.0);
    QCOMPARE(normalizeAngle_180(90), 90.0);
    QCOMPARE(normalizeAngle_180(100), 100.0);
    QCOMPARE(normalizeAngle_180(180), 180.0);
    QCOMPARE(normalizeAngle_180(200), -160.0);
    QCOMPARE(normalizeAngle_180(-181), 179.0);
}

void MathTest::headingOffset1()
{
    using fgap::math::headingOffset;
    QCOMPARE(headingOffset(359, 10), 11.0);
    QCOMPARE(headingOffset(359, 181), -178.0);
    QCOMPARE(headingOffset(359, 179), 180.0);
    QCOMPARE(headingOffset(1, 10), 9.0);
    QCOMPARE(headingOffset(90, 271), -179.0);
}

QTEST_APPLESS_MAIN(MathTest)


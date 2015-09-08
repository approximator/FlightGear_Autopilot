
#include "../../FlightController/utils/FgMath.h"
#include "tst_math.h"

#include <QString>

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

void MathTest::distance_data()
{
    QTest::addColumn<double>("lat1");
    QTest::addColumn<double>("lon1");
    QTest::addColumn<double>("lat2");
    QTest::addColumn<double>("lon2");
    QTest::addColumn<double>("result");

    QTest::newRow("1") << 89.0 << 100.0 << 90.0 << 101.0 << 111699.85;
    QTest::newRow("2") << 37.6328 << -122.3975 << 37.6228 << -122.3875 << 850.92;
}

void MathTest::distance()
{
    using fgap::math::getDistance;
    QFETCH(double, lat1);
    QFETCH(double, lon1);
    QFETCH(double, lat2);
    QFETCH(double, lon2);
    QFETCH(double, result);

    const double allowedError = 600;
    qDebug() << std::fabs(getDistance(lat1, lon1, lat2, lon2) - result);
    QVERIFY(std::fabs(getDistance(lat1, lon1, lat2, lon2) - result) < allowedError);
}

void MathTest::degToMinSec_data()
{
    QTest::addColumn<double>("degrees");
    QTest::addColumn<QString>("result");

    QTest::newRow("1") << 90.0 << "90°0'0\"";
    QTest::newRow("2") << 37.6328 << "37°37'58\"";
    QTest::newRow("3") << -122.3975 << "-122°23'50\"";
}

void MathTest::degToMinSec()
{
    using fgap::math::degToMinSecStr;
    QFETCH(double, degrees);
    QFETCH(QString, result);

    QCOMPARE(degToMinSecStr(degrees), result);
}

void MathTest::headingTo_data()
{
    QTest::addColumn<double>("lat1");
    QTest::addColumn<double>("lon1");
    QTest::addColumn<double>("lat2");
    QTest::addColumn<double>("lon2");
    QTest::addColumn<double>("result");

    QTest::newRow("1") << 89.0 << 100.0 << 90.0 << 101.0 << 0.0;
    QTest::newRow("2") << 37.6328 << -122.3975 << 37.6228 << -122.3875 << -141.49;
}

void MathTest::headingTo()
{
    using fgap::math::headingTo;
    QFETCH(double, lat1);
    QFETCH(double, lon1);
    QFETCH(double, lat2);
    QFETCH(double, lon2);
    QFETCH(double, result);

    const double allowedError = 0.2;
    QVERIFY(std::fabs(headingTo(lat1, lon1, lat2, lon2) - result) < allowedError); // Allow 0.2 degree error
}

QTEST_APPLESS_MAIN(MathTest)


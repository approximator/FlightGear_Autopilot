
#include "../../FlightController/FgControlledAircraft.h"

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
};

ControlledAircraftTest::ControlledAircraftTest()
{
}

void ControlledAircraftTest::initTestCase()
{
}

void ControlledAircraftTest::cleanupTestCase()
{
}

void ControlledAircraftTest::readConfig1()
{
    QString testJson = R"(
        {
            "callsign": "Travis",
            "flightgear": {
                "exe_file": "/usr/games/fgfs",
                "protocol_file": "/usr/share/games/flightgear/Protocol/FgaProtocol.xml",
                "root_directory": "/usr/share/games/flightgear",
                "airport": "KSFO",
                "runway": "10L",
                "aircraft": "c172p",
                "geometry": "800x600",
                "timeofday": "morning",
                "generic": {
                    "in": {
                        "port": 5556,
                        "frequency": 40,
                        "host": "localhost",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
                    },
                    "out": {
                        "port": 5555,
                        "frequency": 40,
                        "host": "localhost",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
                    }
                },
                "multiplay": {
                    "in": {
                        "port": 5001,
                        "frequency": 10,
                        "host": ""
                    },
                    "out": {
                        "port": 5000,
                        "frequency": 10,
                        "host": "mpserver02.flightgear.org"
                    }
                },
                "run_parameters": {
                    "bpp": "32",
                    "disable-random-objects": "",
                    "disable-ai-models": "",
                    "disable-ai-traffic": "",
                    "disable-real-weather-fetch": "",
                    "disable-terrasync": "",
                    "disable-clouds3d": "",
                    "disable-horizon-effect": "",
                    "disable-enhanced-lighting": "",
                    "httpd": "5050",
                    "prop:/engines/engine/running": "true",
                    "prop:/engines/engine/rpm": "2000",
                    "altitude": "2000"
                }
            }
        }
    )";
    FgControlledAircraft aircrft(QJsonDocument::fromJson(testJson.toLocal8Bit()).object());

    QCOMPARE(aircrft.callsign(), QString("Travis"));
    QCOMPARE(aircrft.flightgear().m_ExeFile, QString("/usr/games/fgfs"));
    QCOMPARE(aircrft.flightgear().m_RootDir, QString("/usr/share/games/flightgear"));
    QCOMPARE(aircrft.flightgear().m_Runway, QString("10L"));
    QCOMPARE(aircrft.flightgear().m_Aircraft, QString("c172p"));
    QCOMPARE(aircrft.flightgear().m_WindowSize, QString("800x600"));
    QCOMPARE(aircrft.flightgear().m_TimeOfDay, QString("morning"));
    QCOMPARE(aircrft.flightgear().m_ProtocolFile, QString("/usr/share/games/flightgear/Protocol/FgaProtocol.xml"));
    QCOMPARE(aircrft.flightgear().m_Airport, QString("KSFO"));
    QCOMPARE(aircrft.transport()->networkParams(),
             QString("--generic=socket,out,40,127.0.0.1,5555,udp,FgaProtocol --generic=socket,in,40,127.0.0.1,5556,udp,FgaProtocol"));
    QCOMPARE(aircrft.flightgear().multiplayParams(),
             QString("--multiplay=out,10,mpserver02.flightgear.org,5000 --multiplay=in,10,,5001"));

}

QTEST_APPLESS_MAIN(ControlledAircraftTest)

#include "tst_controlledaircrafttest.moc"

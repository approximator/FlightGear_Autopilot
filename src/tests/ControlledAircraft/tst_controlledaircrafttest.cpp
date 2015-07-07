
#include "../../FlightController/FgControlledAircraft.h"
#include "tst_controlledaircrafttest.h"

ControlledAircraftTest::ControlledAircraftTest()
{
}

void ControlledAircraftTest::initTestCase()
{
}

void ControlledAircraftTest::cleanupTestCase()
{
}

/*!
 * @brief ControlledAircraftTest::readConfig1
 *
 * Reading correct config with all the options set
 */
void ControlledAircraftTest::readConfig1()
{
    QString testJson = R"(
        {
            "flightgear": {
                "callsign": "Travis",
                "exe_file": "/some/path/to/fgfs",
                "protocol_file": "/some/path/to/flightgear/Protocol/FgaProtocol.xml",
                "root_directory": "/some/path/to/share/games/flightgear",
                "airport": "airport name",
                "runway": "runway number",
                "aircraft": "some aircraft",
                "geometry": "1024x600",
                "timeofday": "morning",
                "generic": {
                    "in": {
                        "port": 20000,
                        "frequency": 20,
                        "host": "localhost",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
                    },
                    "out": {
                        "port": 30000,
                        "frequency": 50,
                        "host": "192.168.0.1",
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
    QCOMPARE(aircrft.flightgear().m_ExeFile, QString("/some/path/to/fgfs"));
    QCOMPARE(aircrft.flightgear().m_RootDir, QString("/some/path/to/share/games/flightgear"));
    QCOMPARE(aircrft.flightgear().m_Runway, QString("runway number"));
    QCOMPARE(aircrft.flightgear().m_Aircraft, QString("some aircraft"));
    QCOMPARE(aircrft.flightgear().m_WindowSize, QString("1024x600"));
    QCOMPARE(aircrft.flightgear().m_TimeOfDay, QString("morning"));
    QCOMPARE(aircrft.flightgear().m_ProtocolFile, QString("/some/path/to/flightgear/Protocol/FgaProtocol.xml"));
    QCOMPARE(aircrft.flightgear().m_Airport, QString("airport name"));
    QCOMPARE(aircrft.transport()->networkParams(),
             QString("--generic=socket,out,50,192.168.0.1,30000,udp,FgaProtocol --generic=socket,in,20,127.0.0.1,20000,udp,FgaProtocol"));
    QCOMPARE(aircrft.flightgear().multiplayParams(),
             QString("--multiplay=out,10,mpserver02.flightgear.org,5000 --multiplay=in,10,,5001"));

}

/*!
 * @brief ControlledAircraftTest::readConfig2
 *
 * Reading config without "multiplay" option
 */
void ControlledAircraftTest::readConfig2()
{
    QString testJson = R"(
        {
            "flightgear": {
                "callsign": "Travis",
                "exe_file": "/some/path/to/fgfs",
                "protocol_file": "/some/path/to/flightgear/Protocol/FgaProtocol.xml",
                "root_directory": "/some/path/to/share/games/flightgear",
                "airport": "airport name",
                "runway": "runway number",
                "aircraft": "some aircraft",
                "geometry": "1024x600",
                "timeofday": "morning",
                "generic": {
                    "in": {
                        "port": 20000,
                        "frequency": 20,
                        "host": "localhost",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
                    },
                    "out": {
                        "port": 30000,
                        "frequency": 50,
                        "host": "192.168.0.1",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
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
    QCOMPARE(aircrft.flightgear().m_ExeFile, QString("/some/path/to/fgfs"));
    QCOMPARE(aircrft.flightgear().m_RootDir, QString("/some/path/to/share/games/flightgear"));
    QCOMPARE(aircrft.flightgear().m_Runway, QString("runway number"));
    QCOMPARE(aircrft.flightgear().m_Aircraft, QString("some aircraft"));
    QCOMPARE(aircrft.flightgear().m_WindowSize, QString("1024x600"));
    QCOMPARE(aircrft.flightgear().m_TimeOfDay, QString("morning"));
    QCOMPARE(aircrft.flightgear().m_ProtocolFile, QString("/some/path/to/flightgear/Protocol/FgaProtocol.xml"));
    QCOMPARE(aircrft.flightgear().m_Airport, QString("airport name"));
    QCOMPARE(aircrft.transport()->networkParams(),
             QString("--generic=socket,out,50,192.168.0.1,30000,udp,FgaProtocol --generic=socket,in,20,127.0.0.1,20000,udp,FgaProtocol"));
    QCOMPARE(aircrft.flightgear().multiplayParams(),
             QString(""));
}

/*!
 * @brief ControlledAircraftTest::runParameters1
 */
void ControlledAircraftTest::runParameters1()
{
    QString testJson = R"(
        {
            "flightgear": {
                "callsign": "Travis",
                "exe_file": "/some/path/to/fgfs",
                "protocol_file": "/some/path/to/flightgear/Protocol/FgaProtocol.xml",
                "root_directory": "/some/path/to/share/games/flightgear",
                "airport": "airport_name",
                "runway": "runway_number",
                "aircraft": "some_aircraft",
                "geometry": "1024x600",
                "timeofday": "morning",
                "generic": {
                    "in": {
                        "port": 20000,
                        "frequency": 20,
                        "host": "localhost",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
                    },
                    "out": {
                        "port": 30000,
                        "frequency": 50,
                        "host": "192.168.0.1",
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
    QCOMPARE(aircrft.flightgear().m_ExeFile, QString("/some/path/to/fgfs"));
    QCOMPARE(aircrft.flightgear().m_RootDir, QString("/some/path/to/share/games/flightgear"));
    QCOMPARE(aircrft.flightgear().m_Runway, QString("runway_number"));
    QCOMPARE(aircrft.flightgear().m_Aircraft, QString("some_aircraft"));
    QCOMPARE(aircrft.flightgear().m_WindowSize, QString("1024x600"));
    QCOMPARE(aircrft.flightgear().m_TimeOfDay, QString("morning"));
    QCOMPARE(aircrft.flightgear().m_ProtocolFile, QString("/some/path/to/flightgear/Protocol/FgaProtocol.xml"));
    QCOMPARE(aircrft.flightgear().m_Airport, QString("airport_name"));

    QStringList params = aircrft.flightgear().runParameters().split(' ');
    QStringList expectedParams;
    expectedParams << "--callsign=Travis"
                   << "--airport=airport_name"   << "--runway=runway_number"
                   << "--aircraft=some_aircraft" << "--geometry=1024x600"
                   << "--timeofday=morning"      << "--httpd=5050"
                   << "--altitude=2000"          << "--disable-terrasync"
                   << "--bpp=32"                 << "--disable-real-weather-fetch"
                   << "--disable-ai-models"      << "--disable-random-objects"
                   << "--disable-ai-traffic"     << "--disable-horizon-effect"
                   << "--disable-clouds3d"       << "--disable-enhanced-lighting"
                   << "--prop:/engines/engine/rpm=2000"
                   << "--prop:/engines/engine/running=true"
                   << "--generic=socket,out,50,192.168.0.1,30000,udp,FgaProtocol"
                   << "--generic=socket,in,20,127.0.0.1,20000,udp,FgaProtocol"
                   << "--multiplay=out,10,mpserver02.flightgear.org,5000"
                   << "--multiplay=in,10,,5001";
    params.sort();
    expectedParams.sort();
    QCOMPARE(params, expectedParams);
}

/*!
 * @brief ControlledAircraftTest::runParameters2
 *
 * config without "multiplay" option
 */
void ControlledAircraftTest::runParameters2()
{
    QString testJson = R"(
        {
            "flightgear": {
                "callsign": "Travis",
                "exe_file": "/some/path/to/fgfs",
                "protocol_file": "/some/path/to/flightgear/Protocol/FgaProtocol.xml",
                "root_directory": "/some/path/to/share/games/flightgear",
                "airport": "airport_name",
                "runway": "runway_number",
                "aircraft": "some_aircraft",
                "geometry": "1024x600",
                "timeofday": "morning",
                "generic": {
                    "in": {
                        "port": 20000,
                        "frequency": 20,
                        "host": "localhost",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
                    },
                    "out": {
                        "port": 30000,
                        "frequency": 50,
                        "host": "192.168.0.1",
                        "protocol": "udp",
                        "generic_protocol": "FgaProtocol"
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
    QCOMPARE(aircrft.flightgear().m_ExeFile, QString("/some/path/to/fgfs"));
    QCOMPARE(aircrft.flightgear().m_RootDir, QString("/some/path/to/share/games/flightgear"));
    QCOMPARE(aircrft.flightgear().m_Runway, QString("runway_number"));
    QCOMPARE(aircrft.flightgear().m_Aircraft, QString("some_aircraft"));
    QCOMPARE(aircrft.flightgear().m_WindowSize, QString("1024x600"));
    QCOMPARE(aircrft.flightgear().m_TimeOfDay, QString("morning"));
    QCOMPARE(aircrft.flightgear().m_ProtocolFile, QString("/some/path/to/flightgear/Protocol/FgaProtocol.xml"));
    QCOMPARE(aircrft.flightgear().m_Airport, QString("airport_name"));

    QStringList params = aircrft.flightgear().runParameters().split(' ');
    QStringList expectedParams;
    expectedParams << "--callsign=Travis"
                   << "--airport=airport_name"   << "--runway=runway_number"
                   << "--aircraft=some_aircraft" << "--geometry=1024x600"
                   << "--timeofday=morning"      << "--httpd=5050"
                   << "--altitude=2000"          << "--disable-terrasync"
                   << "--bpp=32"                 << "--disable-real-weather-fetch"
                   << "--disable-ai-models"      << "--disable-random-objects"
                   << "--disable-ai-traffic"     << "--disable-horizon-effect"
                   << "--disable-clouds3d"       << "--disable-enhanced-lighting"
                   << "--prop:/engines/engine/rpm=2000"
                   << "--prop:/engines/engine/running=true"
                   << "--generic=socket,out,50,192.168.0.1,30000,udp,FgaProtocol"
                   << "--generic=socket,in,20,127.0.0.1,20000,udp,FgaProtocol";
    params.sort();
    expectedParams.sort();
    QCOMPARE(params, expectedParams);
}

/*!
 * @brief ControlledAircraftTest::runParameters3
 *
 * config without "generic" option
 */
void ControlledAircraftTest::runParameters3()
{
    QString testJson = R"(
        {
            "flightgear": {
                "callsign": "Travis",
                "exe_file": "/some/path/to/fgfs",
                "protocol_file": "/some/path/to/flightgear/Protocol/FgaProtocol.xml",
                "root_directory": "/some/path/to/share/games/flightgear",
                "airport": "airport_name",
                "runway": "runway_number",
                "aircraft": "some_aircraft",
                "geometry": "1024x600",
                "timeofday": "morning",
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
    QCOMPARE(aircrft.flightgear().m_ExeFile, QString("/some/path/to/fgfs"));
    QCOMPARE(aircrft.flightgear().m_RootDir, QString("/some/path/to/share/games/flightgear"));
    QCOMPARE(aircrft.flightgear().m_Runway, QString("runway_number"));
    QCOMPARE(aircrft.flightgear().m_Aircraft, QString("some_aircraft"));
    QCOMPARE(aircrft.flightgear().m_WindowSize, QString("1024x600"));
    QCOMPARE(aircrft.flightgear().m_TimeOfDay, QString("morning"));
    QCOMPARE(aircrft.flightgear().m_ProtocolFile, QString("/some/path/to/flightgear/Protocol/FgaProtocol.xml"));
    QCOMPARE(aircrft.flightgear().m_Airport, QString("airport_name"));

    QStringList params = aircrft.flightgear().runParameters().split(' ');
    QStringList expectedParams;
    expectedParams << "--callsign=Travis"
                   << "--airport=airport_name"   << "--runway=runway_number"
                   << "--aircraft=some_aircraft" << "--geometry=1024x600"
                   << "--timeofday=morning"      << "--httpd=5050"
                   << "--altitude=2000"          << "--disable-terrasync"
                   << "--bpp=32"                 << "--disable-real-weather-fetch"
                   << "--disable-ai-models"      << "--disable-random-objects"
                   << "--disable-ai-traffic"     << "--disable-horizon-effect"
                   << "--disable-clouds3d"       << "--disable-enhanced-lighting"
                   << "--prop:/engines/engine/rpm=2000"
                   << "--prop:/engines/engine/running=true";
    params.sort();
    expectedParams.sort();
//    qDebug() << params;
//    qDebug() << expectedParams;
    QCOMPARE(params, expectedParams);
}

QTEST_APPLESS_MAIN(ControlledAircraftTest)


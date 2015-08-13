import qbs
import qbs.FileInfo

Project {
    minimumQbsVersion: "1.4"
    qbsSearchPaths: FileInfo.joinPaths(sourceDirectory, "../qbs")

    references: [
        "FlightController/FlightController.qbs"
    ]
}

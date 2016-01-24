/*!
 * @file Filesystem.h
 *
 * @brief Convenient function to manipulate with filesystem paths
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 05, 2015
 * @date Modified Sep 05, 2015
 */

#ifndef FILESYSTEM
#define FILESYSTEM

#include <QDir>

namespace fgap {

namespace path {

inline QString normPath(const QString& path)
{
    return QDir::toNativeSeparators(QDir::cleanPath(path));
}

inline QString join(const QString& path1, const QString& path2)
{
    return normPath(QString("%1/%2").arg(path1, path2));
}

inline QString join(const QString& path1, const QString& path2, const QString& path3)
{
    return normPath(QString("%1/%2/%3").arg(path1, path2, path3));
}

} // path

} // fgap

#endif // FILESYSTEM


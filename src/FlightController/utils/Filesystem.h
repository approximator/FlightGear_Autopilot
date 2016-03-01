/*!
 * @file Filesystem.h
 *
 * @brief Convenient function to manipulate with filesystem paths
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FILESYSTEM
#define FILESYSTEM

#include <QDir>

namespace fgap
{

namespace path
{

inline QString normPath(const QString &path) { return QDir::toNativeSeparators(QDir::cleanPath(path)); }

inline QString join(const QString &path1, const QString &path2) { return normPath(QString("%1/%2").arg(path1, path2)); }

inline QString join(const QString &path1, const QString &path2, const QString &path3)
{
    return normPath(QString("%1/%2/%3").arg(path1, path2, path3));
}

} /* path */

} /* fgap */

#endif /* FILESYSTEM */

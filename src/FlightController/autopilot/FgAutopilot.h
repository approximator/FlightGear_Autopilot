/*!
 * @file FgAutopilot.h
 *
 * @brief Basic autopilot class to inherit
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

#ifndef FGAUTOPILOT_H
#define FGAUTOPILOT_H

#include "QQmlVarPropertyHelpers.h"

#include <QObject>

class FgAutopilot : public QObject
{
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY(bool, engaged)
public:
    explicit FgAutopilot(QObject *parent = 0)
        : QObject(parent)
        , m_engaged(false)
    {
    }

    virtual ~FgAutopilot() {}

    FgAutopilot(const FgAutopilot &other);
    FgAutopilot &operator=(const FgAutopilot &other);

    virtual void computeControl() = 0;
};

Q_DECLARE_METATYPE(FgAutopilot *)

#endif /* FGAUTOPILOT_H */

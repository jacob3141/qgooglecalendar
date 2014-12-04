////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// This file is part of QGoogleCalendar.                                      //
// Copyright (c) 2014 Jacob Dawid <jacob@omg-it.works>                        //
//                                                                            //
// QGoogleCalendar is free software: you can redistribute it and/or modify    //
// it under the terms of the GNU Affero General Public License as             //
// published by the Free Software Foundation, either version 3 of the         //
// License, or (at your option) any later version.                            //
//                                                                            //
// QGoogleCalendar is distributed in the hope that it will be useful,         //
// but WITHOUT ANY WARRANTY; without even the implied warranty of             //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              //
// GNU Affero General Public License for more details.                        //
//                                                                            //
// You should have received a copy of the GNU Affero General Public           //
// License along with QGoogleCalendar.                                        //
// If not, see <http://www.gnu.org/licenses/>.                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#pragma once

// Qt includes
#include <QString>
#include <QJsonObject>

namespace APIV3 {

/**
 * Common resource interface.
 */
class Resource
{
public:
    Resource() { }
    virtual ~Resource() { }

    /** @returns Type of the resource. */
    virtual QString kind() const = 0;

    /** @returns ETag of the resource. */
    virtual QString eTag() const {
        return _eTag;
    }

    /** @returns Identifier of the resource. */
    virtual QString id() const {
        return _id;
    }

    /** @returns a json representation of this resource. */
    virtual QJsonObject toJsonObject() const = 0;

    /** Initializes this model from json. */
    virtual bool fromJson(QJsonObject jsonObject) = 0;

protected:
    QString     _eTag;
    QString     _id;
};

} // APIV3

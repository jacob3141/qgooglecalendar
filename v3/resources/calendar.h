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

// Own includes
#include "resource.h"

namespace APIV3 {

/**
 * Calendar resource as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/calendars
 */
class Calendar : public Resource
{
public:
    explicit Calendar();

    /** @returns Type of the resource ("calendar#calendar"). */
    QString kind() const;

    /** @returns ETag of the resource. */
    QString eTag() const;

    /** @returns Identifier of the calendar. */
    QString id() const;

    /** @returns a json representation of this calendar. */
    QJsonObject toJsonObject() const;

    /** Initializes this model from json. */
    void fromJson(QJsonObject jsonObject);

    /** @returns Title of the calendar. */
    QString summary() const;

    /** @returns Description of the calendar. Optional. */
    QString description() const;

    /**
     * @returns Geographic location of the calendar as free-form text.
     * Optional.
     */
    QString location() const;

    /** @returns The time zone of the calendar. Optional. */
    QString timeZone() const;

    /** Sets the title. */
    void setSummary(QString summary);

    /** Sets the description. */
    void setDescription(QString description);

    /** Sets the location. */
    void setLocation(QString location);
    /** Sets the timezone. */
    void setTimeZone(QString timeZone);

private:
    QString _eTag;
    QString _id;
    QString _summary;
    QString _description;
    QString _location;
    QString _timeZone;
};

} // APIV3

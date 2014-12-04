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

// Own includes
#include "calendar.h"

namespace APIV3 {

Calendar::Calendar() :
    Resource()
{
}

QString Calendar::kind() const
{
    return "calendar#calendar";
}

QString Calendar::eTag() const
{
    return _eTag;
}

QString Calendar::id() const
{
    return _id;
}

QJsonObject Calendar::toJsonObject() const
{
    QJsonObject calendar;
    calendar.insert("kind", kind());
    calendar.insert("etag", eTag());
    calendar.insert("id", id());
    calendar.insert("summary", summary());
    calendar.insert("description", description());
    calendar.insert("location", location());
    calendar.insert("timeZone", timeZone());
    return calendar;
}

bool Calendar::fromJson(QJsonObject jsonObject)
{
    if(jsonObject.value("kind").toString() != kind()) {
        return false;
    }

    _eTag = jsonObject.value("etag").toString();
    _id = jsonObject.value("id").toString();
    _summary = jsonObject.value("summary").toString();
    _description = jsonObject.value("description").toString();
    _location = jsonObject.value("location").toString();
    _timeZone = jsonObject.value("timeZone").toString();
    return true;
}

QString Calendar::summary() const
{
    return _summary;
}

QString Calendar::description() const
{
    return _description;
}

QString Calendar::location() const
{
    return _location;
}

QString Calendar::timeZone() const
{
    return _timeZone;
}

void Calendar::setSummary(QString summary)
{
    _summary = summary;
}

void Calendar::setDescription(QString description)
{
    _description = description;
}

void Calendar::setLocation(QString location)
{
    _location = location;
}

void Calendar::setTimeZone(QString timeZone)
{
    _timeZone = timeZone;
}

} // APIV3

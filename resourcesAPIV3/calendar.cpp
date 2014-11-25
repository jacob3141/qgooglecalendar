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

Calendar::Calendar()
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

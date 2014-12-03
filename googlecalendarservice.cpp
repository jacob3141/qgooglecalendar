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

#include "googlecalendarservice.h"

namespace APIV3 {

GoogleCalendarService::GoogleCalendarService(QObject *parent) :
    QObject(parent)
{
    _acl            = new Acl(this);
    _calendarList   = new CalendarList(this);
    _calendars      = new Calendars(this);
    _channels       = new Channels(this);
    _colors         = new Colors(this);
    _events         = new Events(this);
    _freebusy       = new Freebusy(this);
    _settings       = new Settings(this);
}

Acl *GoogleCalendarService::acl()
{
    return _acl;
}

CalendarList *GoogleCalendarService::calendarList()
{
    return _calendarList;
}

Calendars *GoogleCalendarService::calendars()
{
    return _calendars;
}

Channels *GoogleCalendarService::channels()
{
    return _channels;
}

Colors *GoogleCalendarService::colors()
{
    return _colors;
}

Events *GoogleCalendarService::events()
{
    return _events;
}

Freebusy *GoogleCalendarService::freebusy()
{
    return _freebusy;
}

Settings *GoogleCalendarService::settings()
{
    return _settings;
}

} // APIV3

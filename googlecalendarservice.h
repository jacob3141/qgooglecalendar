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
#include "v3/services/acl.h"
#include "v3/services/calendarlist.h"
#include "v3/services/calendars.h"
#include "v3/services/channels.h"
#include "v3/services/colors.h"
#include "v3/services/events.h"
#include "v3/services/freebusy.h"
#include "v3/services/settings.h"

#include <QObject>

namespace APIV3 {

class GoogleCalendarService : public QObject
{
    Q_OBJECT
public:
    explicit GoogleCalendarService(QObject *parent = 0);

    Acl             *acl();
    CalendarList    *calendarList();
    Calendars       *calendars();
    Channels        *channels();
    Colors          *colors();
    Events          *events();
    Freebusy        *freebusy();
    Settings        *settings();

signals:

public slots:

private:
    Acl             *_acl;
    CalendarList    *_calendarList;
    Calendars       *_calendars;
    Channels        *_channels;
    Colors          *_colors;
    Events          *_events;
    Freebusy        *_freebusy;
    Settings        *_settings;
};

} // APIV3


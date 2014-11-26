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
#include "calendarlistentry.h"

CalendarListEntry::CalendarListEntry() :
    Resource()
{
}

QString CalendarListEntry::kind()
{
    return "calendar#calendarListEntry";
}

CalendarListEntry::AccessRole CalendarListEntry::accessRole() const
{
    return _accessRole;
}

bool CalendarListEntry::deleted() const
{
    return _deleted;
}

QString CalendarListEntry::description() const
{
    return _description;
}

QString CalendarListEntry::location() const
{
    return _location;
}

bool CalendarListEntry::primary() const
{
    return _primary;
}

QString CalendarListEntry::summary() const
{
    return _summary;
}

QString CalendarListEntry::timeZone() const
{
    return _timeZone;
}

QString CalendarListEntry::eTag() const
{
    return _eTag;
}

QString CalendarListEntry::id() const
{
    return _id;
}

QString CalendarListEntry::summaryOverride() const
{
    return _summaryOverride;
}

QString CalendarListEntry::colorId() const
{
    return _colorId;
}

QString CalendarListEntry::backgroundColor() const
{
    return _backgroundColor;
}

QString CalendarListEntry::foregroundColor() const
{
    return _foregroundColor;
}

bool CalendarListEntry::hidden() const
{
    return _hidden;
}

bool CalendarListEntry::selected() const
{
    return _selected;
}

QList<CalendarListEntry::DefaultReminder> CalendarListEntry::defaultReminders() const
{
    return _defaultReminders;
}

QList<CalendarListEntry::Notification> CalendarListEntry::notifications() const
{
    return _notifications;
}

void CalendarListEntry::setSummaryOverride(QString summaryOverride)
{
    _summaryOverride = summaryOverride;
}

void CalendarListEntry::setColorId(QString colorId)
{
    _colorId = colorId;
}

void CalendarListEntry::setBackgroundColor(QString backgroundColor)
{
    _backgroundColor = backgroundColor;
}

void CalendarListEntry::setForegroundColor(QString foregroundColor)
{
    _foregroundColor = foregroundColor;
}

void CalendarListEntry::setHidden(bool hidden)
{
    _hidden = hidden;
}

void CalendarListEntry::setSelected(bool selected)
{
    _selected = selected;
}

void CalendarListEntry::setDefaultReminders(QList<CalendarListEntry::DefaultReminder> defaultReminders)
{
    _defaultReminders = defaultReminders;
}

void CalendarListEntry::setNotifications(QList<CalendarListEntry::Notification> notifications)
{
    _notifications = notifications;
}

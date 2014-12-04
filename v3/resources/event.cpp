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
#include "event.h"

//{
//  "kind": "calendar#event",
//  "etag": etag,
//  "id": string,
//  "status": string,
//  "htmlLink": string,
//  "created": datetime,
//  "updated": datetime,
//  "summary": string,
//  "description": string,
//  "location": string,
//  "colorId": string,
//  "creator": {
//    "id": string,
//    "email": string,
//    "displayName": string,
//    "self": boolean
//  },
//  "organizer": {
//    "id": string,
//    "email": string,
//    "displayName": string,
//    "self": boolean
//  },
//  "start": {
//    "date": date,
//    "dateTime": datetime,
//    "timeZone": string
//  },
//  "end": {
//    "date": date,
//    "dateTime": datetime,
//    "timeZone": string
//  },
//  "endTimeUnspecified": boolean,
//  "recurrence": [
//    string
//  ],
//  "recurringEventId": string,
//  "originalStartTime": {
//    "date": date,
//    "dateTime": datetime,
//    "timeZone": string
//  },
//  "transparency": string,
//  "visibility": string,
//  "iCalUID": string,
//  "sequence": integer,
//  "attendees": [
//    {
//      "id": string,
//      "email": string,
//      "displayName": string,
//      "organizer": boolean,
//      "self": boolean,
//      "resource": boolean,
//      "optional": boolean,
//      "responseStatus": string,
//      "comment": string,
//      "additionalGuests": integer
//    }
//  ],
//  "attendeesOmitted": boolean,
//  "extendedProperties": {
//    "private": {
//      (key): string
//    },
//    "shared": {
//      (key): string
//    }
//  },
//  "hangoutLink": string,
//  "gadget": {
//    "type": string,
//    "title": string,
//    "link": string,
//    "iconLink": string,
//    "width": integer,
//    "height": integer,
//    "display": string,
//    "preferences": {
//      (key): string
//    }
//  },
//  "anyoneCanAddSelf": boolean,
//  "guestsCanInviteOthers": boolean,
//  "guestsCanModify": boolean,
//  "guestsCanSeeOtherGuests": boolean,
//  "privateCopy": boolean,
//  "locked": boolean,
//  "reminders": {
//    "useDefault": boolean,
//    "overrides": [
//      {
//        "method": string,
//        "minutes": integer
//      }
//    ]
//  },
//  "source": {
//    "url": string,
//    "title": string
//  }
//}
namespace APIV3 {

Event::Event() :
    Resource()
{
}

QString Event::kind() const
{
    return "calendar#event";
}

QJsonObject Event::toJsonObject() const
{
    QJsonObject event;

    return event;
}

bool Event::fromJson(QJsonObject jsonObject)
{
    if(jsonObject.value("kind").toString() != kind()) {
        return false;
    }

    return true;
}

QString Event::status()
{
    return _status;
}

QString Event::htmlLink()
{
    return _htmlLink;
}

QDateTime Event::created()
{
    return _created;
}

QDateTime Event::updated()
{
    return _updated;
}

QString Event::summary()
{
    return _summary;
}

QString Event::description()
{
    return _description;
}

QString Event::location()
{
    return _location;
}

QString Event::colorId()
{
    return _colorId;
}

Event::Actor Event::creator()
{
    return _creator;
}

Event::Actor Event::organizer()
{
    return _organizer;
}

Event::PointInTime Event::start()
{
    return _start;
}

Event::PointInTime Event::end()
{
    return _end;
}

bool Event::endTimeUnspecified()
{
    return _endTimeUnspecified;
}

QList<QString> Event::recurrence()
{
    return _recurrence;
}

QString Event::recurringEventId()
{
    return _recurringEventId;
}

Event::PointInTime Event::originalStartTime()
{
    return _originalStartTime;
}

Event::Transparency Event::transparency()
{
    return _transparency;
}

Event::Visibility Event::visibility()
{
    return _visibility;
}

QString Event::iCalUID()
{
    return _iCalUID;
}

int Event::sequence()
{
    return _sequence;
}

QList<Event::Attendee> Event::attendees()
{
    return _attendees;
}

bool Event::attendeesOmitted()
{
    return _attendeesOmitted;
}

Event::ExtendedProperties Event::extendedProperties()
{
    return _extendedProperties;
}

QString Event::hangoutLink()
{
    return _hangoutLink;
}

Event::Gadget Event::gadget()
{
    return _gadget;
}

bool Event::anyoneCanAddSelf()
{
    return _anyoneCanAddSelf;
}

bool Event::guestsCanInviteOthers()
{
    return _guestsCanInviteOthers;
}

bool Event::guestsCanModify()
{
    return _guestsCanModify;
}

bool Event::guestsCanSeeOtherGuests()
{
    return _guestsCanSeeOtherGuests;
}

bool Event::privateCopy()
{
    return _privateCopy;
}

bool Event::locked()
{
    return _locked;
}

Event::Reminders Event::reminders()
{
    return _reminders;
}

Event::Source Event::source()
{
    return _source;
}

void Event::setStatus(EventStatus status)
{
    _status = status;
}

void Event::setSummary(QString summary)
{
    _summary = summary;
}

void Event::setDescription(QString description)
{
    _description = description;
}

void Event::setLocation(QString location)
{
    _location = location;
}

void Event::setColorId(QString colorId)
{
    _colorId = colorId;
}

void Event::setOrganizer(Actor organizer)
{
    _organizer = organizer;
}

void Event::setStart(PointInTime start)
{
    _start = start;
}

void Event::setEnd(PointInTime end)
{
    _end = end;
}

void Event::setEndTimeUnspecified(bool endTimeUnspecified)
{
    _endTimeUnspecified = endTimeUnspecified;
}

void Event::setRecurrence(QList<QString> recurrence)
{
    _recurrence = recurrence;
}

void Event::setTransparency(Transparency transparency)
{
    _transparency = transparency;
}

void Event::setVisibility(Visibility visibility)
{
    _visibility = visibility;
}

void Event::setICalUID(QString iCalUID)
{
    _iCalUID = iCalUID;
}

void Event::setSequence(int sequence)
{
    _sequence = sequence;
}

void Event::setAttendees(QList<Attendee> attendees)
{
    _attendees = attendees;
}

void Event::setAttendeesOmitted(bool attendeesOmitted)
{
    _attendeesOmitted = attendeesOmitted;
}

void Event::setExtendedProperties(ExtendedProperties extendedProperties)
{
    _extendedProperties = extendedProperties;
}

void Event::setGadget(Gadget gadget)
{
    _gadget = gadget;
}

void Event::setAnyoneCanAddSelf(bool anyoneCanAddSelf)
{
    _anyoneCanAddSelf = anyoneCanAddSelf;
}

void Event::setGuestsCanInviteOthers(bool guestsCanInviteOthers)
{
    _guestsCanInviteOthers = guestsCanInviteOthers;
}

void Event::setGuestsCanModify(bool guestsCanModify)
{
    _guestsCanModify = guestsCanModify;
}

void Event::setGuestsCanSeeOtherGuests(bool guestsCanSeeOtherGuests)
{
    _guestsCanSeeOtherGuests = guestsCanSeeOtherGuests;
}

void Event::setReminders(Reminders reminders)
{
    _reminders = reminders;
}

void Event::setSource(Source source)
{
    _source = source;
}

} // APIV3

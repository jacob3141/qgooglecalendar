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

// Qt includes
#include <QJsonArray>

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
    QJsonObject eventObject;
    eventObject.insert("kind", kind());
    eventObject.insert("etag", eTag());
    eventObject.insert("id", id());

    switch(status()) {
    case EventStatusNil:
        break;
    case EventStatusConfirmed:
        eventObject.insert("status", "confirmed");
        break;
    case EventStatusTentative:
        eventObject.insert("status", "tentative");
        break;
    case EventStatusCancelled:
        eventObject.insert("status", "cancelled");
        break;
    }

    eventObject.insert("htmlLink", htmlLink());
    eventObject.insert("created", created().toString());
    eventObject.insert("updated", updated().toString());
    eventObject.insert("summary", summary());
    eventObject.insert("description", description());
    eventObject.insert("location", location());
    eventObject.insert("colorId", colorId());

    QJsonObject creatorObject;
    creatorObject.insert("id", creator().id);
    creatorObject.insert("email", creator().email);
    creatorObject.insert("displayName", creator().displayName);
    creatorObject.insert("self", creator().self);
    eventObject.insert("creator", creatorObject);

    QJsonObject organizerObject;
    organizerObject.insert("id", organizer().id);
    organizerObject.insert("email", organizer().email);
    organizerObject.insert("displayName", organizer().displayName);
    organizerObject.insert("self", organizer().self);
    eventObject.insert("organizer", organizerObject);

    QJsonObject startObject;
    startObject.insert("date", start().date.toString());
    startObject.insert("dateTime", start().dateTime.toString());
    startObject.insert("timeZone", start().timeZone.toString());
    eventObject.insert("start", startObject);

    QJsonObject endObject;
    endObject.insert("date", end().date.toString());
    endObject.insert("dateTime", end().dateTime.toString());
    endObject.insert("timeZone", end().timeZone.toString());
    eventObject.insert("end", endObject);

    eventObject.insert("endTimeUnspecified", endTimeUnspecified());

    QJsonArray recurrenceArray;
    foreach (QString recurrenceItem, _recurrence) {
        recurrenceArray.append(recurrenceItem);
    }
    eventObject.insert("recurrence", recurrenceArray);

    eventObject.insert("recurringEventId", recurringEventId());

    QJsonObject originalStartTimeObject;
    originalStartTimeObject.insert("date", originalStartTime().date.toString());
    originalStartTimeObject.insert("dateTime", originalStartTime().dateTime.toString());
    originalStartTimeObject.insert("timeZone", originalStartTime().timeZone.toString());
    eventObject.insert("originalStartTime", originalStartTimeObject);

    switch (transparency()) {
    case TransparencyNil:
        break;
    case TransparencyOpaque:
        eventObject.insert("transparency", "opaque");
        break;
    case TransparencyTransparent:
        eventObject.insert("transparency", "transparent");
        break;
    }

    switch (visibility()) {
    case VisibilityNil:
        break;
    case VisibilityDefault:
        eventObject.insert("visibility", "default");
        break;
    case VisibilityPublic:
        eventObject.insert("visibility", "public");
        break;
    case VisibilityPrivate:
        eventObject.insert("visibility", "private");
        break;
    case VisibilityConfidential:
        eventObject.insert("visibility", "confidential");
        break;
    }

    eventObject.insert("iCalUID", iCalUID());
    eventObject.insert("sequence", sequence());

    QJsonArray attendeesArray;
    foreach (Attendee attendee, _attendees) {
        QJsonObject attendeeObject;
        attendeeObject.insert("id", attendee.id);
        attendeeObject.insert("email", attendee.email);
        attendeeObject.insert("displayName", attendee.displayName);
        attendeeObject.insert("organizer", attendee.organizer);
        attendeeObject.insert("self", attendee.self);
        attendeeObject.insert("resource", attendee.resource);
        attendeeObject.insert("optional", attendee.optional);

        switch(attendee.responseStatus) {
        case ResponseStatusNil:
            break;
        case ResponseStatusNeedsAction:
            attendeeObject.insert("responseStatus", "needsAction");
            break;
        case ResponseStatusDeclined:
            attendeeObject.insert("responseStatus", "declined");
            break;
        case ResponseStatusTentative:
            attendeeObject.insert("responseStatus", "tentative");
            break;
        case ResponseStatusAccepted:
            attendeeObject.insert("responseStatus", "accepted");
            break;
        }

        attendeeObject.insert("comment", attendee.comment);
        attendeeObject.insert("additionalGuests", attendee.additionalGuests);
        attendeesArray.append(attendeeObject);
    }
    eventObject.insert("attendees", attendeesArray);
    eventObject.insert("attendeesOmitted", attendeesOmitted());

    QJsonObject extendedPropertiesObject;
    QJsonObject privateObject;
    QList<QString> privateKeys = _extendedProperties.privateProperties.keys();
    foreach (QString key, privateKeys) {
        privateObject.insert(key, _extendedProperties.privateProperties.value(key));
    }
    extendedPropertiesObject.insert("private", privateObject);
    QJsonObject sharedObject;
    QList<QString> sharedKeys = _extendedProperties.sharedProperties.keys();
    foreach (QString key, sharedKeys) {
        sharedObject.insert(key, _extendedProperties.sharedProperties.value(key));
    }
    extendedPropertiesObject.insert("shared", sharedObject);
    eventObject.insert("extendedProperties", extendedPropertiesObject);

    eventObject.insert("hangoutLink", hangoutLink());

    QJsonObject gadgetObject;
    gadgetObject.insert("type", gadget().type);
    gadgetObject.insert("title", gadget().title);
    gadgetObject.insert("link", gadget().link);
    gadgetObject.insert("iconLink", gadget().iconLink);
    gadgetObject.insert("width", gadget().width);
    gadgetObject.insert("height", gadget().height);
    gadgetObject.insert("display", gadget().display);

    QJsonObject preferencesObject;
    QList<QString> preferencesKeys = gadget().preferences.keys();
    foreach(QString key, preferencesKeys) {
        preferencesObject.insert(key, gadget().preferences.value(key));
    }
    gadgetObject.insert("preferences", preferencesObject);
    eventObject.insert("gadget", gadgetObject);

    eventObject.insert("anyoneCanAddSelf", anyoneCanAddSelf());
    eventObject.insert("guestsCanInviteOthers", guestsCanInviteOthers());
    eventObject.insert("guestsCanModify", guestsCanModify());
    eventObject.insert("guestsCanSeeOtherGuests", guestsCanSeeOtherGuests());
    eventObject.insert("privateCopy", privateCopy());
    eventObject.insert("locked", locked());

    QJsonObject remindersObject;
    remindersObject.insert("useDefault", reminders().useDefault);
    QJsonArray overridesArray;
    foreach (Reminders::Override override, _reminders.overrides) {
        QJsonObject overrideObject;
        switch (override.method) {
        case Reminders::MethodNil:
            break;
        case Reminders::MethodEmail:
            overrideObject.insert("method", "email");
            break;
        case Reminders::MethodSms:
            overrideObject.insert("method", "sms");
            break;
        case Reminders::MethodPopup:
            overrideObject.insert("method", "popup");
            break;
        }
        overrideObject.insert("minutes", override.minutes);
        overridesArray.append(overrideObject);
    }
    remindersObject.insert("overrides", overridesArray);
    eventObject.insert("reminders", remindersObject);

    QJsonObject sourceObject;
    sourceObject.insert("url", source().url);
    sourceObject.insert("title", source().title);
    eventObject.insert("source", sourceObject);

    return eventObject;
}

bool Event::fromJson(QJsonObject jsonObject)
{
    if(jsonObject.value("kind").toString() != kind()) {
        return false;
    }

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

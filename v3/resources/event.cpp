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
#include <QStringList>

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
    eventObject.insert("created", created().toString(Qt::ISODate));
    eventObject.insert("updated", updated().toString(Qt::ISODate));
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
    organizerObject.insert("id", _organizer.id);
    organizerObject.insert("email", _organizer.email);
    organizerObject.insert("displayName", _organizer.displayName);
    organizerObject.insert("self", _organizer.self);
    eventObject.insert("organizer", organizerObject);

    QJsonObject startObject;
    startObject.insert("date", _start.date.toString(Qt::ISODate));
    startObject.insert("dateTime", _start.dateTime.toString(Qt::ISODate));
    startObject.insert("timeZone", _start.timeZone);
    eventObject.insert("start", startObject);

    QJsonObject endObject;
    endObject.insert("date", _end.date.toString(Qt::ISODate));
    endObject.insert("dateTime", _end.dateTime.toString(Qt::ISODate));
    endObject.insert("timeZone", _end.timeZone);
    eventObject.insert("end", endObject);

    eventObject.insert("endTimeUnspecified", endTimeUnspecified());

    QJsonArray recurrenceArray;
    foreach (QString recurrenceItem, _recurrence) {
        recurrenceArray.append(recurrenceItem);
    }
    eventObject.insert("recurrence", recurrenceArray);

    eventObject.insert("recurringEventId", recurringEventId());

    QJsonObject originalStartTimeObject;
    originalStartTimeObject.insert("date", _originalStartTime.date.toString(Qt::ISODate));
    originalStartTimeObject.insert("dateTime", _originalStartTime.dateTime.toString(Qt::ISODate));
    originalStartTimeObject.insert("timeZone", _originalStartTime.timeZone);
    eventObject.insert("originalStartTime", originalStartTimeObject);

    switch (_transparency) {
    case TransparencyNil:
        break;
    case TransparencyOpaque:
        eventObject.insert("transparency", "opaque");
        break;
    case TransparencyTransparent:
        eventObject.insert("transparency", "transparent");
        break;
    }

    switch (_visibility) {
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

    eventObject.insert("iCalUID", _iCalUID);
    eventObject.insert("sequence", _sequence);

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
    eventObject.insert("attendeesOmitted", _attendeesOmitted);

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
    gadgetObject.insert("type", _gadget.type);
    gadgetObject.insert("title", _gadget.title);
    gadgetObject.insert("link", _gadget.link);
    gadgetObject.insert("iconLink", _gadget.iconLink);
    gadgetObject.insert("width", _gadget.width);
    gadgetObject.insert("height", _gadget.height);
    gadgetObject.insert("display", _gadget.display);

    QJsonObject preferencesObject;
    QList<QString> preferencesKeys = _gadget.preferences.keys();
    foreach(QString key, preferencesKeys) {
        preferencesObject.insert(key, _gadget.preferences.value(key));
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
    remindersObject.insert("useDefault", _reminders.useDefault);
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
    sourceObject.insert("url", _source.url);
    sourceObject.insert("title", _source.title);
    eventObject.insert("source", sourceObject);

    return eventObject;
}

bool Event::fromJson(QJsonObject jsonObject)
{
    if(jsonObject.value("kind").toString() != kind()) {
        return false;
    }

    _eTag = jsonObject.value("etag").toString();
    _id = jsonObject.value("id").toString();

    QString status = jsonObject.value("status").toString();
    if(status == "confirmed") {
        _status = EventStatusConfirmed;
    } else
    if(status == "tentative") {
        _status = EventStatusTentative;
    } else
    if(status == "cancelled") {
        _status = EventStatusCancelled;
    } else {
        _status = EventStatusNil;
    }

    _htmlLink = jsonObject.value("htmlLink").toString();
    _created = QDateTime::fromString(jsonObject.value("created").toString(), Qt::ISODate);
    _updated = QDateTime::fromString(jsonObject.value("updated").toString(), Qt::ISODate);
    _summary = jsonObject.value("summary").toString();
    _description = jsonObject.value("description").toString();
    _location = jsonObject.value("location").toString();
    _colorId = jsonObject.value("colorId").toString();

    QJsonObject creatorObject = jsonObject.value("creator").toObject();
    _creator.id = creatorObject.value("id").toString();
    _creator.email = creatorObject.value("email").toString();
    _creator.displayName = creatorObject.value("displayName").toString();
    _creator.self = creatorObject.value("self").toBool();

    QJsonObject organizerObject = jsonObject.value("organizer").toObject();
    _organizer.id = organizerObject.value("id").toString();
    _organizer.email = organizerObject.value("email").toString();
    _organizer.displayName = organizerObject.value("displayName").toString();
    _organizer.self = organizerObject.value("self").toBool();

    QJsonObject startObject = jsonObject.value("start").toObject();
    _start.date = QDate::fromString(startObject.value("date").toString(), Qt::ISODate);
    _start.dateTime = QDateTime::fromString(startObject.value("dateTime").toString(), Qt::ISODate);
    _start.timeZone = startObject.value("timeZone").toString();

    QJsonObject endObject = jsonObject.value("end").toObject();
    _end.date = QDate::fromString(endObject.value("date").toString(), Qt::ISODate);
    _end.dateTime = QDateTime::fromString(endObject.value("dateTime").toString(), Qt::ISODate);
    _end.timeZone = endObject.value("timeZone").toString();

    _endTimeUnspecified = jsonObject.value("endTimeUnspecified").toBool();

    QJsonArray recurrenceArray = jsonObject.value("recurrence").toArray();
    _recurrence.clear();
    while(recurrenceArray.count()) {
        _recurrence.append(recurrenceArray.at(0).toString());
        _recurrence.removeFirst();
    }

    _recurringEventId = jsonObject.value("recurringEventId").toString();

    QJsonObject originalStartTimeObject = jsonObject
            .value("originalStartTime").toObject();
    _originalStartTime.date = QDate::fromString(
                originalStartTimeObject.value("date").toString(),
                Qt::ISODate);
    _originalStartTime.dateTime = QDateTime::fromString(
                originalStartTimeObject.value("dateTime").toString(),
                Qt::ISODate);
    _originalStartTime.timeZone = originalStartTimeObject
            .value("timeZone").toString();

    QString transparency = jsonObject.value("transparency").toString();
    if(transparency == "opaque") {
        _transparency = TransparencyOpaque;
    } else
    if(transparency == "transparent") {
        _transparency = TransparencyTransparent;
    } else {
        _transparency = TransparencyNil;
    }

    QString visibility = jsonObject.value("visibility").toString();
    if(visibility == "default") {
        _visibility = VisibilityDefault;
    } else
    if(visibility == "public") {
        _visibility = VisibilityPublic;
    } else
    if(visibility == "private") {
        _visibility = VisibilityPrivate;
    } else
    if(visibility == "confidential") {
        _visibility = VisibilityConfidential;
    } else {
        _visibility = VisibilityNil;
    }

    _iCalUID = jsonObject.value("iCalUID").toString();
    _sequence = jsonObject.value("sequence").toInt();

    QJsonArray attendeesArray = jsonObject.value("attendees").toArray();
    _attendees.clear();
    while(attendeesArray.count()) {
        QJsonObject attendeeObject = attendeesArray.at(0).toObject();
        attendeesArray.removeFirst();

        Attendee attendee;
        attendee.id = attendeeObject.value("id").toString();
        attendee.email = attendeeObject.value("email").toString();
        attendee.displayName = attendeeObject.value("displayName").toString();
        attendee.organizer = attendeeObject.value("organizer").toBool();
        attendee.self = attendeeObject.value("self").toBool();
        attendee.resource = attendeeObject.value("resource").toBool();
        attendee.optional = attendeeObject.value("optional").toBool();

        QString responseStatus = attendeeObject.value("responseStatus").toString();
        if(responseStatus == "needsAction") {
            attendee.responseStatus = ResponseStatusNeedsAction;
        } else
        if(responseStatus == "declined") {
            attendee.responseStatus = ResponseStatusDeclined;
        } else
        if(responseStatus == "tentative") {
            attendee.responseStatus = ResponseStatusTentative;
        } else
        if(responseStatus == "accepted") {
            attendee.responseStatus = ResponseStatusAccepted;
        } else {
            attendee.responseStatus = ResponseStatusNil;
        }

        attendee.comment = attendeeObject.value("comment").toString();
        attendee.additionalGuests = attendeeObject.value("additionalGuests").toInt();
        _attendees.append(attendee);
    }

    _attendeesOmitted = jsonObject.value("attendeesOmitted").toBool();

    QJsonObject extendedPropertiesObject = jsonObject
            .value("extendedProperties").toObject();

    QJsonObject privateObject = extendedPropertiesObject.value("private").toObject();
    _extendedProperties.privateProperties.clear();
    QStringList privateKeys = privateObject.keys();
    foreach(QString key, privateKeys) {
        _extendedProperties.privateProperties.insert(key, privateObject.value(key).toString());
    }

    QJsonObject sharedObject = extendedPropertiesObject.value("shared").toObject();
    _extendedProperties.sharedProperties.clear();
    QStringList sharedKeys = sharedObject.keys();
    foreach(QString key, sharedKeys) {
        _extendedProperties.sharedProperties.insert(key, sharedObject.value(key).toString());
    }

    _hangoutLink = jsonObject.value("hangoutLink").toString();

    QJsonObject gadgetObject = jsonObject.value("gadget").toObject();

    _gadget.type = gadgetObject.value("type").toString();
    _gadget.title = gadgetObject.value("title").toString();
    _gadget.link = gadgetObject.value("link").toString();
    _gadget.iconLink = gadgetObject.value("iconLink").toString();
    _gadget.width = gadgetObject.value("width").toInt();
    _gadget.height = gadgetObject.value("height").toInt();

    QString display = gadgetObject.value("display").toString();
    if(display == "icon") {
        _gadget.display = GadgetDisplayModeIcon;
    } else
    if(display == "chip") {
        _gadget.display = GadgetDisplayModeChip;
    } else {
        _gadget.display = GadgetDisplayModeNil;
    }

    QJsonObject preferencesObject = gadgetObject.value("preferences").toObject();
    QStringList preferencesKeys = preferencesObject.keys();
    _gadget.preferences.clear();
    foreach (QString key, preferencesKeys) {
        _gadget.preferences.insert(key, preferencesObject.value(key).toString());
    }

    _anyoneCanAddSelf = jsonObject.value("anyoneCanAddSelf").toBool();
    _guestsCanInviteOthers = jsonObject.value("guestsCanInviteOthers").toBool();
    _guestsCanModify = jsonObject.value("guestsCanModify").toBool();
    _guestsCanSeeOtherGuests = jsonObject.value("guestsCanSeeOtherGuests").toBool();
    _privateCopy = jsonObject.value("privateCopy").toBool();
    _locked = jsonObject.value("locked").toBool();

    QJsonObject remindersObject = jsonObject.value("reminders").toObject();
    _reminders.useDefault = remindersObject.value("useDefault").toBool();
    QJsonArray overridesArray = remindersObject.value("overrides").toArray();
    _reminders.overrides.clear();
    while(overridesArray.count()) {
        QJsonObject overrideObject = overridesArray.at(0).toObject();
        overridesArray.removeFirst();

        Reminders::Override override;
        QString method = overrideObject.value("method").toString();
        if(method == "email") {
            override.method = Reminders::MethodEmail;
        } else
        if(method == "sms") {
            override.method = Reminders::MethodSms;
        } else
        if(method == "popup") {
            override.method = Reminders::MethodPopup;
        } else {
            override.method = Reminders::MethodNil;
        }

        override.minutes = overrideObject.value("minutes").toInt();
    }

    QJsonObject sourceObject = jsonObject.value("source").toObject();
    _source.url = sourceObject.value("url").toString();
    _source.title = sourceObject.value("title").toString();

    return true;
}

Event::EventStatus Event::status() const
{
    return _status;
}

QString Event::htmlLink() const
{
    return _htmlLink;
}

QDateTime Event::created() const
{
    return _created;
}

QDateTime Event::updated() const
{
    return _updated;
}

QString Event::summary() const
{
    return _summary;
}

QString Event::description() const
{
    return _description;
}

QString Event::location() const
{
    return _location;
}

QString Event::colorId() const
{
    return _colorId;
}

Event::Actor Event::creator() const
{
    return _creator;
}

Event::Actor Event::organizer() const
{
    return _organizer;
}

Event::PointInTime Event::start() const
{
    return _start;
}

Event::PointInTime Event::end() const
{
    return _end;
}

bool Event::endTimeUnspecified() const
{
    return _endTimeUnspecified;
}

QList<QString> Event::recurrence() const
{
    return _recurrence;
}

QString Event::recurringEventId() const
{
    return _recurringEventId;
}

Event::PointInTime Event::originalStartTime() const
{
    return _originalStartTime;
}

Event::Transparency Event::transparency() const
{
    return _transparency;
}

Event::Visibility Event::visibility() const
{
    return _visibility;
}

QString Event::iCalUID() const
{
    return _iCalUID;
}

int Event::sequence() const
{
    return _sequence;
}

QList<Event::Attendee> Event::attendees() const
{
    return _attendees;
}

bool Event::attendeesOmitted() const
{
    return _attendeesOmitted;
}

Event::ExtendedProperties Event::extendedProperties() const
{
    return _extendedProperties;
}

QString Event::hangoutLink() const
{
    return _hangoutLink;
}

Event::Gadget Event::gadget() const
{
    return _gadget;
}

bool Event::anyoneCanAddSelf() const
{
    return _anyoneCanAddSelf;
}

bool Event::guestsCanInviteOthers() const
{
    return _guestsCanInviteOthers;
}

bool Event::guestsCanModify() const
{
    return _guestsCanModify;
}

bool Event::guestsCanSeeOtherGuests() const
{
    return _guestsCanSeeOtherGuests;
}

bool Event::privateCopy() const
{
    return _privateCopy;
}

bool Event::locked() const
{
    return _locked;
}

Event::Reminders Event::reminders() const
{
    return _reminders;
}

Event::Source Event::source() const
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

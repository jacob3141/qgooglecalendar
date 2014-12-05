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

// Qt includes
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QMap>

namespace APIV3 {

/**
 * Event resource as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/events
 */
class Event : public Resource
{
public:
    /**
     * The attendee's response status. Possible values are:
     * "needsAction" - The attendee has not responded to the invitation.
     * "declined" - The attendee has declined the invitation.
     * "tentative" - The attendee has tentatively accepted the invitation.
     * "accepted" - The attendee has accepted the invitation.
     */
    enum ResponseStatus {
        ResponseStatusNil,
        ResponseStatusNeedsAction,
        ResponseStatusDeclined,
        ResponseStatusTentative,
        ResponseStatusAccepted
    };

    /**
     * The gadget's display mode. Optional. Possible values are:
     * "icon" - The gadget displays next to the event's title in the
     *          calendar view.
     * "chip" - The gadget displays when the event is clicked.
     */
    enum GadgetDisplayMode {
        GadgetDisplayModeNil,
        GadgetDisplayModeIcon,
        GadgetDisplayModeChip
    };

    /**
     * Status of the event. Optional. Possible values are:
     * "confirmed" - The event is confirmed. This is the default status.
     * "tentative" - The event is tentatively confirmed.
     * "cancelled" - The event is cancelled.
     */
    enum EventStatus {
        EventStatusNil,
        EventStatusConfirmed,
        EventStatusTentative,
        EventStatusCancelled
    };

    /**
     * Whether the event blocks time on the calendar. Optional.
     * Possible values are:
     * "opaque" - The event blocks time on the calendar. This is the default
     *            value.
     * "transparent" - The event does not block time on the calendar.
     */
    enum Transparency {
        TransparencyNil,
        TransparencyOpaque,
        TransparencyTransparent
    };

    /**
     * Visibility of the event. Optional. Possible values are:
     * "default" - Uses the default visibility for events on the calendar.
     *             This is the default value.
     * "public" - The event is public and event details are visible to all
     *            readers of the calendar.
     * "private" - The event is private and only event attendees may view event
     *             details.
     * "confidential" - The event is private. This value is provided for
     *                  compatibility reasons.
     */
    enum Visibility {
        VisibilityNil,
        VisibilityDefault,
        VisibilityPublic,
        VisibilityPrivate,
        VisibilityConfidential
    };

    struct Actor {
        /** The actor's Profile ID, if available. */
        QString id;

        /** The actor's email address, if available. */
        QString email;

        /** The actor's name, if available. */
        QString displayName;

        /**
         * Whether the actor corresponds to the calendar on which this copy
         * of the event appears. Read-only. The default is False.
         */
        bool self;
    };

    struct PointInTime {
        /** The date, in the format "yyyy-mm-dd", if this is an all-day event.*/
        QDate date;

        /**
         * The time, as a combined date-time value (formatted according to
         * RFC 3339). A time zone offset is required unless a time zone is
         * explicitly specified in timeZone.
         */
        QDateTime dateTime;

        /**
         * The name of the time zone in which the time is specified (e.g.
         * "Europe/Zurich"). For recurring events this field is required and
         * specifies the time zone in which the recurrence is expanded. For
         * single events this field is optional and indicates a custom time
         * zone for the event start/end.
         */
        QString timeZone;
    };

    struct Attendee {
        /** The attendee's Profile ID, if available. */
        QString id;

        /**
         * The attendee's email address, if available.
         * This field must be present when adding an attendee.
         */
        QString email;

        /** The attendee's name, if available. Optional. */
        QString displayName;

        /**
         * Whether the attendee is the organizer of the event. Read-only.
         * The default is False.
         */
        bool organizer;

        /**
         * Whether this entry represents the calendar on which this copy of the
         * event appears. Read-only. The default is False.
         */
        bool self;

        /**
         * Whether the attendee is a resource. Read-only.
         * The default is False.
         */
        bool resource;

        /**
         * Whether this is an optional attendee. Optional.
         * The default is False.
         */
        bool optional;

        /**
         * The attendee's response status. Possible values are:
         * "needsAction" - The attendee has not responded to the invitation.
         * "declined" - The attendee has declined the invitation.
         * "tentative" - The attendee has tentatively accepted the invitation.
         * "accepted" - The attendee has accepted the invitation.
         */
        ResponseStatus responseStatus;

        /** The attendee's response comment. Optional. */
        QString comment;

        /** Number of additional guests. Optional. The default is 0. */
        int additionalGuests;
    };

    struct ExtendedProperties {
        /**
         * Properties that are private to the copy of the event that appears on
         * this calendar.
         */
        QMap<QString, QString> privateProperties;

        /**
         * Properties that are shared between copies of the event on other
         * attendees' calendars.
         */
        QMap<QString, QString> sharedProperties;
    };

    struct Gadget {
        /** The gadget's type. */
        QString type;

        /** The gadget's title. */
        QString title;

        /** The gadget's URL. */
        QString link;

        /** The gadget's icon URL. */
        QString iconLink;

        /** The gadget's width in pixels. Optional. */
        int width;

        /** The gadget's height in pixels. Optional. */
        int height;

        /**
         * The gadget's display mode. Optional. Possible values are:
         * "icon" - The gadget displays next to the event's title in the
         *          calendar view.
         * "chip" - The gadget displays when the event is clicked.
         */
        GadgetDisplayMode display;

        /** Preferences. */
        QMap<QString, QString> preferences;
    };

    struct Reminders {
        /**
         * The method used by this reminder. Possible values are:
         * "email" - Reminders are sent via email.
         * "sms" - Reminders are sent via SMS.
         * "popup" - Reminders are sent via a UI popup.
         */
        enum Method {
            MethodNil,
            MethodEmail,
            MethodSms,
            MethodPopup
        };

        struct Override {
            /**
             * The method used by this reminder. Possible values are:
             * "email" - Reminders are sent via email.
             * "sms" - Reminders are sent via SMS.
             * "popup" - Reminders are sent via a UI popup.
             */
            Method method;

            /**
             * Number of minutes before the start of the event when the reminder
             * should trigger.
             */
            int minutes;
        };

        /** Whether the default reminders of the calendar apply to the event. */
        bool useDefault;

        /**
         * If the event doesn't use the default reminders, this lists the
         * reminders specific to the event, or, if not set, indicates that no
         * reminders are set for this event.
         */
        QList<Override> overrides;
    };

    struct Source {
        /**
         * URL of the source pointing to a resource. URL's protocol must be
         * HTTP or HTTPS.
         */
        QString url;

        /**
         * Title of the source; for example a title of a web page or an email
         * subject.
         */
        QString title;
    };

    explicit Event();

    /** @returns Type of the resource. */
    QString kind() const;

    /** @returns a json representation of this resource. */
    QJsonObject toJsonObject() const;

    /** Initializes this model from json. */
    bool fromJson(QJsonObject jsonObject);

    /**
     * Status of the event. Optional. Possible values are:
     * "confirmed" - The event is confirmed. This is the default status.
     * "tentative" - The event is tentatively confirmed.
     * "cancelled" - The event is cancelled.
     */
    EventStatus status();

    /**
     * An absolute link to this event in the Google Calendar Web UI.
     * Read-only.
     */
    QString htmlLink();

    /** Creation time of the event (as a RFC 3339 timestamp). Read-only. */
    QDateTime created();

    /**
     * Last modification time of the event (as a RFC 3339 timestamp).
     * Read-only.
     */
    QDateTime updated();

    /** Title of the event. */
    QString summary();

    /** Description of the event. Optional. **/
    QString description();

    /** Geographic location of the event as free-form text. Optional. */
    QString location();

    /**
     * The color of the event. This is an ID referring to an entry in the event
     * section of the colors definition (see the colors endpoint). Optional.
     */
    QString colorId();

    /** The creator of the event. Read-only. */
    Actor creator();

    /**
     * The organizer of the event. If the organizer is also an attendee, this is
     * indicated with a separate entry in attendees with the organizer field set
     * to True. To change the organizer, use the move operation. Read-only,
     * except when importing an event.
     */
    Actor organizer();

    /**
     * The (inclusive) start time of the event. For a recurring event, this is
     * the start time of the first instance.
     */
    PointInTime start();

    /**
     * The (exclusive) end time of the event. For a recurring event, this is the
     * end time of the first instance.
     */
    PointInTime end();

    /**
     * Whether the end time is actually unspecified. An end time is still
     * provided for compatibility reasons, even if this attribute is set to
     * True. The default is False.
     */
    bool endTimeUnspecified();

    /**
     * List of RRULE, EXRULE, RDATE and EXDATE lines for a recurring event.
     * This field is omitted for single events or instances of recurring events.
     */
    QList<QString> recurrence();

    /**
     * For an instance of a recurring event, this is the event ID of the
     * recurring event itself. Immutable.
     */
    QString recurringEventId();

    /**
     * For an instance of a recurring event, this is the time at which this
     * event would start according to the recurrence data in the recurring event
     * identified by recurringEventId. Immutable.
     */
    PointInTime originalStartTime();

    /**
     * Whether the event blocks time on the calendar. Optional.
     * Possible values are:
     * "opaque" - The event blocks time on the calendar. This is the default
     *            value.
     * "transparent" - The event does not block time on the calendar.
     */
    Transparency transparency();

    /**
     * Visibility of the event. Optional. Possible values are:
     * "default" - Uses the default visibility for events on the calendar.
     *             This is the default value.
     * "public" - The event is public and event details are visible to all
     *            readers of the calendar.
     * "private" - The event is private and only event attendees may view event
     *             details.
     * "confidential" - The event is private. This value is provided for
     *                  compatibility reasons.
     */
    Visibility visibility();

    /** Event ID in the iCalendar format. */
    QString iCalUID();

    /** Sequence number as per iCalendar. */
    int sequence();

    /** The attendees of the event. */
    QList<Attendee> attendees();

    /**
     * Whether attendees may have been omitted from the event's representation.
     * When retrieving an event, this may be due to a restriction specified by
     * the maxAttendee query parameter. When updating an event, this can be used
     * to only update the participant's response. Optional.
     * The default is False.
     */
    bool attendeesOmitted();

    /** Extended properties of the event. */
    ExtendedProperties extendedProperties();

    /**
     * An absolute link to the Google+ hangout associated with this event.
     * Read-only.
     */
    QString hangoutLink();

    /** A gadget that extends this event. */
    Gadget gadget();

    /**
     * Whether anyone can invite themselves to the event. Optional.
     * The default is False.
     */
    bool anyoneCanAddSelf();

    /**
     * Whether attendees other than the organizer can invite others to the
     * event. Optional. The default is True.
     */
    bool guestsCanInviteOthers();

    /** @todo missing documentation. */
    bool guestsCanModify();

    /**
     * Whether attendees other than the organizer can see who the event's
     * attendees are. Optional. The default is True.
     */
    bool guestsCanSeeOtherGuests();

    /**
     * Whether this is a private event copy where changes are not shared with
     * other copies on other calendars. Optional. Immutable.
     * The default is False.
     */
    bool privateCopy();

    /**
     * Whether this is a locked event copy where no changes can be made to the
     * main event fields "summary", "description", "location", "start", "end"
     * or "recurrence". The default is False. Read-Only.
     */
    bool locked();

    /** Information about the event's reminders for the authenticated user. */
    Reminders reminders();

    /**
     * Source of an event from which it was created; for example a web page, an
     * email message or any document identifiable by an URL using HTTP/HTTPS
     * protocol. Accessible only by the creator of the event.
     */
    Source source();

    /** Sets the event's status. */
    void setStatus(EventStatus status);

    /** Sets the event's title. */
    void setSummary(QString summary);

    /** Sets the event's description. */
    void setDescription(QString description);

    /** Sets the event's color id. */
    void setColorId(QString colorId);

    /** Sets the event organizer, if possible. */
    void setOrganizer(Actor organizer);

    /** Sets the start time. */
    void setStart(PointInTime start);

    /** Sets the end time. */
    void setEnd(PointInTime end);

    /** Sets that the end time is not specified. */
    void setEndTimeUnspecified(bool endTimeUnspecified);

    /** Sets recurrence. */
    void setRecurrence(QList<QString> recurrence);

    /** Sets transparency for this event. */
    void setTransparency(Transparency transparency);

    /** Sets visibility of this event. */
    void setVisibility(Visibility visibility);

    /** Sets the iCal UID of this event. */
    void setICalUID(QString iCalUID);

    /** Sets the sequence of this event. */
    void setSequence(int sequence);

    /** Sets the list of attendees for this event. */
    void setAttendees(QList<Attendee> attendees);

    /** Sets that attendees can be omitted. */
    void setAttendeesOmitted(bool attendeesOmitted);

    /** Sets the extended properties for this event. */
    void setExtendedProperties(ExtendedProperties extendedProperties);

    /** Sets the gadget for this event. */
    void setGadget(Gadget gadget);

    /** Sets that anyone can add self for this event. */
    void setAnyoneCanAddSelf(bool anyoneCanAddSelf);

    /** Set the flag that indicates that guests can invite others. */
    void setGuestsCanInviteOthers(bool guestsCanInviteOthers);

    /** Allows guests to modify this event. */
    void setGuestsCanModify(bool guestsCanModify);

    /** Sets the guests can see other guests. */
    void setGuestsCanSeeOtherGuests(bool guestsCanSeeOtherGuests);

    /** Sets the reminders. */
    void setReminders(Reminders reminders);

    /** Set the source of this event. */
    void setSource(Source source);

private:
    EventStatus         _status;
    QString             _htmlLink;
    QDateTime           _created;
    QDateTime           _updated;
    QString             _summary;
    QString             _description;
    QString             _location;
    QString             _colorId;
    Actor               _creator;
    Actor               _organizer;
    PointInTime         _start;
    PointInTime         _end;
    bool                _endTimeUnspecified;
    QList<QString>      _recurrence;
    QString             _recurringEventId;
    PointInTime         _originalStartTime;
    Transparency        _transparency;
    Visibility          _visibility;
    QString             _iCalUID;
    int                 _sequence;
    QList<Attendee>     _attendees;
    bool                _attendeesOmitted;
    ExtendedProperties  _extendedProperties;
    QString             _hangoutLink;
    Gadget              _gadget;
    bool                _anyoneCanAddSelf;
    bool                _guestsCanInviteOthers;
    bool                _guestsCanModify;
    bool                _guestsCanSeeOtherGuests;
    bool                _privateCopy;
    bool                _locked;
    Reminders           _reminders;
    Source              _source;
};

} // APIV3


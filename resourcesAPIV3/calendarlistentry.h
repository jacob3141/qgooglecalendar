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

// Qt includes
#include <QString>

/**
 * CalendarList resource as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/calendarList
 */
class CalendarListEntry
{
public:
    explicit CalendarListEntry();
    enum AccessRole {
        AccessRoleFreeBusyReader,
        AccessRoleReader,
        AccessRoleWriter,
        AccessRoleOwner
    };

    struct DefaultReminder {
        enum Method {
            EMail,
            Sms,
            Popup
        };

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

    struct Notification {
        enum Type {
            EventCreation,
            EventChange,
            EventCancellation,
            EventResponse,
            Agenda
        };

        enum Method {
            EMail,
            Sms
        };

        /**
         * The type of notification. Possible values are:
         * "eventCreation" - Notification sent when a new event is put on the
         * calendar.
         * "eventChange" - Notification sent when an event is changed.
         * "eventCancellation" - Notification sent when an event is cancelled.
         * "eventResponse" - Notification sent when an event is changed.
         * "agenda" - An agenda with the events of the day (sent out in the
         * morning).
         */
        Type type;

        /**
         * The method used to deliver the notification. Possible values are:
         * "email" - Reminders are sent via email.
         * "sms" - Reminders are sent via SMS. This value is read-only and is
         * ignored on inserts and updates.
         */
        Method method;
    };

    /** @returns Type of the resource ("calendar#calendarListEntry"). */
    QString kind();

    /** @returns The effective access role that the authenticated user has on
     * the calendar. Read-only. Possible values are:
     * "freeBusyReader" - Provides read access to free/busy information.
     * "reader" - Provides read access to the calendar. Private events will
     * appear to users with reader access, but event details will be hidden.
     * "writer" - Provides read and write access to the calendar. Private events
     * will appear to users with writer access, and event details will be
     * visible.
     * "owner" - Provides ownership of the calendar. This role has all of the
     * permissions of the writer role with the additional ability to see and
     * manipulate ACLs.
     */
    AccessRole accessRole() const;

    /**
     * @returns Whether this calendar list entry has been deleted from the
     * calendar list. Read-only. Optional. The default is False.
     */
    bool deleted() const;

    /** @returns Description of the calendar. Optional. Read-only. */
    QString description() const;

    /**
     * @returns Geographic location of the calendar as free-form text.
     * Optional. Read-only.
     */
    QString location() const;

    /**
     * @returns Whether the calendar is the primary calendar of the
     * authenticated user. Read-only. Optional. The default is False.
     */
    bool primary() const;

    /** @returns Title of the calendar. Read-only. */
    QString summary() const;

    /** @returns The time zone of the calendar. Optional. Read-only. */
    QString timeZone() const;

    /** @returns ETag of the resource. */
    QString eTag() const;

    /** @returns Identifier of the calendar. */
    QString id() const;

    /**
     * @returns The summary that the authenticated user has set for this
     * calendar. Optional.
     */
    QString summaryOverride() const;

    /**
     * @returns The color of the calendar. This is an ID referring to an entry
     * in the calendar section of the colors definition (see the colors
     * endpoint). Optional.
     */
    QString colorId() const;

    /**
     * @returns The main color of the calendar in the hexadecimal format
     * "#0088aa". This property supersedes the index-based colorId property.
     * Optional.
     */
    QString backgroundColor() const;

    /**
     * @returns The foreground color of the calendar in the hexadecimal format
     * "#ffffff". This property supersedes the index-based colorId property.
     * Optional.
     */
    QString foregroundColor() const;

    /**
     * @returns Whether the calendar has been hidden from the list. Optional.
     * The default is False.
     */
    bool hidden() const;

    /**
     * @returns Whether the calendar content shows up in the calendar UI.
     * Optional. The default is False.
     */
    bool selected() const;

    /**
     * @returns The default reminders that the authenticated user has for this
     * calendar.
     */
    QList<DefaultReminder> defaultReminders() const;

    /**  @returns The list of notifications set for this calendar. */
    QList<Notification> notifications() const;

    void setSummaryOverride(QString summaryOverride);
    void setColorId(QString colorId);
    void setBackgroundColor(QString backgroundColor);
    void setForegroundColor(QString foregroundColor);
    void setHidden(bool hidden);
    void setSelected(bool selected);
    void setDefaultReminders(QList<DefaultReminder> defaultReminders);
    void setNotifications(QList<Notification> notifications);

private:
    QString _eTag;
    QString _id;
    QString _summary;
    QString _description;
    QString _location;
    QString _timeZone;
    QString _summaryOverride;
    QString _colorId;
    QString _backgroundColor;
    QString _foregroundColor;
    bool _hidden;
    bool _selected;
    AccessRole _accessRole;
    QList<DefaultReminder> _defaultReminders;
    QList<Notification> _notifications;
    bool _primary;
    bool _deleted;
};

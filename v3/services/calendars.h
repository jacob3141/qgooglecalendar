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
#include "v3/services/service.h"

#include "v3/services/requests/calendarsclear.h"
#include "v3/services/requests/calendarsdelete.h"
#include "v3/services/requests/calendarsget.h"
#include "v3/services/requests/calendarsinsert.h"
#include "v3/services/requests/calendarspatch.h"
#include "v3/services/requests/calendarsupdate.h"

namespace APIV3 {

/**
 * Service for Calendars endpoint as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/calendars
 */
class Calendars : public Service, public RequestOperationDelegate
{
    Q_OBJECT
public:
    explicit Calendars(QObject *parent = 0);

    void handleReplyNonBlocking(RequestOperation *request, QNetworkReply *networkReply);
    void requestTimedOut(RequestOperation *request);

    /**
     * Blocking methods. These methods will not return immediately.
     * You can use these if you need to wait for the result sequentially.
     * Be careful to avoid using these form within your GUI thread, as they may
     * hang up your visual interface in case the request takes a long time.
     */

    bool clearB(QString calendarId);
    bool deleteB(QString calendarId);
    bool getB(QString calendarId, Calendar& calendar);
    bool insertB(Calendar& calendar);
    bool patchB(QString calendarId, Calendar &calendar);
    bool updateB(QString calendarId, Calendar &calendar);

public slots:
    /**
     * Non-blocking methods. These will fire the request and return immediately.
     * Listen for the specific signals to obtain the results.
     */

    bool clearNB(QString calendarId);
    bool deleteNB(QString calendarId);
    bool getNB(QString calendarId);
    bool insertNB(Calendar calendar);
    bool patchNB(QString calendarId, Calendar calendar);
    bool updateNB(QString calendarId, Calendar calendar);

signals:
    void requestTimedOut();

    void clearFinished();
    void deleteFinished();
    void getFinished(Calendar calendar);
    void insertFinished(Calendar calendar);
    void patchFinished(Calendar calendar);
    void updateFinished(Calendar calendar);

    void clearFailed(QString errorString);
    void deleteFailed(QString errorString);
    void getFailed(QString errorString);
    void insertFailed(QString errorString);
    void patchFailed(QString errorString);
    void updateFailed(QString errorString);

private:
    bool clearReply(QNetworkReply *networkReply);
    bool deleteReply(QNetworkReply *networkReply);
    bool getReply(QNetworkReply *networkReply, Calendar &calendar);
    bool insertReply(QNetworkReply *networkReply, Calendar &calendar);
    bool patchReply(QNetworkReply *networkReply, Calendar &calendar);
    bool updateReply(QNetworkReply *networkReply, Calendar &calendar);

    bool decodeCalendarFromReply(QNetworkReply *networkReply, Calendar &calendar);

    CalendarsClear *    _clear;
    CalendarsDelete *   _delete;
    CalendarsGet *      _get;
    CalendarsInsert *   _insert;
    CalendarsPatch *    _patch;
    CalendarsUpdate *   _update;
};

} // APIV3


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
#include "v3/resources/calendarlistentry.h"
#include "v3/services/requests/requestoperation.h"

#include "requests/calendarlistdelete.h"
#include "requests/calendarlistget.h"
#include "requests/calendarlistinsert.h"
#include "requests/calendarlistlist.h"
#include "requests/calendarlistpatch.h"
#include "requests/calendarlistupdate.h"
#include "requests/calendarlistwatch.h"

namespace APIV3 {

/**
 * Service for CalendarList endpoint as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/calendarList
 */
class CalendarList : public Service, public RequestOperationDelegate
{
    Q_OBJECT
public:
    explicit CalendarList(QObject *parent = 0);

    void handleReplyNonBlocking(RequestOperation *request, QNetworkReply *networkReply);
    void requestTimedOut(RequestOperation *request);

    /**
     * Blocking methods. These methods will not return immediately.
     * You can use these if you need to wait for the result sequentially.
     * Be careful to avoid using these form within your GUI thread, as they may
     * hang up your visual interface in case the request takes a long time.
     */
    bool deleteB(QString calendarId, bool& success);
    bool getB(QString calendarId, CalendarListEntry& calendarListEntry);
    bool insertB(CalendarListEntry& calendarListEntry);
    bool listB(QList<CalendarListEntry> &list,
               int maxResults = -1,
               QString pageToken = "",
               bool showDeleted = false,
               QString syncToken = "");
    bool patchB(QString calendarId, CalendarListEntry& calendarListEntry);
    bool updateB(QString calendarId, CalendarListEntry& calendarListEntry);
    bool watchB();

public slots:
    /**
     * Non-blocking methods. These will fire the request and return immediately.
     * Listen for the specific signals to obtain the results.
     */
    bool deleteNB(QString calendarId);
    bool getNB(QString calendarId);
    bool insertNB(CalendarListEntry calendarListEntry);
    bool listNB(int maxResults = -1,
                QString pageToken = "",
                bool showDeleted = false,
                QString syncToken = "");
    bool patchNB(QString calendarId, CalendarListEntry calendarListEntry);
    bool updateNB(QString calendarId, CalendarListEntry calendarListEntry);
    bool watchNB();

signals:
    void requestTimedOut();

    /** If successful, this method returns an empty response body. */
    void deleteFinished();
    /** If successful, this method returns a Calendar resource in the response body. */
    void getFinished(CalendarListEntry calendarListEntry);
    /** If successful, this method returns a Calendar resource in the response body. */
    void insertFinished(CalendarListEntry calendarListEntry);
    /**
     * If successful, this method returns a response body with a list of calendar
     * resources and meta data.
     */
    void listFinished(QList<CalendarListEntry> list);
    /** If successful, this method returns a Calendar resource in the response body. */
    void patchFinished(CalendarListEntry calendarListEntry);
    /** If successful, this method returns a Calendar resource in the response body. */
    void updateFinished(CalendarListEntry calendarListEntry);
    // TODO
    void watchFinished();

    void deleteFailed(QString errorString);
    void getFailed(QString errorString);
    void insertFailed(QString errorString);
    void listFailed(QString errorString);
    void patchFailed(QString errorString);
    void updateFailed(QString errorString);
    void watchFailed(QString errorString);

private:
    bool deleteReply(QNetworkReply* networkReply);
    bool getReply(QNetworkReply* networkReply, CalendarListEntry &calendarListEntry);
    bool insertReply(QNetworkReply* networkReply, CalendarListEntry &calendarListEntry);
    bool listReply(QNetworkReply* networkReply);
    bool patchReply(QNetworkReply* networkReply, CalendarListEntry &calendarListEntry);
    bool updateReply(QNetworkReply* networkReply, CalendarListEntry &calendarListEntry);
    bool watchReply(QNetworkReply* networkReply);

    bool decodeCalendarListFromReply(QNetworkReply* networkReply, CalendarListEntry& calendarListEntry);

    CalendarListDelete *  _delete;
    CalendarListGet *     _get;
    CalendarListInsert *  _insert;
    CalendarListList *    _list;
    CalendarListPatch *   _patch;
    CalendarListUpdate *  _update;
    CalendarListWatch *   _watch;
};

} // APIV3


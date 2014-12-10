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
#include "v3/resources/aclrule.h"
#include "v3/resources/calendar.h"

#include "requests/acldelete.h"
#include "requests/aclget.h"
#include "requests/aclinsert.h"
#include "requests/acllist.h"
#include "requests/aclpatch.h"
#include "requests/aclupdate.h"
#include "requests/aclwatch.h"

// Qt includes
#include <QList>

namespace APIV3 {

/**
 * Service for Acl endpoint as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/acl
 */
class Acl : public Service, public RequestOperationDelegate
{
    Q_OBJECT
public:
    explicit Acl(QObject *parent = 0);

    void handleReplyNonBlocking(RequestOperation *request, QNetworkReply *networkReply);
    void requestTimedOut(RequestOperation *request);

    /**
     * Blocking methods. These methods will not return immediately.
     * You can use these if you need to wait for the result sequentially.
     * Be careful to avoid using these form within your GUI thread, as they may
     * hang up your visual interface in case the request takes a long time.
     */

    bool deleteB(QString calendarId, QString ruleId, bool& success);
    bool getB(QString calendarId, QString ruleId, AclRule& rule);
    bool insertB(QString calendarId, AclRule& rule);
    bool listB(QString calendarId,
               QList<AclRule>& list,
               int maxResults = -1,
               QString pageToken = "",
               bool showDeleted = false,
               QString syncToken = "");
    bool patchB(QString calendarId, QString ruleId, AclRule& rule);
    bool updateB(QString calendarId, QString ruleId, AclRule& rule);
    bool watchB(QString calendarId);

public slots:
    /**
     * Non-blocking methods. These will fire the request and return immediately.
     * Listen for the specific signals to obtain the results.
     */
    bool deleteNB(QString calendarId, QString ruleId);
    bool getNB(QString calendarId, QString ruleId);
    bool insertNB(QString calendarId, AclRule rule);
    bool listNB(QString calendarId,
             int maxResults = -1,
             QString pageToken = "",
             bool showDeleted = false,
             QString syncToken = "");
    bool patchNB(QString calendarId, QString ruleId);
    bool updateNB(QString calendarId, QString ruleId);
    bool watchNB(QString calendarId);

signals:
    /** Emitted, when the operation in progress has timed out. */
    void requestTimedOut();

    /** If successful, this method returns an empty response body. */
    void deleteFinished();
    /** If successful, this method returns an Acl resource in the response body. */
    void getFinished(AclRule rule);
    /** If successful, this method returns an Acl resource in the response body. */
    void insertFinished(AclRule rule);
    /**
     * If successful, this method returns a response body with a list of acl
     * resources and meta data.
     */
    void listFinished(QList<AclRule> aclList);
    /** If successful, this method returns an Acl resource in the response body. */
    void patchFinished(AclRule rule);
    /** If successful, this method returns an Acl resource in the response body. */
    void updateFinished(AclRule rule);
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
    bool deleteReply(QNetworkReply *networkReply);
    bool getReply(QNetworkReply *networkReply, AclRule& rule);
    bool insertReply(QNetworkReply *networkReply, AclRule& rule);
    // list
    bool patchReply(QNetworkReply *networkReply, AclRule& rule);
    bool updateReply(QNetworkReply *networkReply, AclRule& rule);
    // watch

    bool decodeRuleFromReply(QNetworkReply *networkReply, AclRule& rule);

    AclDelete *  _delete;
    AclGet *     _get;
    AclInsert *  _insert;
    AclList *    _list;
    AclPatch *   _patch;
    AclUpdate *  _update;
    AclWatch *   _watch;
};

} // APIV3


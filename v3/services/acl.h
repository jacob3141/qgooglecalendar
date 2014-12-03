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
#include "v3/services/requests/request.h"

#include "requests/aclremoverequest.h"
#include "requests/aclgetrequest.h"
#include "requests/aclinsertrequest.h"
#include "requests/acllistrequest.h"
#include "requests/aclpatchrequest.h"
#include "requests/aclupdaterequest.h"
#include "requests/aclwatchrequest.h"

namespace APIV3 {

/**
 * Service for Acl endpoint as specified by Google.
 * @see https://developers.google.com/google-apps/calendar/v3/reference/acl
 */
class Acl : public Service, public RequestDelegate
{
    Q_OBJECT
public:
    explicit Acl(QObject *parent = 0);

public:
    // Synchronous methods, blocking
    bool removeSync(Calendar calendar, int ruleId);
    AclRule getSync(Calendar calendar, int ruleId);
    int insertSync(Calendar calendar, AclRule rule);
    // list
    // patch
    // update
    // watch

public slots:
    // Asynchronous methods, non-blocking
    void removeAsync(Calendar calendar, int ruleId);
    void getAsync(Calendar calendar, int ruleId);
    void insertAsync(Calendar calendar, AclRule rule);
    // list
    // patch
    // update
    // watch

signals:
    void requestTimedOut();
    void removeFinished(Calendar calendar, int ruleId, bool success);
    void getFinished(Calendar calendar, AclRule rule);
    void insertFinished(Calendar calendar, int ruleId);

protected:
    void handleReply(Request *request, QNetworkReply *networkReply);
    void requestTimedOut(Request *request);

private:
    void handleRemoveReply(QNetworkReply* networkReply);
    void handleGetReply(QNetworkReply* networkReply);
    void handleInsertReply(QNetworkReply* networkReply);
    void handleListReply(QNetworkReply* networkReply);
    void handlePatchReply(QNetworkReply* networkReply);
    void handleUpdateReply(QNetworkReply* networkReply);
    void handleWatchReply(QNetworkReply* networkReply);

    AclRemoveRequest *  _removeRequest;
    AclGetRequest *     _getRequest;
    AclInsertRequest *  _insertRequest;
    AclListRequest *    _listRequest;
    AclPatchRequest *   _patchRequest;
    AclUpdateRequest *  _updateRequest;
    AclWatchRequest *   _watchRequest;
};

} // APIV3


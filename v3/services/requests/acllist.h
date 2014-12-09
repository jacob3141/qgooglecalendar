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
#include "requestoperation.h"
#include "v3/resources/calendar.h"
#include "v3/services/requestdelegate.h"

namespace APIV3 {

class AclList : public RequestOperation {
public:
    AclList(RequestOperationDelegate *requestDelegate, QObject *parent = 0)
        : RequestOperation(requestDelegate, parent) {
    }

    void setParameters(QString calendarId,
                   int maxResults = -1,
                   QString pageToken = "",
                   bool showDeleted = false,
                   QString syncToken = "") {
        _calendarId = calendarId;
        _maxResults = maxResults;
        _pageToken = pageToken;
        _showDeleted = showDeleted;
        _syncToken = syncToken;
    }

    QNetworkRequest networkRequest() {
        // TODO
        return QNetworkRequest();
    }

    HttpMethod httpMethod() {
        return HttpMethodGet;
    }

    QStringList requiredScopes() {
        QStringList scopes;
        scopes << "https://www.googleapis.com/auth/calendar";
        return scopes;
    }

private:
    QString _calendarId;
    int _maxResults;
    QString _pageToken;
    bool _showDeleted;
    QString _syncToken;
};

} // APIV3

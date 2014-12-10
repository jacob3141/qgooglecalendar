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
#include "v3/resources/calendarlistentry.h"
#include "v3/services/requestdelegate.h"

// Qt includes
#include <QJsonDocument>

namespace APIV3 {

class CalendarListInsert : public RequestOperation {
public:
    CalendarListInsert(RequestOperationDelegate *requestDelegate, QObject *parent = 0)
        : RequestOperation(requestDelegate, parent) {
    }

    void setParameters(CalendarListEntry calendarListEntry) {
        _calendarListEntry = calendarListEntry;
    }

    QNetworkRequest networkRequest() {
        QNetworkRequest networkRequest;
        networkRequest.setUrl(QString("%1/users/me/calendarList")
                              .arg(baseUrl()));
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                                 "application/x-www-form-urlencoded");
        networkRequest.setHeader(QNetworkRequest::UserAgentHeader,
                                 userAgent());
        return networkRequest;
    }

    QByteArray bodyData() {
        QJsonDocument document(_calendarListEntry.toJsonObject());
        return document.toJson();
    }

    HttpMethod httpMethod() {
        return HttpMethodPost;
    }

    QStringList requiredScopes() {
        QStringList scopes;
        scopes << "https://www.googleapis.com/auth/calendar";
        return scopes;
    }

private:
    CalendarListEntry _calendarListEntry;
};

} // APIV3

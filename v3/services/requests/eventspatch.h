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
#include "v3/resources/event.h"
#include "v3/services/requestdelegate.h"

// Qt includes
#include <QJsonDocument>

namespace APIV3 {

class EventsPatch : public RequestOperation {
public:
    EventsPatch(RequestOperationDelegate *requestDelegate, QObject *parent = 0)
        : RequestOperation(requestDelegate, parent) {
    }

    void setParameters(QString calendarId, QString eventId, Event event) {
        _calendarId = calendarId;
        _eventId = eventId;
        _event = event;
    }

    QNetworkRequest networkRequest() {
        // TODO: Find out how to handle destination parameter.
        QNetworkRequest networkRequest;
        networkRequest.setUrl(QString("%1/calendars/%2/events/%3")
                              .arg(baseUrl())
                              .arg(_calendarId)
                              .arg(_eventId));
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader,
                                 "application/x-www-form-urlencoded");
        networkRequest.setHeader(QNetworkRequest::UserAgentHeader,
                                 userAgent());
        return networkRequest;
    }

    QByteArray bodyData() {
        QJsonDocument document(_event.toJsonObject());
        return document.toJson();
    }

    HttpMethod httpMethod() {
        return HttpMethodPatch;
    }

    QStringList requiredScopes() {
        QStringList scopes;
        scopes << "https://www.googleapis.com/auth/calendar";
        return scopes;
    }

private:
    QString _calendarId;
    QString _eventId;
    Event _event;
};

} // APIV3

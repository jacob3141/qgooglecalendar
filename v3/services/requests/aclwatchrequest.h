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
#include "request.h"
#include "v3/resources/calendar.h"
#include "v3/services/requestdelegate.h"

namespace APIV3 {

class AclWatchRequest : public Request {
public:
    AclWatchRequest(RequestDelegate *requestDelegate, QObject *parent = 0)
        : Request(requestDelegate, parent) {
    }

    void configure(Calendar calendar, int ruleId) {
        _calendar = calendar;
        _ruleId = ruleId;
    }

    QNetworkRequest networkRequest() {

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
    Calendar _calendar;
    int _ruleId;
};

} // APIV3

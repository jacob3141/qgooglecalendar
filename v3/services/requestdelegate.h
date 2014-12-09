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
#include <QNetworkReply>

namespace APIV3 {

class RequestOperation;
class RequestOperationDelegate {
public:
    /**
     * This will be called when a request in non-blocking mode has fired.
     * @attention You are supposed to delete the network reply when done.
     * @param request The request object.
     * @param networkReply The corresponding network reply.
     */
    virtual void handleReplyNonBlocking(RequestOperation *request,
                             QNetworkReply *networkReply) = 0;
    virtual void requestTimedOut(RequestOperation *request) = 0;
};

} // APIV3

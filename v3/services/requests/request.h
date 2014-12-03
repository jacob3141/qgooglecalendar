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
#include "v3/services/requestdelegate.h"

// Qt includes
#include <QNetworkAccessManager>
#include <QMutex>
#include <QObject>
#include <QThread>

namespace APIV3 {

/**
 *
 */
class Request : public QObject
{
    Q_OBJECT
public:
    enum HttpMethod {
        HttpMethodGet,
        HttpMethodPost,
        HttpMethodDelete
    };

    Request(RequestDelegate *requestDelegate, QObject *parent = 0);
    virtual ~Request();

    /**
     * Performs a transaction synchronously, ie. the executing thread will be
     * blocked until a reply has been received.
     * @param timeout The maximum time in seconds after the operation times out.
     * @returns true, if the transaction could be initiated, false otherwise.
     */
    bool performSync(int timeout = 30);

    /**
     * Performs a transaction asychronously, ie. the executing thread will not
     * be blocked.
     * @returns true, if the transaction could be initiated, false otherwise.
     */
    bool performAsync(int timeout = 30);

    /**
     * Supposed to supply the transaction with a network request.
     * @returns the network request.
     */
    virtual QNetworkRequest *buildNetworkRequest() = 0;

    /**
     * Supposed to return the appropriate http method.
     * @returns the http method.
     */
    virtual HttpMethod httpMethod();

private slots:
    /**
     * @brief receivedNetworkReply
     * @param networkReply
     */
    void receivedNetworkReply(QNetworkReply *networkReply);

private:
    /**
     * @brief startTransaction
     * @param timeout
     * @return
     */
    bool startRequest(int timeout);

    /**
     * @brief block
     */
    void block();

    RequestDelegate *_requestDelegate;
    QNetworkAccessManager _networkAccessManager;
    QMutex *_requestMutex;
};

} // APIV3

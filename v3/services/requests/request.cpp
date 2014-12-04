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

// Own includes
#include "request.h"

namespace APIV3 {

Request::Request(RequestDelegate *requestDelegate,
                         QObject *parent)
    : QObject(parent)
{
    if(!requestDelegate) {
        qDebug() << "Warning: Request provided with a null observer.";
    }

    _requestDelegate = requestDelegate;

    connect(&_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(receivedNetworkReply(QNetworkReply*)));

    _requestMutex = new QMutex(QMutex::Recursive);
}

Request::~Request()
{
    delete _requestMutex;
}

void Request::configureAccessToken(QString accessToken)
{
    _accessToken = accessToken;
}

bool Request::performSync(int timeout)
{
    bool success = startRequest(timeout);
    block();
    return success;
}

bool Request::performAsync(int timeout)
{
    return startRequest(timeout);
}

QByteArray Request::bodyData()
{
    return "";
}

Request::HttpMethod Request::httpMethod()
{
    return HttpMethodGet;
}

QString Request::userAgent()
{
    return "QGoogleCalender/1.0";
}

void Request::receivedNetworkReply(QNetworkReply *networkReply)
{
    if(_requestDelegate) {
        _requestDelegate->handleTransactionResult(this, networkReply);
    }

    // Unlock to indicate we're done.
    _requestMutex->unlock();
}

bool Request::startRequest(int timeout)
{
    // Try locking to ensure that there is no other request pending.
    if(!_requestMutex->tryLock(timeout * 1000)) {
        if(_requestDelegate) {
            _requestDelegate->transactionTimedOut(this);
        }
        // Do not perform request when another request is pending.
        return false;
    }

    // Perform request
    switch (httpMethod()) {
    case HttpMethodGet:
        _networkAccessManager.get(networkRequest());
        break;
    case HttpMethodPost:
        _networkAccessManager.post(networkRequest(), bodyData());
        break;
    case HttpMethodDelete:
        _networkAccessManager.deleteResource(networkRequest());
        break;
    case HttpMethodPut:
        _networkAccessManager.put(networkRequest(), bodyData());
        break;
    }
    return true;
}

void Request::block()
{
    // Try locking the transaction mutex to probe if it has been unlocked.
    if(_requestMutex->tryLock(timeout * 1000)) {
        // After locking it successfully we can be sure the previous operation
        // has been completed, so now let's unlock it again.
        _requestMutex->unlock();
    } else {
        // If we were not able to lock at all, something went wrong.
        if(_requestDelegate) {
            _requestDelegate->requestTimedOut(this);
        }
    }
}

} // APIV3

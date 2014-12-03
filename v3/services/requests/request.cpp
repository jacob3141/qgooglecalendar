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

Request::HttpMethod Request::httpMethod()
{
    return HttpMethodGet;
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
    // Try locking to ensure that there is no other transaction running.
    if(!_requestMutex->tryLock(timeout * 1000)) {
        if(_requestDelegate) {
            _requestDelegate->transactionTimedOut(this);
        }
        // Do not perform transaction when another transaction is running.
        return false;
    }

    // Build the network request.
    QNetworkRequest *networkRequest = buildNetworkRequest();
    if(networkRequest) {
        switch (httpMethod()) {
        case HttpMethodGet:
            _networkAccessManager.get(networkRequest);
            break;
        case HttpMethodPost:
            _networkAccessManager.post(networkRequest);
            break;
        }
    } else {
        qDebug() << "Warning: Request created null network request.";
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

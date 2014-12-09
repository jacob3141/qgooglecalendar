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
#include "requestoperation.h"

// Qt includes
#include <QNetworkReply>

namespace APIV3 {

RequestOperation::RequestOperation(RequestOperationDelegate *requestDelegate,
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

RequestOperation::~RequestOperation()
{
    delete _requestMutex;
}

void RequestOperation::setAccessToken(QString accessToken)
{
    _accessToken = accessToken;
}

bool RequestOperation::perform(PerformMode performMode, int timeout)
{
    // Try locking to ensure that there is no other request pending.
    if(!_requestMutex->tryLock(timeout * 1000)) {
        if(_requestDelegate) {
            _requestDelegate->requestTimedOut(this);
        }
        // Do not perform request when another request is pending.
        return false;
    }

    _performMode = performMode;

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
    case HttpMethodPatch:
        // TODO
        //_networkAccessManager.sendCustomRequest(networkRequest(), "PATCH", bodyData());
        break;
    }

    if(_performMode == PerformModeBlocking) {
        // Block on synchronous perform mode.
        return block(timeout);
    }
    return true;
}

QByteArray RequestOperation::bodyData()
{
    return "";
}

RequestOperation::HttpMethod RequestOperation::httpMethod()
{
    return HttpMethodGet;
}

QByteArray RequestOperation::customHttpMethodVerb()
{
    return "";
}

QString RequestOperation::userAgent()
{
    return "QGoogleCalender/1.0";
}

QNetworkReply *RequestOperation::networkReply()
{
    return _networkReply;
}

void RequestOperation::doneProcessingNetworkReply()
{
    _networkReply->deleteLater();
}

QString RequestOperation::baseUrl()
{
    return "https://www.googleapis.com/calendar/v3";
}

void RequestOperation::receivedNetworkReply(QNetworkReply *networkReply)
{
    _networkReply = networkReply;
    if(_performMode == PerformModeNonBlocking) {
        if(_requestDelegate) {
            _requestDelegate->handleReplyNonBlocking(this, networkReply);
        }
    }

    // Unlock to indicate we're done.
    _requestMutex->unlock();
}

bool RequestOperation::block(int timeout)
{
    // Try locking the transaction mutex to probe if it has been unlocked.
    if(_requestMutex->tryLock(timeout * 1000)) {
        // After locking it successfully we can be sure the previous operation
        // has been completed, so now let's unlock it again.
        _requestMutex->unlock();
        return true;
    } else {
        // If we were not able to lock at all, something went wrong.
        if(_requestDelegate) {
            _requestDelegate->requestTimedOut(this);
        }
        return false;
    }
}

} // APIV3

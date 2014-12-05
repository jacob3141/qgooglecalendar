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
#include "acl.h"

// Qt includes
#include <QNetworkReply>

namespace APIV3 {

Acl::Acl(QObject *parent) :
    Service(parent),
    RequestDelegate()
{
    _removeRequest  = new AclRemoveRequest(this, parent);
    _getRequest     = new AclGetRequest(this, parent);
    _insertRequest  = new AclInsertRequest(this, parent);
    _listRequest    = new AclListRequest(this, parent);
    _patchRequest   = new AclPatchRequest(this, parent);
    _updateRequest  = new AclUpdateRequest(this, parent);
    _watchRequest   = new AclWatchRequest(this, parent);
}

// Sync

bool Acl::removeSync(QString calendarId, QString ruleId)
{
    _removeRequest->configureAccessToken(_accessToken);
    _removeRequest->configure(calendarId, ruleId);
    _removeRequest->performSync(_operationTimeout);
}

AclRule Acl::getSync(QString calendarId, QString ruleId)
{
    _getRequest->configureAccessToken(_accessToken);
    _getRequest->configure(calendarId, ruleId);
    _getRequest->performSync(_operationTimeout);
}

int Acl::insertSync(QString calendarId, AclRule rule)
{
    _insertRequest->configureAccessToken(_accessToken);
    _insertRequest->configure(calendarId, rule);
    _insertRequest->performSync(_operationTimeout);
}

// Async

void Acl::removeAsync(QString calendarId, QString ruleId)
{
    _removeRequest->configureAccessToken(_accessToken);
    _removeRequest->configure(calendarId, ruleId);
    _removeRequest->performAsync(_operationTimeout);
}

void Acl::getAsync(QString calendarId, QString ruleId)
{
    _getRequest->configureAccessToken(_accessToken);
    _getRequest->configure(calendarId, ruleId);
    _getRequest->performAsync(_operationTimeout);
}

void Acl::insertAsync(QString calendarId, AclRule rule)
{
    _insertRequest->configureAccessToken(_accessToken);
    _insertRequest->configure(calendarId, rule);
    _insertRequest->performAsync(_operationTimeout);
}

// APIRequestDelegate

void Acl::handleReply(Request *request,
                      QNetworkReply *networkReply)
{
    if(request == _removeRequest) {
        handleRemoveReply(networkReply);
    } else
    if(request == _getRequest) {
        handleGetReply(networkReply);
    } else
    if(request == _insertRequest) {
        handleInsertReply(networkReply);
    } else
    if(request == _listRequest) {
        handleListReply(networkReply);
    } else
    if(request == _patchRequest) {
        handlePatchReply(networkReply);
    } else
    if(request == _updateRequest) {
        handleUpdateReply(networkReply);
    } else
    if(request == _watchRequest) {
        handleWatchReply(networkReply);
    } else {
        qDebug() << "Warning: Received response for unknown request.";
    }
}

void Acl::requestTimedOut(Request *request)
{
    Q_UNUSED(request);
    emit requestTimedOut();
}

// Private slots

void Acl::handleRemoveReply(QNetworkReply* networkReply)
{
    //emit removeFinished();
}

void Acl::handleGetReply(QNetworkReply* networkReply)
{

    //emit getFinished();
}

void Acl::handleInsertReply(QNetworkReply* networkReply)
{
    //emit insertFinished();
}

void Acl::handleListReply(QNetworkReply* networkReply)
{

}

void Acl::handlePatchReply(QNetworkReply* networkReply)
{

}

void Acl::handleUpdateReply(QNetworkReply* networkReply)
{

}

void Acl::handleWatchReply(QNetworkReply* networkReply)
{

}

} // APIV3

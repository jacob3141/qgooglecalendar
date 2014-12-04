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
    APIRequestDelegate()
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

bool Acl::removeSync(Calendar calendar, int ruleId)
{
    _removeRequest->configureAccessToken(_accessToken);
    _removeRequest->configure(calendar, ruleId);
    _removeRequest->performSync(_operationTimeout);
}

AclRule Acl::getSync(Calendar calendar, int ruleId)
{
    _getRequest->configureAccessToken(_accessToken);
    _getRequest->configure(calendar, ruleId);
    _getRequest->performSync(_operationTimeout);
}

int Acl::insertSync(Calendar calendar, AclRule rule)
{
    _insertRequest->configureAccessToken(_accessToken);
    _insertRequest->configure(calendar, rule);
    _insertRequest->performSync(_operationTimeout);
}

// Async

void Acl::removeAsync(Calendar calendar, int ruleId)
{
    _removeRequest->configureAccessToken(_accessToken);
    _removeRequest->configure(calendar, ruleId);
    _removeRequest->performAsync(_operationTimeout);
}

void Acl::getAsync(Calendar calendar, int ruleId)
{
    _getRequest->configureAccessToken(_accessToken);
    _getRequest->configure(calendar, ruleId);
    _getRequest->performAsync(_operationTimeout);
}

void Acl::insertAsync(Calendar calendar, AclRule rule)
{
    _insertRequest->configureAccessToken(_accessToken);
    _insertRequest->configure(calendar, rule);
    _insertRequest->performASync(_operationTimeout);
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
    emit removeFinished();
}

void Acl::handleGetReply(QNetworkReply* networkReply)
{

    emit getFinished();
}

void Acl::handleInsertReply(QNetworkReply* networkReply)
{
    emit insertFinished();
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

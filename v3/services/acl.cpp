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
    RequestOperationDelegate()
{
    _deleteRequest  = new AclDelete(this, parent);
    _getRequest     = new AclGet(this, parent);
    _insertRequest  = new AclInsert(this, parent);
    _listRequest    = new AclList(this, parent);
    _patchRequest   = new AclPatch(this, parent);
    _updateRequest  = new AclUpdate(this, parent);
    _watchRequest   = new AclWatch(this, parent);
}

bool Acl::deleteB(QString calendarId, QString ruleId, bool& success)
{
    _deleteRequest->setAccessToken(_accessToken);
    _deleteRequest->setParameters(calendarId, ruleId);
    if(_deleteRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return deleteReply(_deleteRequest->networkReply(), success);
    }
    return false;
}

bool Acl::getB(QString calendarId, QString ruleId, AclRule& rule)
{
    _getRequest->setAccessToken(_accessToken);
    _getRequest->setParameters(calendarId, ruleId);
    if(_getRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return getReply(_getRequest->networkReply(), rule);
    }
    return false;
}

bool Acl::insertB(QString calendarId, AclRule &rule)
{
    _insertRequest->setAccessToken(_accessToken);
    _insertRequest->setParameters(calendarId, rule);
    if(_insertRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return insertReply(_insertRequest->networkReply(), rule);
    }
    return false;
}

bool Acl::listB(QString calendarId,
                   QList<AclRule> &list,
                   int maxResults,
                   QString pageToken,
                   bool showDeleted,
                   QString syncToken)
{
    _listRequest->setAccessToken(_accessToken);
    _listRequest->setParameters(calendarId,
                            maxResults,
                            pageToken,
                            showDeleted,
                            syncToken);
    if(_listRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return false;
    }
    return false;
}

bool Acl::patchB(QString calendarId,
                 QString ruleId,
                 AclRule& rule)
{
    _getRequest->setAccessToken(_accessToken);
    _getRequest->setParameters(calendarId,
                               ruleId);
    if(_getRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return patchReply(_patchRequest->networkReply(), rule);
    }
    return false;
}

bool Acl::updateB(QString calendarId,
                  QString ruleId,
                  AclRule& rule)
{
    _updateRequest->setAccessToken(_accessToken);
    _updateRequest->setParameters(calendarId,
                                  ruleId);
    if(_updateRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return updateReply(_updateRequest->networkReply(), rule);
    }
    return false;
}

bool Acl::watchB(QString calendarId)
{
    // TODO: Implement.
    Q_UNUSED(calendarId);
    Q_ASSERT(false);
}

// Async
bool Acl::deleteNB(QString calendarId, QString ruleId)
{
    _deleteRequest->setAccessToken(_accessToken);
    _deleteRequest->setParameters(calendarId, ruleId);
    return _deleteRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::getNB(QString calendarId, QString ruleId)
{
    _getRequest->setAccessToken(_accessToken);
    _getRequest->setParameters(calendarId, ruleId);
    return _getRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::insertNB(QString calendarId, AclRule rule)
{
    _insertRequest->setAccessToken(_accessToken);
    _insertRequest->setParameters(calendarId, rule);
    return _insertRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::listNB(QString calendarId,
                 int maxResults,
                 QString pageToken,
                 bool showDeleted,
                 QString syncToken)
{
    _listRequest->setAccessToken(_accessToken);
    _listRequest->setParameters(calendarId,
                            maxResults,
                            pageToken,
                            showDeleted,
                            syncToken);
    return _listRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::patchNB(QString calendarId, QString ruleId)
{
    _patchRequest->setAccessToken(_accessToken);
    _patchRequest->setParameters(calendarId,
                                 ruleId);
    return _patchRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::updateNB(QString calendarId, QString ruleId)
{
    _updateRequest->setAccessToken(_accessToken);
    _updateRequest->setParameters(calendarId,
                                  ruleId);
    return _updateRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::watchNB(QString calendarId)
{
    // TODO: Implement.
    Q_UNUSED(calendarId);
    Q_ASSERT(false);
}

// APIRequestDelegate
void Acl::handleReplyNonBlocking(RequestOperation *request,
                      QNetworkReply *networkReply)
{
    // Schedule network reply for deletion
    networkReply->deleteLater();

    if(request == _deleteRequest) {
        bool success;
        if(deleteReply(networkReply, success)) {
            emit deleteFinished(success);
        } else {
            emit deleteFailed(errorString());
        }
    } else
    if(request == _getRequest) {
        AclRule rule;
        if(getReply(networkReply, rule)) {
            emit getFinished(rule);
        } else {
            emit getFailed(errorString());
        }
    } else
    if(request == _insertRequest) {
        AclRule rule;
        if(insertReply(networkReply, rule)) {
            emit insertFinished(rule);
        } else {
            emit insertFailed(errorString());
        }
    } else
    if(request == _listRequest) {
        // TODO: Implement.
    } else
    if(request == _patchRequest) {
        AclRule rule;
        if(patchReply(networkReply, rule)) {
            emit patchFinished(rule);
        } else {
            emit patchFailed(errorString());
        }
    } else
    if(request == _updateRequest) {
        AclRule rule;
        if(updateReply(networkReply, rule)) {
            emit updateFinished(rule);
        } else {
            emit updateFailed(errorString());
        }
    } else
    if(request == _watchRequest) {
        // TODO: Implement.
    } else {
        qDebug() << "Warning: Received response for unknown request.";
    }
}

bool Acl::deleteReply(QNetworkReply *networkReply, bool& success)
{
    if(networkReply->error() == QNetworkReply::NoError) {
        success = networkReply->readAll().isEmpty();
        return true;
    } else {
        return false;
    }
}

bool Acl::getReply(QNetworkReply *networkReply, AclRule& rule)
{
    // Check if any network errors occured.
    if(networkReply->error() == QNetworkReply::NoError) {
        // Parse reply
        QJsonDocument replyDocument = QJsonDocument::fromJson(networkReply->readAll());
        if(rule.fromJson(replyDocument.object())) {
            _errorString = "";
            return true;
        } else {
            _errorString = tr("Failed to decode acl rule from json.");
            return false;
        }
    } else {
        _errorString = networkReply->errorString();
        return false;
    }
}

bool Acl::insertReply(QNetworkReply *networkReply, AclRule& rule)
{
    // Check if any network errors occured.
    if(networkReply->error() == QNetworkReply::NoError) {
        // Parse reply
        QJsonDocument replyDocument = QJsonDocument::fromJson(networkReply->readAll());
        if(rule.fromJson(replyDocument.object())) {
            _errorString = "";
            return true;
        } else {
            _errorString = tr("Failed to decode acl rule from json.");
            return false;
        }
    } else {
        _errorString = networkReply->errorString();
        return false;
    }
}

bool Acl::patchReply(QNetworkReply *networkReply, AclRule& rule)
{
    // Check if any network errors occured.
    if(networkReply->error() == QNetworkReply::NoError) {
        // Parse reply
        QJsonDocument replyDocument = QJsonDocument::fromJson(networkReply->readAll());
        if(rule.fromJson(replyDocument.object())) {
            _errorString = "";
            return true;
        } else {
            _errorString = tr("Failed to decode acl rule from json.");
            return false;
        }
    } else {
        _errorString = networkReply->errorString();
        return false;
    }
}

bool Acl::updateReply(QNetworkReply *networkReply, AclRule& rule)
{
    // Check if any network errors occured.
    if(networkReply->error() == QNetworkReply::NoError) {
        // Parse reply
        QJsonDocument replyDocument = QJsonDocument::fromJson(networkReply->readAll());
        if(rule.fromJson(replyDocument.object())) {
            _errorString = "";
            return true;
        } else {
            _errorString = tr("Failed to decode acl rule from json.");
            return false;
        }
    } else {
        _errorString = networkReply->errorString();
        return false;
    }
}

void Acl::requestTimedOut(RequestOperation *request)
{
    Q_UNUSED(request);
    emit requestTimedOut();
}

} // APIV3

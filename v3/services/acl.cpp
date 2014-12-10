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
    _delete  = new AclDelete(this, parent);
    _get     = new AclGet   (this, parent);
    _insert  = new AclInsert(this, parent);
    _list    = new AclList  (this, parent);
    _patch   = new AclPatch (this, parent);
    _update  = new AclUpdate(this, parent);
    _watch   = new AclWatch (this, parent);
}

bool Acl::deleteB(QString calendarId, QString ruleId, bool& success)
{
    _delete->setAccessToken(_accessToken);
    _delete->setParameters(calendarId, ruleId);
    if(_delete->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return deleteReply(_delete->networkReply());
    }
    return false;
}

bool Acl::getB(QString calendarId, QString ruleId, AclRule& rule)
{
    _get->setAccessToken(_accessToken);
    _get->setParameters(calendarId, ruleId);
    if(_get->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return getReply(_get->networkReply(), rule);
    }
    return false;
}

bool Acl::insertB(QString calendarId, AclRule &rule)
{
    _insert->setAccessToken(_accessToken);
    _insert->setParameters(calendarId, rule);
    if(_insert->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return insertReply(_insert->networkReply(), rule);
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
    _list->setAccessToken(_accessToken);
    _list->setParameters(calendarId,
                            maxResults,
                            pageToken,
                            showDeleted,
                            syncToken);
    if(_list->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return false;
    }
    return false;
}

bool Acl::patchB(QString calendarId,
                 QString ruleId,
                 AclRule& rule)
{
    _get->setAccessToken(_accessToken);
    _get->setParameters(calendarId,
                               ruleId);
    if(_get->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return patchReply(_patch->networkReply(), rule);
    }
    return false;
}

bool Acl::updateB(QString calendarId,
                  QString ruleId,
                  AclRule& rule)
{
    _update->setAccessToken(_accessToken);
    _update->setParameters(calendarId,
                                  ruleId);
    if(_update->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return updateReply(_update->networkReply(), rule);
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
    _delete->setAccessToken(_accessToken);
    _delete->setParameters(calendarId, ruleId);
    return _delete->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::getNB(QString calendarId, QString ruleId)
{
    _get->setAccessToken(_accessToken);
    _get->setParameters(calendarId, ruleId);
    return _get->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::insertNB(QString calendarId, AclRule rule)
{
    _insert->setAccessToken(_accessToken);
    _insert->setParameters(calendarId, rule);
    return _insert->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::listNB(QString calendarId,
                 int maxResults,
                 QString pageToken,
                 bool showDeleted,
                 QString syncToken)
{
    _list->setAccessToken(_accessToken);
    _list->setParameters(calendarId,
                            maxResults,
                            pageToken,
                            showDeleted,
                            syncToken);
    return _list->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::patchNB(QString calendarId, QString ruleId)
{
    _patch->setAccessToken(_accessToken);
    _patch->setParameters(calendarId,
                                 ruleId);
    return _patch->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Acl::updateNB(QString calendarId, QString ruleId)
{
    _update->setAccessToken(_accessToken);
    _update->setParameters(calendarId,
                                  ruleId);
    return _update->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
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

    if(request == _delete) {
        bool success;
        if(deleteReply(networkReply)) {
            emit deleteFinished();
        } else {
            emit deleteFailed(errorString());
        }
    } else
    if(request == _get) {
        AclRule rule;
        if(getReply(networkReply, rule)) {
            emit getFinished(rule);
        } else {
            emit getFailed(errorString());
        }
    } else
    if(request == _insert) {
        AclRule rule;
        if(insertReply(networkReply, rule)) {
            emit insertFinished(rule);
        } else {
            emit insertFailed(errorString());
        }
    } else
    if(request == _list) {
        // TODO: Implement.
    } else
    if(request == _patch) {
        AclRule rule;
        if(patchReply(networkReply, rule)) {
            emit patchFinished(rule);
        } else {
            emit patchFailed(errorString());
        }
    } else
    if(request == _update) {
        AclRule rule;
        if(updateReply(networkReply, rule)) {
            emit updateFinished(rule);
        } else {
            emit updateFailed(errorString());
        }
    } else
    if(request == _watch) {
        // TODO: Implement.
    } else {
        qDebug() << "Warning: Received response for unknown request.";
    }
}

bool Acl::deleteReply(QNetworkReply *networkReply)
{
    if(networkReply->error() == QNetworkReply::NoError) {
        return true;
    } else {
        return false;
    }
}

bool Acl::getReply(QNetworkReply *networkReply, AclRule& rule)
{
    return decodeRuleFromReply(networkReply, rule);
}

bool Acl::insertReply(QNetworkReply *networkReply, AclRule& rule)
{
    return decodeRuleFromReply(networkReply, rule);
}

bool Acl::patchReply(QNetworkReply *networkReply, AclRule& rule)
{
    return decodeRuleFromReply(networkReply, rule);
}

bool Acl::updateReply(QNetworkReply *networkReply, AclRule& rule)
{
    return decodeRuleFromReply(networkReply, rule);
}

bool Acl::decodeRuleFromReply(QNetworkReply *networkReply, AclRule& rule)
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

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
#include "calendarlist.h"

// Qt includes
#include <QNetworkReply>

namespace APIV3 {

CalendarList::CalendarList(QObject *parent) :
    Service(parent),
    RequestOperationDelegate()
{
    _delete = new CalendarListDelete(this, parent);
    _get    = new CalendarListGet   (this, parent);
    _insert = new CalendarListInsert(this, parent);
    _list   = new CalendarListList  (this, parent);
    _patch  = new CalendarListPatch (this, parent);
    _update = new CalendarListUpdate(this, parent);
    _watch  = new CalendarListWatch (this, parent);
}


void CalendarList::handleReplyNonBlocking(RequestOperation *request, QNetworkReply *networkReply)
{
    // Schedule network reply for deletion
    networkReply->deleteLater();

    if(request == _delete) {
        if(deleteReply(networkReply)) {
            emit deleteFinished();
        } else {
            emit deleteFailed(errorString());
        }
    } else
    if(request == _get) {
        CalendarListEntry calendarListEntry;
        if(getReply(networkReply, calendarListEntry)) {
            emit getFinished(calendarListEntry);
        } else {
            emit getFailed(errorString());
        }
    } else
    if(request == _insert) {
        CalendarListEntry calendarListEntry;
        if(insertReply(networkReply, calendarListEntry)) {
            emit insertFinished(calendarListEntry);
        } else {
            emit insertFailed(errorString());
        }
    } else
    if(request == _list) {
        // TODO: Implement.
    } else
    if(request == _patch) {
        CalendarListEntry calendarListEntry;
        if(patchReply(networkReply, calendarListEntry)) {
            emit patchFinished(calendarListEntry);
        } else {
            emit patchFailed(errorString());
        }
    } else
    if(request == _update) {
        CalendarListEntry calendarListEntry;
        if(updateReply(networkReply, calendarListEntry)) {
            emit updateFinished(calendarListEntry);
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

void CalendarList::requestTimedOut(RequestOperation *request)
{

}

bool CalendarList::deleteB(QString calendarId, bool& success)
{
    _delete->setAccessToken(_accessToken);
    _delete->setParameters(calendarId);
    if(_delete->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return deleteReply(_delete->networkReply());
    }
    return false;
}

bool CalendarList::getB(QString calendarId, CalendarListEntry &calendarListEntry)
{
    _get->setAccessToken(_accessToken);
    _get->setParameters(calendarId);
    if(_get->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return getReply(_get->networkReply(), calendarListEntry);
    }
    return false;
}

bool CalendarList::insertB(CalendarListEntry &calendarListEntry)
{
    _insert->setAccessToken(_accessToken);
    _insert->setParameters(calendarListEntry);
    if(_insert->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return insertReply(_insert->networkReply(), calendarListEntry);
    }
    return false;
}

bool CalendarList::listB(QList<CalendarListEntry>& list,
                         int maxResults,
                         QString pageToken,
                         bool showDeleted,
                         QString syncToken)
{
    Q_UNUSED(list);
    Q_UNUSED(maxResults);
    Q_UNUSED(pageToken);
    Q_UNUSED(showDeleted);
    Q_UNUSED(syncToken);
    // TODO: Implement.
    return false;
}

bool CalendarList::patchB(QString calendarId, CalendarListEntry &calendarListEntry)
{
    _patch->setAccessToken(_accessToken);
    _patch->setParameters(calendarId, calendarListEntry);
    if(_patch->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return patchReply(_patch->networkReply(), calendarListEntry);
    }
    return false;
}

bool CalendarList::updateB(QString calendarId, CalendarListEntry &calendarListEntry)
{
    _update->setAccessToken(_accessToken);
    _update->setParameters(calendarId, calendarListEntry);
    if(_update->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return updateReply(_update->networkReply(), calendarListEntry);
    }
    return false;
}

bool CalendarList::watchB()
{
    // TODO: Implement.
    return false;
}

bool CalendarList::deleteNB(QString calendarId)
{
    _delete->setAccessToken(_accessToken);
    _delete->setParameters(calendarId);
    return _delete->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool CalendarList::getNB(QString calendarId)
{
    _get->setAccessToken(_accessToken);
    _get->setParameters(calendarId);
    return _get->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool CalendarList::insertNB(CalendarListEntry calendarListEntry)
{
    _insert->setAccessToken(_accessToken);
    _insert->setParameters(calendarListEntry);
    return _insert->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool CalendarList::listNB(int maxResults,
                          QString pageToken,
                          bool showDeleted,
                          QString syncToken)
{
    Q_UNUSED(maxResults);
    Q_UNUSED(pageToken);
    Q_UNUSED(showDeleted);
    Q_UNUSED(syncToken);

    // TODO: Implement.
    return false;
}

bool CalendarList::patchNB(QString calendarId, CalendarListEntry calendarListEntry)
{
    _patch->setAccessToken(_accessToken);
    _patch->setParameters(calendarId, calendarListEntry);
    return _patch->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool CalendarList::updateNB(QString calendarId, CalendarListEntry calendarListEntry)
{
    _patch->setAccessToken(_accessToken);
    _patch->setParameters(calendarId, calendarListEntry);
    return _patch->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool CalendarList::watchNB()
{
    // TODO: Implement.
    return false;
}

bool CalendarList::deleteReply(QNetworkReply* networkReply)
{
    if(networkReply->error() == QNetworkReply::NoError) {
        return true;
    } else {
        return false;
    }
}

bool CalendarList::getReply(QNetworkReply* networkReply, CalendarListEntry& calendarListEntry)
{
    return decodeCalendarListFromReply(networkReply, calendarListEntry);
}

bool CalendarList::insertReply(QNetworkReply* networkReply, CalendarListEntry &calendarListEntry)
{
    return decodeCalendarListFromReply(networkReply, calendarListEntry);
}

bool CalendarList::listReply(QNetworkReply* networkReply)
{
    // TODO: Implement.
    return false;
}

bool CalendarList::patchReply(QNetworkReply* networkReply, CalendarListEntry &calendarListEntry)
{
    return decodeCalendarListFromReply(networkReply, calendarListEntry);
}

bool CalendarList::updateReply(QNetworkReply* networkReply, CalendarListEntry& calendarListEntry)
{
    return decodeCalendarListFromReply(networkReply, calendarListEntry);
}

bool CalendarList::watchReply(QNetworkReply* networkReply)
{
    // TODO: Implement.
    return false;
}

bool CalendarList::decodeCalendarListFromReply(QNetworkReply* networkReply, CalendarListEntry &calendarListEntry)
{
    // Check if any network errors occured.
    if(networkReply->error() == QNetworkReply::NoError) {
        // Parse reply
        QJsonDocument replyDocument = QJsonDocument::fromJson(networkReply->readAll());
        if(calendarListEntry.fromJson(replyDocument.object())) {
            _errorString = "";
            return true;
        } else {
            _errorString = tr("Failed to decode calendar list from json.");
            return false;
        }
    } else {
        _errorString = networkReply->errorString();
        return false;
    }
}


} // APIV3

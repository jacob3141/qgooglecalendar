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
}


void CalendarList::handleReplyNonBlocking(RequestOperation *request, QNetworkReply *networkReply)
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
        Calendar calendar;
        if(getReply(networkReply, calendar)) {
            emit getFinished(calendar);
        } else {
            emit getFailed(errorString());
        }
    } else
    if(request == _insertRequest) {
        Calendar calendar;
        if(insertReply(networkReply, calendar)) {
            emit insertFinished(calendar);
        } else {
            emit insertFailed(errorString());
        }
    } else
    if(request == _listRequest) {
        // TODO: Implement.
    } else
    if(request == _patchRequest) {
        Calendar calendar;
        if(patchReply(networkReply, calendar)) {
            emit patchFinished(calendar);
        } else {
            emit patchFailed(errorString());
        }
    } else
    if(request == _updateRequest) {
        Calendar calendar;
        if(updateReply(networkReply, calendar)) {
            emit updateFinished(calendar);
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

void CalendarList::requestTimedOut(RequestOperation *request)
{

}

bool CalendarList::deleteB(QString calendarId, bool& success)
{
    _deleteRequest->setAccessToken(_accessToken);
    _deleteRequest->setParameters(calendarId);
    if(_deleteRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return deleteReply(_deleteRequest->networkReply(), success);
    }
    return false;
}

bool CalendarList::getB(QString calendarId, Calendar& calendar)
{
    _getRequest->setAccessToken(_accessToken);
    _getRequest->setParameters(calendarId);
    if(_getRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return getReply(_getRequest->networkReply(), calendar);
    }
    return false;
}

bool CalendarList::insertB(Calendar& calendar)
{
    _insertRequest->setAccessToken(_accessToken);
    _insertRequest->setParameters(calendar);
    if(_insertRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return insertReply(_insertRequest->networkReply(), calendar);
    }
    return false;
}

bool CalendarList::listB(QList<Calendar>& list,
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

bool CalendarList::patchB(QString calendarId, Calendar& calendar)
{
    _patchRequest->setAccessToken(_accessToken);
    _patchRequest->setParameters(calendarId, calendar);
    if(_patchRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return patchReply(_patchRequest->networkReply(), calendar);
    }
    return false;
}

bool CalendarList::updateB(QString calendarId, Calendar& calendar)
{
    _updateRequest->setAccessToken(_accessToken);
    _updateRequest->setParameters(calendarId, calendar);
    if(_updateRequest->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return updateReply(_updateRequest->networkReply(), calendar);
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
    _deleteRequest->setAccessToken(_accessToken);
    _deleteRequest->setParameters(calendarId);
    return _deleteRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool CalendarList::getNB(QString calendarId)
{
    _getRequest->setAccessToken(_accessToken);
    _getRequest->setParameters(calendarId);
    _getRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool CalendarList::insertNB(Calendar calendar)
{
    _insertRequest->setAccessToken(_accessToken);
    _insertRequest->setParameters(calendar);
    _insertRequest->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
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

bool CalendarList::patchNB(QString calendarId)
{

}

bool CalendarList::updateNB(QString calendarId)
{

}

bool CalendarList::watchNB()
{

}

bool CalendarList::deleteReply(QNetworkReply* networkReply, bool& success)
{

}

bool CalendarList::getReply(QNetworkReply* networkReply, Calendar& calendar)
{

}

bool CalendarList::insertReply(QNetworkReply* networkReply, Calendar& calendar)
{

}

bool CalendarList::listReply(QNetworkReply* networkReply)
{

}

bool CalendarList::patchReply(QNetworkReply* networkReply, Calendar& calendar)
{

}

bool CalendarList::updateReply(QNetworkReply* networkReply, Calendar& calendar)
{

}

bool CalendarList::watchReply(QNetworkReply* networkReply)
{

}

} // APIV3

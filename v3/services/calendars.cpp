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
#include "calendars.h"

namespace APIV3 {

Calendars::Calendars(QObject *parent) :
    Service(parent),
    RequestOperationDelegate()
{
    _clear  = new CalendarsClear    (this, parent);
    _delete = new CalendarsDelete   (this, parent);
    _get    = new CalendarsGet      (this, parent);
    _insert = new CalendarsInsert   (this, parent);
    _patch  = new CalendarsPatch    (this, parent);
    _update = new CalendarsUpdate   (this, parent);
}

void Calendars::handleReplyNonBlocking(RequestOperation *request,
                                       QNetworkReply *networkReply)
{
    // Schedule network reply for deletion
    networkReply->deleteLater();

    if(request == _clear) {
        if(clearReply(networkReply)) {
            emit clearFinished();
        } else {
            emit clearFailed(errorString());
        }
    } else
    if(request == _delete) {
        if(deleteReply(networkReply)) {
            emit deleteFinished();
        } else {
            emit deleteFailed(errorString());
        }
    } else
    if(request == _get) {
        Calendar calendar;
        if(getReply(networkReply, calendar)) {
            emit getFinished(calendar);
        } else {
            emit getFailed(errorString());
        }
    } else
    if(request == _insert) {
        Calendar calendar;
        if(insertReply(networkReply, calendar)) {
            emit insertFinished(calendar);
        } else {
            emit insertFailed(errorString());
        }
    } else
    if(request == _patch) {
        Calendar calendar;
        if(patchReply(networkReply, calendar)) {
            emit patchFinished(calendar);
        } else {
            emit patchFailed(errorString());
        }
    } else
    if(request == _update) {
        Calendar calendar;
        if(updateReply(networkReply, calendar)) {
            emit updateFinished(calendar);
        } else {
            emit updateFailed(errorString());
        }
    } else {
        qDebug() << "Warning: Received response for unknown request";
    }
}

void Calendars::requestTimedOut(RequestOperation *request)
{
}

// Blocking methods

bool Calendars::clearB(QString calendarId)
{
    _clear->setAccessToken(_accessToken);
    _clear->setParameters(calendarId);
    if(_clear->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return clearReply(_clear->networkReply());
    }
    return false;
}

bool Calendars::deleteB(QString calendarId)
{
    _delete->setAccessToken(_accessToken);
    _delete->setParameters(calendarId);
    if(_clear->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return deleteReply(_clear->networkReply());
    }
    return false;
}

bool Calendars::getB(QString calendarId, Calendar &calendar)
{
    _get->setAccessToken(_accessToken);
    _get->setParameters(calendarId);
    if(_get->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return getReply(_get->networkReply(), calendar);
    }
    return false;
}

bool Calendars::insertB(Calendar& calendar)
{
    _insert->setAccessToken(_accessToken);
    _insert->setParameters(calendar);
    if(_insert->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return insertReply(_insert->networkReply(), calendar);
    }
    return false;
}

bool Calendars::patchB(QString calendarId, Calendar& calendar)
{
    _patch->setAccessToken(_accessToken);
    _patch->setParameters(calendarId, calendar);
    if(_patch->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return patchReply(_patch->networkReply(), calendar);
    }
    return false;
}

bool Calendars::updateB(QString calendarId, Calendar& calendar)
{
    _update->setAccessToken(_accessToken);
    _update->setParameters(calendarId, calendar);
    if(_update->perform(RequestOperation::PerformModeBlocking, _operationTimeout)) {
        return updateReply(_update->networkReply(), calendar);
    }
    return false;
}

// Non-blocking methods

bool Calendars::clearNB(QString calendarId)
{
    _clear->setAccessToken(_accessToken);
    _clear->setParameters(calendarId);
    return _clear->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Calendars::deleteNB(QString calendarId)
{
    _delete->setAccessToken(_accessToken);
    _delete->setParameters(calendarId);
    return _delete->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Calendars::getNB(QString calendarId)
{
    _get->setAccessToken(_accessToken);
    _get->setParameters(calendarId);
    return _get->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Calendars::insertNB(Calendar calendar)
{
    _insert->setAccessToken(_accessToken);
    _insert->setParameters(calendar);
    return _insert->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Calendars::patchNB(QString calendarId, Calendar calendar)
{
    _patch->setAccessToken(_accessToken);
    _patch->setParameters(calendarId, calendar);
    return _patch->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

bool Calendars::updateNB(QString calendarId, Calendar calendar)
{
    _update->setAccessToken(_accessToken);
    _update->setParameters(calendarId, calendar);
    return _update->perform(RequestOperation::PerformModeNonBlocking, _operationTimeout);
}

// Reply handlers

bool Calendars::clearReply(QNetworkReply *networkReply)
{
    if(networkReply->error() == QNetworkReply::NoError) {
        return true;
    } else {
        return false;
    }
}

bool Calendars::deleteReply(QNetworkReply *networkReply)
{
    if(networkReply->error() == QNetworkReply::NoError) {
        return true;
    } else {
        return false;
    }
}

bool Calendars::getReply(QNetworkReply *networkReply, Calendar& calendar)
{
    return decodeCalendarFromReply(networkReply, calendar);
}

bool Calendars::insertReply(QNetworkReply *networkReply, Calendar& calendar)
{
    return decodeCalendarFromReply(networkReply, calendar);
}

bool Calendars::patchReply(QNetworkReply *networkReply, Calendar& calendar)
{
    return decodeCalendarFromReply(networkReply, calendar);
}

bool Calendars::updateReply(QNetworkReply *networkReply, Calendar& calendar)
{
    return decodeCalendarFromReply(networkReply, calendar);
}

bool Calendars::decodeCalendarFromReply(QNetworkReply *networkReply, Calendar &calendar)
{
    // Check if any network errors occured.
    if(networkReply->error() == QNetworkReply::NoError) {
        // Parse reply
        QJsonDocument replyDocument = QJsonDocument::fromJson(networkReply->readAll());
        if(calendar.fromJson(replyDocument.object())) {
            _errorString = "";
            return true;
        } else {
            _errorString = tr("Failed to decode calendar from json.");
            return false;
        }
    } else {
        _errorString = networkReply->errorString();
        return false;
    }
}

} // APIV3

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

namespace APIV3 {

CalendarList::CalendarList(QObject *parent) :
    Service(parent),
    RequestDelegate()
{
}

// Synchronous methods, blocking
bool CalendarList::removeSync(Calendar calendar, int ruleId)
{

}

AclRule CalendarList::getSync(Calendar calendar, int ruleId)
{

}

int CalendarList::insertSync(Calendar calendar, AclRule rule)
{

}

// list
// patch
// update
// watch

// Asynchronous methods, non-blocking
void CalendarList::removeAsync(Calendar calendar, int ruleId)
{

}

void CalendarList::getAsync(Calendar calendar, int ruleId)
{

}

void CalendarList::insertAsync(Calendar calendar, AclRule rule)
{

}

// list
// patch
// update
// watch


void CalendarList::handleReply(Request *request, QNetworkReply *networkReply)
{

}

void CalendarList::requestTimedOut(Request *request)
{

}

void CalendarList::handleRemoveReply(QNetworkReply* networkReply)
{

}

void CalendarList::handleGetReply(QNetworkReply* networkReply)
{

}

void CalendarList::handleInsertReply(QNetworkReply* networkReply)
{

}

void CalendarList::handleListReply(QNetworkReply* networkReply)
{

}

void CalendarList::handlePatchReply(QNetworkReply* networkReply)
{

}

void CalendarList::handleUpdateReply(QNetworkReply* networkReply)
{

}

void CalendarList::handleWatchReply(QNetworkReply* networkReply)
{

}

} // APIV3

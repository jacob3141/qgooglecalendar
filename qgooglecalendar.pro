################################################################################
##                                                                            ##
## This file is part of QGoogleCalendar.                                      ##
## Copyright (c) 2014 Jacob Dawid <jacob@omg-it.works>                        ##
##                                                                            ##
## QGoogleCalendar is free software: you can redistribute it and/or modify    ##
## it under the terms of the GNU Affero General Public License as             ##
## published by the Free Software Foundation, either version 3 of the         ##
## License, or (at your option) any later version.                            ##
##                                                                            ##
## QGoogleCalendar is distributed in the hope that it will be useful,         ##
## but WITHOUT ANY WARRANTY; without even the implied warranty of             ##
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              ##
## GNU Affero General Public License for more details.                        ##
##                                                                            ##
## You should have received a copy of the GNU Affero General Public           ##
## License along with QGoogleCalendar.                                        ##
## If not, see <http://www.gnu.org/licenses/>.                                ##
##                                                                            ##
################################################################################

QT       += core network
QT       -= gui

TEMPLATE = lib
CONFIG += staticlib flat

TARGET = qgooglecalendar

HEADERS += \
    googlecalendarservice.h \
    v3/resources/calendarlistentry.h \
    v3/resources/aclrule.h \
    v3/resources/calendar.h \
    v3/resources/setting.h \
    v3/resources/resource.h \
    v3/services/acl.h \
    v3/services/calendars.h \
    v3/services/calendarlist.h \
    v3/services/settings.h \
    v3/services/channels.h \
    v3/services/colors.h \
    v3/services/events.h \
    v3/services/freebusy.h \
    v3/resources/color.h \
    v3/resources/event.h \
    v3/services/service.h \
    v3/services/requestdelegate.h \
    v3/services/requests/requestoperation.h \
    v3/services/requests/aclget.h \
    v3/services/requests/aclinsert.h \
    v3/services/requests/acllist.h \
    v3/services/requests/aclpatch.h \
    v3/services/requests/aclupdate.h \
    v3/services/requests/aclwatch.h \
    v3/services/requests/calendarlistget.h \
    v3/services/requests/calendarlistinsert.h \
    v3/services/requests/calendarlistlist.h \
    v3/services/requests/calendarlistpatch.h \
    v3/services/requests/calendarlistupdate.h \
    v3/services/requests/calendarlistwatch.h \
    v3/services/requests/acldelete.h \
    v3/services/requests/calendarlistdelete.h \
    v3/services/requests/calendarsclear.h \
    v3/services/requests/calendarsdelete.h \
    v3/services/requests/calendarsget.h \
    v3/services/requests/calendarsinsert.h \
    v3/services/requests/calendarspatch.h \
    v3/services/requests/calendarsupdate.h \
    v3/services/requests/channelsstop.h \
    v3/services/requests/colorsget.h \
    v3/services/requests/eventsdelete.h \
    v3/services/requests/eventsget.h \
    v3/services/requests/eventsimport.h \
    v3/services/requests/eventsinsert.h \
    v3/services/requests/eventsinstances.h \
    v3/services/requests/eventslist.h \
    v3/services/requests/eventsmove.h \
    v3/services/requests/eventspatch.h \
    v3/services/requests/eventsquickadd.h \
    v3/services/requests/eventsupdate.h \
    v3/services/requests/eventswatch.h \
    v3/services/requests/freebusyquery.h \
    v3/services/requests/settingsget.h \
    v3/services/requests/settingslist.h \
    v3/services/requests/settingswatch.h

SOURCES += \
    googlecalendarservice.cpp \
    v3/resources/calendarlistentry.cpp \
    v3/resources/aclrule.cpp \
    v3/resources/calendar.cpp \
    v3/resources/setting.cpp \
    v3/services/acl.cpp \
    v3/services/calendars.cpp \
    v3/services/calendarlist.cpp \
    v3/services/settings.cpp \
    v3/services/channels.cpp \
    v3/services/events.cpp \
    v3/services/freebusy.cpp \
    v3/services/colors.cpp \
    v3/resources/color.cpp \
    v3/resources/event.cpp \
    v3/services/service.cpp \
    v3/services/requests/requestoperation.cpp


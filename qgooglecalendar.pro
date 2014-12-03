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
CONFIG += static

TARGET = libqgooglecalendar

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
    v3/services/requests/request.h \
    v3/services/requests/aclremoverequest.h \
    v3/services/requestdelegate.h \
    v3/services/requests/aclgetrequest.h \
    v3/services/requests/aclinsertrequest.h \
    v3/services/requests/acllistrequest.h \
    v3/services/requests/aclpatchrequest.h \
    v3/services/requests/aclupdaterequest.h \
    v3/services/requests/aclwatchrequest.h \
    v3/services/requests/calendarlistremoverequest.h \
    v3/services/requests/calendarlistgetrequest.h \
    v3/services/requests/calendarlistinsertrequest.h \
    v3/services/requests/calendarlistlistrequest.h \
    v3/services/requests/calendarlistpatchrequest.h \
    v3/services/requests/calendarlistupdaterequest.h \
    v3/services/requests/calendarlistwatchrequest.h

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
    v3/services/requests/request.cpp


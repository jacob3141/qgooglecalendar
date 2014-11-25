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
    resourcesAPIV3/colors.h \
    resourcesAPIV3/events.h \
    resourcesAPIV3/freebusy.h \
    resourcesAPIV3/calendarlistentry.h \
    resourcesAPIV3/aclrule.h \
    resourcesAPIV3/calendar.h \
    resourcesAPIV3/setting.h

SOURCES += \
    googlecalendarservice.cpp \
    resourcesAPIV3/colors.cpp \
    resourcesAPIV3/events.cpp \
    resourcesAPIV3/freebusy.cpp \
    resourcesAPIV3/calendarlistentry.cpp \
    resourcesAPIV3/aclrule.cpp \
    resourcesAPIV3/calendar.cpp \
    resourcesAPIV3/setting.cpp


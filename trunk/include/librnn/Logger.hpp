/**************************************************************************
 *                                                                        *
 * This file is part of librnn. Copyright (C) 2003-2006 Keyan Zahedi.     *
 * All rights reserved. Email: keyan@users.sourceforge.net                *
 * Web: http://sourceforge.net/projects/librnn                            *
 *                                                                        *
 * For a list of contributors see the file AUTHORS.                       *
 *                                                                        *
 * librnn is free software; you can redistribute it and/or modify it      *
 * under the terms of the GNU General Public License as published by the  *
 * Free Software Foundation; either version 2 of the License, or (at      *
 * your option) any later version.                                        *
 *                                                                        *
 * librnn is distributed in the hope that it will be useful, but WITHOUT  *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or  *
 * FITNESS FOR A PARTICULAR PURPOSE.                                      *
 *                                                                        *
 * You should have received a copy of the GNU General Public License      *
 * along with librnn in the file COPYING; if not, write to the Free       *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA     *
 * 02110-1301, USA.                                                       *
 *                                                                        *
 **************************************************************************/



#ifndef __LIBRNN_LOGGER_H__
#define __LIBRNN_LOGGER_H__

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/PatternLayout.hh>

static log4cpp::Category& libRnnLogger = log4cpp::Category::getInstance("libRnnLogger");

static bool _loggerDefined = false;

extern "C" 
{
  static void initLogger()
  {
    if(_loggerDefined)
    {
      libRnnLogger.debug("Logger::initLogger already called. Not calling anymore.");
      return;
    }
    _loggerDefined = true;
    time_t    time_now;
    struct tm *time_ptr;
    char       string[1024];

    time(&time_now);  
    time_ptr = gmtime(&time_now);

    strftime(string, 1024, "logs/librnn-%F-%H-%M-%S.log", time_ptr);
    log4cpp::Appender* app2 = new log4cpp::FileAppender("stdout", fileno(stdout));
    log4cpp::Appender* app  = new log4cpp::FileAppender("FileAppender", string);
    log4cpp::Layout* layout = new log4cpp::PatternLayout();
    app2->setLayout(layout);
    libRnnLogger.setAdditivity(false);
    libRnnLogger.setAppender(app2);
    libRnnLogger.addAppender(app);
    libRnnLogger.setPriority(log4cpp::Priority::FATAL);

  }
}

#endif // __LIBRNN_LOGGER_H__

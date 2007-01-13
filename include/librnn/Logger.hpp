#ifndef __LIBRNN_LOGGER_H__
#define __LIBRNN_LOGGER_H__

#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/BasicLayout.hh>

static log4cpp::Category& libRnnLogger = log4cpp::Category::getInstance("libRnnLogger");

static bool _loggerDefined = false;

extern "C" 
{
  static void initLogger()
  {
    if(_loggerDefined)
    {
      printf("not calling anymore\n");
      return;
    }
    printf("calling again\n");
    _loggerDefined = true;
    time_t    time_now;
    struct tm *time_ptr;
    char       string[1024];

    time(&time_now);     /* get time in seconds */

    /* display local time     */
    //pritnf("%s\n\n", asctime(localtime(&time_now)));    

    /* custom build the format of the date/ time */
    time_ptr = gmtime(&time_now);

    strftime(string, 1024, "logs/librnn-%F-%H-%M-%S.log", time_ptr);

    /* display new format string */
    //printf("logfile:%s\n\n", string);
    // 1 instantiate an appender object that 
    // will append to a log file
    log4cpp::Appender* app  = new log4cpp::FileAppender("FileAppender", string);
    log4cpp::Appender* app2 = new log4cpp::FileAppender("stdout", fileno(stdout));

    // 2. Instantiate a layout object
    // Two layouts come already available in log4cpp
    // unless you create your own.
    // BasicLayout includes a time stamp
    log4cpp::Layout* layout = new log4cpp::BasicLayout();

    // 3. attach the layout object to the 
    // appender object
    app->setLayout(layout);

    // 4. Instantiate the category object
    // you may extract the root category, but it is
    // usually more practical to directly instance
    // a child category

    // 5. Step 1 
    // an Appender when added to a category becomes
    // an additional output destination unless 
    // Additivity is set to false when it is false,
    // the appender added to the category replaces
    // all previously existing appenders
    libRnnLogger.setAdditivity(false);

    // 5. Step 2
    // this appender becomes the only one
    libRnnLogger.setAppender(app);
    libRnnLogger.addAppender(app2);

    // 6. Set up the priority for the category
    // and is given INFO priority
    // attempts to log DEBUG messages will fail
    libRnnLogger.setPriority(log4cpp::Priority::DEBUG);

  }
}

#endif // __LIBRNN_LOGGER_H__

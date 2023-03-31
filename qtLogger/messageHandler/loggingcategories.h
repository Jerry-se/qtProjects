#ifndef LOGGINGCATEGORIES_H
#define LOGGINGCATEGORIES_H

#include <QLoggingCategory>

Q_DECLARE_LOGGING_CATEGORY(logDebug)
Q_DECLARE_LOGGING_CATEGORY(logInfo)
Q_DECLARE_LOGGING_CATEGORY(logWarning)
Q_DECLARE_LOGGING_CATEGORY(logFatal)

class LoggingCategories
{
public:
    LoggingCategories();
};

#endif // LOGGINGCATEGORIES_H

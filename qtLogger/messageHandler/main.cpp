#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <QMutex>

#include "loggingcategories.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // static QMutex mutex;
    // mutex.lock();
    QString errType;
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        errType = QString("Debug");
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        errType = QString("Info");
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        errType = QString("Warning");
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        errType = QString("Critical");
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        errType = QString("Fatal");
        break;
    }
    errType = context.category;
    QString dt = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString strMessage = QString("%1 \t%2 \t%3 | %4 | %5 : %6").arg(errType).arg(dt).arg(file).arg(context.line).arg(function).arg(localMsg.constData());
    QFile outFile("test.log");
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream fileStream(&outFile);
        fileStream << strMessage << "\n";
        fileStream.flush();
    }
    // mutex.unlock();
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    qDebug() << "application start";
    qDebug("Debug log message from Qt test program");
    qInfo("Info log message from Qt test program");
    qWarning("Warning log message from Qt test program");
    qCritical("Critical log message from Qt test program");

    // test logging category
    qDebug(logDebug()) << "Debug log message from Qt test program";
    qInfo(logInfo()) << "Info log message from Qt test program";
    qWarning(logWarning()) << "Warning log message from Qt test program";
    qCritical(logFatal()) << "Critical log message from Qt test program";
    // Causes program to abort. Uncomment to test.
    // qFatal("Fatal log message from Qt test program");
    // QCoreApplication a(argc, argv);

    // return a.exec();
    qDebug() << "application over";
}

#include "tarsnapcli.h"

#include <QDebug>

TarsnapCLI::TarsnapCLI(QUuid uuid, QObject *parent) : QObject(), _uuid(uuid), _process(NULL), _requiresPassword(false)
{
    Q_UNUSED(parent)
    _thread.start();
    moveToThread(&_thread);
    _process.moveToThread(&_thread);

    _process.setProcessChannelMode( QProcess::MergedChannels );
    connect(&_process, SIGNAL(started()), this, SIGNAL(clientStarted()));
    connect(&_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readProcessOutput()));
    connect(&_process, SIGNAL(finished(int, QProcess::ExitStatus)), this,
             SLOT(processFinished(int, QProcess::ExitStatus)));
    connect(&_process, SIGNAL(error(QProcess::ProcessError)), this,
             SLOT(processError(QProcess::ProcessError)));
}

TarsnapCLI::~TarsnapCLI()
{
    killClient();
    _thread.quit();
    _thread.wait();
}
QString TarsnapCLI::command() const
{
    return _command;
}

void TarsnapCLI::setCommand(const QString &command)
{
    _command = command;
}
QStringList TarsnapCLI::arguments() const
{
    return _arguments;
}

void TarsnapCLI::setArguments(const QStringList &arguments)
{
    _arguments = arguments;
}

void TarsnapCLI::runClient()
{
    _process.setProgram(_command);
    _process.setArguments(_arguments);
    qDebug().noquote() << "Running command: " << _process.program() << _process.arguments();
    _process.start();
    if(_requiresPassword)
    {
        QByteArray password( _password.toUtf8() + "\n" );
        _process.write( password.data(), password.size() );
    }
}

void TarsnapCLI::killClient()
{
    if(_process.state() == QProcess::Running)
    {
        _process.terminate();
        if(false == _process.waitForFinished(1000))
            _process.kill();
    }
}

QProcess::ProcessState TarsnapCLI::statusClient()
{
    return _process.state();
}

bool TarsnapCLI::waitForClient()
{
    return _process.waitForFinished(-1);
}

void TarsnapCLI::readProcessOutput()
{
    _processOutput.append(_process.readAll());
}

void TarsnapCLI::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << QString::fromStdString(_processOutput.toStdString());
    qDebug() << "Tarsnap process finished with return code " << exitCode << ".";
    QString message;
    switch (exitStatus) {
    case QProcess::NormalExit:
        break;
    case QProcess::CrashExit:
        message = tr("Tarsnap CLI process crashed.");
        break;
    }
    emit clientFinished(exitCode, message, QString(_processOutput));
}

void TarsnapCLI::processError(QProcess::ProcessError error)
{
    qDebug() << "Tarsnap process error " << error << " occured.";
}
QUuid TarsnapCLI::uuid() const
{
    return _uuid;
}

void TarsnapCLI::setUuid(const QUuid &uuid)
{
    _uuid = uuid;
}


bool TarsnapCLI::requiresPassword() const
{
    return _requiresPassword;
}

void TarsnapCLI::setRequiresPassword(bool requiresPassword)
{
    _requiresPassword = requiresPassword;
}

QString TarsnapCLI::password() const
{
    return _password;
}

void TarsnapCLI::setPassword(const QString &password)
{
    _password = password;
}





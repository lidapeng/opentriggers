#ifndef CTHREADDATA_H
#define CTHREADDATA_H

#include <QThread>

class CThreadData : public QThread
{
    Q_OBJECT
public:
    explicit CThreadData(QObject *parent = 0);

signals:

public slots:

};

#endif // CTHREADDATA_H

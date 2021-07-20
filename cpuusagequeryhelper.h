#ifndef CPUUSAGEQUERYHELPER_H
#define CPUUSAGEQUERYHELPER_H
#include <QThread>
#include <pdh.h>
#include <pdhmsg.h>
#include <QDebug>
#include <Windows.h>


class CpuUsageQueryHelper :public QThread
{
public:
    explicit CpuUsageQueryHelper(QObject* parent = nullptr):QThread(parent),m_flag(true),
        m_query(nullptr),m_cpucounter(nullptr)
    {
        PDH_STATUS status = PdhOpenQuery(NULL, NULL, &m_query);
        if (status != ERROR_SUCCESS)
        {
            qDebug() << "Open Query Error \n";
            m_flag = false;
            return;
        }

        status = PdhAddCounter(m_query, LPCWSTR(L"\\Processor Information(_Total)\\% Processor Time"), NULL, &m_cpucounter);

        if (status != ERROR_SUCCESS)
        {
            qDebug() << "Add Query Counter Error \n";
            PdhCloseQuery(m_query);
            m_flag = false;
            return;
        }
    }
    ~CpuUsageQueryHelper(){}

    void StopQuery()
    {
        m_flag = false;
    }

    double GetCpuUsage()
    {
        return m_cpuusage;
    }
private:
    void run();
private:

    bool m_flag;

    HANDLE m_query;
    HANDLE m_cpucounter;

    double m_cpuusage;
};

#endif // CPUUSAGEQUERYHELPER_H

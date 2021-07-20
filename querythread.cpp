#include "cpuusagequeryhelper.h"

void CpuUsageQueryHelper::run()
{

    if(m_query)
    {
        while(m_flag)
        {
            PdhCollectQueryData(m_query);
            Sleep(1000);
            PdhCollectQueryData(m_query);

            PDH_FMT_COUNTERVALUE pdhValue;
            DWORD dwValue;

            PdhGetFormattedCounterValue(m_cpucounter,PDH_FMT_DOUBLE,&dwValue,&pdhValue);

            m_cpuusage = pdhValue.doubleValue;
        }
    }


}
 

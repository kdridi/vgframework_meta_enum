#include "core/Precomp.h"
#include "Logger.h"
#include "core/Math/Math.h"

namespace vg::core
{
    //--------------------------------------------------------------------------------------
    void Logger::Init()
    {

    }

    //--------------------------------------------------------------------------------------
    void Logger::Deinit()
    {

    }

    //--------------------------------------------------------------------------------------
    void Logger::Log(Level _level, const char * _format, ...)
    {
        const int bufferSize = 4096;
        char tempBuffer[bufferSize];

        if (_format)
        {
            tempBuffer[0] = 0;
            va_list args;
            va_start(args, _format);
            vsnprintf_s(tempBuffer, bufferSize - 1, _format, args);
            log(_level, tempBuffer);
            va_end(args);
        }        
    }  

    //--------------------------------------------------------------------------------------
    void Logger::Clear()
    {
        Lock();
        {
            m_entries.clear();
        }
        Unlock();
    }

    //--------------------------------------------------------------------------------------
    void Logger::Lock()
    {
        m_mutex.lock();
    }

    //--------------------------------------------------------------------------------------
    void Logger::Unlock()
    {
        m_mutex.unlock();
    }

    //--------------------------------------------------------------------------------------
    const uint Logger::GetLogCount() const
    {
        return (uint)m_entries.size();
    }

    //--------------------------------------------------------------------------------------
    const LogEntry & Logger::GetLog(uint _index) const
    {
        return m_entries[_index];
    }

    //--------------------------------------------------------------------------------------
    void Logger::log(Level _level, const char * _msg)
    {
        Lock();
        {
            VG_DEBUGPRINT("[%s] %s\n", asString(_level).c_str(), _msg);

            string category;
            string message = _msg;
            auto begin = message.find('[');
            if (!begin)
            {
                auto end = message.find(']', 1);
                if (string::npos != end)
                {
                    category = message.substr(begin + 1, end - begin - 1);
                    message = message.substr(end + 1);
                }
            }
            auto first = message.find_first_not_of(" \t");
            if (string::npos != first)
                message = message.substr(first);

            u64 crc = computeCRC64(message.c_str(), message.length());
            size_t index = -1;
            for (uint i = 0; i < m_entries.size(); ++i)
            {
                if (m_entries[i].crc == crc)
                {
                    index = i;
                    break;
                }
            }

            if (-1 == index)
            {
                m_entries.emplace_back(LogEntry{ crc, _level, category, message, 1 });
            }
            else
            {
                LogEntry entry = m_entries[index];
                m_entries.erase(m_entries.begin() + index);
                entry.count++;
                m_entries.push_back(entry);
            }
        }
        Unlock();
    }
}
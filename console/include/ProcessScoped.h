#pragma once

#include "common.h"

namespace LAB
{
    class ProcessScoped final {
    public:

        //--------------------------

        explicit ProcessScoped(const std::wstring& filename, STARTUPINFO si = { .cb = sizeof(STARTUPINFO) });

        //--------------------------

        ProcessScoped(const ProcessScoped&) = delete;

        //--------------------------

        ProcessScoped(ProcessScoped&&) = delete;

        //--------------------------

        ProcessScoped& operator = (const ProcessScoped&) = delete;

        //--------------------------

        ProcessScoped& operator = (ProcessScoped&&) = delete;

        //--------------------------

        ~ProcessScoped();

        //--------------------------

    private:
        PROCESS_INFORMATION m_pi;
    };

}

#include "../include/ProcessScoped.h"

namespace LAB
{
    //--------------------------

    ProcessScoped::ProcessScoped(const std::wstring& filename, STARTUPINFO si) :
        m_pi{}
    {
        std::wcout << "filename: " << filename << "\n";
        CreateProcessW(filename.c_str(), 0, 0, 0, true, 0, 0, 0, &si, &m_pi);
    }

    //--------------------------

    ProcessScoped::~ProcessScoped()
    {
        TerminateProcess(m_pi.hProcess, 0);
        CloseHandle(m_pi.hProcess);
        CloseHandle(m_pi.hThread);
    }

    //--------------------------
}
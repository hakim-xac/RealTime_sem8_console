#include "../include/HandleScoped.h"
#include "../include/Structs.h"

namespace LAB 
{
    //--------------------------

	HandleScoped::HandleScoped() :
        m_sa
        {
            .nLength = sizeof(SECURITY_ATTRIBUTES),
            .lpSecurityDescriptor = 0,
            .bInheritHandle = true
        },
        m_hmap{ CreateFileMappingW(reinterpret_cast<HANDLE>(-1), &m_sa, PAGE_READWRITE, 0, sizeof(SharedData), 0) }
    {
    }

    //--------------------------

    HandleScoped::~HandleScoped()
    {
        if (m_hmap)
            CloseHandle(m_hmap);
    }

    //--------------------------

    [[nodiscard]]
    HANDLE 
    HandleScoped::getHandle() const noexcept
    {
        return m_hmap;
    }

    //--------------------------
}
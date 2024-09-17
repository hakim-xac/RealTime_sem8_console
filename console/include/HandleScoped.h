#pragma once

#include "common.h"

namespace LAB
{
    class HandleScoped final {
    public:
        //--------------------------

        HandleScoped();

        //--------------------------

        HandleScoped(const HandleScoped&) = delete;

        //--------------------------

        HandleScoped(HandleScoped&&) = delete;

        //--------------------------

        HandleScoped& operator = (const HandleScoped&) = delete;

        //--------------------------
        HandleScoped& operator = (HandleScoped&&) = delete;

        //--------------------------

        ~HandleScoped();
        //--------------------------

        HANDLE getHandle() const noexcept;

        //--------------------------

    private:

        SECURITY_ATTRIBUTES m_sa;
        HANDLE m_hmap;
    };
}


#pragma once

#include "common.h"
#include "Structs.h"
#include "HandleScoped.h"
#include "ProcessScoped.h"

namespace LAB
{
	class Core
	{
	public:
		enum class CircleType { Cyrcle1, Cyrcle2 };
		enum class SquareType { Square1, Square2 };

		//--------------------------

		explicit Core(std::wstring appname);

		//--------------------------
		
		[[nodiscard]] bool isInit() const noexcept;
		
		//--------------------------
		
		[[nodiscard]] void selectCircle(CircleType ct) const;
		
		//--------------------------
		
		[[nodiscard]] void selectSquare(SquareType st) const;
		
		//--------------------------

	private:

		//--------------------------
		
		[[nodiscard]] bool init(std::wstring appname);

		//--------------------------
		
		[[nodiscard]] WindowInfo getWindowInfo();
		
		//--------------------------
		
		[[nodiscard]] Circle getCircleInfo1();
		
		//--------------------------
		
		[[nodiscard]] Circle getCircleInfo2();
		
		//--------------------------
		
		[[nodiscard]] Square getSquareInfo1();
		
		//--------------------------
		
		[[nodiscard]] Square getSquareInfo2();
		
		//--------------------------

		HandleScoped m_handle_scoped;
		std::unique_ptr<LAB::SharedData, decltype(&UnmapViewOfFile)> m_data_uptr;
		std::unique_ptr<ProcessScoped> m_process_scoped_uptr;
		bool m_is_init;
	};

}
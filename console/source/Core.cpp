#include "../include/Core.h"


namespace LAB
{
	//--------------------------

	Core::Core(std::wstring appname) :
		m_handle_scoped {},
		m_data_uptr { 
			static_cast<LAB::SharedData*>(MapViewOfFile(m_handle_scoped.getHandle(), FILE_MAP_WRITE, 0, 0, sizeof(LAB::SharedData)))
			, &UnmapViewOfFile
		},
		m_process_scoped_uptr { },
		m_is_init { init(std::move(appname)) }
	{

	}
	
	//--------------------------
	
	[[nodiscard]]
	bool
	Core::isInit() const noexcept
	{
		return m_is_init;
	}
	
	//--------------------------
	
	[[nodiscard]]
	void
	Core::selectCircle(CircleType ct) const
	{
		bool is_exit_to_menu {};
		while (!is_exit_to_menu)
		{
			system("cls");
			std::wcout << std::left << std::setw(30) << L"Увеличить Y на 10 единиц:" << "1\n";
			std::wcout << std::left << std::setw(30) << L"Уменьшить Y на 10 единиц:" << "2\n";
			std::wcout << std::left << std::setw(30) << L"Вернуться в меню:" << "0\n";

			auto mx{ std::numeric_limits<std::streamsize>::max };
			int32_t cmd{ };

			for (std::wcin >> cmd; std::wcin.fail(); std::wcin >> cmd)
			{
				std::wcout << L"Неверное значение! Повторите ввод:\n";
				std::wcin.clear();
				std::wcin.ignore(mx(), '\n');
			}

			switch (cmd)
			{
			case 0:
			{
				is_exit_to_menu = true;
				return;
			} break;
			case 1:
			{
				LAB::Circle& circle { ct == CircleType::Cyrcle1 ? m_data_uptr->circle1 : m_data_uptr->circle2 };
				circle.pos_y -= 10;
			} break;
			case 2:
			{
				LAB::Circle& circle{ ct == CircleType::Cyrcle1 ? m_data_uptr->circle1 : m_data_uptr->circle2 };
				circle.pos_y += 10;
			} break;
			default:
				std::wcout << L"Неверное значение! Повторите ввод:\n";
				break;
			}

			std::wcin.clear();
			std::wcin.ignore(mx(), '\n');
		}
	}
	
	//--------------------------
	
	[[nodiscard]]
	void
	Core::selectSquare(SquareType st) const
	{
		bool is_exit_to_menu{};
		while (!is_exit_to_menu)
		{
			system("cls");
			std::wcout << std::left << std::setw(30) << L"Увеличить Y на 10 единиц:" << "1\n";
			std::wcout << std::left << std::setw(30) << L"Уменьшить Y на 10 единиц:" << "2\n";
			std::wcout << std::left << std::setw(30) << L"Вернуться в меню:" << "0\n";

			auto mx{ std::numeric_limits<std::streamsize>::max };
			int32_t cmd{ };

			for (std::wcin >> cmd; std::wcin.fail(); std::wcin >> cmd)
			{
				std::wcout << L"Неверное значение! Повторите ввод:\n";
				std::wcin.clear();
				std::wcin.ignore(mx(), '\n');
			}

			switch (cmd)
			{
			case 0:
			{
				is_exit_to_menu = true;
				return;
			} break;
			case 1:
			{
				LAB::Square& square { st == SquareType::Square1 ? m_data_uptr->square1: m_data_uptr->square2 };
				square.pos_y -= 10;
			} break;
			case 2:
			{
				LAB::Square& square{ st == SquareType::Square2 ? m_data_uptr->square1 : m_data_uptr->square2 };
				square.pos_y += 10;
			} break;
			default:
				std::wcout << L"Неверное значение! Повторите ввод:\n";
				break;
			}

			std::wcin.clear();
			std::wcin.ignore(mx(), '\n');
		}
	}

	//--------------------------
	
	[[nodiscard]]
	bool
	Core::init(std::wstring appname)
	{
		const std::wstring str{ std::to_wstring(reinterpret_cast<size_t>(m_handle_scoped.getHandle())) };

		if (SetEnvironmentVariableW(L"hmap", str.c_str()) == false)
		{
			std::wcerr << "Error: can not set environment variable!\n";
			return false;
		}

		if (!m_data_uptr)
		{
			std::wcerr << "Error: m_data_uptr == nullptr\n";
			return false;
		}

		m_data_uptr->win_info = getWindowInfo();
		m_data_uptr->circle1 = getCircleInfo1();
		m_data_uptr->circle2 = getCircleInfo2();

		m_data_uptr->square1 = getSquareInfo1();
		m_data_uptr->square2 = getSquareInfo2();

		m_process_scoped_uptr = std::make_unique<ProcessScoped>(std::move(appname));
		if (!m_process_scoped_uptr)
		{
			std::wcerr << "Error: m_process_scoped_uptr == nullptr\n";
			return false;
		}
		return m_process_scoped_uptr != nullptr;
	}
	
	//--------------------------
	
	[[nodiscard]]
	WindowInfo
	Core::getWindowInfo()
	{
		int32_t window_width{};
		int32_t window_height{};

		auto mx{ std::numeric_limits<std::streamsize>::max };
		system("cls");
		std::wcout << L"Введите ширину окна:";

		for (std::wcin >> window_width; std::wcin.fail(); std::wcin >> window_width)
		{
			std::wcout << L"Неверное значение! Повторите ввод:\n";
			std::wcin.clear();
			std::wcin.ignore(mx(), '\n');
		}

		std::wcin.clear();
		std::wcin.ignore(mx(), '\n');

		std::wcout << L"Введите высоту окна:";

		for (std::wcin >> window_height; std::wcin.fail(); std::wcin >> window_height)
		{
			std::wcout << L"Неверное значение! Повторите ввод:\n";
			std::wcin.clear();
			std::wcin.ignore(mx(), '\n');
		}

		std::wcin.clear();
		std::wcin.ignore(mx(), '\n');

		return LAB::WindowInfo
		{
			.pos_x = 100,
			.pos_y = 100,
			.width = window_width,
			.height = window_height
		};
	}

	//--------------------------
	
	[[nodiscard]]
	Circle
	Core::getCircleInfo1()
	{
		return Circle {
			.pos_x = 100,
			.pos_y = 100,
			.radius = 100,
			.color = {
				.r = 10,
				.g = 200,
				.b = 100,
			}
		};
	}

	//--------------------------
	
	[[nodiscard]]
	Circle
	Core::getCircleInfo2()
	{
		return Circle {
			.pos_x = 500,
			.pos_y = 250,
			.radius = 50,
			.color = {
				.r = 10,
				.g = 200,
				.b = 100,
			}
		};
	}

	//--------------------------
	
	[[nodiscard]]
	Square
	Core::getSquareInfo1()
	{
		return Square {
			.pos_x = 100,
			.pos_y = 350,
			.length = 50,
			.color = {
				.r = 150,
				.g = 0,
				.b = 0,
			}
		};
	}

	//--------------------------
	
	[[nodiscard]]
	Square
	Core::getSquareInfo2()
	{
		return Square {
			.pos_x = 600,
			.pos_y = 450,
			.length = 50,
			.color = {
				.r = 150,
				.g = 0,
				.b = 0,
			}
		};
	}
	
	//--------------------------
}
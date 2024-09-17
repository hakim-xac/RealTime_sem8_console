#include "include/common.h"
#include "include/Structs.h"
#include "include/HandleScoped.h"
#include "include/ProcessScoped.h"
#include "include/Core.h"

int main()
{
    std::setlocale(LC_ALL, "ru");

    LAB::Core core { L"window.exe" };

    if (core.isInit() == false) [[unlikely]]
    {
        std::wcerr << L"Can not init App!\n";
        return 1;
    }

    auto mx { std::numeric_limits<std::streamsize>::max };
    bool is_running { true };
    int32_t cmd { };

    while (is_running)
    {
        system("cls");
        std::wcout << std::left << std::setw(30) << L"Изменить окружность 1:" << "1\n";
        std::wcout << std::left << std::setw(30) << L"Изменить окружность 2:" << "2\n";
        std::wcout << std::left << std::setw(30) << L"Изменить квадрат 1:" << "3\n";
        std::wcout << std::left << std::setw(30) << L"Изменить квадрат 2:" << "4\n";
        std::wcout << std::left << std::setw(30) << L"Выйти из программы:" << "0\n";

        for (std::wcin >> cmd; std::wcin.fail(); std::wcin >> cmd)
        {
            std::wcout << L"Неверное значение! Повторите ввод: \n";
            std::wcin.clear();
            std::wcin.ignore(mx(), '\n');
        }

        switch (cmd)
        {
            case 0:
            {
                is_running = false;
            } break;
            case 1:
            {
                core.selectCircle(LAB::Core::CircleType::Cyrcle1);
            } break;
            case 2:
            {
                core.selectCircle(LAB::Core::CircleType::Cyrcle2);
            } break;
            case 3:
            {
                core.selectSquare(LAB::Core::SquareType::Square1);
            } break;
            case 4:
            {
                core.selectSquare(LAB::Core::SquareType::Square2);
            } break;
            default:
            {
                std::wcerr << L"Неизвестная команда! Повторите ввод: \n";
            } break;
        }

        std::cin.clear();
        std::wcin.ignore(mx(), '\n');
    }

}

#include "logger.h"
#include <iostream>

int main(int argc, char const** argv)
{
    try {
        const std::string app =
                std::string(argv[0]).substr(std::string(argv[0]).rfind("/") + 1);
        if (argc < 2) {
            std::cout << "usage: "
                      << app
                      << " <n>\n"
                         "where:\n"
                         "  n - number of clusters\n";
            exit(1);
        }
        if (argc > 2) {
            gLogger->set_level(spdlog::level::debug);
        }

        int n = std::stoi(argv[1]);
        std::cout << "Starting " << app << " with " << n << " clusters.\n";


    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

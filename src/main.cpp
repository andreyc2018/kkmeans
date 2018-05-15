#include "logger.h"
#include <fplus/fplus.hpp>
#include <dlib/clustering.h>
#include <iostream>

using sample_type_t = dlib::matrix<double,2,1>;

using kernel_type_t = dlib::radial_basis_kernel<sample_type_t>;

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

        const std::string input (
            std::istreambuf_iterator<char>(std::cin.rdbuf()),
            std::istreambuf_iterator<char>());

        // std::cout << input << '\n';

        const auto parts = fplus::split('\n', false, input);
        for (const auto& p : parts) {
            std::cout << ": " << p << "\n";
            const auto coords = fplus::split(';', false, p);
            for (const auto& c : coords) {
                std::cout << "  : " << c << "\n";
            }
        }
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

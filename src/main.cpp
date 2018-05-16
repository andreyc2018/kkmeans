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
            std::cout << "usage: " << app << " <n>\n"
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

        const auto parts = fplus::split_lines(false, input);
        std::vector<sample_type_t> samples;
        for (const auto& p : parts) {
            const auto coords = fplus::split(';', false, p);
            sample_type_t m;
            m(0) = std::stod(coords[0]);
            m(1) = std::stod(coords[1]);
            samples.push_back(m);
        }

        dlib::kcentroid<kernel_type_t> kc(kernel_type_t(0.1),0.01, 8);
        dlib::kkmeans<kernel_type_t> test(kc);

        test.set_number_of_centers(n);

        std::vector<sample_type_t> initial_centers;
        dlib::pick_initial_centers(3, initial_centers, samples, test.get_kernel());
        test.train(samples,initial_centers);

    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

#include <iostream>
#include <iomanip>
#include <random>
#include <map>

int main(int argc, char** argv)
{
    const std::string app =
        std::string(argv[0]).substr(std::string(argv[0]).rfind("/") + 1);
    if (argc < 2) {
        std::cout << "usage: " << app << " <n> <items> <min> <max>\n"
                        "where:\n"
                        "  n - number of clusters\n";
        exit(1);
    }

    int n = std::stoi(argv[1]);
    int items = (argc > 2)? std::stoi(argv[2]) : 200;
    int min = (argc > 3)? std::stoi(argv[3]) : -100;
    int max = (argc > 4)? std::stoi(argv[4]) : 100;

    std::cout << "Starting " << app << " will generate " << items 
              << " points between " << min << " and " << max
              << " in " << n << " clusters.\n";

    for (int i = 0; i < n; ++i) {
        // Seed with a real random value, if available
        std::random_device r;
    
        // Choose a random mean between min and max
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(min, max);
        int mean = uniform_dist(e1);
        std::cout << "Randomly-chosen mean: " << mean << '\n';

        // Generate a distribution around that mean
        std::seed_seq seed2{r(), r(), r(), r(), r(), r(), r(), r()}; 
        std::mt19937 e2(seed2);
        std::normal_distribution<> normal_dist(mean, 2);

        for (int j = 0; j < items; ++j) {
            auto x = normal_dist(e2);
            auto y = normal_dist(e2);
            std::cerr << std::fixed << std::setprecision(2)
                      << x << ";" << y << "\n";
        }
    }
}

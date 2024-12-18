#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto time = zoned_time{current_zone(), now};
    std::cout << "Current time: " << time << std::endl;
    return 0;
}

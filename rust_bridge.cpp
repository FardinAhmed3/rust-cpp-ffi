#include <iostream>
#include <chrono>

// Calling 
extern "C" {
    int add(int a, int b);
    int subtract(int a, int b);
}

int cpp_add(int a, int b){
    return a+b;
}

int main(){

    auto start = std::chrono::high_resolution_clock::now();
    int result = add(3000,411023);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout<<" Result: " << result << std::endl;


    std::cout << "Elapsed time for library driven addition: " << elapsed.count() << " seconds\n";


    // native
    
    auto start_2 = std::chrono::high_resolution_clock::now();
    int result_2 = cpp_add(3000,411023);
    auto end_2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_2 = end_2 - start_2;
    std::cout<< "Results for native " << result_2 << std::endl;

    std::cout<< "Elapsed time for native addition: " << elapsed_2.count() << "seconds" << std::endl;


    constexpr int ITERATIONS = 100'000'0000;

    volatile int sink = 0;

    // library-driven (Rust via FFI)
    auto start_3 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        sink += add(i, i);
    }
    auto end_3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_3 = end_3 - start_3;

    std::cout << "Elapsed time for library driven addition (loop): "
              << elapsed_3.count() << " seconds\n";

    // native C++
    auto start_4 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; ++i) {
        sink += cpp_add(i, i);
    }
    auto end_4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_4 = end_4 - start_4;

    std::cout << "Elapsed time for native addition (loop): "
              << elapsed_4.count() << " seconds\n";

              
    std::cout << "Sink: " << sink << std::endl;


}


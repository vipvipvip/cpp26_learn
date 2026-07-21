#include "std_learn/transform.h"


void run_std_tranform_demo() {
    printf("Hello from transform\n");

    std::vector<int> v1 = {1,2,3,4,5};
    std::vector<int> v2(v1.size());

    for (size_t i=0; i < 5; i++) {
        std::ranges::transform(v1, v2.begin(), [] (int a) { return a+1;});
    }
    for (int val : v2) {
        std::cout << val << " "; 
    }
}
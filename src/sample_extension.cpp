#include "dart_api.h"
#include "dart_api_dl.h"
#include <iostream>

// Export a sample function to create an initial ABI signature
extern "C" DART_EXPORT int64_t InitPoCExtension(void* data) {
    if (Dart_InitializeApiDL(data) != 0) {
        return -1; // Initialization failed
    }
    std::cout << "PoC Extension Initialized Successfully!" << std::endl;
    return 0;
}

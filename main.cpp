#include <iostream>// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
#include "Cache/Cache.h"

using namespace std;

int main()
{
    size_t cacheSize = 32 * 1024;
    size_t blockSize = 32;
    size_t associativity = 1;

    Cache cache(cacheSize, blockSize, associativity);
    // Hardcoded addresses in hex
    size_t addresses[] = {
        0x3b5c, 0x1ef4, 0x3b5c, 0x1f78, 0x352c, 0x37dc, 0x4, 0x2fe0
    };

    ifstream MyReadFile("random.txt");

    // Run through cache
    int totalAccesses = sizeof(addresses) / sizeof(addresses[0]);
    int hits = 0;

    for (int i = 0; i < totalAccesses; i++) {
        if (cache.access(addresses[i])) {
            hits++;
        }
    }

    // Print results
    double hitRate = (double)hits / totalAccesses * 100.0;
    cout << "Cache Configuration:" << endl;
    cout << "  Size: " << cacheSize / 1024 << " KB" << endl;
    cout << "  Block Size: " << blockSize << " bytes" << endl;
    cout << "  Associativity: " << associativity << "-way" << endl;
    cout << "Results:" << endl;
    cout << "  Total Accesses: " << totalAccesses << endl;
    cout << "  Cache Hits: " << hits << endl;
    cout << "  Hit Rate: " << fixed << setprecision(2) << hitRate << "%" << endl;

    return 0;
}
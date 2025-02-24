#include <iostream>// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or

#include "SieveOfEratosthenes/LRU_Cache.h"

int main()
{
    LRU_Cache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;
    cache.put(3, 3);
    cout  << cache.get(2) << endl;
    cache.put(4, 4);
    cout << cache.get(1) << endl;
    cout << cache.get(3) << endl;
    cout << cache.get(4) << endl;
    return 0;
}

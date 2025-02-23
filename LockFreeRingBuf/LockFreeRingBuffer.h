#ifndef LOCKFREE_RINGBUFFER_H
#define LOCKFREE_RINGBUFFER_H

#include <vector>
#include <atomic>

class LockFreeRingBuffer {
public:
    // Structure to hold market data.
    struct MarketData {
        long timestamp = 0; // The timestamp of the market data entry, initialized to 0.
        double price = 0.0; // The price of the market data entry, initialized to 0.0.
        int volume = 0;     // The volume of the market data entry, initialized to 0.
    };

private:
    std::vector<MarketData> buffer; // The underlying buffer to store market data entries.
    size_t capacity;                 // The maximum number of entries the buffer can hold.
    std::atomic<size_t> head;       // Atomic head index for the buffer, indicating where to push new data.
    std::atomic<size_t> tail;       // Atomic tail index for the buffer, indicating where to pop data from.


public:
    // Constructor to initialize the ring buffer with a specified capacity.
    // cap: The maximum number of entries the buffer can hold.
    explicit LockFreeRingBuffer(const size_t cap)
        : buffer(cap), capacity(cap), head(0), tail(0) {}

    // Pushes a new market data entry into the buffer.
    // ts: The timestamp of the market data entry.
    // price: The price of the market data entry.
    // vol: The volume of the market data entry.
    // Returns true if the push was successful, false if the buffer is full.
    bool push(long ts, double price, int vol);

    // Pops a market data entry from the buffer.
    // data: A reference to a MarketData object where the popped data will be stored.
    // Returns true if the pop was successful, false if the buffer is empty.
    bool pop(MarketData &data);
};

#endif // LOCKFREE_RINGBUFFER_H

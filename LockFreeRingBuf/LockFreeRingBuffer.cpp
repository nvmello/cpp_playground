#include "LockFreeRingBuffer.h"

// Pushes a new market data entry into the ring buffer.
// ts: The timestamp of the market data entry.
// price: The price of the market data entry.
// vol: The volume of the market data entry.
// Returns true if the push was successful; false if the buffer is full.
bool LockFreeRingBuffer::push(long ts, double price, int vol) {
    // Load the current tail index with relaxed memory order.
    size_t current_tail = tail.load(std::memory_order_relaxed);
    // Calculate the next tail index using modulo for wrapping around the buffer.
    size_t next_tail = (current_tail + 1) % capacity;

    // Check if the buffer is full by comparing the next tail with the head index.
    if (next_tail == head.load(std::memory_order_acquire)) {
        return false;  // Buffer full; cannot push new data.
    }

    // Store the new market data entry at the current tail index.
    buffer[current_tail] = {ts, price, vol};
    // Update the tail index to the next position.
    tail.store(next_tail, std::memory_order_release);
    return true; // Push successful.
}

// Pops a market data entry from the ring buffer into the provided data reference.
// data: A reference to a MarketData object where the popped data will be stored.
// Returns true if the pop was successful; false if the buffer is empty.
bool LockFreeRingBuffer::pop(MarketData &data) {
    // Load the current head index with relaxed memory order.
    size_t current_head = head.load(std::memory_order_relaxed);

    // Check if the buffer is empty by comparing the head with the tail index.
    if (current_head == tail.load(std::memory_order_acquire)) {
        return false;  // Buffer empty; cannot pop data.
    }

    // Retrieve the market data entry from the current head index.
    data = buffer[current_head];
    // Update the head index to the next position using modulo for wrapping around the buffer.
    head.store((current_head + 1) % capacity, std::memory_order_release);
    return true; // Pop successful.
}

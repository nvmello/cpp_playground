#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include "LockFreeRingBuf/LockFreeRingBuffer.h"  // Include your ring buffer class

// Function to stream market data from a CSV file into the lock-free ring buffer.
// ringBuffer: Reference to the LockFreeRingBuffer instance to store the data.
// filePath: Path to the CSV file containing market data.
void stream_market_data(LockFreeRingBuffer &ringBuffer, const std::string &filePath) {
    // Open the specified file for reading market data.
    std::ifstream file(filePath);
    // Check if the file was successfully opened.
    if (!file) {
        std::cerr << "Error opening file! Check the path." << std::endl;
        return;
    }

    std::string line;  // Variable to store each line of the CSV file.
    long ts;          // Variable to store the timestamp.
    double price;     // Variable to store the price.
    int volume;       // Variable to store the volume.


    // Read each line of the file until the end.
    while (std::getline(file, line)) {
        std::stringstream ss(line);  // Create a stringstream to parse the line.
        std::string item;             // Variable to temporarily store each parsed item.

        // Parse the timestamp, price, and volume from the CSV line.
        std::getline(ss, item, ','); ts = std::stol(item);         // Convert and store timestamp.
        std::getline(ss, item, ','); price = std::stod(item);      // Convert and store price.
        std::getline(ss, item, ',');
        std::getline(ss, item, ',');
        std::getline(ss, item, ',');
        std::getline(ss, item, ','); volume = std::stoi(item);     // Convert and store volume.

        // Push the parsed market data into the ring buffer.
        ringBuffer.push(ts, price, volume);
        // Simulate latency to mimic real-time data streaming.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Function to continuously process market data from the lock-free ring buffer.
// ringBuffer: Reference to the LockFreeRingBuffer instance to retrieve data from.
void process_market_data(LockFreeRingBuffer &ringBuffer) {
    LockFreeRingBuffer::MarketData data;  // Variable to hold the market data retrieved from the buffer.

    // Infinite loop to continuously process market data.
    while (true) {
        // Attempt to pop data from the ring buffer.
        if (ringBuffer.pop(data)) {
            // If successful, print the processed trade data to the console.
            std::cout << "Processing Trade - Timestamp: " << data.timestamp
                      << ", Price: " << data.price
                      << ", Volume: " << data.volume << std::endl;
        }
    }
}

// Main function to set up the application.
int main() {
    // Create an instance of LockFreeRingBuffer with a capacity of 1000 entries.
    LockFreeRingBuffer ringBuffer(1000);
    std::string filePath = "/home/parallels/Projects/TradingSim/data/mstr.csv"; // Path to the market data CSV file.

    // Start the data streaming thread for reading market data.
    std::thread producer(stream_market_data, std::ref(ringBuffer), filePath);
    // Start the data processing thread for processing market data.
    std::thread consumer(process_market_data, std::ref(ringBuffer));

    // Wait for both threads to complete before exiting the program.
    producer.join();
    consumer.join();

    return 0; // Indicate successful program termination.
}


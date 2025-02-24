# **Cache Performance Analysis for the Sieve of Eratosthenes**

## **Context**
Emirp* Technologies has approached ASU requesting an investigation into the performance of the Sieve of Eratosthenes algorithm. They have observed that the algorithm's performance, measured in instructions per second, decreases as the search region increases.

Due to your expertise with the algorithm and knowledge of processor caches, they would like you to:
- Simulate the cache performance of the Sieve of Eratosthenes
- Analyze its behavior
- Provide recommendations for improvement

> *(*An emirp is a type of prime number that, when its digits are reversed, produces a different prime number.)*

---

## **Learning Objectives**
1. Implement a **cache simulator** that accounts for different configurations, including size, block size, and associativity.
2. **Instrument actual code** for cache analysis.
3. **Analyze cache performance** and provide recommendations for improvement.

---

## **Provided Resources**
Use the provided test vectors to validate your cache simulator. Each test should be run **twice** through the cache (without resetting it) while recording hits and total accesses.

### **Test Vectors**
- `random.txt` – Random access pattern to a 16MiB buffer.
- `stride8.txt` – A test pattern that sequentially accesses every 8th byte.

### **Expected Results**
Expected hit rates for different cache configurations are provided in CSV files:
- `random_by_asociativity.csv` – Hit rates for **random access** with varying associativity.
- `random_by_blocksize.csv` – Hit rates for **random access** with varying block sizes.
- `stride8_by_associativity.csv` – Hit rates for **stride8 access** with varying associativity.
- `stride8_by_blocksize.csv` – Hit rates for **stride8 access** with varying block sizes.

---

## **Project Steps**

### **Step 1: Implement the Cache Simulator**
Create a **cache class** that supports the following configurations:
- **Size:** Up to at least **256KiB**
- **Associativity:** Direct-mapped to **8-way set associative**
- **Block Size:** From **1 byte to at least 64 bytes**
- **Replacement Policy:** **Least Recently Used (LRU)** for set-associative caches

#### **Required Function**
Your cache class should implement:

```cpp
bool Cache::access(unsigned long address);

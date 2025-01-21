# Adapter Pattern in C++

## Overview
The Adapter Pattern is a structural design pattern that bridges the gap between incompatible interfaces. It allows objects with differing interfaces to collaborate seamlessly by providing a translation layer (adapter).

---

## Key Components

### 1. Target Interface
Defines the interface expected by the client.

### 2. Adaptee
An existing class with an incompatible interface that needs to be adapted.

### 3. Adapter
A wrapper that implements the Target Interface and translates requests to the Adaptee.

---

## Advantages
1. **Enables Reuse**: Leverages existing classes without modifying their code.
2. **Flexibility**: Adapts different interfaces dynamically.
3. **Compatibility**: Resolves interface mismatches between systems.

---

## Disadvantages
1. **Increased Complexity**: Adds an additional layer of abstraction.
2. **Performance Overhead**: May slightly impact performance due to the adapter layer.

---

## Example Use Case
Suppose you have:
- A **modern audio player** that expects MP3 files.
- A **legacy audio player** that can only play WAV files.

Using the Adapter Pattern, the legacy player can be integrated into the modern system by wrapping it in an adapter.

---

## How to Run
1. Clone the repository:
   ```bash
   git clone <repository-url>
   ```

2. Navigate to the project directory:
   ```bash
   cd adapter-pattern-cpp
   ```

3. Compile the code:
   ```bash
   g++ -std=c++17 -o adapter_pattern main.cpp
   ```

4. Run the executable:
   ```bash
   ./adapter_pattern
   ```

---

## Example Output
```
Playing MP3 file: song.mp3
Converting WAV to MP3...
Playing WAV file: track.wav
```

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for more details.

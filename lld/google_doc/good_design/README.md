# Document Editor

A C++ implementation of a document editor system demonstrating various design patterns including Singleton, Factory, and Single Responsibility Principle.

## Project Structure

```
good_design/
├── CMakeLists.txt
├── include/
│   ├── document.h          # Document singleton class
│   ├── document_element.h  # Base class for document elements
│   ├── document_renderer.h # Document rendering functionality
│   └── document_storage.h  # Document storage operations
├── src/
│   ├── document.cpp
│   ├── document_element.cpp
│   ├── document_renderer.cpp
│   ├── document_storage.cpp
│   └── main.cpp
└── build/                  # Build directory (created during build)
```

## Design Patterns Used

1. **Singleton Pattern**
   - Document class ensures only one instance exists
   - Provides global access to document state

2. **Single Responsibility Principle**
   - Document: Manages document elements
   - DocumentRenderer: Handles rendering
   - DocumentStorage: Manages file I/O
   - DocumentElement: Defines element interface

3. **Factory Pattern**
   - DocumentElement hierarchy for different types of elements
   - TextElement and ImageElement implementations

## Building the Project

### Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler with C++20 support
- Make

### Build Steps

1. Create and enter build directory:
```bash
mkdir -p build
cd build
```

2. Generate build files:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

4. Clean build (if needed):
```bash
make clean_all  # Complete clean
# or
make clean      # Standard clean
```

## Running the Program

After building, run the executable:
```bash
./document_editor
```

The program will:
1. Create a document with sample text and images
2. Render the document to console
3. Save the document to 'output.txt'

## Features

- Document management with singleton pattern
- Support for multiple element types (text, images)
- Document rendering
- File I/O operations
- Clean separation of concerns

## Class Structure

### Document (Singleton)
- Manages document elements
- Provides global access point
- Handles element addition/removal

### DocumentElement
- Abstract base class for document elements
- Defines common interface
- Implemented by TextElement and ImageElement

### DocumentRenderer
- Handles document rendering
- Converts elements to displayable format

### DocumentStorage
- Manages file operations
- Handles saving and loading documents

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MKV License - see the LICENSE file for details. 
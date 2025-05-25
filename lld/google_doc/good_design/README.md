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
   - Other classes (DocumentRenderer, DocumentStorage) use the singleton instance through getInstance()

2. **Single Responsibility Principle**
   - Document: Manages document elements
   - DocumentRenderer: Handles rendering
   - DocumentStorage: Manages file I/O
   - DocumentElement: Defines element interface

3. **Factory Pattern**
   - DocumentElement hierarchy for different types of elements
   - TextElement and ImageElement implementations

4. **Strategy Pattern**
   - Used in DocumentRenderer for rendering different element types
   - Allows adding new rendering strategies without modifying existing code
   - Implements Open/Closed Principle for rendering functionality

5. **Open/Closed Principle**
   - DocumentElement hierarchy is open for extension (new element types)
   - Rendering system is open for extension (new rendering strategies)
   - New features can be added without modifying existing code
   - Example: Adding new element types or rendering strategies doesn't require changing existing classes

6. **Liskov Substitution Principle**
   - DocumentElement hierarchy properly implements LSP
   - Base class (DocumentElement) defines a consistent interface
   - Derived classes (TextElement, ImageElement) maintain behavioral compatibility
   - Any DocumentElement can be substituted with its derived classes
   - Common interface includes:
     - getContent()
     - getType()
     - setContent()
   - Derived classes implement the interface without violating the base class contract
   - No runtime type checking needed
   - Enables polymorphic behavior and extensibility

7. **Interface Segregation Principle**
   - **Segregated Interfaces**:
     - `IDocumentElement`: Base interface with only essential `getType()` method
     - `IEditable`: For elements that can be edited (text and tables)
     - `IRenderable`: For elements that can be rendered
     - `IStylable`: For elements that can be styled (text and tables)
   - **Flexible Implementation**:
     - `TextElement`: Implements all interfaces (IEditable, IRenderable, IStylable)
     - `ImageElement`: Implements only necessary interfaces (IRenderable)
     - `TableElement`: Implements multiple interfaces (IEditable, IRenderable, IStylable)
   - **Benefits**:
     - Clients only depend on interfaces they use
     - No forced implementation of unnecessary methods
     - Clear separation of concerns
     - Easy to add new element types with specific capabilities
     - Better maintainability and extensibility
     - Clear interface identification with 'I' prefix convention

8. **Dependency Inversion Principle**
   - **Interface-Based Design**:
     - Clear interfaces (`IDocumentElement`, `IEditable`, `IRenderable`, `IStylable`) represent abstractions
     - Concrete implementations depend on interfaces rather than concrete implementations
   - **High-Level Modules Independence**:
     - `Document` class depends on `IDocumentElement` interface
     - Uses `std::unique_ptr<IDocumentElement>` for flexibility
   - **Interface Segregation**:
     - Functionality broken into focused interfaces
     - Classes implement only needed interfaces
   - **Abstraction Through Interfaces**:
     - `Document` operates on abstract `IDocumentElement` interface
     - Enables easy extension with new element types
   - **Polymorphic Behavior**:
     - Virtual functions and polymorphism through interfaces
     - Runtime flexibility and extension
   - **Benefits**:
     - More maintainable code
     - Easier testing
     - Flexible for future extensions
     - Reduced coupling between components

9. **Class Relationships**
   - **Dependency**: DocumentRenderer and DocumentStorage depend on Document singleton
   - **Association**: Classes use Document's services without owning it
   - **Client-Service**: DocumentRenderer and DocumentStorage act as clients to the Document singleton service
   - Note: This is not an aggregation relationship as there's no ownership or containment

10. **Ownership and Memory Management**
   - **Strong Aggregation (Composition)**: Document exclusively owns its DocumentElements
   - **Smart Pointers**: 
     - `unique_ptr` used for DocumentElements to express exclusive ownership
     - Elements are automatically destroyed when Document is destroyed
     - No shared ownership of elements allowed
     - Prevents memory leaks and dangling pointers
   - **Lifecycle Management**:
     - DocumentElements cannot exist without Document
     - Elements are created and destroyed with Document
     - Clear ownership semantics with `unique_ptr`

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
- Document rendering with extensible strategy pattern
- File I/O operations
- Clean separation of concerns
- Open for extension, closed for modification
- Safe memory management with smart pointers

## Class Structure

### Document (Singleton)
- Manages document elements
- Provides global access point
- Handles element addition/removal
- Exclusive owner of DocumentElements
- Uses unique_ptr for memory management

### DocumentElement
- Abstract base class for document elements
- Defines common interface
- Implemented by TextElement and ImageElement
- Open for extension with new element types

### DocumentRenderer
- Handles document rendering
- Uses Strategy Pattern for rendering different elements
- Converts elements to displayable format
- Uses Document singleton through dependency relationship
- Open for extension with new rendering strategies

### DocumentStorage
- Manages file operations
- Handles saving and loading documents
- Uses Document singleton through dependency relationship

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MKV License - see the LICENSE file for details. 
# VectorStore-Assignment-1

C++ implementation for Assignment 1 of the Data Structures and Algorithms (DSA) course at HCMUT (Ho Chi Minh City University of Technology).

## 📋 Overview

This project implements a **Vector Store** data structure in C++, focusing on efficient storage and retrieval of vector data with various operations commonly used in data structure courses.


## 📚 Key Features

- **Vector Storage**: Efficient storage and management of vector elements
- **Core Operations**: Insert, delete, search, and access operations
- **Dynamic Memory Management**: Proper allocation and deallocation
- **Testing Support**: Helper functions for unit testing and validation

## 📁 Project Structure

```
VectorStore-Assignment-1/
├── src/
│   ├── VectorStore.h        # Vector Store class definition
│   ├── VectorStore.cpp      # Vector Store implementation
│   ├── main.h               # Main function declarations
│   ├── TestHelper.h         # Helper functions for testing
│   └── utils.h              # Utility functions
├── tests/                   # Test cases directory
├── main.cpp                 # Entry point
├── _251_CO2003___DSA__Assignment_1_VI.pdf  # Assignment specification
├── README.md
├── .gitignore
└── main                     # Compiled executable
```

## 🛠️ Requirements

- **C++ Compiler**: C++11 or later (g++, clang, etc.)
- **Operating System**: Linux, macOS, or Windows (with MinGW/MSVC)
- No external dependencies required

## 📦 Compilation

### Using g++:
```bash
g++ -o main main.cpp src/VectorStore.cpp -std=c++11
```

## ▶️ Running the Program

```bash
./main
```

## 🧪 Testing

The project includes testing utilities in `TestHelper.h` for validating Vector Store operations:

```bash
# Compile and run tests
g++ -o main main.cpp src/VectorStore.cpp -std=c++11
./main
```

## 📖 Course Information

- **Course**: CO2003 - Data Structures and Algorithms
- **Institution**: HCMUT (Ho Chi Minh City University of Technology)
- **Assignment**: Assignment 1
- **Language**: C++

## 📝 Assignment Specification

For detailed requirements and specifications, refer to the PDF file:
[`_251_CO2003___DSA__Assignment_1_VI.pdf`](_251_CO2003___DSA__Assignment_1_VI.pdf)

## ✅ Notes

- Ensure all files in the `src/` directory are properly included
- The project uses standard C++ libraries
- Memory management follows proper allocation/deallocation practices
- Test cases are available in the `tests/` directory

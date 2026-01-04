# Architecture Documentation

## Overview

The CLI Todo App follows a modular, object-oriented architecture with clear separation of concerns. The application is structured into distinct layers that handle different aspects of task management, from data persistence to user interface rendering.

## Design Principles

- **Separation of Concerns**: Each class has a single, well-defined responsibility
- **Encapsulation**: Internal implementation details are hidden behind clean interfaces
- **Memory Safety**: Uses modern C++ smart pointers (`unique_ptr`) for automatic memory management
- **Cross-Platform Compatibility**: Platform-specific code is isolated and conditionally compiled
- **SOLID Principles**: The design adheres to SOLID principles for maintainable and extensible code

## Architecture Diagram

```
┌─────────────────────────────────────────────────────┐
│                    main.cpp                         │
│              (Application Entry Point)              │
└────────────┬────────────────────────────────────────┘
             │
             ├──────────────┬──────────────┬──────────────┐
             │              │              │              │
             ▼              ▼              ▼              ▼
    ┌──────────────┐ ┌─────────────┐ ┌──────────┐ ┌──────────┐
    │ TaskManager  │ │ FileHandler │ │UIManager │ │  Utils   │
    │              │ │             │ │          │ │          │
    │ - Business   │ │ - Data      │ │ - User   │ │ - Helper │
    │   Logic      │ │   Persistence│ │   Interface│ │   Functions│
    └──────┬───────┘ └─────────────┘ └──────────┘ └──────────┘
           │
           │ manages
           ▼
    ┌──────────────┐
    │     Task     │
    │              │
    │ - Data Model │
    └──────────────┘
```

## Core Components

### 1. Task (`Task.h`, `Task.cpp`)

**Purpose**: Represents a single task entity with all its properties.

**Responsibilities**:
- Store task data (title, description, category, due date, priority, completion status)
- Track timestamps (creation time, completion time)
- Serialize/deserialize task data for file storage
- Provide getters and setters for task properties

**Key Design Decisions**:
- Uses `enum class Priority` for type-safe priority levels
- Stores timestamps as `time_t` for precise time tracking
- Immutable ID ensures task identity remains constant
- Serialization uses pipe-delimited format for simplicity and human readability

**Data Structure**:
```cpp
class Task {
    int id;                    // Unique identifier
    string title;              // Task name (required)
    string description;        // Detailed description (optional)
    string category;           // Category/group (default: "General")
    string dueDate;            // Due date in YYYY-MM-DD format
    Priority priority;         // LOW, MEDIUM, or HIGH
    bool completed;            // Completion status
    time_t createdAt;          // Creation timestamp
    time_t completedAt;        // Completion timestamp (0 if incomplete)
};
```

### 2. TaskManager (`TaskManager.h`, `TaskManager.cpp`)

**Purpose**: Manages the collection of tasks and provides business logic operations.

**Responsibilities**:
- Maintain a collection of all tasks
- Generate unique task IDs
- Provide CRUD operations (Create, Read, Update, Delete)
- Filter and search tasks
- Handle task state transitions (completion toggling)

**Key Design Decisions**:
- Uses `vector<unique_ptr<Task>>` for automatic memory management and ownership semantics
- Implements auto-incrementing ID system for task identification
- Returns raw pointers (`Task*`) for non-owning access to tasks
- Case-insensitive search and category filtering for better user experience

**Operations**:
- `addTask()`: Creates and adds a new task
- `deleteTask()`: Removes a task by ID
- `toggleTaskCompletion()`: Changes completion status
- `getTask()`: Retrieves a specific task
- `getAllTasks()`: Returns all tasks
- `getTasksByCategory()`: Filters by category
- `searchTasks()`: Searches by keyword
- `clearAllTasks()`: Removes all tasks and resets ID counter

### 3. FileHandler (`FileHandler.h`, `FileHandler.cpp`)

**Purpose**: Handles persistent storage of tasks to disk.

**Responsibilities**:
- Save task collection to file
- Load tasks from file on startup
- Ensure data directory exists
- Clear file contents when needed

**Key Design Decisions**:
- Stores data in `data/tasks.dat` by default
- Uses simple text-based format for portability
- First line stores the next ID to maintain ID continuity across sessions
- Platform-specific directory creation using conditional compilation
- Graceful error handling (returns boolean success status)

**File Format**:
```
<next_id>
<task1_serialized_data>
<task2_serialized_data>
...
```

**Platform Considerations**:
```cpp
#ifdef _WIN32
    mkdir("data");              // Windows
#else
    mkdir("data", 0755);        // Unix-like systems
#endif
```

### 4. UIManager (`UIManager.h`, `UIManager.cpp`)

**Purpose**: Provides all user interface rendering and formatting.

**Responsibilities**:
- Clear screen in a cross-platform manner
- Display formatted headers with box-drawing characters
- Render tasks with color coding and formatting
- Display menu options
- Show success, error, and info messages
- Handle user input prompts

**Key Design Decisions**:
- Static class (utility pattern) - no state needed
- ANSI color codes for terminal coloring
- Platform-specific terminal width detection
- Box-drawing characters for visual appeal
- Color-coded priorities for quick visual recognition

**Color Scheme**:
- **Red**: High priority tasks
- **Yellow**: Medium priority tasks
- **Green**: Low priority tasks and success messages
- **Blue**: Informational messages
- **Cyan**: Headers and due dates
- **Magenta**: Categories

**Platform-Specific Code**:
```cpp
// Screen clearing
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

// Terminal width detection
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
#endif
```

### 5. Utils (`Utils.h`, `Utils.cpp`)

**Purpose**: Provides utility functions used throughout the application.

**Responsibilities**:
- Input validation (integers, dates)
- String manipulation (trimming, case conversion)
- Type conversion (string to int, string to priority)

**Key Functions**:
- `isValidInteger()`: Validates numeric input
- `stringToInt()`: Safe string-to-integer conversion
- `stringToPriority()`: Converts string to Priority enum
- `trim()`: Removes leading/trailing whitespace
- `toLowerCase()`: Case-insensitive comparisons
- `isValidDate()`: Validates YYYY-MM-DD date format using regex

**Design Pattern**: Static utility class (no instantiation needed)

### 6. Main Application (`main.cpp`)

**Purpose**: Application entry point and user interaction orchestration.

**Responsibilities**:
- Initialize TaskManager and FileHandler
- Load existing tasks on startup
- Display menu and handle user input
- Route user choices to appropriate flow functions
- Save tasks after modifications
- Coordinate between all components

**Flow Functions**:
Each user action is handled by a dedicated flow function:
- `addTaskFlow()`: Guides user through task creation
- `viewAllTasksFlow()`: Displays all tasks
- `viewByCategoryFlow()`: Shows tasks in a specific category
- `toggleTaskFlow()`: Changes task completion status
- `deleteTaskFlow()`: Removes a task
- `searchTasksFlow()`: Searches and displays matching tasks
- `clearAllTasksFlow()`: Clears all tasks with confirmation

**Main Loop Structure**:
```
1. Load tasks from file
2. While running:
   a. Display menu
   b. Get user choice
   c. Execute corresponding flow
   d. Save if data changed
   e. Wait for user acknowledgment
3. Save tasks and exit
```

## Data Flow

### Task Creation Flow
```
User Input → main.cpp (addTaskFlow)
    ↓
Validation → Utils (trim, validation)
    ↓
Create Task → TaskManager.addTask()
    ↓
Store in Memory → vector<unique_ptr<Task>>
    ↓
Persist → FileHandler.saveTasks()
    ↓
Write to Disk → data/tasks.dat
```

### Task Retrieval Flow
```
Application Startup → main.cpp
    ↓
Load File → FileHandler.loadTasks()
    ↓
Parse Data → Task.deserialize()
    ↓
Recreate Tasks → TaskManager.addTask()
    ↓
Display → UIManager.printTaskList()
    ↓
Render to Terminal → Formatted output with colors
```

### Search Flow
```
User Keyword → main.cpp (searchTasksFlow)
    ↓
Normalize → Utils.toLowerCase()
    ↓
Filter Tasks → TaskManager.searchTasks()
    ↓
Match Title/Description → Case-insensitive search
    ↓
Display Results → UIManager.printTaskList()
```

## Memory Management

### Smart Pointers
The application uses modern C++ smart pointers for automatic memory management:

```cpp
// TaskManager stores tasks in unique_ptr for ownership
vector<unique_ptr<Task>> tasks;

// Non-owning access via raw pointers
Task* getTask(int id);
vector<Task*> getAllTasks();
```

**Benefits**:
- Automatic cleanup when tasks are deleted
- Clear ownership semantics
- Exception-safe code
- No manual `delete` calls needed

### Resource Management
- **File Handles**: Automatically closed when `ifstream`/`ofstream` objects go out of scope
- **Memory Allocation**: All heap allocations managed by smart pointers
- **No Memory Leaks**: RAII (Resource Acquisition Is Initialization) principles throughout

## Error Handling

### Strategy
- **File Operations**: Return boolean success/failure status
- **User Input**: Validate before processing, display clear error messages
- **Parsing**: Use try-catch blocks for exception-prone operations
- **Graceful Degradation**: Continue operation when possible, fail gracefully when not

### Examples
```cpp
// File loading - continues with empty task list if file doesn't exist
if (!file.is_open()) {
    return false;  // Not an error, just no saved tasks
}

// Parsing - skip corrupted tasks, continue with valid ones
try {
    Task task = Task::deserialize(line);
    // Process task
} catch (...) {
    continue;  // Skip this task, process next
}
```

## Cross-Platform Considerations

### Platform-Specific Code
The application uses conditional compilation for platform differences:

**File System**:
```cpp
#ifdef _WIN32
    #include <direct.h>
    #define mkdir _mkdir
#else
    #include <sys/types.h>
#endif
```

**Terminal Operations**:
```cpp
#ifdef _WIN32
    #include <windows.h>
    // Windows console API
#else
    #include <sys/ioctl.h>
    // Unix terminal control
#endif
```

### Supported Platforms
- **Linux**: x86_64, ARM64
- **macOS**: x86_64 (Intel), ARM64 (Apple Silicon)
- **Windows**: x86_64, ARM64

## Build System

### CMake Configuration
The project uses CMake for cross-platform builds with the following structure:

```cmake
cmake_minimum_required(VERSION 3.25)
project(todo-app)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Executable
add_executable(todo-app ${SOURCES})
```

### CI/CD Pipeline
GitHub Actions automates the build and release process:

**Workflow** (`.github/workflows/build-release.yml`):
1. Trigger on version tags (v*)
2. Build matrix for all platform/architecture combinations
3. Cross-compile for ARM64 on Linux
4. Generate SHA256 checksums for all artifacts
5. Create GitHub release with all binaries
6. Attach combined checksums file

**Build Matrix**:
- 6 platform/architecture combinations
- Parallel builds for efficiency
- Automated artifact packaging
- Checksum generation for security

## Extensibility Points

### Adding New Features

**New Task Properties**:
1. Add property to `Task` class
2. Update constructor and getters/setters
3. Modify `serialize()` and `deserialize()` methods
4. Update `UIManager` display if needed

**New Operations**:
1. Add method to `TaskManager`
2. Create flow function in `main.cpp`
3. Add menu option in `UIManager`
4. Update main switch statement

**New Storage Backends**:
1. Create new handler class (e.g., `DatabaseHandler`)
2. Implement same interface as `FileHandler`
3. Replace `FileHandler` instance in `main.cpp`

### Design Patterns Used

**Singleton-like Pattern**: `UIManager` and `Utils` (static utility classes)
**Factory Pattern**: Task deserialization creates objects from data
**Repository Pattern**: `FileHandler` abstracts data storage
**Strategy Pattern**: Can swap storage implementations
**RAII**: Smart pointers and file handles

## Performance Considerations

### Current Approach
- **In-Memory Storage**: All tasks loaded into memory for fast access
- **Linear Search**: O(n) search complexity, suitable for typical use cases
- **Full File Rewrite**: Simple but effective for small datasets

### Scalability Limits
- Designed for personal task management (hundreds to thousands of tasks)
- Linear search becomes slow beyond ~10,000 tasks
- File I/O is synchronous (blocks on save/load)

### Future Optimizations
- Index by category for faster filtering
- Binary search for sorted operations
- Incremental file updates instead of full rewrites
- Async file I/O for large datasets
- Database backend for very large task collections

## Testing Considerations

### Testability
The modular architecture makes the codebase highly testable:

**Unit Testing Opportunities**:
- `Task`: Serialization/deserialization, state transitions
- `TaskManager`: CRUD operations, search/filter logic
- `Utils`: All utility functions
- `FileHandler`: Save/load operations (with mock file system)

**Integration Testing**:
- End-to-end user flows
- File persistence across sessions
- Cross-platform behavior

### Recommended Testing Strategy
1. **Unit Tests**: Test each class in isolation
2. **Integration Tests**: Test component interactions
3. **Platform Tests**: Verify cross-platform compatibility
4. **Manual Tests**: User experience and UI rendering

## Security Considerations

### Input Validation
- All user input is validated before processing
- Integer inputs checked with `isValidInteger()`
- Date format validated with regex
- SQL injection not applicable (no database)

### File System Security
- Tasks stored in local `data/` directory
- No network communication
- No sensitive data encryption (user responsibility)

### Future Enhancements
- Optional task encryption
- Password-protected task files
- Secure export formats

## Conclusion

The CLI Todo App demonstrates a clean, maintainable architecture suitable for a command-line application. The modular design allows for easy extension and modification while maintaining clear separation of concerns. The use of modern C++ features ensures memory safety and cross-platform compatibility.
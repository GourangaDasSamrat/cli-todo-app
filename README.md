# CLI Todo App

A feature-rich, cross-platform command-line task management application built with modern C++. Organize your tasks with categories, priorities, due dates, and more.

![License](https://img.shields.io/github/license/GourangaDasSamrat/cli-todo-app)
![Build Status](https://img.shields.io/github/actions/workflow/status/GourangaDasSamrat/cli-todo-app/build-release.yml)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-blue)

## Features

- ✨ **Intuitive Interface** - Clean, colorful terminal UI with box-drawing characters
- 📝 **Rich Task Details** - Title, description, category, due date, and priority levels
- 🏷️ **Category Organization** - Group and filter tasks by custom categories
- 🔍 **Powerful Search** - Search tasks by title or description
- ✅ **Task Completion Tracking** - Toggle task status with timestamps
- 💾 **Persistent Storage** - Automatic save/load functionality
- 🎨 **Priority Color Coding** - Visual distinction between High, Medium, and Low priority tasks
- ⏰ **Timestamps** - Track when tasks are created and completed
- 🌍 **Cross-Platform** - Runs on Linux, macOS, and Windows (x64 and ARM64)

## Installation

### Download Pre-built Binaries

Download the latest release for your platform from the [Releases](https://github.com/GourangaDasSamrat/cli-todo-app/releases) page:

- **Linux**: `todo-app-vX.X.X-linux-amd64` or `todo-app-vX.X.X-linux-arm64`
- **macOS**: `todo-app-vX.X.X-macos-amd64` or `todo-app-vX.X.X-macos-arm64`
- **Windows**: `todo-app-vX.X.X-windows-amd64.exe` or `todo-app-vX.X.X-windows-arm64.exe`

#### Verify Download (Optional)

```bash
# Download the checksums file
curl -LO https://github.com/GourangaDasSamrat/cli-todo-app/releases/download/vX.X.X/checksums.txt

# Verify on Linux/macOS
sha256sum -c checksums.txt --ignore-missing

# Verify on Windows (PowerShell)
Get-FileHash todo-app-vX.X.X-windows-amd64.exe -Algorithm SHA256
```

#### Make Executable (Linux/macOS)

```bash
chmod +x todo-app-vX.X.X-linux-amd64
./todo-app-vX.X.X-linux-amd64
```

### Build from Source

#### Prerequisites

- CMake 3.25 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

#### Build Steps

```bash
# Clone the repository
git clone https://github.com/GourangaDasSamrat/cli-todo-app.git
cd cli-todo-app

# Create build directory
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build build --config Release

# Run (Linux/macOS)
./build/todo-app

# Run (Windows)
build\Release\todo-app.exe
```

## Usage

### Main Menu

When you launch the application, you'll see the main menu:

```
╔═══════════════════════════════════════════════════╗
║              TODO APPLICATION                      ║
╚═══════════════════════════════════════════════════╝

╔══ MENU ══╗
 1. Add Task
 2. View All Tasks
 3. View by Category
 4. Toggle Task Completion
 5. Delete Task
 6. Search Tasks
 7. Clear All Tasks
 0. Exit
```

### Adding a Task

1. Select option `1` from the main menu
2. Enter task details when prompted:
   - **Title** (required)
   - **Description** (optional)
   - **Category** (default: "General")
   - **Due Date** (format: YYYY-MM-DD, optional)
   - **Priority** (High/Medium/Low, default: Medium)

Example:

```
Enter task title: Complete project documentation
Enter description (optional): Write comprehensive README and API docs
Enter category (default: General): Work
Enter due date (YYYY-MM-DD, optional): 2026-01-15
Enter priority (High/Medium/Low, default: Medium): High
```

### Viewing Tasks

- **View All Tasks** (option `2`): Display all tasks with their details
- **View by Category** (option `3`): Filter tasks by a specific category

Tasks are displayed with:

- Completion status ([✓] or [ ])
- Color-coded priority (Red=High, Yellow=Medium, Green=Low)
- Full task details including timestamps

### Managing Tasks

- **Toggle Completion** (option `4`): Mark a task as complete or incomplete
- **Delete Task** (option `5`): Permanently remove a task
- **Search Tasks** (option `6`): Find tasks by keyword in title or description

### Data Storage

Tasks are automatically saved to `data/tasks.dat` in the application directory. The data persists between sessions, so your tasks are always available when you return.

## Priority Levels

| Priority | Color  | Usage                          |
| -------- | ------ | ------------------------------ |
| High     | Red    | Urgent or critical tasks       |
| Medium   | Yellow | Standard priority tasks        |
| Low      | Green  | Optional or low-priority items |

## Project Structure

```
cli-todo-app/
├── .github/workflows/    # CI/CD configuration
├── include/              # Header files
│   ├── FileHandler.h     # File I/O operations
│   ├── Task.h            # Task model
│   ├── TaskManager.h     # Task management logic
│   ├── UIManager.h       # User interface
│   └── Utils.h           # Utility functions
├── src/                  # Implementation files
├── docs/                 # Documentation
└── CMakeLists.txt        # Build configuration
```

## Contributing

Contributions are welcome! Please read our [Contributing Guidelines](docs/CONTRIBUTING.md) and [Code of Conduct](docs/CODE_OF_CONDUCT.md) before submitting pull requests.

### Development Setup

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Commit your changes: `git commit -m 'Add amazing feature'`
4. Push to the branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

## Architecture

For detailed information about the codebase architecture, see [ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Security

Please report security vulnerabilities to the project maintainers. See [SECURITY.md](docs/SECURITY.md) for details.

## Roadmap

- [ ] Export tasks to JSON/CSV
- [ ] Task sorting options
- [ ] Recurring tasks
- [ ] Task tags and labels
- [ ] Interactive task editing
- [ ] Task dependencies
- [ ] Configuration file support
- [ ] Multiple task lists

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built with modern C++17
- Cross-platform compatibility using CMake
- Automated multi-platform builds with GitHub Actions

## Support

- 📫 **Issues**: [GitHub Issues](https://github.com/GourangaDasSamrat/cli-todo-app/issues)
- 💬 **Discussions**: [GitHub Discussions](https://github.com/GourangaDasSamrat/cli-todo-app/discussions)
- ⭐ **Star this repo** if you find it helpful!

---

Made with ❤️ by [Gouranga Das Samrat](https://github.com/GourangaDasSamrat)

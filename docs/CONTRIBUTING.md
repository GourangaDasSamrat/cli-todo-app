# Contributing to CLI Todo App

Thank you for considering contributing to CLI Todo App! This guide will help you get started.

## Code of Conduct

By participating in this project, you agree to abide by our [Code of Conduct](CODE_OF_CONDUCT.md). Please report unacceptable behavior to [gouranga.samrat@gmail.com](mailto:gouranga.samrat@gmail.com).

## How to Contribute

### Reporting Bugs

1. Check if the bug has already been reported in [Issues](https://github.com/GourangaDasSamrat/cli-todo-app/issues)
2. If not, create a new issue with:
   - Clear title and description
   - Steps to reproduce
   - Expected vs actual behavior
   - Your environment (OS, version, architecture)

### Suggesting Features

1. Search existing [feature requests](https://github.com/GourangaDasSamrat/cli-todo-app/issues?q=is%3Aissue+label%3Aenhancement)
2. Open a new issue describing:
   - The problem you're trying to solve
   - Your proposed solution
   - Any alternatives considered

### Contributing Code

1. **Fork and clone** the repository
2. **Create a branch**: `git checkout -b feature/your-feature-name`
3. **Make your changes** following our coding standards
4. **Test thoroughly** on your platform
5. **Commit** with clear messages: `feat(scope): description`
6. **Push** to your fork: `git push origin feature/your-feature-name`
7. **Open a Pull Request** with a clear description

## Development Setup

### Prerequisites

- CMake 3.25+
- C++17 compiler (GCC 7+, Clang 5+, MSVC 2017+)

### Build

```bash
git clone https://github.com/YOUR-USERNAME/cli-todo-app.git
cd cli-todo-app
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/todo-app  # Linux/macOS
```

## Coding Standards

### Style Guide

- **Indentation**: 4 spaces
- **Line length**: Max 100 characters
- **Naming**:
  - Classes: `PascalCase`
  - Functions/variables: `camelCase`
  - Constants: `UPPER_SNAKE_CASE`
- **C++17 standard**: Use modern C++ features
- **Smart pointers**: Prefer `unique_ptr`/`shared_ptr`
- **Const correctness**: Mark methods/parameters `const` where applicable

### Example

```cpp
class TaskManager {
private:
    std::vector<std::unique_ptr<Task>> tasks;

public:
    void addTask(const std::string& title);
    Task* getTask(int id) const;
};
```

## Commit Messages

Follow [Conventional Commits](https://www.conventionalcommits.org/):

```
<type>(<scope>): <description>

Types: feat, fix, docs, style, refactor, test, chore
```

**Examples:**

- `feat(task): add priority color coding`
- `fix(file): handle missing data directory`
- `docs(readme): update build instructions`

## Pull Request Guidelines

- Keep PRs focused on a single feature/fix
- Update documentation if needed
- Reference related issues: `Fixes #123`
- Ensure CI checks pass
- Respond to review feedback promptly

### PR Checklist

- [ ] Code follows style guidelines
- [ ] Tested on at least one platform
- [ ] Documentation updated
- [ ] Commit messages follow convention
- [ ] No merge conflicts

## Need Help?

- Check existing [Issues](https://github.com/GourangaDasSamrat/cli-todo-app/issues)
- Start a [Discussion](https://github.com/GourangaDasSamrat/cli-todo-app/discussions)
- Email: [gouranga.samrat@gmail.com](mailto:gouranga.samrat@gmail.com)

## Recognition

Contributors are recognized in release notes and the GitHub Contributors page.

---

Thank you for contributing! 🚀

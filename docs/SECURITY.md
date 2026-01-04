# Security Policy

## Supported Versions

We release patches for security vulnerabilities. Currently supported versions:

| Version | Supported          |
| ------- | ------------------ |
| 1.0.x   | :white_check_mark: |
| < 1.0   | :x:                |

## Reporting a Vulnerability

We take the security of CLI Todo App seriously. If you believe you have found a security vulnerability, please report it to us as described below.

### How to Report a Security Vulnerability

**Please do not report security vulnerabilities through public GitHub issues.**

Instead, please report them via one of the following methods:

1. **GitHub Security Advisory**: Use the [Security Advisory](../../security/advisories/new) feature
2. **Email**: Send details to the repository maintainer (check GitHub profile for contact)

### What to Include

#### Please include the following information in your report:

- Type of vulnerability
- Full paths of source file(s) related to the vulnerability
- Location of the affected source code (tag/branch/commit or direct URL)
- Step-by-step instructions to reproduce the issue
- Proof-of-concept or exploit code (if possible)
- Impact of the vulnerability, including how an attacker might exploit it

### What to Expect

- **Acknowledgment**: We'll acknowledge your report within 48 hours
- **Updates**: We'll provide regular updates on our progress
- **Timeline**: We aim to release a fix within 30 days for critical issues
- **Credit**: We'll credit you in the security advisory (unless you prefer to remain anonymous)

## Security Considerations

### Data Storage

- All task data is stored locally in `data/tasks.dat`
- No data is transmitted over the network
- File permissions should be set appropriately by the user

### Input Validation

- All user inputs are validated before processing
- Integer overflow protection in place
- String length limits enforced

### Known Limitations

1. **File System Access**: The application requires write access to the `data/` directory
2. **No Encryption**: Task data is stored in plain text format
3. **Local Only**: This is a single-user, local application with no authentication

## Best Practices for Users

1. **File Permissions**: Ensure proper file permissions on `data/tasks.dat`
   ```bash
   chmod 600 data/tasks.dat
   ```

2. **Sensitive Data**: Avoid storing highly sensitive information in task descriptions

3. **Updates**: Keep the application updated to the latest version

4. **Verification**: Always verify downloaded binaries using the provided checksums
   ```bash
   sha256sum -c checksums.txt
   ```

## Security Updates

Security updates will be released as patch versions (e.g., 1.0.1) and announced in:
- GitHub Releases
- Security Advisories
- Repository README

## Scope

This security policy applies to:
- The CLI Todo App source code
- Official binary releases
- Documentation

It does not apply to:
- Third-party forks
- User modifications
- Unofficial builds

## Contact

For security-related questions that are not vulnerabilities, please open a regular GitHub issue with the `security` label.

## Attribution

We appreciate the security research community and will acknowledge researchers who responsibly disclose vulnerabilities to us.

---

**Last Updated**: January 2025

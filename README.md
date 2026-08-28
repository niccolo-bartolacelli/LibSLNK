# LibSLNK

### Low-level C library for working with Microsoft Shell Link (`.lnk`) files.

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_%28programming_language%29)
[![Version](https://img.shields.io/badge/version-0.1-orange.svg)](https://github.com/niccolo-bartolacelli/LibSLNK)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)

**LibSLNK** is a low-level C API for creating, configuring, and accessing the binary structure of Microsoft Shell Link (`.lnk`) files.

The project is designed for developers who need direct control over Shell Link data without hiding the underlying file format behind a high-level abstraction.

> **⚠️ Security & stability notice:** LibSLNK provides low-level access to `.lnk` structures. Certain configurations can produce unexpected or potentially dangerous behavior. Review the security considerations below before using it with untrusted or self-referential links.

---

## Why LibSLNK?

Windows shortcut files look simple from the outside, but `.lnk` files contain a structured binary representation of a Shell Link.

LibSLNK exposes that structure through a C API, allowing applications to programmatically construct and manipulate Shell Link files.

The library follows a simple workflow:

```text
Initialize
    ↓
Configure
    ↓
Build
    ↓
Free
```

This keeps the API small while still providing low-level control over the resulting file.

---

## Quick Start

A minimal example creating a shortcut to `C:\test\a.txt`:

```c
#include "LibSLNK.h"

int main(void)
{
    struct MSShellLink lnk;

    /* Initialize */
    LnkInit(&lnk);

    /* Configure */
    LnkSetPath(&lnk, L"C:\\test\\a.txt");
    LnkSetString(
        &lnk,
        L"a.txt - Text File linked with LibSLNK",
        LNK_SD_NAME_STRING
    );

    /* Build */
    LnkBuild(&lnk, L"C:\\Users\\nicco\\Desktop\\buildlink.lnk");

    /* Cleanup */
    LnkFree(&lnk);

    return 0;
}
```

The basic API therefore consists of four stages:

1. **Initialization** — create and initialize an `MSShellLink` structure.
2. **Configuration** — specify the target and other link properties.
3. **Build** — serialize the configured link to a `.lnk` file.
4. **Cleanup** — release resources allocated by the library.

---

## API

The main interface is exposed through `LibSLNK.h`.

### Core functions

| Function         | Purpose                               |
| ---------------- | ------------------------------------- |
| `LnkInit()`      | Initialize an `MSShellLink` structure |
| `LnkSetPath()`   | Set the link target                   |
| `LnkSetString()` | Configure string properties           |
| `LnkBuild()`     | Build/write the `.lnk` file           |
| `LnkFree()`      | Release resources                     |

The library also exposes structures representing the underlying Shell Link data.

In normal usage, however, applications should prefer the provided API functions rather than directly manipulating the internal structures.

---

## Architecture

At its core, LibSLNK separates **link representation** from **link construction**:

```text
                 ┌──────────────────────┐
                 │    MSShellLink       │
                 │                      │
                 │  Shell Link state    │
                 └──────────┬───────────┘
                            │
             ┌──────────────┼──────────────┐
             │              │              │
             ▼              ▼              ▼
        LnkSetPath     LnkSetString    Other API
             │              │              │
             └──────────────┼──────────────┘
                            ▼
                      ┌───────────┐
                      │ LnkBuild  │
                      └─────┬─────┘
                            ▼
                       .lnk file
```

This approach makes the library useful both as a practical API and as a tool for exploring the internals of the Shell Link format.

---

## Security Considerations

LibSLNK operates at a deliberately low level.

**Do not assume that every valid API configuration is safe to execute on a real system.**

In particular, configurations involving links that point to other links can lead to unexpected behavior.

For example, attempting to create an `.lnk` file that points to itself while allowing link-to-link targets can result in a system crash under the conditions currently documented by the project.

```text
example.lnk
     │
     └──────────────► example.lnk
```

If you are experimenting with unusual Shell Link configurations:

* Use a virtual machine or isolated test environment.
* Avoid testing against production systems.
* Treat externally supplied `.lnk` files as untrusted input.
* Do not enable permissive link configurations unless you understand their consequences.

**This project is experimental software. Use it at your own risk.**

---

## Project Structure

```text
LibSLNK/
├── src/
│   └── ...
├── examples/
│   └── ...
├── test.c
├── LibSLNK.h
└── README.md
```

---

## Status

**Version:** `0.1`

LibSLNK is currently an experimental project and its API may change.

The project is particularly useful for:

* Windows internals research
* Shell Link format experimentation
* systems programming
* security research
* binary file format analysis
* applications requiring low-level `.lnk` manipulation

---

## Research & Security

LibSLNK was developed as a low-level exploration of the Microsoft Shell Link format.

During development, unusual link-resolution behavior was investigated, including self-referential link configurations.

If you discover a security issue, please avoid publicly disclosing sensitive details before allowing the issue to be investigated responsibly.

For non-sensitive bugs and improvements, opening a GitHub issue or pull request is welcome.

---

## Contributing

Contributions, experiments, bug reports, and improvements are welcome.

Before contributing, please keep in mind that LibSLNK intentionally operates close to the underlying file format. Changes to serialization or link resolution should therefore be tested carefully.

---

## License

See the repository for the current licensing information.

---

## Author

**Niccolò Bartolacelli**

GitHub: [@niccolo-bartolacelli](https://github.com/niccolo-bartolacelli)

---

<p align="center">
  <i>Low-level access. Minimal abstraction. Direct control.</i>
</p>

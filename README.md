# LibSLNK

### Low-level C library for working with Microsoft Shell Link (`.lnk`) files.

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_%28programming_language%29)
[![Version](https://img.shields.io/badge/version-0.1-orange.svg)](https://github.com/niccolo-bartolacelli/LibSLNK)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)

**LibSLNK** is a low-level C API for creating, configuring, and accessing the binary structure of Microsoft Shell Link (`.lnk`) files.

The project is designed for developers who need direct control over Shell Link data without hiding the underlying file format behind a high-level abstraction.

---

## Overview

LibSLNK exposes `.lnk` files structured binary representation through a C API, allowing applications to programmatically construct and manipulate Shell Link files.

The library follows a simple workflow:

```text
Initialize
    ↓
Configure
    ↓
  Build
```

This keeps the API small while still providing low-level control over the resulting file.

---

## Quick Start

A minimal example creating a shortcut to `C:\test\a.txt`:

```c
#include <stdio.h>
#include "LibSLNK.h"

int main(void)
{
    FILE *fptr;
    struct MSShellLink *lnk;

    /* Initialize */
    LnkInit(lnk);

    /* Configure */
    LnkSetPath(lnk, L"C:\\test\\a.txt");
    LnkSetString(
        lnk,
        L"a.txt - Text File linked with LibSLNK",
        LNK_SD_NAME_STRING
    );

    /* Build */
	fptr = _wfopen(L"C:\\test\\lnk_to_a.txt.lnk", L"wb");
    if (fptr) {
        LnkBuild(lnk, fptr);
        fclose(fptr);   
    }

    /* Cleanup */
    LnkFree(lnk);

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

| Function         | Description                           |
| ---------------- | ------------------------------------- |
| `LnkInit()`      | Initialize an `MSShellLink` structure |
| `LnkSetPath()`   | Set the link target                   |
| `LnkBuild()`     | Build/write the `.lnk` file           |
| `LnkFree()`      | Release resources                     |

The library also exposes structures representing the underlying Shell Link data.

In normal usage, however, applications should prefer the provided API functions rather than directly manipulating the internal structures, particularly for elements which have an associated API function.

### More functions

| Function                         | Description                                                              |
| -------------------------------- | ------------------------------------------------------------------------ |
| `LnkSetFlag()` et al.            | Set, Clear or Check Link Flags (`LNK_FLAG_*`)                            |
| `LnkSetFileAttribute()` et al.   | Set, Clear or Check File Attributes (`LNK_FILE_ATTRIBUTE_*`)             |
| `LnkSetCreationTime()` et al.    | Set or Get FILETIMEs (Creation, Access, Write)                           |
| `LnkSetHotKey()` et al.          | Set, Get or Clear Link activation hotkey                                 |
| `LnkSetPath()`                   | Create the Link IDList structure from an existing path                   |
| `LnkGetPath()`                   | Decode the Link IDList structure to a string path (_under development_)  |
| `LnkSetString()` et al.          | Set or Clear Link StringData structures (`LNK_SD_*`)                     |

See `examples` for a more in-depth explanation.

---

## Architecture

Architecturally, LibSLNK separates **link representation** from **link construction**:

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
        LnkSetPath      LnkSetFlag     Other API
             │              │              │
             └──────────────┼──────────────┘
                            ▼
                      ┌───────────┐
                      │ LnkBuild  │
                      └─────┬─────┘
                            ▼
                       .lnk file
```

This approach gives the flexibility to use it as a higher level API to manipulate common LNK elements or to directly interact with a 1:1 representation of the actual LNK data.

---

## Security Considerations

LibSLNK operates at a deliberately low level.

**Do not assume that every valid API configuration is safe to execute on a real system.**

If you are experimenting with unusual Shell Link configurations:

* Use a virtual machine or isolated test environment.
* Avoid testing against production systems.
* Treat externally supplied `.lnk` files as untrusted input.
* Do not enable permissive link configurations unless you understand their consequences.

**This project is experimental software.**

---

## Project Structure

LibSLNK comes with a simple structure, and exposes its whole API through a single header file (`"LibSLNK.h"`)

```text
LibSLNK/
├── src/
│   └── ...
├── examples/
│   └── ...
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

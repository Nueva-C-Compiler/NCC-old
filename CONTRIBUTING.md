# Contributing Guidelines

This document is a work in process and details some loose guidelines for contributing code to NCC.

# Quality of Life
- **Comment your code.** The author of the code should not be the only one who understands it.
- Divide large blocks of code into multiple functions - it is difficult to focus on code that has too many moving parts, and therefore harder to debug.
- Name variables such that their purpose is easily identifiable
- Keep indentation/naming style consistent within a document. `snake_case` and K&R is nice.

# Stability
- **Do not commit to master.** Create branches for changes and create pull requests so that other contributors can review them.
- Do not silence compiler warnings. Turn them up. Compiler warnings are good.
- Consider undefined behavior. If you're doing something hack-y (like weird pointer casts, accessing past arrays...) look up the standard and check if this results in undefined behavior.
  - *Do not rely on undefined behavior.*
  - Also consider things like overflows and initization when writing code
  - Compiler warnings help with this process.
- Pay attention to memory allocation and free() your pointers.

# Misc
- One-line `if`s (`if (condition) statement;`) are OK, but the following is not as it is the source of many notable bugs.
```
if (condition)
    statement;
```
- Don't leave sections of commented-out code in your code
- Avoid #ifdefs when possible
- Use <stdint.h> for specificity.
- Avoid complicated uses of obscure features - or jus write large comment blocks explaining them

# Code Review
Check if the submitted code looks good, then check if it is following these guidelines.

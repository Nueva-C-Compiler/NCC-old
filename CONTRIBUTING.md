# Contributing Guidelines

This document is a work in process and details some loose guidelines for contributing code to NCC.

# Quality of Life
- **Comment your code.** The author of the code should not be the only one who understands it.
- Divide large blocks of code into multiple functions - it is difficult to focus on code that has too many moving parts, and therefore harder to debug.
- Do not prematurely optimize, especially if it makes things harder to understand.

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

# Pull/Push
Always pull before you begin working on something new. If you encounter a merge conflict, double check you actually resolved it instead of deleting someone's code.

# Commits
- Commit messages should describe what you changed in past tense. Example: "Added syntax tree data structure" or "Updated properties of node struct"
  - Commit messages should be coherent and spelled correctly.
  - Treat commit messages relatively seriously, they are meant to aid debugging.

  
  

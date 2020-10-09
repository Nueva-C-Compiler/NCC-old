# Style Guide

Maintaining a consistent coding style helps keep things coherent and easy to maintain.
This is a work in progress, and will likely be changed quite a bit.
<!-- This is essentially a slightly modified and reduced version of the [Google C++ Style Guide] (https://google.github.io/styleguide/cppguide.html). !-->

## Formatting
### Indentation
An indent is 4 spaces.

### Brackets
Use modified K&R style: 
```
if (condition) {
    statement;
} else if (...) {
    statement
} else {
    statement;
}
```
```
while (int i = 0; i < bound; i++) {
    statement;
}
```

### Line Length
This doesn't matter too much - ideally under 80 characters, though.

### Misc
- Prefer `0.1` to `.1` for floating point (or double) literals.

## Naming
### Variables
- Variable names should be in `snake_case`. (Example: `node_ptr` or `global_id` as opposed to `nodePtr`/`globalId`).
- Variable names should be sufficiently explanatory (even to someone not working on your section!) while also short.

### Functions
- Name functions such that their purpose is clear.
- Same naming as variables.

### Macros
- Macros are UPPER_CASE. Example: `#define MAX_LINE_SIZE 1024`

### Files
- Source files are in lower case separated by underscores like `lexical_analyzer.c`.
- Header files end in .h, and should be representative of their contents: `syntax_tree.h`

### Misc 
- Prefer struct to typedef so as to be more explicit.

## Comments
Code should explain itself - do not justify overly complicated code with an abundance of comments.


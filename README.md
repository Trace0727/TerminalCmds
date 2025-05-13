# TerminalCmds

A C-based console program that mimics basic DOS shell commands (`cd`, `dir`, `type`, `del`, `ren`, `copy`) using equivalent UNIX operations. The program includes support for a `help` command to describe available commands, a typed `exit` option for IDE environments, and clean termination via `Ctrl+C` in terminal environments.

---

## Project Structure

    TerminalCmds/
    ├── src/
    │   └── TerminalCmds.c
    └── 

---

## Core C File

### `TerminalCmds.c`
Implements the entire command-line interface:
- Simulates DOS commands using UNIX functions and system calls:
  - `cd <directory>` → changes directory using `chdir()`
  - `dir` → lists files using `ls`
  - `type <file>` → shows file type using the `file` command
  - `del <file>` → deletes a file using `remove()`
  - `ren <old> <new>` → renames a file using `mv`
  - `copy <src> <dest>` → copies a file using `cp`
- Includes:
  - `help`: prints a list of supported commands and their descriptions
  - `exit`: cleanly stops the program in IDEs
  - `Ctrl+C` signal handling using `SIGINT` to print `program exited` and terminate

---

## Future Enhancements
- Add support for additional shell features (`mkdir`, `rmdir`, `cat`)
- Enhance output formatting with colors or padding
- Implement history or autocomplete using GNU Readline
- Log commands to a file for session replay or auditing

---

## License
This project is licensed for personal, non-commercial educational use only. Redistribution or modification without permission is not allowed.  
See the [LICENSE] file for full details.

---

## Author
**Trace Davis**  
- GitHub: https://github.com/Trace0727  
- LinkedIn: https://www.linkedin.com/in/trace-d-926380138/

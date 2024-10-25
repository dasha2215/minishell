# **Minishell**

Minishell is a simple shell implementation. It replicates core features of the Bash shell, offering basic functionalities like command execution, built-in commands, pipelines, redirection, and more, all written in C.

## **Table of Contents**

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Supported Commands](#supported-commands)
- [Built-in Commands](#built-in-commands)
- [Redirection & Pipelines](#redirection--pipelines)
- [Signal Handling](#signal-handling)
- [Error Handling](#error-handling)
- [Development & Structure](#development--structure)
- [Acknowledgments](#acknowledgments)

## **Features**

Minishell supports a variety of Bash-like features, including:

- **Prompt display**: Shows a prompt when waiting for a new command.
- **History management**: Keeps a history of commands during the session.
- **Command execution**: Executes external binaries based on `$PATH`, as well as relative and absolute paths.
- **Pipelines and redirection**: Supports piping between commands and I/O redirection.
- **Environment variables**: Expands environment variables (e.g., `$HOME`, `$PATH`, `$?`).
- **Signal handling**: Responds to signals like `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` to manage process flow.
- **Built-in commands**: Implements essential built-ins like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Error messages**: Displays error messages similar to Bash.

## **Installation**

To build and run minishell, you'll need to install the `readline` library:

1. **Install readline**:

   - On **macOS**:
     ```bash
     brew install readline
     ```
     
   - On **Linux (Debian/Ubuntu)**:
     ```bash
     sudo apt-get install libreadline-dev
     ```
     
2. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/minishell.git
    cd minishell
    ```

3. **Build the project**:
    ```bash
    make
    ```

4. **Run minishell**:
    ```bash
    ./minishell
    ```

## **Usage**

Once started, minishell displays a prompt (`minishell $`) and waits for user input.

### **Basic Commands**
Commands can be run like in Bash:
```bash
minishell $ ls -l
minishell $ pwd
minishell $ echo "Hello, World!"
```

### **History**
Use the up and down arrow keys to navigate through command history during the session.

### **Exit**
To exit minishell, use the `exit` command or press `Ctrl+D`:
```bash
minishell $ exit
```

## **Supported Commands**

Minishell supports the execution of all commands available in the system’s `$PATH`. It can run binaries from standard locations like `/bin/` and `/usr/bin/`, as well as relative or absolute paths provided by the user.

### **Example**:
```bash
minishell $ /bin/ls
minishell $ ./your_script.sh
```

## **Built-in Commands**

Minishell implements the following built-ins:

1. **`echo`**:
   - Options: `-n` (no newline)
   - Example: `echo -n "Hello, no newline"`

2. **`cd`**:
   - Supports relative and absolute paths.
   - Example: `cd /home/user` or `cd ../`

3. **`pwd`**:
   - Prints the current working directory.
   - Example: `pwd`

4. **`export`**:
   - Sets environment variables.
   - Example: `export VAR=value`

5. **`unset`**:
   - Unsets environment variables.
   - Example: `unset VAR`

6. **`env`**:
   - Displays environment variables.
   - Example: `env`

7. **`exit`**:
   - Exits the shell with a status.
   - Example: `exit 0`

## **Redirection & Pipelines**

Minishell supports:

- **Input redirection** (`<`): Redirects input from a file.
  - Example: `cat < file.txt`
  
- **Output redirection** (`>`): Redirects output to a file.
  - Example: `echo "Hello" > file.txt`
  
- **Append redirection** (`>>`): Appends output to a file.
  - Example: `echo "Another line" >> file.txt`
  
- **Heredoc** (`<<`): Reads input until a delimiter is reached.
  - Example: `cat << EOF`

- **Pipes** (`|`): Pipes output from one command to another.
  - Example: `ls -l | grep minishell`

## **Signal Handling**

Minishell handles the following signals:

- **`Ctrl+C`** (`SIGINT`): Interrupts the current command and returns to the prompt.
- **`Ctrl+D`** (`EOF`): Exits the shell if typed at an empty prompt.
- **`Ctrl+\`** (`SIGQUIT`): Quits the current process, similar to Bash.

## **Error Handling**

Minishell displays error messages similar to Bash, including:

- **Command not found**: If a command cannot be found in the `$PATH`.
- **Redirection errors**: If a file cannot be read/written.
- **Invalid option**: If an unsupported option is provided for a built-in.

## **Development & Structure**

Minishell is developed in C with the following key files:

- **`main.c`**: Entry point of the program.
- **`parser.c`**: Handles command parsing and syntax analysis.
- **`executor.c`**: Manages command execution, redirection, and piping.
- **`builtins.c`**: Implements built-in commands.
- **`signals.c`**: Handles signal processing and handling.

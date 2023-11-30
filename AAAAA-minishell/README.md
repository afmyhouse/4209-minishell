# minishell
Simple bash-like shell

## About
minishell is a simple shell based on bash. It is able to parse input from the user and execute commands in a similar way to bash.

The capabilities of minishell are the following:
- Working history.
- Executes commands by searching the `$PATH` variable or by absolute or relative path.
- `"`,`'`: Interprets quotations the same way as bash, where parameters are only expanded if they are contained in `"`. Nested quotation marks are handled the same way as bash. Unclosed quotes or escaped quotes are not handled.
- Redirections:
   - `>`: redirects output
   - `>>`: redirects output in append mode
   - `<`: redirects input
   - `<<`: heredoc
- `|`: Interprets pipes in the same manner as bash, where the output of the command before the pipe is passed as input for the one after the pipe. Pipes can be chained.
- Environment Variables: `$` followed by a sequence of characters are expanded to the value given in the environment.
- `$?`: Returns the exit code of the previous command.
- Signals:
   - `ctrl-C`: SIGINT - Sends an interupt signal to the running program. If in interactive mode, displays a prompt on a new line.
   - `ctrl-D`: EOF - Sends an end of file to the running program. If in interactive mode, exits the current shell.
   - `ctrl-\`: SIGQUIT - Sends a quit signal to the running program. If in interactive mode, does nothing.
- Reimplements the following "built-ins":
   - `echo`: with option `-n`
   - `cd`: with relative or absolute path. Does not interpret `-` or `~`.
   - `pwd`: with no options.
   - `export`: with no options.
   - `unset`: with no options.
   - `env`: with no options or arguments
   - `exit`: with no options.

minishell parses the input using a lexer and parser, first splitting the string into tokens, then parsing those tokens to fill a structure that is used to execute the necessary commands in the correct order and with the correct arguments.

## Example usage
[![asciicast](https://asciinema.org/a/HwcCVUJPnW8qhRmqa5hnolgqZ.svg)](https://asciinema.org/a/HwcCVUJPnW8qhRmqa5hnolgqZ)

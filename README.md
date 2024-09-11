
# Compiler-B Lexical Analyzer

This repository contains the implementation of a lexical analyzer (lexer) for the small-b language written in C. The lexical analyzer processes a program's source file and generates a list of tokens. Each token is identified by its type (identifier, integer, string, etc.) and location in the source file. Additionally, the analyzer handles errors by producing error messages and performing error recovery to continue processing.

## Features

- Reads a source file written in the small-b language.
- Generates a list of tokens with their types and positions in the source file.
- Supports token types such as:
  - Identifiers
  - Integers
  - Strings
  - Special characters
  - Comments
- Performs error handling and recovery when invalid input is encountered.
- Includes a set of test cases to cover various language features, including:
  - Comments
  - Strings
  - Special characters
  - Invalid input handling and error recovery.

## Usage

1. Clone the repository:
    ```bash
    git clone https://github.com/ashkanvg/compiler-b-lexical-analyzer.git
    ```

2. Rename the file path in the code. Use your file path instead of `test.txt` in `main.cpp`. 
2. Compile the lexical analyzer:
    ```bash
    gcc main.c -o lexer
    ```

3. Run the lexical analyzer with a small-b source file:
    ```bash
    ./lexer
    ```

4. The output will display the list of tokens with their types and locations in the source file.

## Error Handling

If an invalid input is discovered, the analyzer will generate an error message and attempt to recover from the error. The error recovery ensures that the analysis continues for the remainder of the input file.


## License

This project is licensed under the MIT License.

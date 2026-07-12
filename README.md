# Simple Calculator

A simple calculator written in **C** that parses and evaluates mathematical expressions by building an **Abstract Syntax Tree (AST)**.

This project started as a learning exercise. My original goal was to build a compiler from scratch, but I quickly realized that I was missing many of the fundamental concepts required to do so. Instead of jumping directly into compiler development, I decided to build a calculator that implements many of the same core ideas used in compilers and interpreters.

By building this project from the ground up, I wanted to understand topics such as:

* [Lexical Analysis (Lexer)](https://en.wikipedia.org/wiki/Lexical_analysis)
* [Parsing](https://en.wikipedia.org/wiki/Parsing)
* [Recursive Descent Parsing](https://en.wikipedia.org/wiki/Recursive_descent_parser)
* [Abstract Syntax Trees (AST)](https://en.wikipedia.org/wiki/Abstract_syntax_tree)
* Expression Evaluation
* Operator Precedence
* Memory Management
* Recursive Algorithms

Although this is "just" a calculator, the overall architecture is very similar to the front-end of a simple compiler or interpreter.

---

## Project Structure

```
.
├── include
│   ├── ast.h
│   ├── lexer.h
│   ├── parser.h
│   ├── evaluator.h
│   └── calculator.h
│
├── src
│   ├── ast.c
│   ├── lexer.c
│   ├── parser.c
│   ├── evaluator.c
│   ├── calculator.c
│   └── main.c
│
├── Makefile
└── README.md
```

---

## How It Works

The calculator processes an expression in several stages:

```
Input
   │
   ▼
Lexer
   │
   ▼
Parser
   │
   ▼
Abstract Syntax Tree (AST)
   │
   ▼
Evaluator
   │
   ▼
Result
```

---

## 1. Lexer

The lexer converts raw text into a sequence of tokens.

A lexer is responsible for understanding individual pieces of input, such as numbers and operators, without understanding the meaning of the expression.

Example:

```
Input:

2 + 3 * 4
```

becomes:

```
NUMBER(2)
PLUS
NUMBER(3)
MUL
NUMBER(4)
END
```

The lexer currently handles:

* Numbers
* Operators
* Parentheses
* Whitespace
* End of input detection

More information about lexical analysis:

https://en.wikipedia.org/wiki/Lexical_analysis

---

## 2. Parser

The parser consumes the tokens produced by the lexer and checks whether they follow the calculator grammar.

This project uses a **recursive descent parser**.

Grammar:

```text
Expression := Term (('+' | '-') Term)*

Term       := Factor (('*' | '/') Factor)*

Factor     := NUMBER
            | '(' Expression ')'
```

This grammar ensures correct operator precedence:

```
2 + 3 * 4
```

is interpreted as:

```
2 + (3 * 4)
```

rather than:

```
(2 + 3) * 4
```

More about recursive descent parsing:

https://en.wikipedia.org/wiki/Recursive_descent_parser

---

## 3. Abstract Syntax Tree

The parser builds an AST representing the structure of the expression.

Example:

Expression:

```
2 + 3 * 4
```

AST:

```
        +
       / \
      2   *
         / \
        3   4
```

The AST removes unnecessary syntax details and keeps only the important structure needed for evaluation.

Instead of immediately calculating values while parsing, the parser first creates a tree representation. This makes the design closer to how real interpreters and compilers work.

More information about ASTs:

https://en.wikipedia.org/wiki/Abstract_syntax_tree

---

## 4. Evaluation

The evaluator recursively walks through the AST and calculates the final result.

Example:

```
evaluate(+)
│
├── evaluate(2)
│
└── evaluate(*)
      │
      ├── evaluate(3)
      └── evaluate(4)
```

Result:

```
14
```

The evaluator uses:

```c
int evaluate(ASTNode *node, double *result);
```

The function returns:

```
0 -> success
1 -> failure
```

The calculated value is returned through the `result` pointer.

This allows the evaluator to report errors such as:

* Division by zero
* Invalid AST nodes
* Unknown node types

without terminating the entire program.

---

## 5. Calculator Module

The calculator module connects all components together.

Its responsibility is to manage the complete calculation pipeline:

```
Expression
    |
    ▼
Parser
    |
    ▼
AST
    |
    ▼
Evaluator
    |
    ▼
Result
```

This keeps the lexer, parser, AST, and evaluator independent from each other.

---

# Current Features

* Integer arithmetic
* Addition (`+`)
* Subtraction (`-`)
* Multiplication (`*`)
* Division (`/`)
* Parentheses
* Operator precedence
* Recursive descent parser
* Abstract Syntax Tree generation
* AST printing for debugging
* AST memory cleanup
* Expression evaluation
* Error handling for invalid expressions and division by zero

---

# Improvements Made

## Lexer

* Added token-based processing.
* Separated tokenization from parsing.
* Improved handling of operators and numbers.

## Parser

* Added safer error handling.
* Prevented invalid AST creation after parsing failures.
* Improved recursive descent structure.
* Added support for nested expressions using parentheses.

## AST

* Added AST node creation functions.
* Added AST printing for debugging.
* Added recursive memory cleanup using `free_ast()`.

## Evaluator

* Changed evaluation from returning only a number to using:

```c
int evaluate(ASTNode *node, double *result);
```

This allows:

* Returning calculation results separately.
* Reporting evaluation failures.
* Handling errors without immediately exiting.

---

# Planned Improvements

This project is still a work in progress.

Future features include:

* [ ] Better syntax error messages with token positions
* [ ] Detect invalid trailing input
* [ ] Floating-point numbers
* [ ] Unary minus (`-5`, `-(2 + 3)`)
* [ ] Exponentiation (`^`)
* [ ] Modulo operator (`%`)
* [ ] Built-in constants (`pi`, `e`)
* [ ] Mathematical functions (`sqrt`, `pow`, `sin`, `cos`, ...)
* [ ] Interactive REPL
* [ ] Variable support
* [ ] Token debugging mode
* [ ] AST visualization mode
* [ ] Automated tests

---

# Building

Compile the project using:

```bash
make
```

Run:

```bash
./bin/calculator
```

Example:

```
Input:
(2 + 3) * 4

Output:
20
```

---

# Why This Project?

The goal of this project is not to build the most feature-rich calculator.

The goal is to understand how programming language tools work internally by implementing the core components myself instead of relying on existing libraries.

Building this calculator has been a practical way to understand how source code is transformed step by step:

```
Raw text
    |
    ▼
Tokens
    |
    ▼
Syntax Tree
    |
    ▼
Evaluation
    |
    ▼
Result
```

These same concepts form the foundation of interpreters and compilers.

Once this project is complete, I plan to continue learning by exploring topics such as semantic analysis, symbol tables, bytecode generation, and eventually building a small programming language or compiler.


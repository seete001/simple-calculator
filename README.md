# Simple Calculator

A simple calculator written in **C** that parses and evaluates mathematical expressions by building an **Abstract Syntax Tree (AST)**.

This project started as a learning exercise. My original goal was to build a compiler from scratch, but I quickly realized that I was missing many of the fundamental concepts required to do so. Instead of jumping directly into compiler development, I decided to build a calculator that implements many of the same core ideas used in compilers and interpreters.

By building this project from the ground up, I wanted to understand topics such as:

* Lexical Analysis (Lexer)
* Parsing
* Recursive Descent Parsing
* Abstract Syntax Trees (AST)
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
│   └── parser.h
├── src
│   ├── ast.c
│   ├── lexer.c
│   ├── main.c
│   └── parser.c
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

### 1. Lexer

The lexer converts raw text into a sequence of tokens.

Example:

```
Input:

2 + 3 * 4
```

becomes

```
NUMBER(2)
PLUS
NUMBER(3)
MUL
NUMBER(4)
END
```

---

### 2. Parser

The parser consumes the tokens using a recursive descent parser.

Grammar:

```text
Expression := Term (('+' | '-') Term)*

Term       := Factor (('*' | '/') Factor)*

Factor     := NUMBER
            | '(' Expression ')'
```

This grammar ensures the correct operator precedence.

---

### 3. Abstract Syntax Tree

The parser builds an AST representing the expression.

Example:

```
2 + 3 * 4
```

becomes

```
      +
     / \
    2   *
       / \
      3   4
```

instead of

```
      *
     / \
    +   4
   / \
  2   3
```

which would produce the wrong result.

---

### 4. Evaluation

The evaluator recursively traverses the AST.

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

---

## Current Features

* Integer arithmetic
* Addition (`+`)
* Subtraction (`-`)
* Multiplication (`*`)
* Division (`/`)
* Parentheses
* Recursive descent parser
* Abstract Syntax Tree generation
* AST evaluation

---

## Planned Improvements

This project is still a work in progress.

Planned features include:

* [ ] Free all allocated AST nodes (`free_ast`)
* [ ] Better syntax error messages
* [ ] Detect invalid trailing input
* [ ] Floating-point numbers
* [ ] Unary minus
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

## Building

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

## Why This Project?

The goal of this project is not to build the most feature-rich calculator.

The goal is to learn how programming language tools work internally by implementing the core components myself instead of relying on existing libraries.

Building this calculator has been a practical way to understand how source code is transformed step by step—from raw text, to tokens, to a syntax tree, and finally into a computed result. These same ideas form the foundation of interpreters and compilers.

Once this project is complete, I plan to continue learning by exploring topics such as semantic analysis, symbol tables, bytecode generation, and eventually building a small programming language or compiler.


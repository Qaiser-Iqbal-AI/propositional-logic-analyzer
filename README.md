# propositional-logic-analyzer
A comprehensive C++ program for propositional logic analysis, including truth table generation, argument validation, equivalence checking, and automated reasoning using rules of inference.

# Propositional Logic Analyzer in C++

This project is a comprehensive C++ implementation of a propositional logic analysis system.
It allows users to evaluate logical expressions, generate truth tables, validate arguments,
check logical equivalence, and derive conclusions using formal rules of inference.

The program was developed from scratch without using built-in string manipulation or logic libraries,
focusing on core computer science principles, algorithmic thinking, and correctness.

---

## Key Features

- Truth table generation for propositional logic expressions
- Validation of logical arguments using semantic entailment
- Logical equivalence checking between expressions
- Automated reasoning using rules of inference:
  - Modus Ponens
  - Modus Tollens
  - Hypothetical Syllogism
  - Disjunctive Syllogism
  - Simplification
- Support for logical operators:
  - NOT (!)
  - AND (&)
  - OR (|)
  - IMPLIES (>)
  - BICONDITIONAL (=)
- Custom-built expression parser and infix-to-postfix conversion (Shunting Yard Algorithm)
- File-based persistence for saved truth tables, arguments, and equivalence results
- Interactive console-based user interface

---

## Technologies Used

- C++
- Standard Template Library (STL) (minimal usage)
- Windows Console API for UI formatting

---

## Program Structure

The system is modular and function-driven, including:
- Custom input validation and tokenization
- Infix to postfix conversion
- Postfix expression evaluation
- Dynamic truth table generation
- Logical inference engine
- File handling for persistent result storage

No external logic or parsing libraries were used.

---

## How to Run

1. Compile the program using a C++ compiler (Windows recommended)
2. Run the executable
3. 
---

## Educational Purpose

This project was developed to strengthen understanding of:
- Propositional logic
- Formal reasoning
- Algorithm design
- Stack-based expression evaluation
- Clean and structured C++ programming

All logic and algorithms were implemented manually for learning purposes.

---

## Notes

- The program is designed for academic and educational use.
- Input expressions support up to 5 distinct variables.
- Console-based UI works best on Windows systems.




Project NO;02
Battleship Game in C++

This project is a complete console-based implementation of the classic Battleship game written in C++. It allows players to compete in both Player vs Player and Player vs Computer modes while managing ship placement, turn-based attacks, scoring, and win conditions. The program emphasizes clear game logic, structured design, and an engaging text-based user experience.

The game was developed entirely from scratch without the use of external game engines or graphical libraries. All gameplay mechanics, board rendering, and state management were implemented manually, focusing on fundamental programming concepts and correctness.

Key Features

Player vs Player and Player vs Computer game modes

Manual and random ship placement options

Dynamic board updates showing hits, misses, and sunk ships

Turn-based gameplay with score tracking

Multiple shots per turn based on remaining ships

Persistent leaderboard system using file handling

Color-coded console output for improved readability

Technologies Used

C++

Standard C++ libraries for input/output, file handling, and randomization

Windows Console API for color control and screen formatting

Program Structure

The system follows a modular, function-driven design and includes:

Board initialization and display logic

Ship placement and validation

Turn-based attack handling

Hit detection and ship sinking logic

Score calculation system

Leaderboard management using file input/output

No external game engines or UI libraries were used.

How to Run

Compile the program using a standard C++ compiler such as MinGW or MSVC.

Run the generated executable from the Windows console.

Follow the on-screen prompts to select a game mode and begin playing.

Educational Purpose

This project was developed to strengthen understanding of core C++ concepts, including two-dimensional arrays, control flow, functions, file handling, and program state management. It demonstrates how a complete game can be implemented using only standard programming tools and console output.

Notes

This program is intended for academic and learning purposes.

The project is designed for Windows systems due to the use of the Windows Console API.

The computer opponent uses a randomized attack strategy.



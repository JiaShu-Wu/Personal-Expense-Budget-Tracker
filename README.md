# Personal Expense & Budget Tracker — DD1 Foundation

A C11 menu-driven application scaffold for the Personal Expense & Budget Tracker.
This first development stage implements the enum-based finite state machine (FSM),
persistent main loop, robust menu input handling, exit confirmation, and independent
FSM transition tests. Transaction and budget features are placeholders at this stage.

## Requirements

- GCC or another C11-compatible compiler
- GNU Make

## Build

```bash
make
```

## Run

```bash
./expense_tracker
```

or:

```bash
make run
```

## Test

The test executable is separate from the interactive application. It calls the
non-interactive FSM helper functions directly and does not launch the CLI.

```bash
make test
```

## Clean generated executables

```bash
make clean
```

## Current development scope

Implemented:

- `enum` states for the main menu, application modes, exit confirmation and exit
- persistent main loop that ends only at the exit state
- menu-choice validation using `fgets` and `strtol`
- safe handling of invalid and overlong input lines
- exit confirmation and safe EOF handling
- separate test executable for FSM state mapping and transitions

Not implemented yet:

- transaction CRUD operations
- financial reports and category analysis
- budget calculations and dashboard
- persistent transaction and budget storage

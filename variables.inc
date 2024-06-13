    SECTION FRAGMENT "Variables", WRAM0
    return_stack_pointer::
    dw ; return stack pointer

    startvars
    defvar "STATE", STATE, 0
    defvar "HERE", HERE, 0
    ; defvar "LATEST", LATEST, 42
    defvar16 "S0", SZ, $FFFE
    defvar "BASE", BASE, 10
    endvars

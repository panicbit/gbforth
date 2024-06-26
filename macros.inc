; esi -> de (next subroutine address)

macro NEXT
    jp next
endm

macro PUSHRSP ; \1 = bc/de, clobbers a, hl
    ld hl, return_stack_pointer

    ld a, HIGH(\1)
    ld [hld], a

    ld a, LOW(\1)
    ld [hld], a

    ld a, h
    ld [return_stack_pointer + 1], a

    ld a, l
    ld [return_stack_pointer], a
endm

macro POPRSP ; \1 = bc/de, clobbers a, hl
    ld hl, return_stack_pointer

    ld a, [hli]
    ld LOW(\1), a

    ld a, [hli]
    ld HIGH(\1), a

    ld a, h
    ld [return_stack_pointer + 1], a

    ld a, l
    ld [return_stack_pointer], a
endm

def link = 0

macro defword ; \1 = name, \2 = flags, \3 = label
    name_\3::
        dw link ; previous entry
        db STRLEN(\1) + \2 ; 
        db \1
    \3::
        db DOCOL
    def link = name_\3
endm

macro defcode ; \1 = name, \2 = flags, \3 = label
    SECTION FRAGMENT "Code", ROM0
    name_\3:
        dw link
        db STRLEN(\1) + \2
    \3:
        dw code_\3
    code_\3:
    def link = name_\3
endm

macro startvars
    SECTION FRAGMENT "Variables", WRAM0
    variables_start::

    SECTION FRAGMENT "Variables Init", ROM0
    init_variables::
    ld hl, variables_start
endm

macro defvar ; \1 = name, \2 = label, \3 = initial
    defcode \1, 0, \2
    ld hl, var_\2
    push hl
    NEXT

    SECTION FRAGMENT "Variables", WRAM0
    var_\2:
    db

    SECTION FRAGMENT "Variables Init", ROM0
    ld a, \3
    ld [hli], a
endm

macro defvar16 ; \1 = name, \2 = label, \3 = initial
    defcode \1, 0, \2
    ld hl, var_\2
    push hl
    NEXT

    SECTION FRAGMENT "Variables", WRAM0
    var_\2:
    dw

    SECTION FRAGMENT "Variables Init", ROM0
    ld a, LOW(\3)
    ld [hli], a
    ld a, HIGH(\3)
    ld [hli], a
endm

macro endvars
    SECTION FRAGMENT "Variables Init", ROM0
    ret
endm

macro defconst ; \1 = name, \2 = label, \3 = value
    defcode \1, 0, \2
    ld hl, sp + 0
    ld a, \3
    ld [hl], a
    dec sp
    NEXT
endm

macro defconst16 ; \1 = name, \2 = label, \3 = value
    defcode \1, 0, \2
    ld hl, \3
    push hl
    NEXT
endm
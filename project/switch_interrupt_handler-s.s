.text
    .balign 2

    .global switch_interrupt_handler
    .extern switches
    .extern switch_update_interrupt_sense

switch_interrupt_handler:
    call #switch_update_interrupt_sense
    
    xor.b #0xff, r12 ; ~p2val
    and.b #15, r12 ; ~p2val & SWITCHES
    mov.b r12, &switches

    ret


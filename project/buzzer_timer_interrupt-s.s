.text
    .balign 2
    .global buzzer_timer_interrupt

jt: .word option_playing
    .word option_off

    .extern buzzer_state
    .extern update_ball_sound

buzzer_timer_interrupt:
    mov &buzzer_state, r12   
    add r12, r12 ; playing = 0, off = 2    since addresses are 2 bytes
    mov jt(r12), r0

option_off:
    jmp end

option_playing:
    call #update_ball_sound
    jmp end

end:
  pop r0

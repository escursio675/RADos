[BITS 32]
global contextSwitch

; void contextSwitch(uint32_t* oldEsp, uint32_t newEsp)
;                    [esp+4]           [esp+8]
contextSwitch:
    ; --- Save callee-saved registers onto current (old) stack ---
    push ebp
    push ebx
    push esi
    push edi

    ; --- Save current ESP into *oldEsp ---
    mov  eax, [esp + 20]   ; eax = oldEsp ptr  (4 regs pushed = 16 bytes + 4 ret = 20)
    mov  [eax], esp        ; *oldEsp = esp

    ; --- Load new ESP ---
    mov  eax, [esp + 24]   ; eax = newEsp value (same offset shift)
    mov  esp, eax

    ; --- Restore callee-saved registers from new stack ---
    pop  edi
    pop  esi
    pop  ebx
    pop  ebp

    ; --- Return into new process (EIP was pushed as "return address") ---
    ret
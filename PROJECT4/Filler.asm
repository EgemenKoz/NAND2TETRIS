(INFINITE)
  // Check keyboard input
  @KBD
  D=M
  @FILLER
  D;JNE    // If key pressed (D != 0), jump to FILLER
  @INFINITE
  0;JMP    // Otherwise, keep checking KBD in an infinite loop

(FILLER)
  // Initialize screen pointer
  @SCREEN
  D=A
  @ptr
  M=D      // ptr = SCREEN address

(FILL_LOOP)  // Inner loop to fill screen
  @ptr
  A=M      // Dereference ptr (go to screen address)
  M=-1     // Fill 16 pixels with 1's (white)

  // Increment pointer
  @ptr
  M=M+1

  // Check if we reached KBD (0x6000)
  @KBD
  D=A
  @ptr
  D=D-M    // D = KBD - ptr
  @FILL_LOOP
  D;JGT    // If (KBD - ptr) > 0, keep filling

  // After filling, return to INFINITE loop
  @INFINITE
  0;JMP
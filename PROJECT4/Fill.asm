(INFINITE)
  @KBD
  D=M          // Load keyboard input
  
  @FILL_SCREEN
  D;JNE        // If key pressed (D != 0), fill screen
  
  // Else (D == 0), clear screen
  @SCREEN
  D=A
  @ptr
  M=D          // ptr = SCREEN address
  
(CLEAR_LOOP)
  @ptr
  A=M
  M=0          // Set 16 pixels to 0 (black)
  
  @ptr
  M=M+1        // Move to next word
  
  @KBD
  D=A
  @ptr
  D=D-M        // D = KBD - ptr
  @CLEAR_LOOP
  D;JGT        // Loop until ptr reaches KBD
  
  @INFINITE
  0;JMP        // Return to main loop

(FILL_SCREEN)
  @SCREEN
  D=A
  @ptr
  M=D          // ptr = SCREEN address
  
(FILL_LOOP)
  @ptr
  A=M
  M=-1         // Set 16 pixels to -1 (white)
  
  @ptr
  M=M+1        // Move to next word
  
  @KBD
  D=A
  @ptr
  D=D-M        // D = KBD - ptr
  @FILL_LOOP
  D;JGT        // Loop until ptr reaches KBD
  
  @INFINITE
  0;JMP        // Return to main loop
# 3-state Busy Beaver
# Starts on a blank tape, writes 6 ones, halts after 14 steps.

states:    A B C HALT
alphabet:  0 1
blank:     0
initial:   A
accepting: HALT

transitions:
A  0  B  1  R
A  1  C  1  L
B  0  A  1  L
B  1  B  1  R
C  0  B  1  L
C  1  HALT  1  R

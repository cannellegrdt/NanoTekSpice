# Turing Machine: increment a binary number
# Input : binary string on tape, e.g. "1011"
# Output: input + 1 written on tape

states:    q_right q_carry q_accept
alphabet:  0 1 _
blank:     _
initial:   q_right
accepting: q_accept

transitions:
# scan right to find the end
q_right  0  q_right  0  R
q_right  1  q_right  1  R
q_right  _  q_carry  _  L

# propagate carry left
q_carry  1  q_carry   0  L
q_carry  0  q_accept  1  R
q_carry  _  q_accept  1  R

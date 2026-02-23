# Turing Machine: palindrome checker on alphabet {a, b}
# Accepts if the word on the tape is a palindrome.
# Uses 'X' as a marker for already-matched symbols.

states:    q0 qa qb q_check_a q_check_b q_match q_back q_accept q_reject
alphabet:  a b _ X
blank:     _
initial:   q0
accepting: q_accept
rejecting: q_reject

transitions:
# read first symbol
q0  a  qa          X  R
q0  b  qb          X  R
q0  _  q_accept    _  R
q0  X  q0          X  R

# scan right to end (left was 'a')
qa  a  qa  a  R
qa  b  qa  b  R
qa  X  qa  X  R
qa  _  q_check_a  _  L

# scan right to end (left was 'b')
qb  a  qb  a  R
qb  b  qb  b  R
qb  X  qb  X  R
qb  _  q_check_b  _  L

# check that rightmost unmatched symbol is 'a'
q_check_a  a  q_match  X  L
q_check_a  X  q_check_a  X  L
q_check_a  _  q_accept  _  R
q_check_a  b  q_reject  b  R

# check that rightmost unmatched symbol is 'b'
q_check_b  b  q_match  X  L
q_check_b  X  q_check_b  X  L
q_check_b  _  q_accept  _  R
q_check_b  a  q_reject  a  R

# matched — go back to leftmost unmatched symbol
q_match  a  q_match  a  L
q_match  b  q_match  b  L
q_match  X  q0  X  R

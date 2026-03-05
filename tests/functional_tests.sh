#!/bin/bash

##
## EPITECH PROJECT, 2025
## G-OOP-400-LYN-4-1-tekspice-1
## File description:
## functional_tests.sh
##

cd "$(dirname "$0")/.." || exit 1

BIN="./nanotekspice"
NTS_S="./nts_single"
NTS_A="./nts_advanced"
TMPDIR_NTS=$(mktemp -d)

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
PURPLE='\033[0;35m'
BOLD='\033[1m'
NC='\033[0m'

PASS=0
FAIL=0

cleanup() { rm -rf "$TMPDIR_NTS"; }
trap cleanup EXIT

if [ ! -x "$BIN" ]; then
    echo -e "${RED}[ERREUR]${NC} Binary '$BIN' not found."
    echo "  Run 'make' before executing the tests."
    exit 1
fi

for f in and.nts or.nts xor.nts not.nts true.nts false.nts clock.nts input_output.nts; do
    if [ ! -f "$NTS_S/$f" ]; then
        echo -e "${YELLOW}[WARN]${NC} File $NTS_S/$f missing — some tests will be skipped."
    fi
done


normalize() { sed 's/[[:space:]]*$//'; }

run_test() {
    local name="$1" nts_file="$2" input_cmds="$3" expected_out="$4"
    local expected_exit="${5:-0}"

    local actual_out actual_exit
    actual_out=$(printf '%s' "$input_cmds" | "$BIN" "$nts_file" 2>/dev/null)
    actual_exit=$?

    local norm_actual norm_expected
    norm_actual=$(printf '%s\n' "$actual_out"   | normalize)
    norm_expected=$(printf '%s\n' "$expected_out" | normalize)

    local ok=1
    [ "$actual_exit" -ne "$expected_exit" ] && ok=0
    [ "$norm_actual" != "$norm_expected"  ] && ok=0

    if [ "$ok" -eq 1 ]; then
        echo -e "  ${GREEN}[PASS]${NC} $name"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}[FAIL]${NC} $name"
        if [ "$actual_exit" -ne "$expected_exit" ]; then
            echo -e "         exit  : expected=${YELLOW}$expected_exit${NC}  got=${YELLOW}$actual_exit${NC}"
        fi
        if [ "$norm_actual" != "$norm_expected" ]; then
            echo "         stdout (- expected / + got) :"
            diff <(printf '%s\n' "$expected_out" | normalize) \
                 <(printf '%s\n' "$actual_out"   | normalize) \
                 | sed 's/^/           /' || true
        fi
        FAIL=$((FAIL + 1))
    fi
}

run_error_test() {
    local name="$1" nts_file="${2:-}" input_cmds="${3:-}"
    local expected_exit="${4:-84}"

    local actual_exit actual_stderr
    if [ -z "$nts_file" ] || [ "$nts_file" = "-" ]; then
        printf '%s' "$input_cmds" | "$BIN" >/dev/null 2>/tmp/nts_stderr_$$
        actual_exit=$?
    else
        printf '%s' "$input_cmds" | "$BIN" "$nts_file" >/dev/null 2>/tmp/nts_stderr_$$
        actual_exit=$?
    fi
    actual_stderr=$(cat /tmp/nts_stderr_$$ 2>/dev/null)
    rm -f /tmp/nts_stderr_$$

    local ok=1
    [ "$actual_exit" -ne "$expected_exit" ] && ok=0
    [ -z "$actual_stderr" ] && ok=0

    if [ "$ok" -eq 1 ]; then
        echo -e "  ${GREEN}[PASS]${NC} $name"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}[FAIL]${NC} $name"
        if [ "$actual_exit" -ne "$expected_exit" ]; then
            echo -e "         exit  : expected=${YELLOW}$expected_exit${NC}  got=${YELLOW}$actual_exit${NC}"
        fi
        if [ -z "$actual_stderr" ]; then
            echo "         stderr: expected error message (empty stderr)"
        fi
        FAIL=$((FAIL + 1))
    fi
}

section() {
    echo ""
    echo -e "${PURPLE}${BOLD}━━━ $1 ━━━${NC}"
}


cat > "$TMPDIR_NTS/bad_link.nts" << 'EOF'
.chipsets:
input i
output o
.links:
a:1 o:1
EOF

cat > "$TMPDIR_NTS/bad_type.nts" << 'EOF'
.chipsets:
unknownchip foo
output out
.links:
foo:1 out:1
EOF

cat > "$TMPDIR_NTS/duplicate.nts" << 'EOF'
.chipsets:
input a
input a
output out
.links:
a:1 out:1
EOF

cat > "$TMPDIR_NTS/no_chipsets.nts" << 'EOF'
.links:
a:1 b:1
EOF

touch "$TMPDIR_NTS/empty.nts"

cat > "$TMPDIR_NTS/or_gate.nts" << 'EOF'
.chipsets:
input   a
input   b
4071    or
output  s
.links:
a:1     or:1
b:1     or:2
or:3    s:1
EOF


section "1. Error handling (exit 84 + stderr message)"

run_error_test "No argument → exit 84" "" "" 84
run_error_test "File does not exist → exit 84" "/tmp/file_does_not_exist_42.nts" "" 84
run_error_test "Unknown name in .links → exit 84" "$TMPDIR_NTS/bad_link.nts" "" 84
run_error_test "Unknown component type → exit 84" "$TMPDIR_NTS/bad_type.nts" "" 84
run_error_test "Duplicate name → exit 84" "$TMPDIR_NTS/duplicate.nts" "" 84
run_error_test "No .chipsets section → exit 84" "$TMPDIR_NTS/no_chipsets.nts" "" 84

if [ -f "$NTS_S/input_output.nts" ]; then
    actual_stdout=$(printf 'unknowncommand\nexit\n' | "$BIN" "$NTS_S/input_output.nts" 2>/dev/null)
    actual_exit=$?
    if echo "$actual_stdout" | grep -qi "error\|erreur\|unknown\|inconnu" 2>/dev/null; then
        echo -e "  ${RED}[FAIL]${NC} Runtime error → on stderr (not stdout)"
        echo "         stderr should receive the message, not stdout"
        FAIL=$((FAIL + 1))
    else
        echo -e "  ${GREEN}[PASS]${NC} Runtime error → on stderr (not stdout)"
        PASS=$((PASS + 1))
    fi
fi


section "2. Session (prompt, EOF, exit)"

if [ -f "$NTS_S/input_output.nts" ]; then
    actual=$(printf 'exit\n' | "$BIN" "$NTS_S/input_output.nts" 2>/dev/null)
    if printf '%s' "$actual" | grep -q "^> "; then
        echo -e "  ${GREEN}[PASS]${NC} Prompt '> ' present before each command"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}[FAIL]${NC} Prompt '> ' present before each command"
        echo "         stdout received: $(printf '%s' "$actual" | head -1 | cat -A)"
        FAIL=$((FAIL + 1))
    fi
fi

if [ -f "$NTS_S/input_output.nts" ]; then
    printf 'exit\n' | "$BIN" "$NTS_S/input_output.nts" >/dev/null 2>/dev/null
    ec=$?
    if [ "$ec" -eq 0 ]; then
        echo -e "  ${GREEN}[PASS]${NC} Command 'exit' → exit 0"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}[FAIL]${NC} Command 'exit' → exit 0 (got: $ec)"
        FAIL=$((FAIL + 1))
    fi
fi

if [ -f "$NTS_S/input_output.nts" ]; then
    printf '' | "$BIN" "$NTS_S/input_output.nts" >/dev/null 2>/dev/null
    ec=$?
    if [ "$ec" -eq 0 ]; then
        echo -e "  ${GREEN}[PASS]${NC} EOF (CTRL+D) → exit 0"
        PASS=$((PASS + 1))
    else
        echo -e "  ${RED}[FAIL]${NC} EOF (CTRL+D) → exit 0 (got: $ec)"
        FAIL=$((FAIL + 1))
    fi
fi

run_test "Subject example 1: OR gate (a=1, b=0 → s=1)" \
    "$TMPDIR_NTS/or_gate.nts" \
    "$(printf 'b=0\na=1\nsimulate\ndisplay\nexit\n')" \
    "> > > > tick: 1
input(s):
  a: 1
  b: 0
output(s):
  s: 1
> " \
    0

section "3. Display format and tick counter"

if [ -f "$NTS_S/and.nts" ]; then

    run_test "Tick = 0 before simulate" \
        "$NTS_S/and.nts" \
        "$(printf 'display\nexit\n')" \
        "> tick: 0
input(s):
  in_1: U
  in_2: U
output(s):
  out: U
> " \
        0

    run_test "Tick = 1 after 1 simulate" \
        "$NTS_S/and.nts" \
        "$(printf 'simulate\ndisplay\nexit\n')" \
        "> > tick: 1
input(s):
  in_1: U
  in_2: U
output(s):
  out: U
> " \
        0

    run_test "Tick = 3 after 3 simulates" \
        "$NTS_S/and.nts" \
        "$(printf 'simulate\nsimulate\nsimulate\ndisplay\nexit\n')" \
        "> > > > tick: 3
input(s):
  in_1: U
  in_2: U
output(s):
  out: U
> " \
        0

    run_test "ASCII sort of names (in_1 before in_2)" \
        "$NTS_S/and.nts" \
        "$(printf 'in_2=1\nin_1=0\nsimulate\ndisplay\nexit\n')" \
        "> > > > tick: 1
input(s):
  in_1: 0
  in_2: 1
output(s):
  out: 0
> " \
        0

fi

section "4. Special components (true, false, input, clock)"

if [ -f "$NTS_S/true.nts" ]; then
    run_test "true → always 1" \
        "$NTS_S/true.nts" \
        "$(printf 'simulate\ndisplay\nexit\n')" \
        "> > tick: 1
input(s):
output(s):
  out: 1
> " \
        0
fi

if [ -f "$NTS_S/false.nts" ]; then
    run_test "false → always 0" \
        "$NTS_S/false.nts" \
        "$(printf 'simulate\ndisplay\nexit\n')" \
        "> > tick: 1
input(s):
output(s):
  out: 0
> " \
        0
fi

if [ -f "$NTS_S/input_output.nts" ]; then
    run_test "input/output: default U" \
        "$NTS_S/input_output.nts" \
        "$(printf 'simulate\ndisplay\nexit\n')" \
        "> > tick: 1
input(s):
  in: U
output(s):
  out: U
> " \
        0

    run_test "input/output: in=0 → out=0" \
        "$NTS_S/input_output.nts" \
        "$(printf 'in=0\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in: 0
output(s):
  out: 0
> " \
        0

    run_test "input/output: in=1 → out=1" \
        "$NTS_S/input_output.nts" \
        "$(printf 'in=1\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in: 1
output(s):
  out: 1
> " \
        0

    run_test "input/output: in=1 then in=U → back to U" \
        "$NTS_S/input_output.nts" \
        "$(printf 'in=1\nsimulate\nin=U\nsimulate\ndisplay\nexit\n')" \
        "> > > > > tick: 2
input(s):
  in: U
output(s):
  out: U
> " \
        0
fi

if [ -f "$NTS_S/clock.nts" ]; then
    run_test "clock: tick 0 → cl=U" \
        "$NTS_S/clock.nts" \
        "$(printf 'display\nexit\n')" \
        "> tick: 0
input(s):
  cl: U
output(s):
  out: U
> " \
        0

    run_test "clock: cl=0 + simulate → cl=0 (tick 1)" \
        "$NTS_S/clock.nts" \
        "$(printf 'cl=0\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  cl: 0
output(s):
  out: 0
> " \
        0

    run_test "clock: 2nd simulate → cl=1 (toggle)" \
        "$NTS_S/clock.nts" \
        "$(printf 'cl=0\nsimulate\nsimulate\ndisplay\nexit\n')" \
        "> > > > tick: 2
input(s):
  cl: 1
output(s):
  out: 1
> " \
        0

    run_test "clock: cl=0 + 5 simulates → cl=0 (tick 5)" \
        "$NTS_S/clock.nts" \
        "$(printf 'cl=0\nsimulate\nsimulate\nsimulate\nsimulate\nsimulate\ndisplay\nexit\n')" \
        "> > > > > > > tick: 5
input(s):
  cl: 0
output(s):
  out: 0
> " \
        0
fi

section "5. AND gate (nts_single/and.nts)"

if [ -f "$NTS_S/and.nts" ]; then

    for combo in "0 0 0" "0 1 0" "1 0 0" "1 1 1"; do
        a=$(echo "$combo" | cut -d' ' -f1)
        b=$(echo "$combo" | cut -d' ' -f2)
        r=$(echo "$combo" | cut -d' ' -f3)
        run_test "AND $a AND $b = $r" \
            "$NTS_S/and.nts" \
            "$(printf 'in_1=%s\nin_2=%s\nsimulate\ndisplay\nexit\n' "$a" "$b")" \
            "> > > > tick: 1
input(s):
  in_1: $a
  in_2: $b
output(s):
  out: $r
> " \
            0
    done

    run_test "AND U AND 0 = 0 (undefined state)" \
        "$NTS_S/and.nts" \
        "$(printf 'in_2=0\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in_1: U
  in_2: 0
output(s):
  out: 0
> " \
        0

    run_test "AND 1 AND U = U (undefined state)" \
        "$NTS_S/and.nts" \
        "$(printf 'in_1=1\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in_1: 1
  in_2: U
output(s):
  out: U
> " \
        0

fi

section "6. OR gate (nts_single/or.nts)"

if [ -f "$NTS_S/or.nts" ]; then

    for combo in "0 0 0" "0 1 1" "1 0 1" "1 1 1"; do
        a=$(echo "$combo" | cut -d' ' -f1)
        b=$(echo "$combo" | cut -d' ' -f2)
        r=$(echo "$combo" | cut -d' ' -f3)
        run_test "OR $a OR $b = $r" \
            "$NTS_S/or.nts" \
            "$(printf 'in_1=%s\nin_2=%s\nsimulate\ndisplay\nexit\n' "$a" "$b")" \
            "> > > > tick: 1
input(s):
  in_1: $a
  in_2: $b
output(s):
  out: $r
> " \
            0
    done

    run_test "OR U OR 1 = 1 (undefined state)" \
        "$NTS_S/or.nts" \
        "$(printf 'in_2=1\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in_1: U
  in_2: 1
output(s):
  out: 1
> " \
        0

    run_test "OR 0 OR U = U (undefined state)" \
        "$NTS_S/or.nts" \
        "$(printf 'in_1=0\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in_1: 0
  in_2: U
output(s):
  out: U
> " \
        0

fi

section "7. XOR gate (nts_single/xor.nts)"

if [ -f "$NTS_S/xor.nts" ]; then

    for combo in "0 0 0" "0 1 1" "1 0 1" "1 1 0"; do
        a=$(echo "$combo" | cut -d' ' -f1)
        b=$(echo "$combo" | cut -d' ' -f2)
        r=$(echo "$combo" | cut -d' ' -f3)
        run_test "XOR $a XOR $b = $r" \
            "$NTS_S/xor.nts" \
            "$(printf 'in_1=%s\nin_2=%s\nsimulate\ndisplay\nexit\n' "$a" "$b")" \
            "> > > > tick: 1
input(s):
  in_1: $a
  in_2: $b
output(s):
  out: $r
> " \
            0
    done

    run_test "XOR U XOR 0 = U (undefined state)" \
        "$NTS_S/xor.nts" \
        "$(printf 'in_2=0\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in_1: U
  in_2: 0
output(s):
  out: U
> " \
        0

fi

section "8. NOT gate (nts_single/not.nts)"

if [ -f "$NTS_S/not.nts" ]; then

    run_test "NOT 0 = 1" \
        "$NTS_S/not.nts" \
        "$(printf 'in=0\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in: 0
output(s):
  out: 1
> " \
        0

    run_test "NOT 1 = 0" \
        "$NTS_S/not.nts" \
        "$(printf 'in=1\nsimulate\ndisplay\nexit\n')" \
        "> > > tick: 1
input(s):
  in: 1
output(s):
  out: 0
> " \
        0

    run_test "NOT U = U (undefined state)" \
        "$NTS_S/not.nts" \
        "$(printf 'simulate\ndisplay\nexit\n')" \
        "> > tick: 1
input(s):
  in: U
output(s):
  out: U
> " \
        0

fi

section "9. Advanced circuits"

if [ -f "$NTS_A/and-or-not.nts" ]; then
    run_test "and-or-not : in_a=1 in_b=0 in_c=1 → out=0" \
        "$NTS_A/and-or-not.nts" \
        "$(printf 'in_a=1\nin_b=0\nin_c=1\nsimulate\ndisplay\nexit\n')" \
        "> > > > > tick: 1
input(s):
  in_a: 1
  in_b: 0
  in_c: 1
output(s):
  out: 0
> " \
        0

    run_test "and-or-not : in_a=0 in_b=0 in_c=1 → out=0" \
        "$NTS_A/and-or-not.nts" \
        "$(printf 'in_a=0\nin_b=0\nin_c=1\nsimulate\ndisplay\nexit\n')" \
        "> > > > > tick: 1
input(s):
  in_a: 0
  in_b: 0
  in_c: 1
output(s):
  out: 0
> " \
        0
fi

if [ -f "$NTS_A/and.nts" ]; then
    run_test "AND 4081: 5 inputs at 1 → out=1" \
        "$NTS_A/and.nts" \
        "$(printf 'in_a=1\nin_b=1\nin_c=1\nin_d=1\nin_e=1\nsimulate\ndisplay\nexit\n')" \
        "> > > > > > > tick: 1
input(s):
  in_a: 1
  in_b: 1
  in_c: 1
  in_d: 1
  in_e: 1
output(s):
  out: 1
> " \
        0

    run_test "AND 4081: 1 input at 0 → out=0" \
        "$NTS_A/and.nts" \
        "$(printf 'in_a=1\nin_b=1\nin_c=0\nin_d=1\nin_e=1\nsimulate\ndisplay\nexit\n')" \
        "> > > > > > > tick: 1
input(s):
  in_a: 1
  in_b: 1
  in_c: 0
  in_d: 1
  in_e: 1
output(s):
  out: 0
> " \
        0
fi


# tests/extra_tests.sh

section "11. Individual Gates Tests"

# 4001: NOR
cat > "$TMPDIR_NTS/4001.nts" << 'EOF'
.chipsets:
input a
input b
4001 nor
output out
.links:
a:1 nor:1
b:1 nor:2
nor:3 out:1
EOF
run_test "4001 NOR gate: 0 NOR 0 = 1" "$TMPDIR_NTS/4001.nts" "$(printf 'a=0\nb=0\nsimulate\ndisplay\nexit\n')" "> > > > tick: 1
input(s):
  a: 0
  b: 0
output(s):
  out: 1
> " 0

run_test "4001 NOR gate: 1 NOR 0 = 0" "$TMPDIR_NTS/4001.nts" "$(printf 'a=1\nb=0\nsimulate\ndisplay\nexit\n')" "> > > > tick: 1
input(s):
  a: 1
  b: 0
output(s):
  out: 0
> " 0

# 4011: NAND
cat > "$TMPDIR_NTS/4011.nts" << 'EOF'
.chipsets:
input a
input b
4011 nand
output out
.links:
a:1 nand:1
b:1 nand:2
nand:3 out:1
EOF
run_test "4011 NAND gate: 1 NAND 1 = 0" "$TMPDIR_NTS/4011.nts" "$(printf 'a=1\nb=1\nsimulate\ndisplay\nexit\n')" "> > > > tick: 1
input(s):
  a: 1
  b: 1
output(s):
  out: 0
> " 0

run_test "4011 NAND gate: 0 NAND 1 = 1" "$TMPDIR_NTS/4011.nts" "$(printf 'a=0\nb=1\nsimulate\ndisplay\nexit\n')" "> > > > tick: 1
input(s):
  a: 0
  b: 1
output(s):
  out: 1
> " 0

# 4030: XOR
cat > "$TMPDIR_NTS/4030.nts" << 'EOF'
.chipsets:
input a
input b
4030 xor
output out
.links:
a:1 xor:1
b:1 xor:2
xor:3 out:1
EOF
run_test "4030 XOR gate: 1 XOR 1 = 0" "$TMPDIR_NTS/4030.nts" "$(printf 'a=1\nb=1\nsimulate\ndisplay\nexit\n')" "> > > > tick: 1
input(s):
  a: 1
  b: 1
output(s):
  out: 0
> " 0

run_test "4030 XOR gate: 0 XOR 1 = 1" "$TMPDIR_NTS/4030.nts" "$(printf 'a=0\nb=1\nsimulate\ndisplay\nexit\n')" "> > > > tick: 1
input(s):
  a: 0
  b: 1
output(s):
  out: 1
> " 0

# 4069: INVERTER
cat > "$TMPDIR_NTS/4069.nts" << 'EOF'
.chipsets:
input a
4069 inv
output out
.links:
a:1 inv:1
inv:2 out:1
EOF
run_test "4069 INVERTER gate: INV 0 = 1" "$TMPDIR_NTS/4069.nts" "$(printf 'a=0\nsimulate\ndisplay\nexit\n')" "> > > tick: 1
input(s):
  a: 0
output(s):
  out: 1
> " 0

# 4071: OR
cat > "$TMPDIR_NTS/4071.nts" << 'EOF'
.chipsets:
input a
input b
4071 or
output out
.links:
a:1 or:1
b:1 or:2
or:3 out:1
EOF
run_test "4071 OR gate: 0 OR 1 = 1" "$TMPDIR_NTS/4071.nts" "$(printf 'a=0\nb=1\nsimulate\ndisplay\nexit\n')" "> > > > tick: 1
input(s):
  a: 0
  b: 1
output(s):
  out: 1
> " 0
# tests/advanced_tests.sh

section "12. Advanced Components Instantiation Tests"

cat > "$TMPDIR_NTS/4008.nts" << 'EOF'
.chipsets:
4008 adder
output out
.links:
adder:10 out:1
EOF
run_test "4008 (4-bit adder) instantiation" "$TMPDIR_NTS/4008.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: U
> " 0

cat > "$TMPDIR_NTS/4013.nts" << 'EOF'
.chipsets:
4013 ff
output out
.links:
ff:1 out:1
EOF
run_test "4013 (dual flip-flop) instantiation" "$TMPDIR_NTS/4013.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: 0
> " 0

cat > "$TMPDIR_NTS/4017.nts" << 'EOF'
.chipsets:
4017 johnson
output out
.links:
johnson:3 out:1
EOF
run_test "4017 (Johnson counter) instantiation" "$TMPDIR_NTS/4017.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: 0
> " 0

cat > "$TMPDIR_NTS/4040.nts" << 'EOF'
.chipsets:
4040 ripple
output out
.links:
ripple:9 out:1
EOF
run_test "4040 (ripple counter) instantiation" "$TMPDIR_NTS/4040.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: 0
> " 0

cat > "$TMPDIR_NTS/4094.nts" << 'EOF'
.chipsets:
4094 shiftreg
output out
.links:
shiftreg:4 out:1
EOF
run_test "4094 (shift register) instantiation" "$TMPDIR_NTS/4094.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: U
> " 0

cat > "$TMPDIR_NTS/4512.nts" << 'EOF'
.chipsets:
4512 selector
output out
.links:
selector:14 out:1
EOF
run_test "4512 (data selector) instantiation" "$TMPDIR_NTS/4512.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: U
> " 0

cat > "$TMPDIR_NTS/4514.nts" << 'EOF'
.chipsets:
4514 decoder
output out
.links:
decoder:11 out:1
EOF
run_test "4514 (decoder) instantiation" "$TMPDIR_NTS/4514.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: 1
> " 0

cat > "$TMPDIR_NTS/4801.nts" << 'EOF'
.chipsets:
4801 ram
output out
.links:
ram:9 out:1
EOF
run_test "4801 (RAM) instantiation" "$TMPDIR_NTS/4801.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: U
> " 0

cat > "$TMPDIR_NTS/2716.nts" << 'EOF'
.chipsets:
2716 rom
output out
.links:
rom:9 out:1
EOF
run_test "2716 (ROM) instantiation" "$TMPDIR_NTS/2716.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
output(s):
  out: U
> " 0

cat > "$TMPDIR_NTS/logger.nts" << 'EOF'
.chipsets:
clock clk
input in
logger log
.links:
clk:1 log:9
in:1 log:1
EOF
run_test "logger instantiation" "$TMPDIR_NTS/logger.nts" "$(printf 'simulate\ndisplay\nexit\n')" "> > tick: 1
input(s):
  clk: U
  in: U
output(s):
> " 0


rm -f ./log.bin

cat > "$TMPDIR_NTS/dupli_last_char.nts" << 'EOF'
.chipsets:
clock clk
input i0
input i1
input i2
input i3
input i4
input i5
input i6
input i7
input inhib
logger log

.links:
clk:1   log:9
inhib:1 log:10
i0:1    log:1
i1:1    log:2
i2:1    log:3
i3:1    log:4
i4:1    log:5
i5:1    log:6
i6:1    log:7
i7:1    log:8
EOF

rm -f ./log.bin
printf 'i0=1\ni1=0\ni2=0\ni3=0\ni4=0\ni5=0\ni6=1\ni7=0\ninhib=0\nclk=0\nsimulate\nclk=1\nsimulate\ni0=0\ni1=1\nclk=0\nsimulate\nclk=1\nsimulate\nexit\n' | "$BIN" "$TMPDIR_NTS/dupli_last_char.nts" >/dev/null 2>/dev/null
actual_size=$(wc -c < ./log.bin 2>/dev/null || echo 0)
actual_hex=$(xxd -p ./log.bin 2>/dev/null || echo "")
expected_hex="4142"
if [ "$actual_size" -eq 2 ] && [ "$actual_hex" = "$expected_hex" ]; then
    echo -e "  ${GREEN}[PASS]${NC} dupli last char"
    PASS=$((PASS + 1))
else
    echo -e "  ${RED}[FAIL]${NC} dupli last char"
    echo "         expected log.bin: 2 bytes (4142 = 'AB')"
    echo "         got log.bin: $actual_size bytes ($actual_hex)"
    FAIL=$((FAIL + 1))
fi
rm -f ./log.bin


echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
total=$((PASS + FAIL))
echo -e "  Results: ${GREEN}${BOLD}$PASS passed${NC} / $total tests"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

if [ "$FAIL" -gt 0 ]; then
    exit 1
fi
exit 0

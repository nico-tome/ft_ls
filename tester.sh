#!/usr/bin/env bash
set -euo pipefail

export LC_TIME=C

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

FT_LS="./ft_ls"
TEST_DIR="."
TMP_DIR="$(mktemp -d "${TMPDIR:-/tmp}/ft_ls_tester.XXXXXX")"

cleanup() {
  rm -rf "$TMP_DIR"
}
trap cleanup EXIT

if [ ! -d "$TEST_DIR" ]; then
  printf "Warning: test directory '%s' not found, using current directory instead.\n" "$TEST_DIR"
  TEST_DIR="."
fi

if [ ! -x "$FT_LS" ]; then
  printf "Building ft_ls...\n"
  if ! make > /dev/null 2>&1; then
    printf "Error: impossible de compiler ft_ls.\n"
    exit 1
  fi
fi

if ! command -v ls > /dev/null 2>&1; then
  printf "Error: commande ls introuvable.\n"
  exit 1
fi

GREEN='\033[32m'
RED='\033[31m'
YELLOW='\033[33m'
PURPLE='\033[35m'
BOLD='\033[1m'
RESET='\033[0m'

if command ls --color=never . > /dev/null 2>&1; then
  LS_CMD=(command ls --color=never)
else
  LS_CMD=(command ls)
fi

if command -v valgrind > /dev/null 2>&1; then
  VALGRIND_AVAILABLE=1
else
  VALGRIND_AVAILABLE=0
fi

run_command() {
  local output_file="$1"
  shift
  if [ "${1:-}" = "command" ]; then
    shift
  fi
  if command -v python3 > /dev/null 2>&1; then
    python3 - "$output_file" "$@" <<'PY' > /dev/null
import os
import sys
import fcntl
import termios
import struct
import pty
import subprocess
out_file = sys.argv[1]
cmd = sys.argv[2:]
raw_output = b''
with open(out_file + '.raw', 'wb') as f:
    master, slave = pty.openpty()
    size = struct.pack('HHHH', 24, 120, 0, 0)
    fcntl.ioctl(slave, termios.TIOCSWINSZ, size)
    env = os.environ.copy()
    env['COLUMNS'] = '120'
    env['TERM'] = 'xterm'
    p = subprocess.Popen(cmd, stdin=slave, stdout=slave, stderr=slave, close_fds=True, env=env)
    os.close(slave)
    while True:
        try:
            data = os.read(master, 1024)
        except OSError:
            break
        if not data:
            break
        f.write(data)
        raw_output += data
    os.close(master)
    ret = p.wait()

with open(out_file, 'wb') as f:
    f.write(raw_output.replace(b'\r\n', b'\n').replace(b'\r', b'\n'))
sys.exit(ret)
PY
    return $?
  fi

  if "$@" > "$output_file" 2>&1; then
    return 0
  fi
  return $?
}

run_valgrind() {
  local log_file="$1"
  shift
  if [ "$VALGRIND_AVAILABLE" -eq 0 ]; then
    return 127
  fi
  valgrind --leak-check=full --errors-for-leak-kinds=all --error-exitcode=42 --quiet --log-file="$log_file" "$@" > /dev/null 2>&1
  return $?
}

extract_valgrind_summary() {
  local log_file="$1"
  if [ ! -f "$log_file" ]; then
    printf "valgrind: not run\n"
    return
  fi
  grep -E 'ERROR SUMMARY:|definitely lost:|still reachable:' "$log_file" | sed 's/^/  /'
}

show_diff_sbs() {
  local left="$1"
  local right="$2"
  local cols
  local left_label="ls output"
  local right_label="ft_ls output"
  local left_width
  local diff_cmd

  cols=$(tput cols 2>/dev/null || echo 120)
  left_width=$(( (cols - 4) / 2 ))
  printf "    %-${left_width}s | %s\n" "$left_label" "$right_label"

  if command -v colordiff > /dev/null 2>&1; then
    diff_cmd=(colordiff -y --suppress-common-lines --width="$cols")
  elif diff --help 2>&1 | grep -q -- '--color'; then
    diff_cmd=(diff --color=always -y --suppress-common-lines --width="$cols")
  else
    diff_cmd=(diff -y --suppress-common-lines --width="$cols")
  fi

  "${diff_cmd[@]}" "$left" "$right" 2>/dev/null | awk -v red="$RED" -v reset="$RESET" '{ if ($0 ~ /[|<>]/) print red $0 reset; else print }' || true
}

sanitize_output() {
  local src="$1"
  local dst="$2"
  perl -pe 's/\e\[[0-9;]*[A-Za-z]//g' "$src" > "$dst"
}

compare_outputs() {
  cd "$SCRIPT_DIR" || exit 1
  local flags="$1"
  local label="$2"
  local expected_file="$TMP_DIR/ls.${label}.out"
  local actual_file="$TMP_DIR/ft_ls.${label}.out"
  local diff_file="$TMP_DIR/diff.${label}.txt"
  local vg_log="$TMP_DIR/valgrind.${label}.log"
  local ls_status
  local ft_status
  local vg_status

  local expected_clean="$TMP_DIR/ls.${label}.clean.out"
  local actual_clean="$TMP_DIR/ft_ls.${label}.clean.out"

  if [ -z "$flags" ]; then
    run_command "$expected_file" "${LS_CMD[@]}" "$TEST_DIR"
    ls_status=$?
    run_command "$actual_file" "$FT_LS" "$TEST_DIR"
    ft_status=$?
    run_valgrind "$vg_log" "$FT_LS" "$TEST_DIR"
    vg_status=$?
  else
    run_command "$expected_file" "${LS_CMD[@]}" "$flags" "$TEST_DIR"
    ls_status=$?
    run_command "$actual_file" "$FT_LS" "$flags" "$TEST_DIR"
    ft_status=$?
    run_valgrind "$vg_log" "$FT_LS" "$flags" "$TEST_DIR"
    vg_status=$?
  fi

  sanitize_output "$expected_file" "$expected_clean"
  sanitize_output "$actual_file" "$actual_clean"

  local display="${flags:-default}"
  local diff_ok=0
  if diff -u "$expected_clean" "$actual_clean" > "$diff_file"; then
    diff_ok=1
  fi

  if [ "$diff_ok" -eq 1 ] && [ "$ls_status" -eq "$ft_status" ] && [ "$vg_status" -ne 42 ]; then
    printf "%b\n" "${BOLD}${PURPLE}[${display}]${RESET} ${GREEN}OK ✅${RESET}"
    return 0
  fi

  printf "%b\n" "${BOLD}${PURPLE}[${display}]${RESET} ${RED}KO ❌${RESET}"
  printf "%b\n" "${YELLOW}Result details:${RESET}"
  printf "  Expected exit code: %s\n" "$ls_status"
  printf "  Actual exit code:   %s\n" "$ft_status"
  if [ "$diff_ok" -ne 1 ]; then
    printf "%b\n" "  Output:             ${RED}diff found${RESET}"
    printf "  Diff file:           %s\n" "$diff_file"
    printf "%b\n" "  Diff side-by-side:${RESET}"
    show_diff_sbs "$expected_clean" "$actual_clean" | sed 's/^/    /'
  else
    printf "%b\n" "  Output:             ${GREEN}match${RESET}"
  fi
  if [ "$VALGRIND_AVAILABLE" -eq 1 ]; then
    if [ "$vg_status" -eq 42 ]; then
      printf "%b\n" "  Valgrind:           ${RED}memory issues${RESET}"
    else
      printf "%b\n" "  Valgrind:           ${GREEN}clean${RESET}"
    fi
    extract_valgrind_summary "$vg_log"
  else
    printf "%b\n" "  Valgrind:           ${YELLOW}not installed${RESET}"
  fi
  printf "  Reference output:    %s\n" "$expected_file"
  printf "  ft_ls output:         %s\n" "$actual_file"
  printf "  Valgrind log:       %s\n" "$vg_log"
  printf '\n'
  return 1
}

run_base_tests() {
  local flags_list=("" "-l" "-a" "-la" "-al" "-R" "-r" "-t" "-d" "-1" "-ltr" "-alR")
  local passed=0
  local total=0

  printf "Running base ft_ls tests on '%s'...\n" "$TEST_DIR"
  for flags in "${flags_list[@]}"; do
    local label
    label="${flags// /_}"
    label="${label//[^a-zA-Z0-9]/_}"
    [ -z "$label" ] && label="default"

    printf '========================================\n'
    total=$((total + 1))
    if compare_outputs "$flags" "$label"; then
      passed=$((passed + 1))
    fi
  done
  printf '========================================\n'

  printf "\nScore: %d/%d\n" "$passed" "$total"
  if [ "$passed" -ne "$total" ]; then
    printf "Some tests failed.\n"
    exit 1
  fi

  printf "All base tests passed.\n"
}

compare_with_args() {
  cd "$SCRIPT_DIR" || exit 1
  local expected_file="$TMP_DIR/ls.args.out"
  local actual_file="$TMP_DIR/ft_ls.args.out"
  local expected_clean="$TMP_DIR/ls.args.clean.out"
  local actual_clean="$TMP_DIR/ft_ls.args.clean.out"
  local diff_file="$TMP_DIR/diff.args.txt"
  local vg_log="$TMP_DIR/valgrind.args.log"
  local ls_status
  local ft_status
  local vg_status
  local display="$*"

  printf "Comparing 'ls' and 'ft_ls' with args: %s\n" "$*"
  run_command "$expected_file" "${LS_CMD[@]}" "$@"
  ls_status=$?
  run_command "$actual_file" "$FT_LS" "$@"
  ft_status=$?
  run_valgrind "$vg_log" "$FT_LS" "$@"
  vg_status=$?

  sanitize_output "$expected_file" "$expected_clean"
  sanitize_output "$actual_file" "$actual_clean"

  local diff_ok=0
  if diff -u "$expected_clean" "$actual_clean" > "$diff_file"; then
    diff_ok=1
  fi

  if [ "$diff_ok" -eq 1 ] && [ "$ls_status" -eq "$ft_status" ] && [ "$vg_status" -ne 42 ]; then
    printf "%b\n" "${BOLD}${PURPLE}[${display}]${RESET} ${GREEN}OK ✅${RESET}"
    return 0
  fi

  printf "%b\n" "${BOLD}${PURPLE}[${display}]${RESET} ${RED}KO ❌${RESET}"
  printf "%b\n" "${YELLOW}Result details:${RESET}"
  printf "  Expected exit code: %s\n" "$ls_status"
  printf "  Actual exit code:   %s\n" "$ft_status"
  if [ "$diff_ok" -ne 1 ]; then
    printf "%b\n" "  Output:             ${RED}diff found${RESET}"
    printf "  Diff file:           %s\n" "$diff_file"
    printf "%b\n" "  Diff side-by-side:${RESET}"
    show_diff_sbs "$expected_clean" "$actual_clean" | sed 's/^/    /'
  else
    printf "%b\n" "  Output:             ${GREEN}match${RESET}"
  fi
  if [ "$VALGRIND_AVAILABLE" -eq 1 ]; then
    if [ "$vg_status" -eq 42 ]; then
      printf "%b\n" "  Valgrind:           ${RED}memory issues${RESET}"
    else
      printf "%b\n" "  Valgrind:           ${GREEN}clean${RESET}"
    fi
    extract_valgrind_summary "$vg_log"
  else
    printf "%b\n" "  Valgrind:           ${YELLOW}not installed${RESET}"
  fi
  printf "  Reference output:    %s\n" "$expected_file"
  printf "  ft_ls output:         %s\n" "$actual_file"
  printf "  Valgrind log:       %s\n" "$vg_log"
  printf '\n'
  exit 1
}

if [ "$#" -eq 0 ]; then
  run_base_tests
else
  compare_with_args "$@"
fi

#!/bin/bash

# Strict mode for safer scripts
set -uo pipefail

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# Project Paths
MANDATORY="./build/cub3D"
BONUS="./build/cub3D_bonus"
TEST_DIR="maps/tests"

# Header
echo -e "${BLUE}==================================================${NC}"
echo -e "${BLUE}       cub3D Invalid Maps Tester                  ${NC}"
echo -e "${BLUE}==================================================${NC}"

# Ensure binaries are built
build_binaries() {
    echo -e "${YELLOW}Ensuring binaries are up to date...${NC}"
    if ! make > /dev/null 2>&1; then
        echo -e "${RED}Error: Failed to build mandatory binary.${NC}"
        exit 1
    fi
    if ! make bonus > /dev/null 2>&1; then
        echo -e "${RED}Error: Failed to build bonus binary.${NC}"
        exit 1
    fi
}

run_test_suite() {
    local binary="$1"
    local suite_name="$2"
    
    if [[ ! -f "$binary" ]]; then
        echo -e "${RED}Binary $binary not found. Skipping $suite_name tests.${NC}"
        return
    fi

    echo -e "\n${BLUE}--- Testing $suite_name ($binary) ---${NC}" 
    
    local total=0
    local passed=0
    local failed=0

    # Using find with a null delimiter to safely handle spaces in filenames
    while IFS= read -r -d '' map_path; do
        map_name=$(basename "$map_path")
        ((total++))
        
        # Run binary. We expect a non-zero exit code for invalid maps.
        # We also capture output in case we want to check for "Error\n" prefix later.
        "$binary" "$map_path" > /dev/null 2>&1
        exit_code=$?

        if [ $exit_code -ne 0 ]; then
            printf " [%-45s] ${GREEN}OK${NC}\n" "$map_name"
            ((passed++))
        else
            printf " [%-45s] ${RED}KO (Returned 0)${NC}\n" "$map_name"
            ((failed++))
        fi
    done < <(find "$TEST_DIR" -maxdepth 1 -name "*invalid_*.cub" -print0 | sort -z)

    echo -e "\n$suite_name Results:"
    echo -e "  Total:  $total"
    echo -e "  ${GREEN}Passed: $passed${NC}"
    echo -e "  ${RED}Failed: $failed${NC}"
}

# Main execution
build_binaries
run_test_suite "$MANDATORY" "Mandatory"
run_test_suite "$BONUS" "Bonus"

echo -e "\n${BLUE}==================================================${NC}"
echo -e "${BLUE}                Tests Completed                   ${NC}"
echo -e "${BLUE}==================================================${NC}"

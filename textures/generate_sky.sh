#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    generate_sky.sh                                    :+:      :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafael <rafael@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/07 16:45:00 by rafael            #+#    #+#              #
#    Updated: 2026/03/07 16:45:00 by rafael           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

set -euo pipefail

# Configuration
TEXTURES_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
OUTPUT_FILE="${TEXTURES_DIR}/skybox.xpm"

usage() {
    echo "Usage: $0 <input_image>"
    echo "Transforms an image into the skybox.xpm file required for cub3D bonus."
    exit 1
}

# Check arguments
if [[ $# -ne 1 ]]; then
    usage
fi

INPUT_IMAGE="$1"

# Check if input file exists
if [[ ! -f "${INPUT_IMAGE}" ]]; then
    echo "Error: File '${INPUT_IMAGE}' not found." >&2
    exit 1
fi

# Check if 'magick' or 'convert' is installed
if command -v magick >/dev/null 2>&1; then
    CONVERT_CMD="magick"
elif command -v convert >/dev/null 2>&1; then
    CONVERT_CMD="convert"
else
    echo "Error: ImageMagick is not installed (magick/convert not found)." >&2
    exit 1
fi

# Remove previous output if it exists
if [[ -f "${OUTPUT_FILE}" ]]; then
    echo "Removing existing ${OUTPUT_FILE}..."
    rm "${OUTPUT_FILE}"
fi

# Transform image to XPM with vertical padding for high pitch angles
echo "Transforming '${INPUT_IMAGE}' to '${OUTPUT_FILE}' (padding to 2000px height)..."
"${CONVERT_CMD}" "${INPUT_IMAGE}" -resize "x2000>" -gravity center -background black -extent "x2000" "${OUTPUT_FILE}"

echo "Success! Skybox texture generated."

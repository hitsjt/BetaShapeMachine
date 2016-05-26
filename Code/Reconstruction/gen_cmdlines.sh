#!/bin/bash

if [[ $# -lt 2 ]]
then
  echo "Usage: $0 <training-dir> <synth-dir>"
  exit 0
fi

REL_SCRIPT_DIR=`dirname $0`
SCRIPT_DIR="`perl -e 'use Cwd "abs_path";print abs_path(shift)' "$REL_SCRIPT_DIR"`"

TRAIN_DIR="$1"
SYNTH_DIR="$2"

cd "$SCRIPT_DIR"
make
cd -

ls -1 "$SYNTH_DIR"/*.sparse.xyz | xargs -I filename "${SCRIPT_DIR}/ConvertOutput" "$TRAIN_DIR" filename

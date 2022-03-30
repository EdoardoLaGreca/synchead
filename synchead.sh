#! /bin/sh

source_path="$1"

## DO NOT TOUCH ##
function_regex="^\s*((struct|enum)\s+)?([A-z_][A-z0-9_]+)\**\s*\**([A-z_][A-z0-9_]+)\s*\(\s*(\s*((struct|enum)\s+)?([A-z_][A-z0-9_]+)\**\s\**([A-z_][A-z0-9_]+)\s*,?)*\s*\)"
##################

# check if a path was provided
if [ -z $source_path ]
then
	echo "ERROR: no file path provided."
	exit 1
fi

# check if the source file exists
if [ ! -f $source_path ]
then
	echo "ERROR: file does not exist or cannot be read."
fi

# get functions from source file
source_functions=`grep -E $function_regex $source_path`

# check if source file has functions
if [ -z $source_functions ]
then
	echo "no functions found in source file"
fi

header_path=`echo $source_file | sed s/.c/.h/`

# check if header path exists
if [ ! -f $header_path ]
then
	echo "header file not found, creating..."
	touch $header_path
fi


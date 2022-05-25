#! /bin/sh

header_path="$1"
source_path=`echo $header_path | sed "s/.h/.c/"`

## DO NOT TOUCH ##
function_regex="^\s*((struct|enum)\s+)?([A-z_][A-z0-9_]+)\**\s*\**([A-z_][A-z0-9_]+)\s*\(\s*(\s*((struct|enum)\s+)?([A-z_][A-z0-9_]+)\**\s\**([A-z_][A-z0-9_]+)\s*,?)*\s*\)"
function_name_regex="^\s*((struct|enum)\s+)?([A-z_][A-z0-9_]+)\**\s*\**func_name\s*\(\s*(\s*((struct|enum)\s+)?([A-z_][A-z0-9_]+)\**\s\**([A-z_][A-z0-9_]+)\s*,?)*\s*\)"
##################

# check if a path was provided
if [ -z $header_path ]
then
	echo "ERROR: no file path provided." >&2
	exit 1
fi

# check if source file exists
if [ ! -f $source_path ]
then
	echo "ERROR: file does not exist or cannot be read." >&2
	exit 1
fi

# get functions from source file and replace newlines with spaces
source_functions=`grep -E $function_regex $source_path | sed "s/\n/ /g"`

# check if source file has functions
if [ -z $source_functions ]
then
	echo "no functions found in source file" >&2
	exit 0
fi

# check if header file exists
# if it doesn't, create it and paste the functions
if [ ! -f $header_path ]
then
	echo "header file not found, creating..." >&2
	echo $source_functions >$header_path
	exit 0
fi

# get functions from header file and replace newlines with spaces
header_functions=`grep -E $function_regex $header_path | sed "s/\n/ /g"`

echo $source_functions | while read curr_function
do
	# get function name
	#TODO
done

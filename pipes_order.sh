#!/bin/bash
set -x
# This script is used to order the pipes in the order of the input file
# The input file is the list of pipes in the order they need to be ordered
# The output file is the list of pipes in the order they are ordered
# The input file is the first argument
# The output file is the second argument

# Check if the input file is provided
if [ -z $1 ]; then
	echo "Input file is not provided"
	exit 1
fi

# Check if the output file is provided
if [ -z $2 ]; then
	echo "Output file is not provided"
	exit 1
fi

# Check if the input file exists
if [ ! -f $1 ]; then
	echo "Input file does not exist"
	exit 1
fi

# Check if the output file exists
if [ -f $2 ]; then
	echo "Output file already exists"
	exit 1
fi

# Get the list of pipes from the input file
pipes=$(cat $1)

# Order the pipes
for pipe in $pipes; do
	# Check if the pipe exists
	if [ ! -p $pipe ]; then
		echo "Pipe $pipe does not exist"
		exit 1
	fi
done

# Write the ordered pipes to the output file
echo $pipes > $2
```


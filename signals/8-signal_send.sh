#!/bin/bash

if [ $# -ne 2 ]; then
	echo "Usage: $0 <pid>"
	exit 1
fi
kill -SIGQUIT $1

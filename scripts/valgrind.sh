#!/bin/bash
cd ../bin/release/
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./tcash

#!/bin/bash
echo $?
./minishell
exit
echo $?
./minishell
exit 2
echo $?
./minishell
exit 42
echo $?
./minishell
exit -42
echo $?
./minishell
exit 42 10
echo $?
./minishell
exit 42 school
echo $?
./minishell
exit 42school
echo $?
./minishell
exit 9223372036854775807
echo $?
./minishell
exit -9223372036854775808
echo $?
./minishell
exit 9223372036854775808
echo $?
./minishell
exit 0
echo $?
./minishell
exit  +20
echo $?

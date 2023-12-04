/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:49:28 by antoda-s          #+#    #+#             */
/*   Updated: 2023/12/04 14:49:00 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

/* ************************************************************************** */
///	ERROR CODES
/* ************************************************************************** */
# ifndef ERROR
#  define ERROR 1
# endif
# ifndef SUCCESS
#  define SUCCESS 0
# endif

# ifndef LINE_ERROR
#  define LINE_ERROR 50
# endif

# ifndef ARGS_ERROR
#  define ARGS_ERROR 52
# endif

# ifndef SYNTAX_ERROR
#  define SYNTAX_ERROR 54
# endif
# ifndef COLOR_ERROR
#  define COLOR_ERROR 55
# endif


/* ************************************************************************** */
///	MALLOC ERROR CODES
/* ************************************************************************** */
# ifndef MALLOC_ERROR
#  define MALLOC_ERROR 100
# endif
# ifndef MALLOC_NOT_ALLOCATED
#  define MALLOC_NOT_ALLOCATED 101
# endif
# ifndef MALLOC_NOT_FREED
#  define MALLOC_NOT_FREED 102
# endif
# ifndef MALLOC_NOT_REALLOCATED
#  define MALLOC_NOT_REALLOCATED 103
# endif

/* ************************************************************************** */
///	FILE ERROR CODES and STATUS
/* ************************************************************************** */
# ifndef FILE_ERROR
#  define FILE_ERROR 200
# endif
# ifndef FILE_EMPTY
#  define FILE_EMPTY 201
# endif
# ifndef FILE_NOT_FOUND
#  define FILE_NOT_FOUND 202
# endif
# ifndef FILE_NOT_READABLE
#  define FILE_NOT_READABLE 203
# endif
# ifndef FILE_NOT_VALID
#  define FILE_NOT_VALID 204
# endif
# ifndef FILE_NOT_OPEN
#  define FILE_NOT_OPEN 205
# endif
# ifndef FILE_NOT_CLOSED
#  define FILE_NOT_CLOSED 206
# endif
# ifndef FILE_NOT_WRITABLE
#  define FILE_NOT_WRITABLE 207
# endif
# ifndef FILE_NOT_CREATED
#  define FILE_NOT_CREATED 208
# endif
# ifndef FILE_NOT_DELETED
#  define FILE_NOT_DELETED 209
# endif
# ifndef FILE_NOT_RENAMED
#  define FILE_NOT_RENAMED 210
# endif
# ifndef FILE_NOT_COPIED
#  define FILE_NOT_COPIED 211
# endif
# ifndef FILE_NOT_MOVED
#  define FILE_NOT_MOVED 212
# endif
# ifndef FILE_NOT_EXECUTABLE
#  define FILE_NOT_EXECUTABLE 213
# endif
# ifndef FILE_NOT_EXECUTED
#  define FILE_NOT_EXECUTED 214
# endif

/* ************************************************************************** */
///	PIPE ERROR CODES and STATUS
/* ************************************************************************** */
# ifndef PIPE_ERROR
#  define PIPE_ERROR 300
# endif
# ifndef PIPE_OPEN
#  define PIPE_OPEN 301
# endif
# ifndef PIPE_CLOSED
#  define PIPE_CLOSED 302
# endif
# ifndef PIPE_NOT_OPEN
#  define PIPE_NOT_OPEN 303
# endif
# ifndef PIPE_NOT_CLOSED
#  define PIPE_NOT_CLOSED 304
# endif
# ifndef PIPE_NOT_CREATED
#  define PIPE_NOT_CREATED 305
# endif
# ifndef PIPE_NOT_DELETED
#  define PIPE_NOT_DELETED 306
# endif
# ifndef PIPE_NOT_RENAMED
#  define PIPE_NOT_RENAMED 307
# endif
# ifndef PIPE_NOT_COPIED
#  define PIPE_NOT_COPIED 308
# endif
# ifndef PIPE_NOT_MOVED
#  define PIPE_NOT_MOVED 309
# endif
# ifndef PIPE_NOT_EXECUTABLE
#  define PIPE_NOT_EXECUTABLE 310
# endif
# ifndef PIPE_NOT_EXECUTED
#  define PIPE_NOT_EXECUTED 311
# endif

/* ************************************************************************** */
///	PROCESS ERROR CODES and STATUS
/* ************************************************************************** */
# ifndef PROCESS_ERROR
#  define PROCESS_ERROR 400
# endif
# ifndef PROCESS_OPEN
#  define PROCESS_OPEN 401
# endif
# ifndef PROCESS_CLOSED
#  define PROCESS_CLOSED 402
# endif
# ifndef PROCESS_NOT_OPEN
#  define PROCESS_NOT_OPEN 403
# endif
# ifndef PROCESS_NOT_CLOSED
#  define PROCESS_NOT_CLOSED 404
# endif
# ifndef PROCESS_NOT_CREATED
#  define PROCESS_NOT_CREATED 405
# endif
# ifndef PROCESS_NOT_DELETED
#  define PROCESS_NOT_DELETED 406
# endif
# ifndef PROCESS_NOT_RENAMED
#  define PROCESS_NOT_RENAMED 407
# endif
# ifndef PROCESS_NOT_COPIED
#  define PROCESS_NOT_COPIED 408
# endif
# ifndef PROCESS_NOT_MOVED
#  define PROCESS_NOT_MOVED 409
# endif
# ifndef PROCESS_NOT_EXECUTABLE
#  define PROCESS_NOT_EXECUTABLE 410
# endif
# ifndef PROCESS_NOT_EXECUTED
#  define PROCESS_NOT_EXECUTED 411
# endif

/* ************************************************************************** */
///	FORK ERROR CODES and STATUS
/* ************************************************************************** */
# ifndef FORK_OPEN
#  define FORK_OPEN 501
# endif
# ifndef FORK_CLOSED
#  define FORK_CLOSED 502
# endif
# ifndef FORK_NOT_OPEN
#  define FORK_NOT_OPEN 503
# endif
# ifndef FORK_NOT_CLOSED
#  define FORK_NOT_CLOSED 504
# endif
# ifndef FORK_NOT_CREATED
#  define FORK_NOT_CREATED 505
# endif
# ifndef FORK_NOT_DELETED
#  define FORK_NOT_DELETED 506
# endif
# ifndef FORK_NOT_RENAMED
#  define FORK_NOT_RENAMED 507
# endif
# ifndef FORK_NOT_COPIED
#  define FORK_NOT_COPIED 508
# endif
# ifndef FORK_NOT_MOVED
#  define FORK_NOT_MOVED 509
# endif
# ifndef FORK_NOT_EXECUTABLE
#  define FORK_NOT_EXECUTABLE 510
# endif
# ifndef FORK_NOT_EXECUTED
#  define FORK_NOT_EXECUTED 511
# endif


/* ************************************************************************** */
///	EXEC ERROR CODES and STATUS
/* ************************************************************************** */
# ifndef EXEC_ERROR
#  define EXEC_ERROR 600
# endif
# ifndef EXEC_OPEN
#  define EXEC_OPEN 601
# endif
# ifndef EXEC_CLOSED
#  define EXEC_CLOSED 602
# endif
# ifndef EXEC_NOT_OPEN
#  define EXEC_NOT_OPEN 603
# endif
# ifndef EXEC_NOT_CLOSED
#  define EXEC_NOT_CLOSED 604
# endif
# ifndef EXEC_NOT_CREATED
#  define EXEC_NOT_CREATED 605
# endif
# ifndef EXEC_NOT_DELETED
#  define EXEC_NOT_DELETED 606
# endif
# ifndef EXEC_NOT_RENAMED
#  define EXEC_NOT_RENAMED 607
# endif
# ifndef EXEC_NOT_COPIED
#  define EXEC_NOT_COPIED 608
# endif
# ifndef EXEC_NOT_MOVED
#  define EXEC_NOT_MOVED 609
# endif
# ifndef EXEC_NOT_EXECUTABLE
#  define EXEC_NOT_EXECUTABLE 610
# endif
# ifndef EXEC_NOT_EXECUTED
#  define EXEC_NOT_EXECUTED 611
# endif


/* ************************************************************************** */
///	CD ERROR CODES and STATUS
/* ************************************************************************** */
# ifndef CD_ERROR
#  define CD_ERROR 700
# endif
# ifndef CD_OPEN
#  define CD_OPEN 701
# endif
# ifndef CD_CLOSED
#  define CD_CLOSED 702
# endif
# ifndef CD_NOT_OPEN
#  define CD_NOT_OPEN 703
# endif
# ifndef CD_NOT_CLOSED
#  define CD_NOT_CLOSED 704
# endif
# ifndef CD_NOT_CREATED
#  define CD_NOT_CREATED 705
# endif
# ifndef CD_NOT_DELETED
#  define CD_NOT_DELETED 706
# endif
# ifndef CD_NOT_RENAMED
#  define CD_NOT_RENAMED 707
# endif
# ifndef CD_NOT_COPIED
#  define CD_NOT_COPIED 708
# endif
# ifndef CD_NOT_MOVED
#  define CD_NOT_MOVED 709
# endif
# ifndef CD_NOT_EXECUTABLE
#  define CD_NOT_EXECUTABLE 710
# endif
# ifndef CD_NOT_EXECUTED
#  define CD_NOT_EXECUTED 711
# endif

// # ifndef FILE_ERROR
// #  define FILE_ERROR 21
// # endif


#endif

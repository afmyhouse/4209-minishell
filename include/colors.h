/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoda-s <antoda-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:25:51 by antoda-s          #+#    #+#             */
/*   Updated: 2023/10/29 17:54:20 by antoda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# ifndef NUMCOLORS
#  define NUMCOLORS 255
# endif
/* ************************************************************************** */
///	STRINGS COLORS
/* ************************************************************************** */
# define SRED "\033[0;31m"
# define SGRN "\033[0;32m"
# define SYLW "\033[0;33m"
# define SBLU "\033[0;34m"
# define SPPL "\033[0;35m"
# define SCYN "\033[1;36m"
# define SWHT "\033[0m"
# define SBOLD "\033[1;1m"

/* ************************************************************************** */
///	MLX PIXEL COLORS
/* ************************************************************************** */
// RED 0x
# define INDIANRED 0xcd5c5c
# define LIGHTCORAL 0xf08080
# define SALMON 0xfa8072
# define DARKSALMON 0xe9967a
# define LIGHTSALMON 0xffa07a
# define CRIMSON 0xdc143c
# define RED 0xff0000
# define FIREBRICK 0xb22222
# define DARKRED 0x8b0000
// PINK 0x
# define PINK 0xffc0cb
# define LIGHTPINK 0xffb6c1
# define HOTPINK 0xff69b4
# define DEEPPINK 0xff1493
# define MEDIUMVIOLETRED 0xc71585
# define PALEVIOLETRED 0xdb7093
// ORANGE 0x
# define CORAL 0xff7f50
# define ORANGE 0xffa500
# define DARKORANGE 0xff8c00
# define ORANGERED 0xff4500
# define LIGHTSALMON 0xffa07a
# define TOMATO 0xff6347
// YELLOW 0x
# define GOLD 0xffd700
# define LIGHTGOLDENRODYELLOW 0xfafad2
# define PALEGOLDENROD 0xeee8aa
# define KHAKI 0xf0e68c
# define DARKKHAKI 0xbdb76b
# define LEMONCHIFFON 0xfffacd
# define MOCCASIN 0xffe4b5
# define PAPAYAWHIP 0xffefd5
# define PEACHPUFF 0xffdab9
# define YELLOW 0xffff00
# define YELLOWGREEN 0x9acd32
# define LIGHTYELLOW 0xffffe0
// PURPLE 0x
# define SLATEBLUE 0x6a5acd
# define DARKSLATEBLUE 0x483d8b
# define MEDIUMSLATEBLUE 0x7b68ee
# define BLUEVIOLET 0x8a2be2
# define FUCHSIA 0xff00ff
# define INDIGO 0x4b0082
# define LAVENDER 0xe6e6fa
# define MAGENTA 0xff00ff
# define DARKMAGENTA 0x8b008b
# define ORCHID 0xda70d6
# define DARKORCHID 0x9932cc
# define MEDIUMORCHID 0xba55d3
# define PLUM 0xdda0dd
# define PURPLE 0x800080
# define MEDIUMPURPLE 0x9370db
# define REBECCAPURPLE 0x663399
# define THISTLE 0xd8bfd8
# define VIOLET 0xee82ee
# define DARKVIOLET 0x9400d3
// GREEN 0x
# define MEDIUMAQUAMARINE 0x66cdaa
# define CHARTREUSE 0x7fff00
# define DARKCYAN 0x008b8b
# define GREEN 0x008000
# define DARKGREEN 0x006400
# define FORESTGREEN 0x228b22
# define LAWNGREEN 0x7cfc00
# define LIMEGREEN 0x32cd32
# define LIGHTGREEN 0x90ee90
# define PALEGREEN 0x98fb98
# define SEAGREEN 0x2e8b57
# define DARKSEAGREEN 0x8fbc8b
# define LIGHTSEAGREEN 0x20b2aa
# define MEDIUMSEAGREEN 0x3cb371
# define SPRINGGREEN 0x00ff7f
# define MEDIUMSPRINGGREEN 0x00fa9a
# define GREENYELLOW 0xadff2f
# define LIME 0x00ff00
# define OLIVE 0x808000
# define DARKOLIVEGREEN 0x556b2f
# define OLIVEDRAB 0x6b8e23
# define TEAL 0x008080
// BLUE 0x
# define CYAN 0x00ffff
# define LIGHTCYAN 0xe0ffff
# define PALETURQUOISE 0xafeeee
# define AQUAMARINE 0x7fffd4
# define TURQUOISE 0x40e0d0
# define MEDIUMTURQUOISE 0x48d1cc
# define DARKTURQUOISE 0x00ced1
# define CADETBLUE 0x5f9ea0
# define STEELBLUE 0x4682b4
# define LIGHTSTEELBLUE 0xb0c4de
# define POWDERBLUE 0xb0e0e6
# define LIGHTBLUE 0xadd8e6
# define SKYBLUE 0x87ceeb
# define LIGHTSKYBLUE 0x87cefa
# define DEEPSKYBLUE 0x00bfff
# define DODGERBLUE 0x1e90ff
# define CORNFLOWERBLUE 0x6495ed
# define MEDIUMSLATEBLUE 0x7b68ee
# define ROYALBLUE 0x4169e1
# define BLUE 0x0000ff
# define MEDIUMBLUE 0x0000cd
# define DARKBLUE 0x00008b
# define NAVY 0x000080
# define MIDNIGHTBLUE 0x191970
// BROWN 0x
# define CORNSILK 0xfff8dc
# define BLANCHEDALMOND 0xffebcd
# define BISQUE 0xffe4c4
# define NAVAJOWHITE 0xffdead
# define WHEAT 0xf5deb3
# define BURLYWOOD 0xdeb887
# define TAN 0xd2b48c
# define ROSYBROWN 0xbc8f8f
# define SANDYBROWN 0xf4a460
# define GOLDENROD 0xdaa520
# define DARKGOLDENROD 0xb8860b
# define PERU 0xcd853f
# define CHOCOLATE 0xd2691e
# define SADDLEBROWN 0x8b4513
# define SIENNA 0xa0522d
# define BROWN 0xa52a2a
# define MAROON 0x800000
// WHITE 0x
# define WHITE 0xffffff
# define SNOW 0xfffafa
# define HONEYDEW 0xf0fff0
# define MINTCREAM 0xf5fffa
# define AZURE 0xf0ffff
# define ALICEBLUE 0xf0f8ff
# define GHOSTWHITE 0xf8f8ff
# define WHITESMOKE 0xf5f5f5
# define SEASHELL 0xfff5ee
# define BEIGE 0xf5f5dc
# define OLDLACE 0xfdf5e6
# define FLORALWHITE 0xfffaf0
# define IVORY 0xfffff0
# define ANTIQUEWHITE 0xfaebd7
# define LINEN 0xfaf0e6
# define LAVENDERBLUSH 0xfff0f5
# define MISTYROSE 0xffe4e1
// GRAY 0x
# define GAINSBORO 0xdcdcdc
# define LIGHTGRAY 0xd3d3d3
# define SILVER 0xc0c0c0
# define DARKGRAY 0xa9a9a9
# define GRAY 0x808080
# define DIMGRAY 0x696969
# define LIGHTSLATEGRAY 0x778899
# define SLATEGRAY 0x708090
# define DARKSLATEGRAY 0x2f4f4f
# define BLACK 0x000000
# define ALMOSTBLACK 0x393939

#endif
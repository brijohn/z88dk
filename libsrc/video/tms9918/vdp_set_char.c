/*

	MSX specific routines

	GFX - a small graphics library 
	Copyright (C) 2004  Rafael de Oliveira Jannone

	Set char \a c shape, attributes and color, all in one
	
	$Id: vdp_set_char.c,v 1.2 2016-06-16 20:54:24 dom Exp $
*/

#include <video/tms99x8.h>


void vdp_set_char(int c, void* form, void *attr, unsigned int color, unsigned int place) {
	vdp_set_char_form(c, form, place);
	if (attr)
		vdp_set_char_attr(c, attr, place);
	else
		vdp_set_char_color(c, color, place);
}


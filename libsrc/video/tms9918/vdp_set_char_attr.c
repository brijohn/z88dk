/*

	MSX specific routines

	GFX - a small graphics library 
	Copyright (C) 2004  Rafael de Oliveira Jannone

	Set char \a c attributes, from \a attr, at the given screen map \a place
	
	$Id: vdp_set_char_attr.c,v 1.4 2016-06-16 20:54:24 dom Exp $
*/

#include <video/tms99x8.h>


void vdp_set_char_attr(int c, void *attr, unsigned int place) {
	unsigned int addr = c;
	addr <<= 3;
	addr += MODE2_ATTR;

	if (place & place_1) vdp_vwrite_direct(attr, addr, 8);
	if (place & place_2) vdp_vwrite_direct(attr, (256 * 8) + addr, 8);
	if (place & place_3) vdp_vwrite_direct(attr, (256 * 8 * 2) + addr, 8);
}


/*

	MSX specific routines

	GFX - a small graphics library 
	Copyright (C) 2004  Rafael de Oliveira Jannone

	Set the sprite handle with the shape from data (big size)
	
	$Id: msx_set_sprite_16.c,v 1.5 2016-06-16 20:54:25 dom Exp $
*/

#include <video/tms99x8.h>

void vdp_set_sprite_16(unsigned int handle, void* data) {
	vdp_vwrite_direct(data, _tms9918_sprite_generator + (handle << 5), 32);
}

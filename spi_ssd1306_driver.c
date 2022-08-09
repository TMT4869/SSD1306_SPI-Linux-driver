#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>

#include "ssd1306.h"

/*
**  Jerry Logo
*/
static uint8_t jerry[1024] = {
  	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x9f, 0xe7, 0xf3, 0xf9, 0xfd, 
	0xfd, 0xfd, 0xf9, 0xf1, 0x81, 0x03, 0x07, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xfe, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0x78, 0x7f, 
	0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x8f, 0xcf, 0xef, 0xef, 0xcf, 0xdf, 0x3f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x7f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0x1f, 0x7f, 
	0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 
	0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x3e, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0xff, 0x7f, 0x00, 0xf0, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x07, 
	0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0xfe, 
	0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xe6, 0xf1, 0xfc, 0xff, 0xff, 0xff, 0xff, 
	0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xf9, 0xe7, 0xef, 0xdf, 0xdf, 
	0x9f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x04, 0xc2, 0xc0, 0x60, 0x2c, 0x20, 0x00, 0x00, 0x00, 0x40, 0xc4, 0xc2, 0x80, 0x04, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x3f, 0x0f, 0x03, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf8, 0xfc, 0xfe, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x3f, 0x3f, 0x3f, 0x1f, 0x1f, 
	0x1f, 0x1f, 0x1c, 0x0c, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30, 0x30, 0x30, 0x20, 
	0x44, 0x8e, 0x8f, 0x0e, 0x0c, 0x0c, 0x08, 0x08, 0x0c, 0x0c, 0x8c, 0xcf, 0x4f, 0x07, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x38, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf0, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x3f, 0x0f, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 
	0xe0, 0x60, 0x70, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0xc0, 0xe0, 0xe0, 0xe1, 0xc1, 0xc0, 0xc0, 0xc1, 0xc1, 0xe1, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 
	0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x1e, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xfb, 0xf8, 0xf0, 0x00, 0x00, 0x08, 0xfc, 0xfe, 0xff, 0xff, 0x3f, 0x0f, 0x07, 0x03, 0x03, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xc7, 0x81, 0x00, 0xe0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xc0, 0x80, 0x80, 0xc0, 0xf0, 
	0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe1, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 
	0x3f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xf8, 0xe0, 0x60, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc1, 0xe3, 0x83, 0x03, 0x07, 0x07, 0x07, 
	0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 
	0x1f, 0x07, 0x07, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

/*
**  Tom Logo
*/
static uint8_t tom[1024] = {
  	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xf7, 0xf7, 0x77, 0x77, 0x77, 0x33, 0x3b, 0x1b, 
	0x9b, 0x9b, 0x09, 0x49, 0x0d, 0x85, 0x95, 0xd5, 0xc4, 0xe4, 0xe8, 0xe8, 0xe0, 0xe4, 0xf4, 0xd4, 
	0xfc, 0xfe, 0x7e, 0xfe, 0xfe, 0xff, 0xdf, 0xdf, 0xf3, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xff, 0xff, 
	0xfe, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
	0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x87, 0x87, 0x27, 0x67, 0xe7, 0xf7, 0xf7, 0xf2, 0xfb, 0xfb, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xdf, 0xdf, 0xfe, 0xfe, 0xfc, 0x7c, 0xf9, 0xfb, 0xfb, 0xfb, 0x77, 0xf7, 
	0xf7, 0xd7, 0xf7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xf7, 
	0x2f, 0x2f, 0x6f, 0x6f, 0x6f, 0xed, 0xed, 0xec, 0xae, 0xce, 0xde, 0xdf, 0xdf, 0x5f, 0x0f, 0xc7, 
	0xf1, 0xdc, 0xfe, 0xff, 0xff, 0xff, 0xdf, 0xff, 0xf7, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xbf, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x83, 0xc3, 0xc1, 0xe0, 0xf0, 0xf0, 
	0xf8, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 
	0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x7f, 0x1f, 0x1f, 0x9f, 0x9f, 0x1f, 0x0f, 0x0f, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xfd, 0xf9, 0xfb, 0xf3, 0xf5, 0xc7, 0x0e, 0xff, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xd2, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xf9, 0xff, 0xff, 
	0xef, 0xdf, 0xdf, 0x7b, 0xbc, 0x70, 0x73, 0xff, 0x6b, 0x8f, 0x1f, 0x8f, 0x0f, 0x07, 0x07, 0xc3, 
	0xc1, 0xe1, 0x60, 0x90, 0x30, 0x78, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xf3, 0xc1, 0x81, 0x00, 0x00, 
	0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x87, 0x0f, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 
	0x3f, 0x1e, 0x0c, 0x01, 0x81, 0x43, 0x67, 0x3f, 0xa7, 0x83, 0xd3, 0xd3, 0xe9, 0xe9, 0xe5, 0xf6, 
	0xf4, 0xf4, 0xf2, 0xfa, 0xfa, 0xfa, 0xf8, 0x7d, 0x7d, 0x01, 0xb8, 0x96, 0x53, 0x4a, 0x48, 0x2b, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x9f, 0x9f, 0x1f, 0x1f, 0x0f, 0x2f, 0x27, 0x70, 0xff, 
	0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xd3, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x3f, 0x1f, 0x1f, 0x0f, 
	0x07, 0x07, 0x87, 0x83, 0xc3, 0xc0, 0x80, 0xb0, 0x31, 0x7a, 0xf8, 0xfc, 0xfc, 0xd0, 0xf0, 0x8e, 
	0xc3, 0xcb, 0xef, 0xff, 0xff, 0xfe, 0xfc, 0xf9, 0xd3, 0xe7, 0xef, 0xdf, 0xdf, 0x3f, 0x3f, 0x3f, 
	0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x1e, 0x1e, 0x1f, 0x0f, 0x2f, 0x17, 0x07, 0x43, 0x21, 0x88, 0xc4, 
	0xe0, 0xf0, 0xf8, 0xf9, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xbf, 0xdf, 0xef, 0xff, 
	0xf7, 0xfb, 0xfb, 0xfd, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xfc, 0xf1, 0xe6, 0xe8, 0xe0, 0x52, 0x82, 
	0xdf, 0xbf, 0xbf, 0x7f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xf3, 0xf1, 0xf0, 0xf2, 0xf3, 
	0xfa, 0xf8, 0xc3, 0x8e, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0x9f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x7f, 0x1f, 0x0f, 0x07, 0x03, 0x81, 0xc1, 0xc0, 0xe0, 0xf0, 0xf8, 0x3c, 0x0e, 0x0e, 
	0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x0f, 0x1f, 0x3f, 0x7e, 0xfc, 0xf9, 0xfa, 0xf7, 0xe7, 
	0xcf, 0x9f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xfe, 0xfe, 0xfe, 0xfe, 0x7f, 0x7e, 0xfe, 0x36, 0xcb, 0xe7, 0xfb, 0xf8, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef, 0xf7, 0xfb, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x7f, 0x7f, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0xff, 0xfb, 0xff, 0xfd, 0xff, 0xfe, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xf9, 0xf9, 
	0xfb, 0xfb, 0xfb, 0xfd, 0xfc, 0xfc, 0xfd, 0xf8, 0xf3, 0xed, 0xdf, 0xbf, 0x3f, 0x7f, 0xbe, 0xfe, 
	0xf9, 0xc0, 0x80, 0xc0, 0xf0, 0xe6, 0xcf, 0x9f, 0x3f, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xfc, 0xf8, 
	0xf8, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x7f, 
	0x3f, 0x1f, 0x8f, 0x40, 0x40, 0x89, 0x89, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x31, 0x11, 0x01, 
	0x00, 0xc0, 0xf0, 0x70, 0x71, 0x11, 0x01, 0x00, 0x03, 0x03, 0x03, 0x07, 0x0f, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xf7, 0xfb, 0xfd, 0xfe, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 
	0xf9, 0xf3, 0xf7, 0xef, 0xcf, 0x9f, 0x3f, 0x7f, 0xbf, 0xff, 0xfe, 0xfe, 0xfd, 0xf9, 0xfb, 0xe3, 
	0xf7, 0xf7, 0xf7, 0xef, 0xef, 0xcf, 0xcf, 0xcf, 0xcf, 0xcf, 0xc7, 0xc3, 0xe1, 0xc9, 0xc0, 0xd0, 
	0xd8, 0x2f, 0x92, 0xc8, 0xf4, 0xf2, 0xfb, 0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xf8, 0xf8, 
	0xf0, 0xf1, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xdf, 0xff, 0xbf, 0x3f, 0x3f, 0x1f, 0x1f, 0x8f, 0x8f, 0xcf, 0xe7, 0xe3, 0x73, 0xf9, 
	0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfd, 0xf9, 0xf3, 0xe7, 0x0b, 0x17, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x3f, 0xbe, 0xbf, 
	0x00, 0x5f, 0xef, 0xef, 0xf7, 0xff, 0xfb, 0xfb, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 
	0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xfb, 0xf9, 0xfc, 0xfc, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static struct spi_device *etx_spi_device;

//Register information about your slave device
struct spi_board_info etx_spi_device_info = 
{
  .modalias     = "etx-spi-ssd1306-driver",
  .max_speed_hz = 4000000,              // speed your device (slave) can handle
  .bus_num      = SPI_BUS_NUM,          // SPI 1
  .chip_select  = 0,                    // Use 0 Chip select (GPIO 18)
  .mode         = SPI_MODE_0            // SPI mode 0
};

/****************************************************************************
 * Name: etx_spi_write
 *
 * Details : This function writes the 1-byte data to the slave device using SPI.
 ****************************************************************************/
int etx_spi_write( uint8_t data )
{
  int     ret = -1;
  uint8_t rx  = 0x00;
  
  if( etx_spi_device )
  {    
    struct spi_transfer	tr = 
    {
		.tx_buf	= &data,
		.rx_buf = &rx,
		.len = 1,
	};

    spi_sync_transfer( etx_spi_device, &tr, 1 );
  }
  
  pr_info("Received = 0x%02X \n", rx);
  
  return( ret );
}

/****************************************************************************
 * Name: etx_spi_init
 *
 * Details : This function Register and Initilize the SPI.
 ****************************************************************************/
static int __init etx_spi_init(void)
{
  int     ret;
  uint8_t i;
  struct  spi_master *master;
  
  master = spi_busnum_to_master( etx_spi_device_info.bus_num );
  if ( master == NULL )
  {
    pr_err("SPI Master not found.\n");
    return -ENODEV;
  }
   
  // create a new slave device, given the master and device info
  etx_spi_device = spi_new_device( master, &etx_spi_device_info );
  if ( etx_spi_device == NULL ) 
  {
    pr_err("FAILED to create slave.\n");
    return -ENODEV;
  }
  
  // 8-bits in a word
  etx_spi_device->bits_per_word = 8;

  // setup the SPI slave device
  ret = spi_setup( etx_spi_device );
  if ( ret )
  {
    pr_err("FAILED to setup slave.\n");
    spi_unregister_device( etx_spi_device );
    return -ENODEV;
  }
  
  //Initialize the OLED SSD1306
  ETX_SSD1306_DisplayInit();
  
  /* Print the String */
  ETX_SSD1306_SetBrightness( 255 );           // Full brightness
  ETX_SSD1306_InvertDisplay( false );         // Invert the dispaly : OFF
  
  // Enable the Horizontal scroll for first 3 lines
  ETX_SSD1306_StartScrollHorizontal( true, 0, 2);
  
  
  ETX_SSD1306_SetCursor(0,0);                 // Set cursor at 0th line 0th col
  //Write String to OLED
  ETX_SSD1306_String("Welcome\nTo\nET-E9\n");
  
  ETX_SSD1306_SetCursor(4,35);                // Set cursor at 4th line 35th col
  //Write String to OLED
  ETX_SSD1306_String("SPI Linux\n");
  ETX_SSD1306_SetCursor(5,23);                // Set cursor at 5th line 23rd col
  ETX_SSD1306_String("Device Driver\n");
  ETX_SSD1306_SetCursor(6,37);                // Set cursor at 6th line 37th col
  ETX_SSD1306_String("Project\n");
  
  msleep(11000);                               // 11 secs delay
  
  ETX_SSD1306_ClearDisplay();                 // Clear Display
  ETX_SSD1306_DeactivateScroll();             // Deactivate the scroll
  
  /* Print the Image */
  for (i=0; i<3; i++)
  {
    ETX_SSD1306_PrintLogo(jerry);
    msleep(8000);
    ETX_SSD1306_PrintLogo(tom);
    msleep(8000);
  }
  
  pr_info("SPI driver Registered\n");
  return 0;
}
 
/****************************************************************************
 * Name: etx_spi_exit
 *
 * Details : This function Unregister and DeInitilize the SPI.
 ****************************************************************************/
static void __exit etx_spi_exit(void)
{ 
  if( etx_spi_device )
  {
    // Clear the display
    ETX_SSD1306_ClearDisplay();                 // Clear Display
    ETX_SSD1306_DisplayDeInit();                // Deinit the SSD1306
    spi_unregister_device( etx_spi_device );    // Unregister the SPI slave
    pr_info("SPI driver Unregistered\n");
  }
}
 
module_init(etx_spi_init);
module_exit(etx_spi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ET-E9");
MODULE_DESCRIPTION("A simple device driver - SPI Slave Protocol Driver");
MODULE_VERSION("1.44");
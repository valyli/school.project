////////////////////////////////////////////////////////
//	S3 Trio 32/64 10E mode Drive's I/O Data
//	   come from S3 Trio64V+ 's 10E mode
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include "DOS.H"
#include "VCDAPI.H"

unsigned char T400X300IO[]=// Init S3 Trio 10E mode I/O Data
{        /* This Data got from [s3trio.vid]. */
0xCC,0x43,0xD4,0x83,0x38,0x48,0xD4,0x83,0x39,0xA5,0xCC,
0x43,0xD4,0x83,0x38,0x48,0xD4,0x83,0x39,0xA5,0xDA,0x43,0xC0,0x03,0x00,0xC4,
0x83,0x00,0x01,0xC4,0x83,0x01,0x20,0xC4,0x83,0x01,0x21,0xC2,0x03,0x6F,0xC4,
0x83,0x00,0x03,0xC4,0x83,0x02,0x0F,0xC4,0x83,0x03,0x00,0xC4,0x83,0x04,0x0E,
0xD4,0x83,0x11,0x00,0xD4,0x83,0x00,0x5F,0xD4,0x83,0x01,0x4F,0xD4,0x83,0x02,
0x50,0xD4,0x83,0x03,0x82,0xD4,0x83,0x04,0x54,0xD4,0x83,0x05,0x80,0xD4,0x83,
0x06,0xBF,0xD4,0x83,0x07,0x1F,0xD4,0x83,0x08,0x00,0xD4,0x83,0x09,0x41,0xD4,
0x83,0x0A,0x00,0xD4,0x83,0x0B,0x00,0xD4,0x83,0x0C,0x00,0xD4,0x83,0x0D,0x00,
0xD4,0x83,0x0E,0xFF,0xD4,0x83,0x0F,0x00,0xD4,0x83,0x10,0x9C,0xD4,0x83,0x11,
0x8E,0xD4,0x83,0x12,0x8F,0xD4,0x83,0x13,0x50,0xD4,0x83,0x14,0x40,0xD4,0x83,
0x15,0x96,0xD4,0x83,0x16,0xB9,0xD4,0x83,0x17,0xA3,0xD4,0x83,0x18,0xFF,0xDA,
0x43,0xC0,0x03,0x00,0xC0,0x03,0x00,0xC0,0x03,0x01,0xC0,0x03,0x01,0xC0,0x03,
0x02,0xC0,0x03,0x02,0xC0,0x03,0x03,0xC0,0x03,0x03,0xC0,0x03,0x04,0xC0,0x03,
0x04,0xC0,0x03,0x05,0xC0,0x03,0x05,0xC0,0x03,0x06,0xC0,0x03,0x06,0xC0,0x03,
0x07,0xC0,0x03,0x07,0xC0,0x03,0x08,0xC0,0x03,0x10,0xC0,0x03,0x09,0xC0,0x03,
0x11,0xC0,0x03,0x0A,0xC0,0x03,0x12,0xC0,0x03,0x0B,0xC0,0x03,0x13,0xC0,0x03,
0x0C,0xC0,0x03,0x14,0xC0,0x03,0x0D,0xC0,0x03,0x15,0xC0,0x03,0x0E,0xC0,0x03,
0x16,0xC0,0x03,0x0F,0xC0,0x03,0x17,0xC0,0x03,0x10,0xC0,0x03,0x41,0xC0,0x03,
0x11,0xC0,0x03,0x00,0xC0,0x03,0x12,0xC0,0x03,0x0F,0xC0,0x03,0x13,0xC0,0x03,
0x00,0xC0,0x03,0x14,0xC0,0x03,0x00,0xCC,0x03,0x00,0xCA,0x03,0x01,0xCE,0x83,
0x00,0x00,0xCE,0x83,0x01,0x00,0xCE,0x83,0x02,0x00,0xCE,0x83,0x03,0x00,0xCE,
0x83,0x04,0x00,0xCE,0x83,0x05,0x40,0xCE,0x83,0x06,0x05,0xCE,0x83,0x07,0x0F,
0xCE,0x83,0x08,0xFF,0xCC,0x43,0xD4,0x83,0x30,0x55,0xD4,0x03,0x30,0xD5,0x43,
0xD4,0x03,0x66,0xD5,0x43,0xD4,0x83,0x66,0xA8,0xD4,0x83,0x38,0x48,0xD4,0x83,
0x39,0xA5,0xD4,0x83,0x31,0x05,0xD4,0x83,0x32,0x40,0xD4,0x83,0x33,0x00,0xD4,
0x83,0x34,0x00,0xD4,0x83,0x35,0x00,0xD4,0x83,0x3B,0x5A,0xD4,0x83,0x3C,0x10,
0xD4,0x83,0x43,0x00,0xD4,0x83,0x45,0x00,0xD4,0x83,0x50,0x00,0xD4,0x83,0x51,
0x00,0xD4,0x83,0x53,0x00,0xD4,0x83,0x54,0x30,0xD4,0x83,0x55,0x00,0xD4,0x83,
0x58,0x03,0xD4,0x83,0x5D,0x00,0xD4,0x83,0x5E,0x00,0xD4,0x83,0x60,0x0F,0xD4,
0x83,0x67,0x00,0xD4,0x83,0x68,0xFC,0xD4,0x83,0x69,0x00,0xD4,0x83,0x6A,0x00,
0xD4,0x83,0x6F,0x18,0xC4,0x83,0x08,0x06,0xC4,0x83,0x0B,0x00,0xC4,0x83,0x14,
0x00,0xC4,0x83,0x18,0x40,0xD4,0x03,0x36,0xD5,0x43,0xD4,0x03,0x66,0xD5,0x43,
0xD4,0x83,0x66,0x98,0xD4,0x03,0x36,0xD5,0x43,0xD4,0x83,0x40,0x20,0xD4,0x03,
0x42,0xD5,0x43,0xD5,0x03,0x00,0xCC,0x43,0xCC,0x43,0xD4,0x83,0x38,0x48,0xD4,
0x83,0x39,0xA5,0xD4,0x83,0x50,0x10,0xD4,0x03,0x40,0xD5,0x43,0xD4,0x83,0x40,
0x21,0xD4,0x03,0x66,0xD5,0x43,0xD4,0x83,0x66,0xA9,0xD4,0x03,0x53,0xD5,0x43,
0xD4,0x83,0x53,0x10,0xD4,0x83,0x40,0x31,0xD4,0x83,0x53,0x10,0xD4,0x83,0x53,
0x00,0xD4,0x83,0x53,0x00,0xD4,0x03,0x41,0xD5,0x43,0xD4,0x03,0x52,0xD5,0x43,
0xC4,0x83,0x04,0x0E,0xCC,0x43,0xD4,0x03,0x66,0xD5,0x43,0xD4,0x83,0x66,0x89,
0xD4,0x83,0x11,0x00,0xD4,0x83,0x00,0x5F,0xD4,0x83,0x01,0x4F,0xD4,0x83,0x02,
0x50,0xD4,0x83,0x03,0x82,0xD4,0x83,0x04,0x54,0xD4,0x83,0x05,0x80,0xD4,0x83,
0x06,0xBF,0xD4,0x83,0x07,0x1F,0xD4,0x83,0x08,0x00,0xD4,0x83,0x09,0x41,0xD4,
0x83,0x0A,0x00,0xD4,0x83,0x0B,0x00,0xD4,0x83,0x0C,0x00,0xD4,0x83,0x0D,0x00,
0xD4,0x83,0x0E,0xFF,0xD4,0x83,0x0F,0x00,0xD4,0x83,0x10,0x9C,0xD4,0x83,0x11,
0x8E,0xD4,0x83,0x12,0x8F,0xD4,0x83,0x13,0x50,0xD4,0x83,0x14,0x40,0xD4,0x83,
0x15,0x96,0xD4,0x83,0x16,0xB9,0xD4,0x83,0x17,0xA3,0xD4,0x83,0x18,0xFF,0xD4,
0x83,0x0A,0x00,0xD4,0x83,0x0B,0x00,0xD4,0x83,0x0C,0x00,0xD4,0x83,0x5D,0x00,
0xD4,0x83,0x5E,0x00,0xCC,0x43,0xD4,0x83,0x38,0x48,0xD4,0x83,0x39,0xA5,0xCC,
0x43,0xD4,0x03,0x2E,0xD5,0x43,0xD4,0x03,0x2F,0xD5,0x43,0xC4,0x83,0x12,0x61,
0xC4,0x83,0x13,0x28,0xC4,0x83,0x18,0x40,0xC4,0x83,0x15,0x00,0xC4,0x83,0x15,
0x03,0xD4,0x83,0x42,0x00,0xD4,0x03,0x40,0xD5,0x43,0xD4,0x83,0x40,0x31,0xD4,
0x83,0x13,0x50,0xD4,0x83,0x51,0x00,0xD4,0x03,0x3A,0xD5,0x43,0xD4,0x83,0x3A,
0x95,0xD4,0x83,0x31,0x09,0xD4,0x83,0x50,0x00,0xD4,0x03,0x34,0xD5,0x43,0xD4,
0x83,0x34,0x10,0xD4,0x83,0x60,0xFF,0xD4,0x03,0x3A,0xD5,0x43,0xD4,0x03,0x5D,
0xD5,0x43,0xD4,0x03,0x00,0xD5,0x43,0xD4,0x83,0x3C,0x2F,0xD4,0x83,0x3B,0x5E,
0xC4,0x03,0x15,0xC5,0x43,0xC4,0x83,0x15,0x13,0xD4,0x03,0x32,0xD5,0x43,0xD4,
0x83,0x32,0x00,0xD4,0x03,0x6B,0xD5,0x43,0xD4,0x83,0x59,0xF8,0xD4,0x83,0x5A,
0x00,0xCC,0x43,0xD4,0x83,0x67,0x50,0xC4,0x43,0xC4,0x83,0x08,0x00,0xC4,0x03,
0x15,0xC6,0x43,0xC8,0x03,0x00,0xC9,0x03,0x00,0xC9,0x03,0x00,0xC9,0x03,0x00,
0xC8,0x03,0x01,0xC9,0x03,0x00,0xC9,0x03,0x00,0xC9,0x03,0x2A,0xC8,0x03,0x02,
0xC9,0x03,0x00,0xC9,0x03,0x2A,0xC9,0x03,0x00,0xC8,0x03,0x03,0xC9,0x03,0x00,
0xC9,0x03,0x2A,0xC9,0x03,0x2A,0xC8,0x03,0x04,0xC9,0x03,0x2A,0xC9,0x03,0x00,
0xC9,0x03,0x00,0xC8,0x03,0x05,0xC9,0x03,0x2A,0xC9,0x03,0x00,0xC9,0x03,0x2A,
0xC8,0x03,0x06,0xC9,0x03,0x2A,0xC9,0x03,0x15,0xC9,0x03,0x00,0xC8,0x03,0x07,
0xC9,0x03,0x2A,0xC9,0x03,0x2A,0xC9,0x03,0x2A,0xC8,0x03,0x08,0xC9,0x03,0x15,
0xC9,0x03,0x15,0xC9,0x03,0x15,0xC8,0x03,0x09,0xC9,0x03,0x15,0xC9,0x03,0x15,
0xC9,0x03,0x3F,0xC8,0x03,0x0A,0xC9,0x03,0x15,0xC9,0x03,0x3F,0xC9,0x03,0x15,
0xC8,0x03,0x0B,0xC9,0x03,0x15,0xC9,0x03,0x3F,0xC9,0x03,0x3F,0xC8,0x03,0x0C,
0xC9,0x03,0x3F,0xC9,0x03,0x15,0xC9,0x03,0x15,0xC8,0x03,0x0D,0xC9,0x03,0x3F,
0xC9,0x03,0x15,0xC9,0x03,0x3F,0xC8,0x03,0x0E,0xC9,0x03,0x3F,0xC9,0x03,0x3F,
0xC9,0x03,0x15,0xC8,0x03,0x0F,0xC9,0x03,0x3F,0xC9,0x03,0x3F,0xC9,0x03,0x3F,
0xC8,0x03,0x10,0xC9,0x03,0x00,0xC9,0x03,0x00,0xC9,0x03,0x00,0xC8,0x03,0x11,
0xC9,0x03,0x05,0xC9,0x03,0x05,0xC9,0x03,0x05,0xC8,0x03,0x12,0xC9,0x03,0x08,
0xC9,0x03,0x08,0xC9,0x03,0x08,0xC8,0x03,0x13,0xC9,0x03,0x0B,0xC9,0x03,0x0B,
0xC9,0x03,0x0B,0xC8,0x03,0x14,0xC9,0x03,0x0E,0xC9,0x03,0x0E,0xC9,0x03,0x0E,
0xC8,0x03,0x15,0xC9,0x03,0x11,0xC9,0x03,0x11,0xC9,0x03,0x11,0xC8,0x03,0x16,
0xC9,0x03,0x14,0xC9,0x03,0x14,0xC9,0x03,0x14,0xC8,0x03,0x17,0xC9,0x03,0x18,
0xC9,0x03,0x18,0xC9,0x03,0x18,0xC8,0x03,0x18,0xC9,0x03,0x1C,0xC9,0x03,0x1C,
0xC9,0x03,0x1C,0xC8,0x03,0x19,0xC9,0x03,0x20,0xC9,0x03,0x20,0xC9,0x03,0x20,
0xC8,0x03,0x1A,0xC9,0x03,0x24,0xC9,0x03,0x24,0xC9,0x03,0x24,0xC8,0x03,0x1B,
0xC9,0x03,0x28,0xC9,0x03,0x28,0xC9,0x03,0x28,0xC8,0x03,0x1C,0xC9,0x03,0x2D,
0xC9,0x03,0x2D,0xC9,0x03,0x2D,0xC8,0x03,0x1D,0xC9,0x03,0x32,0xC9,0x03,0x32,
0xC9,0x03,0x32,0xC8,0x03,0x1E,0xC9,0x03,0x38,0xC9,0x03,0x38,0xC9,0x03,0x38,
0xC8,0x03,0x1F,0xC9,0x03,0x3F,0xC9,0x03,0x3F,0xC9,0x03,0x3F,0xC8,0x03,0x20,
0xC9,0x03,0x00,0xC9,0x03,0x00,0xC9,0x03,0x3F,0xC8,0x03,0x21,0xC9,0x03,0x10,
0xC9,0x03,0x00,0xC9,0x03,0x3F,0xC8,0x03,0x22,0xC9,0x03,0x1F,0xC9,0x03,0x00,
0xC9,0x03,0x3F,0xC8,0x03,0x23,0xC9,0x03,0x2F,0xC9,0x03,0x00,0xC9,0x03,0x3F,
0xC8,0x03,0x24,0xC9,0x03,0x3F,0xC9,0x03,0x00,0xC9,0x03,0x3F,0xC8,0x03,0x25,
0xC9,0x03,0x3F,0xC9,0x03,0x00,0xC9,0x03,0x2F,0xC8,0x03,0x26,0xC9,0x03,0x3F,
0xC9,0x03,0x00,0xC9,0x03,0x1F,0xC8,0x03,0x27,0xC9,0x03,0x3F,0xC9,0x03,0x00,
0xC9,0x03,0x10,0xC8,0x03,0x28,0xC9,0x03,0x3F,0xC9,0x03,0x00,0xC9,0x03,0x00,
0xC8,0x03,0x29,0xC9,0x03,0x3F,0xC9,0x03,0x10,0xC9,0x03,0x00,0xC8,0x03,0x2A,
0xC9,0x03,0x3F,0xC9,0x03,0x1F,0xC9,0x03,0x00,0xC8,0x03,0x2B,0xC9,0x03,0x3F,
0xC9,0x03,0x2F,0xC9,0x03,0x00,0xC8,0x03,0x2C,0xC9,0x03,0x3F,0xC9,0x03,0x3F,
0xC9,0x03,0x00,0xC8,0x03,0x2D,0xC9,0x03,0x2F,0xC9,0x03,0x3F,0xC9,0x03,0x00,
0xC8,0x03,0x2E,0xC9,0x03,0x1F,0xC9,0x03,0x3F,0xC9,0x03,0x00,0xC8,0x03,0x2F,
0xC9,0x03,0x10,0xC9,0x03,0x3F,0xC9,0x03,0x00,0xC8,0x03,0x30,0xC9,0x03,0x00,
0xC9,0x03,0x3F,0xC9,0x03,0x00,0xC8,0x03,0x31,0xC9,0x03,0x00,0xC9,0x03,0x3F,
0xC9,0x03,0x10,0xC8,0x03,0x32,0xC9,0x03,0x00,0xC9,0x03,0x3F,0xC9,0x03,0x1F,
0xC8,0x03,0x33,0xC9,0x03,0x00,0xC9,0x03,0x3F,0xC9,0x03,0x2F,0xC8,0x03,0x34,
0xC9,0x03,0x00,0xC9,0x03,0x3F,0xC9,0x03,0x3F,0xC8,0x03,0x35,0xC9,0x03,0x00,
0xC9,0x03,0x2F,0xC9,0x03,0x3F,0xC8,0x03,0x36,0xC9,0x03,0x00,0xC9,0x03,0x1F,
0xC9,0x03,0x3F,0xC8,0x03,0x37,0xC9,0x03,0x00,0xC9,0x03,0x10,0xC9,0x03,0x3F,
0xC8,0x03,0x38,0xC9,0x03,0x1F,0xC9,0x03,0x1F,0xC9,0x03,0x3F,0xC8,0x03,0x39,
0xC9,0x03,0x27,0xC9,0x03,0x1F,0xC9,0x03,0x3F,0xC8,0x03,0x3A,0xC9,0x03,0x2F,
0xC9,0x03,0x1F,0xC9,0x03,0x3F,0xC8,0x03,0x3B,0xC9,0x03,0x37,0xC9,0x03,0x1F,
0xC9,0x03,0x3F,0xC8,0x03,0x3C,0xC9,0x03,0x3F,0xC9,0x03,0x1F,0xC9,0x03,0x3F,
0xC8,0x03,0x3D,0xC9,0x03,0x3F,0xC9,0x03,0x1F,0xC9,0x03,0x37,0xC8,0x03,0x3E,
0xC9,0x03,0x3F,0xC9,0x03,0x1F,0xC9,0x03,0x2F,0xC8,0x03,0x3F,0xC9,0x03,0x3F,
0xC9,0x03,0x1F,0xC9,0x03,0x27,0xC8,0x03,0x40,0xC9,0x03,0x3F,0xC9,0x03,0x1F,
0xC9,0x03,0x1F,0xC8,0x03,0x41,0xC9,0x03,0x3F,0xC9,0x03,0x27,0xC9,0x03,0x1F,
0xC8,0x03,0x42,0xC9,0x03,0x3F,0xC9,0x03,0x2F,0xC9,0x03,0x1F,0xC8,0x03,0x43,
0xC9,0x03,0x3F,0xC9,0x03,0x37,0xC9,0x03,0x1F,0xC8,0x03,0x44,0xC9,0x03,0x3F,
0xC9,0x03,0x3F,0xC9,0x03,0x1F,0xC8,0x03,0x45,0xC9,0x03,0x37,0xC9,0x03,0x3F,
0xC9,0x03,0x1F,0xC8,0x03,0x46,0xC9,0x03,0x2F,0xC9,0x03,0x3F,0xC9,0x03,0x1F,
0xC8,0x03,0x47,0xC9,0x03,0x27,0xC9,0x03,0x3F,0xC9,0x03,0x1F,0xC8,0x03,0x48,
0xC9,0x03,0x1F,0xC9,0x03,0x3F,0xC9,0x03,0x1F,0xC8,0x03,0x49,0xC9,0x03,0x1F,
0xC9,0x03,0x3F,0xC9,0x03,0x27,0xC8,0x03,0x4A,0xC9,0x03,0x1F,0xC9,0x03,0x3F,
0xC9,0x03,0x2F,0xC8,0x03,0x4B,0xC9,0x03,0x1F,0xC9,0x03,0x3F,0xC9,0x03,0x37,
0xC8,0x03,0x4C,0xC9,0x03,0x1F,0xC9,0x03,0x3F,0xC9,0x03,0x3F,0xC8,0x03,0x4D,
0xC9,0x03,0x1F,0xC9,0x03,0x37,0xC9,0x03,0x3F,0xC8,0x03,0x4E,0xC9,0x03,0x1F,
0xC9,0x03,0x2F,0xC9,0x03,0x3F,0xC8,0x03,0x4F,0xC9,0x03,0x1F,0xC9,0x03,0x27,
0xC9,0x03,0x3F,0xC8,0x03,0x50,0xC9,0x03,0x2D,0xC9,0x03,0x2D,0xC9,0x03,0x3F,
0xC8,0x03,0x51,0xC9,0x03,0x31,0xC9,0x03,0x2D,0xC9,0x03,0x3F,0xC8,0x03,0x52,
0xC9,0x03,0x36,0xC9,0x03,0x2D,0xC9,0x03,0x3F,0xC8,0x03,0x53,0xC9,0x03,0x3A,
0xC9,0x03,0x2D,0xC9,0x03,0x3F,0xC8,0x03,0x54,0xC9,0x03,0x3F,0xC9,0x03,0x2D,
0xC9,0x03,0x3F,0xC8,0x03,0x55,0xC9,0x03,0x3F,0xC9,0x03,0x2D,0xC9,0x03,0x3A,
0xC8,0x03,0x56,0xC9,0x03,0x3F,0xC9,0x03,0x2D,0xC9,0x03,0x36,0xC8,0x03,0x57,
0xC9,0x03,0x3F,0xC9,0x03,0x2D,0xC9,0x03,0x31,0xC8,0x03,0x58,0xC9,0x03,0x3F,
0xC9,0x03,0x2D,0xC9,0x03,0x2D,0xC8,0x03,0x59,0xC9,0x03,0x3F,0xC9,0x03,0x31,
0xC9,0x03,0x2D,0xC8,0x03,0x5A,0xC9,0x03,0x3F,0xC9,0x03,0x36,0xC9,0x03,0x2D,
0xC8,0x03,0x5B,0xC9,0x03,0x3F,0xC9,0x03,0x3A,0xC9,0x03,0x2D,0xC8,0x03,0x5C,
0xC9,0x03,0x3F,0xC9,0x03,0x3F,0xC9,0x03,0x2D,0xC8,0x03,0x5D,0xC9,0x03,0x3A,
0xC9,0x03,0x3F,0xC9,0x03,0x2D,0xC8,0x03,0x5E,0xC9,0x03,0x36,0xC9,0x03,0x3F,
0xC9,0x03,0x2D,0xC8,0x03,0x5F,0xC9,0x03,0x31,0xC9,0x03,0x3F,0xC9,0x03,0x2D,
0xC8,0x03,0x60,0xC9,0x03,0x2D,0xC9,0x03,0x3F,0xC9,0x03,0x2D,0xC8,0x03,0x61,
0xC9,0x03,0x2D,0xC9,0x03,0x3F,0xC9,0x03,0x31,0xC8,0x03,0x62,0xC9,0x03,0x2D,
0xC9,0x03,0x3F,0xC9,0x03,0x36,0xC8,0x03,0x63,0xC9,0x03,0x2D,0xC9,0x03,0x3F,
0xC9,0x03,0x3A,0xC8,0x03,0x64,0xC9,0x03,0x2D,0xC9,0x03,0x3F,0xC9,0x03,0x3F,
0xC8,0x03,0x65,0xC9,0x03,0x2D,0xC9,0x03,0x3A,0xC9,0x03,0x3F,0xC8,0x03,0x66,
0xC9,0x03,0x2D,0xC9,0x03,0x36,0xC9,0x03,0x3F,0xC8,0x03,0x67,0xC9,0x03,0x2D,
0xC9,0x03,0x31,0xC9,0x03,0x3F,0xC8,0x03,0x68,0xC9,0x03,0x00,0xC9,0x03,0x00,
0xC9,0x03,0x1C,0xC8,0x03,0x69,0xC9,0x03,0x07,0xC9,0x03,0x00,0xC9,0x03,0x1C,
0xC8,0x03,0x6A,0xC9,0x03,0x0E,0xC9,0x03,0x00,0xC9,0x03,0x1C,0xC8,0x03,0x6B,
0xC9,0x03,0x15,0xC9,0x03,0x00,0xC9,0x03,0x1C,0xC8,0x03,0x6C,0xC9,0x03,0x1C,
0xC9,0x03,0x00,0xC9,0x03,0x1C,0xC8,0x03,0x6D,0xC9,0x03,0x1C,0xC9,0x03,0x00,
0xC9,0x03,0x15,0xC8,0x03,0x6E,0xC9,0x03,0x1C,0xC9,0x03,0x00,0xC9,0x03,0x0E,
0xC8,0x03,0x6F,0xC9,0x03,0x1C,0xC9,0x03,0x00,0xC9,0x03,0x07,0xC8,0x03,0x70,
0xC9,0x03,0x1C,0xC9,0x03,0x00,0xC9,0x03,0x00,0xC8,0x03,0x71,0xC9,0x03,0x1C,
0xC9,0x03,0x07,0xC9,0x03,0x00,0xC8,0x03,0x72,0xC9,0x03,0x1C,0xC9,0x03,0x0E,
0xC9,0x03,0x00,0xC8,0x03,0x73,0xC9,0x03,0x1C,0xC9,0x03,0x15,0xC9,0x03,0x00,
0xC8,0x03,0x74,0xC9,0x03,0x1C,0xC9,0x03,0x1C,0xC9,0x03,0x00,0xC8,0x03,0x75,
0xC9,0x03,0x15,0xC9,0x03,0x1C,0xC9,0x03,0x00,0xC8,0x03,0x76,0xC9,0x03,0x0E,
0xC9,0x03,0x1C,0xC9,0x03,0x00,0xC8,0x03,0x77,0xC9,0x03,0x07,0xC9,0x03,0x1C,
0xC9,0x03,0x00,0xC8,0x03,0x78,0xC9,0x03,0x00,0xC9,0x03,0x1C,0xC9,0x03,0x00,
0xC8,0x03,0x79,0xC9,0x03,0x00,0xC9,0x03,0x1C,0xC9,0x03,0x07,0xC8,0x03,0x7A,
0xC9,0x03,0x00,0xC9,0x03,0x1C,0xC9,0x03,0x0E,0xC8,0x03,0x7B,0xC9,0x03,0x00,
0xC9,0x03,0x1C,0xC9,0x03,0x15,0xC8,0x03,0x7C,0xC9,0x03,0x00,0xC9,0x03,0x1C,
0xC9,0x03,0x1C,0xC8,0x03,0x7D,0xC9,0x03,0x00,0xC9,0x03,0x15,0xC9,0x03,0x1C,
0xC8,0x03,0x7E,0xC9,0x03,0x00,0xC9,0x03,0x0E,0xC9,0x03,0x1C,0xC8,0x03,0x7F,
0xC9,0x03,0x00,0xC9,0x03,0x07,0xC9,0x03,0x1C,0xC8,0x03,0x80,0xC9,0x03,0x0E,
0xC9,0x03,0x0E,0xC9,0x03,0x1C,0xC8,0x03,0x81,0xC9,0x03,0x11,0xC9,0x03,0x0E,
0xC9,0x03,0x1C,0xC8,0x03,0x82,0xC9,0x03,0x15,0xC9,0x03,0x0E,0xC9,0x03,0x1C,
0xC8,0x03,0x83,0xC9,0x03,0x18,0xC9,0x03,0x0E,0xC9,0x03,0x1C,0xC8,0x03,0x84,
0xC9,0x03,0x1C,0xC9,0x03,0x0E,0xC9,0x03,0x1C,0xC8,0x03,0x85,0xC9,0x03,0x1C,
0xC9,0x03,0x0E,0xC9,0x03,0x18,0xC8,0x03,0x86,0xC9,0x03,0x1C,0xC9,0x03,0x0E,
0xC9,0x03,0x15,0xC8,0x03,0x87,0xC9,0x03,0x1C,0xC9,0x03,0x0E,0xC9,0x03,0x11,
0xC8,0x03,0x88,0xC9,0x03,0x1C,0xC9,0x03,0x0E,0xC9,0x03,0x0E,0xC8,0x03,0x89,
0xC9,0x03,0x1C,0xC9,0x03,0x11,0xC9,0x03,0x0E,0xC8,0x03,0x8A,0xC9,0x03,0x1C,
0xC9,0x03,0x15,0xC9,0x03,0x0E,0xC8,0x03,0x8B,0xC9,0x03,0x1C,0xC9,0x03,0x18,
0xC9,0x03,0x0E,0xC8,0x03,0x8C,0xC9,0x03,0x1C,0xC9,0x03,0x1C,0xC9,0x03,0x0E,
0xC8,0x03,0x8D,0xC9,0x03,0x18,0xC9,0x03,0x1C,0xC9,0x03,0x0E,0xC8,0x03,0x8E,
0xC9,0x03,0x15,0xC9,0x03,0x1C,0xC9,0x03,0x0E,0xC8,0x03,0x8F,0xC9,0x03,0x11,
0xC9,0x03,0x1C,0xC9,0x03,0x0E,0xC8,0x03,0x90,0xC9,0x03,0x0E,0xC9,0x03,0x1C,
0xC9,0x03,0x0E,0xC8,0x03,0x91,0xC9,0x03,0x0E,0xC9,0x03,0x1C,0xC9,0x03,0x11,
0xC8,0x03,0x92,0xC9,0x03,0x0E,0xC9,0x03,0x1C,0xC9,0x03,0x15,0xC8,0x03,0x93,
0xC9,0x03,0x0E,0xC9,0x03,0x1C,0xC9,0x03,0x18,0xC8,0x03,0x94,0xC9,0x03,0x0E,
0xC9,0x03,0x1C,0xC9,0x03,0x1C,0xC8,0x03,0x95,0xC9,0x03,0x0E,0xC9,0x03,0x18,
0xC9,0x03,0x1C,0xC8,0x03,0x96,0xC9,0x03,0x0E,0xC9,0x03,0x15,0xC9,0x03,0x1C,
0xC8,0x03,0x97,0xC9,0x03,0x0E,0xC9,0x03,0x11,0xC9,0x03,0x1C,0xC8,0x03,0x98,
0xC9,0x03,0x14,0xC9,0x03,0x14,0xC9,0x03,0x1C,0xC8,0x03,0x99,0xC9,0x03,0x16,
0xC9,0x03,0x14,0xC9,0x03,0x1C,0xC8,0x03,0x9A,0xC9,0x03,0x18,0xC9,0x03,0x14,
0xC9,0x03,0x1C,0xC8,0x03,0x9B,0xC9,0x03,0x1A,0xC9,0x03,0x14,0xC9,0x03,0x1C,
0xC8,0x03,0x9C,0xC9,0x03,0x1C,0xC9,0x03,0x14,0xC9,0x03,0x1C,0xC8,0x03,0x9D,
0xC9,0x03,0x1C,0xC9,0x03,0x14,0xC9,0x03,0x1A,0xC8,0x03,0x9E,0xC9,0x03,0x1C,
0xC9,0x03,0x14,0xC9,0x03,0x18,0xC8,0x03,0x9F,0xC9,0x03,0x1C,0xC9,0x03,0x14,
0xC9,0x03,0x16,0xC8,0x03,0xA0,0xC9,0x03,0x1C,0xC9,0x03,0x14,0xC9,0x03,0x14,
0xC8,0x03,0xA1,0xC9,0x03,0x1C,0xC9,0x03,0x16,0xC9,0x03,0x14,0xC8,0x03,0xA2,
0xC9,0x03,0x1C,0xC9,0x03,0x18,0xC9,0x03,0x14,0xC8,0x03,0xA3,0xC9,0x03,0x1C,
0xC9,0x03,0x1A,0xC9,0x03,0x14,0xC8,0x03,0xA4,0xC9,0x03,0x1C,0xC9,0x03,0x1C,
0xC9,0x03,0x14,0xC8,0x03,0xA5,0xC9,0x03,0x1A,0xC9,0x03,0x1C,0xC9,0x03,0x14,
0xC8,0x03,0xA6,0xC9,0x03,0x18,0xC9,0x03,0x1C,0xC9,0x03,0x14,0xC8,0x03,0xA7,
0xC9,0x03,0x16,0xC9,0x03,0x1C,0xC9,0x03,0x14,0xC8,0x03,0xA8,0xC9,0x03,0x14,
0xC9,0x03,0x1C,0xC9,0x03,0x14,0xC8,0x03,0xA9,0xC9,0x03,0x14,0xC9,0x03,0x1C,
0xC9,0x03,0x16,0xC8,0x03,0xAA,0xC9,0x03,0x14,0xC9,0x03,0x1C,0xC9,0x03,0x18,
0xC8,0x03,0xAB,0xC9,0x03,0x14,0xC9,0x03,0x1C,0xC9,0x03,0x1A,0xC8,0x03,0xAC,
0xC9,0x03,0x14,0xC9,0x03,0x1C,0xC9,0x03,0x1C,0xC8,0x03,0xAD,0xC9,0x03,0x14,
0xC9,0x03,0x1A,0xC9,0x03,0x1C,0xC8,0x03,0xAE,0xC9,0x03,0x14,0xC9,0x03,0x18,
0xC9,0x03,0x1C,0xC8,0x03,0xAF,0xC9,0x03,0x14,0xC9,0x03,0x16,0xC9,0x03,0x1C,
0xC8,0x03,0xB0,0xC9,0x03,0x00,0xC9,0x03,0x00,0xC9,0x03,0x10,0xC8,0x03,0xB1,
0xC9,0x03,0x04,0xC9,0x03,0x00,0xC9,0x03,0x10,0xC8,0x03,0xB2,0xC9,0x03,0x08,
0xC9,0x03,0x00,0xC9,0x03,0x10,0xC8,0x03,0xB3,0xC9,0x03,0x0C,0xC9,0x03,0x00,
0xC9,0x03,0x10,0xC8,0x03,0xB4,0xC9,0x03,0x10,0xC9,0x03,0x00,0xC9,0x03,0x10,
0xC8,0x03,0xB5,0xC9,0x03,0x10,0xC9,0x03,0x00,0xC9,0x03,0x0C,0xC8,0x03,0xB6,
0xC9,0x03,0x10,0xC9,0x03,0x00,0xC9,0x03,0x08,0xC8,0x03,0xB7,0xC9,0x03,0x10,
0xC9,0x03,0x00,0xC9,0x03,0x04,0xC8,0x03,0xB8,0xC9,0x03,0x10,0xC9,0x03,0x00,
0xC9,0x03,0x00,0xC8,0x03,0xB9,0xC9,0x03,0x10,0xC9,0x03,0x04,0xC9,0x03,0x00,
0xC8,0x03,0xBA,0xC9,0x03,0x10,0xC9,0x03,0x08,0xC9,0x03,0x00,0xC8,0x03,0xBB,
0xC9,0x03,0x10,0xC9,0x03,0x0C,0xC9,0x03,0x00,0xC8,0x03,0xBC,0xC9,0x03,0x10,
0xC9,0x03,0x10,0xC9,0x03,0x00,0xC8,0x03,0xBD,0xC9,0x03,0x0C,0xC9,0x03,0x10,
0xC9,0x03,0x00,0xC8,0x03,0xBE,0xC9,0x03,0x08,0xC9,0x03,0x10,0xC9,0x03,0x00,
0xC8,0x03,0xBF,0xC9,0x03,0x04,0xC9,0x03,0x10,0xC9,0x03,0x00,0xC8,0x03,0xC0,
0xC9,0x03,0x00,0xC9,0x03,0x10,0xC9,0x03,0x00,0xC8,0x03,0xC1,0xC9,0x03,0x00,
0xC9,0x03,0x10,0xC9,0x03,0x04,0xC8,0x03,0xC2,0xC9,0x03,0x00,0xC9,0x03,0x10,
0xC9,0x03,0x08,0xC8,0x03,0xC3,0xC9,0x03,0x00,0xC9,0x03,0x10,0xC9,0x03,0x0C,
0xC8,0x03,0xC4,0xC9,0x03,0x00,0xC9,0x03,0x10,0xC9,0x03,0x10,0xC8,0x03,0xC5,
0xC9,0x03,0x00,0xC9,0x03,0x0C,0xC9,0x03,0x10,0xC8,0x03,0xC6,0xC9,0x03,0x00,
0xC9,0x03,0x08,0xC9,0x03,0x10,0xC8,0x03,0xC7,0xC9,0x03,0x00,0xC9,0x03,0x04,
0xC9,0x03,0x10,0xC8,0x03,0xC8,0xC9,0x03,0x08,0xC9,0x03,0x08,0xC9,0x03,0x10,
0xC8,0x03,0xC9,0xC9,0x03,0x0A,0xC9,0x03,0x08,0xC9,0x03,0x10,0xC8,0x03,0xCA,
0xC9,0x03,0x0C,0xC9,0x03,0x08,0xC9,0x03,0x10,0xC8,0x03,0xCB,0xC9,0x03,0x0E,
0xC9,0x03,0x08,0xC9,0x03,0x10,0xC8,0x03,0xCC,0xC9,0x03,0x10,0xC9,0x03,0x08,
0xC9,0x03,0x10,0xC8,0x03,0xCD,0xC9,0x03,0x10,0xC9,0x03,0x08,0xC9,0x03,0x0E,
0xC8,0x03,0xCE,0xC9,0x03,0x10,0xC9,0x03,0x08,0xC9,0x03,0x0C,0xC8,0x03,0xCF,
0xC9,0x03,0x10,0xC9,0x03,0x08,0xC9,0x03,0x0A,0xC8,0x03,0xD0,0xC9,0x03,0x10,
0xC9,0x03,0x08,0xC9,0x03,0x08,0xC8,0x03,0xD1,0xC9,0x03,0x10,0xC9,0x03,0x0A,
0xC9,0x03,0x08,0xC8,0x03,0xD2,0xC9,0x03,0x10,0xC9,0x03,0x0C,0xC9,0x03,0x08,
0xC8,0x03,0xD3,0xC9,0x03,0x10,0xC9,0x03,0x0E,0xC9,0x03,0x08,0xC8,0x03,0xD4,
0xC9,0x03,0x10,0xC9,0x03,0x10,0xC9,0x03,0x08,0xC8,0x03,0xD5,0xC9,0x03,0x0E,
0xC9,0x03,0x10,0xC9,0x03,0x08,0xC8,0x03,0xD6,0xC9,0x03,0x0C,0xC9,0x03,0x10,
0xC9,0x03,0x08,0xC8,0x03,0xD7,0xC9,0x03,0x0A,0xC9,0x03,0x10,0xC9,0x03,0x08,
0xC8,0x03,0xD8,0xC9,0x03,0x08,0xC9,0x03,0x10,0xC9,0x03,0x08,0xC8,0x03,0xD9,
0xC9,0x03,0x08,0xC9,0x03,0x10,0xC9,0x03,0x0A,0xC8,0x03,0xDA,0xC9,0x03,0x08,
0xC9,0x03,0x10,0xC9,0x03,0x0C,0xC8,0x03,0xDB,0xC9,0x03,0x08,0xC9,0x03,0x10,
0xC9,0x03,0x0E,0xC8,0x03,0xDC,0xC9,0x03,0x08,0xC9,0x03,0x10,0xC9,0x03,0x10,
0xC8,0x03,0xDD,0xC9,0x03,0x08,0xC9,0x03,0x0E,0xC9,0x03,0x10,0xC8,0x03,0xDE,
0xC9,0x03,0x08,0xC9,0x03,0x0C,0xC9,0x03,0x10,0xC8,0x03,0xDF,0xC9,0x03,0x08,
0xC9,0x03,0x0A,0xC9,0x03,0x10,0xC8,0x03,0xE0,0xC9,0x03,0x0B,0xC9,0x03,0x0B,
0xC9,0x03,0x10,0xC8,0x03,0xE1,0xC9,0x03,0x0C,0xC9,0x03,0x0B,0xC9,0x03,0x10,
0xC8,0x03,0xE2,0xC9,0x03,0x0D,0xC9,0x03,0x0B,0xC9,0x03,0x10,0xC8,0x03,0xE3,
0xC9,0x03,0x0F,0xC9,0x03,0x0B,0xC9,0x03,0x10,0xC8,0x03,0xE4,0xC9,0x03,0x10,
0xC9,0x03,0x0B,0xC9,0x03,0x10,0xC8,0x03,0xE5,0xC9,0x03,0x10,0xC9,0x03,0x0B,
0xC9,0x03,0x0F,0xC8,0x03,0xE6,0xC9,0x03,0x10,0xC9,0x03,0x0B,0xC9,0x03,0x0D,
0xC8,0x03,0xE7,0xC9,0x03,0x10,0xC9,0x03,0x0B,0xC9,0x03,0x0C,0xC8,0x03,0xE8,
0xC9,0x03,0x10,0xC9,0x03,0x0B,0xC9,0x03,0x0B,0xC8,0x03,0xE9,0xC9,0x03,0x10,
0xC9,0x03,0x0C,0xC9,0x03,0x0B,0xC8,0x03,0xEA,0xC9,0x03,0x10,0xC9,0x03,0x0D,
0xC9,0x03,0x0B,0xC8,0x03,0xEB,0xC9,0x03,0x10,0xC9,0x03,0x0F,0xC9,0x03,0x0B,
0xC8,0x03,0xEC,0xC9,0x03,0x10,0xC9,0x03,0x10,0xC9,0x03,0x0B,0xC8,0x03,0xED,
0xC9,0x03,0x0F,0xC9,0x03,0x10,0xC9,0x03,0x0B,0xC8,0x03,0xEE,0xC9,0x03,0x0D,
0xC9,0x03,0x10,0xC9,0x03,0x0B,0xC8,0x03,0xEF,0xC9,0x03,0x0C,0xC9,0x03,0x10,
0xC9,0x03,0x0B,0xC8,0x03,0xF0,0xC9,0x03,0x0B,0xC9,0x03,0x10,0xC9,0x03,0x0B,
0xC8,0x03,0xF1,0xC9,0x03,0x0B,0xC9,0x03,0x10,0xC9,0x03,0x0C,0xC8,0x03,0xF2,
0xC9,0x03,0x0B,0xC9,0x03,0x10,0xC9,0x03,0x0D,0xC8,0x03,0xF3,0xC9,0x03,0x0B,
0xC9,0x03,0x10,0xC9,0x03,0x0F,0xC8,0x03,0xF4,0xC9,0x03,0x0B,0xC9,0x03,0x10,
0xC9,0x03,0x10,0xC8,0x03,0xF5,0xC9,0x03,0x0B,0xC9,0x03,0x0F,0xC9,0x03,0x10,
0xC8,0x03,0xF6,0xC9,0x03,0x0B,0xC9,0x03,0x0D,0xC9,0x03,0x10,0xC8,0x03,0xF7,
0xC9,0x03,0x0B,0xC9,0x03,0x0C,0xC9,0x03,0x10,0xDA,0x43,0xC0,0x03,0x20,0xC4,
0x43,0xC4,0x03,0x01,0xC5,0x43,0xC4,0x83,0x01,0x01,0xC4,0x03,0x15,0x00,0x00,
0x00,0x00
};    /* Data End */
unsigned pascal far __A000H(void);
static	void	S3TrioClearScreen(void)
{
	_AX=0x4F05;
	_BX=0;_DX=1;//Select Bank 0
	geninterrupt(0x10);
	_ES=FP_OFF(__A000H);	//Screen Buffer as A000 Segment.
	_DI=0;
	asm	mov	cx,32768
	asm	xor	ax,ax
	asm	rep	stosw
	_AX=0x4F05;
	_BX=0;_DX=0;//Select Bank 0
	geninterrupt(0x10);
	asm	mov	cx,32768
	asm	xor	ax,ax
	asm	rep	stosw
}
void  PASCAL FAR	InitS3Trio10E(void)
{
	char	far	*DataPtr;

	DataPtr=T400X300IO;
	asm	push	ds
	asm	lds	si,DataPtr
	asm	cld
	LOOP:
	asm	lodsw
	if(_AX==0) goto EXIT;
	asm	mov	bx,ax
	asm	mov	dx,ax
	asm	and	dx,0x3FFF
	switch(_BX&0xC000)
		{
		case	0:	asm	lodsb
				asm	out	dx,al
				break;
		case 	0x4000:
				asm	in	al,dx
				break;
		case	0x8000:	asm	lodsw
				asm	out	dx,ax
				break;
		default:
			goto	EXIT;
		}
	goto	LOOP;
	EXIT:
	asm	pop	ds
	S3TrioClearScreen();
}

/** Graphics hardware detector header for TURBO C 2.00
*
*   Kraisorn Liansee
*   Date    : 4/27/89
*   Updated : 4/27/89
*
*   Suttipong Kanakakorn
*   Updated : Sun  08-27-1989 20:25:09
*/

#ifndef COMMON_GRDETECT_H_INCLUDED
#define COMMON_GRDETECT_H_INCLUDED

typedef enum Graphics_hardware {
	DETECT, /* request autodetection */
	CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514,         /* 1 - 6 */
	HERCMONO, ATT400, VGA, PC3270,                   /* 7 - 10 */
	MDA = 128,
	UNKNOWN_HW = -1
} graphics_hardware;

/* check current video configuration */
void graph_detecthardware( graphics_hardware *mode_ptr );

/* check if the equipped adaptor is EGA or VGA */
int is_egavga( void );

/* determines EGA/VGA adaptor configuration */
void egavga_class( graphics_hardware *mode_ptr );

/* check if the equipped adaptor is MCGA */
int is_mcga( void );

/* check if there is any transition on 0x3BF port */
int check_vretrace( void );

#endif /* COMMON_GRDETECT_H_INCLUDED */
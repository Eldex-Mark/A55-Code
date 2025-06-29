#include "lvgl/lvgl.h"
#include "lvgl/demos/lv_demos.h"

#if !USE_WAYLAND
#include "lv_drivers/display/fbdev.h"
#endif

#if USE_EVDEV
#include "lv_drivers/indev/evdev.h"
#endif

#if USE_LIBINPUT
#include "lv_drivers/indev/libinput_drv.h"
#endif

#if USE_WAYLAND
#include "lv_drivers/wayland/wayland.h"
#endif

#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>

#include <linux/fb.h>

#if USE_WAYLAND
#include <limits.h>
#include <errno.h>
#include <poll.h>
#endif

#define DISP_BUF_SIZE (256 * 1024)

#if !USE_WAYLAND
  #define FCHAR 'F'
  #if USE_EVDEV
    #define VCHAR 'S'
  #endif
  #if USE_LIBINPUT
    #define VCHAR 'P'
  #endif   
#else
  #define FCHAR 'W'
  #define VCHAR 'P'
#endif


typedef enum  {ILI_FB_DEVICE,HDMI_FB_DEVICE} fb_device_type ;
typedef struct {
                  uint32_t fb_width ;
                  uint32_t fb_height ;
                  int32_t  fb_device_id ;
                  uint32_t fb_bit_per_pixel ;
                  uint32_t ws_width ;
                  uint32_t ws_height ;
                  bool     is_primary_device ;
                  bool     is_weston_device ;
                  bool     is_valid_device ;
                } grapic_info_type ; 
                
#define INFO_DISPLAY_DEVICES_SIZE  2 
grapic_info_type  info_display_devices[INFO_DISPLAY_DEVICES_SIZE]  = { { 0,0,-1,0,0,0,false,false,false }, { 0,0,-1,0,0,0,false,false,false } } ;
        

int search_fb_device ( fb_device_type  fb_device )
{
    char eventId[8];
    int id=-1;        
    FILE *fp;
     
    if (fb_device == ILI_FB_DEVICE) {
      fp = popen("cat /proc/fb | awk 'BEGIN {s=1000} { if (($0 ~ /fb_ili/) || ($0 ~ /ili.*drmfb/)) {s = $1 ; exit}} END{print s}'", "r");  
    }
    if (fb_device == HDMI_FB_DEVICE) {   
      fp = popen("cat /proc/fb | awk 'BEGIN {s=1000} { if ($0 ~ /rcar/) {s = $1 ; exit}} END{print s}'", "r"); 
    }    
    while (fgets(eventId, sizeof(eventId), fp) != NULL) {
      id = atoi(eventId);
    }
    pclose(fp);
    if (id >99) {id = -1;}
    return id ;
}

int check_wayland_service_status ( )
{
    int id;        
    FILE *fp;
     
    fp = popen("systemctl is-active weston* --quiet", "r");  
    id = pclose(fp);
    return WEXITSTATUS(id) ;
}

int check_wayland_setting ( grapic_info_type *device_info )
{
    char eventId[255];
    char *token ;
    int ii ;
    FILE *fp;
    int weston_status =  check_wayland_service_status() ;
    
    if ( weston_status == 0 ) {  
      device_info->is_weston_device= true ;
      fp = popen("weston-info | awk 'BEGIN{s=0;w=0;h=0} { if ($1 == \"interface:\"){if(s==1){exit};s=0}; if ( $1 ~ \"xdg_output\" ) {s=1}; if(s==1 && $0 ~ \"logical_[w|h]\") {gsub(\",\",\"\");for(i=1;i<=NF;i+=2){if($i==\"logical_width:\"){w=$(i+1)};if($i==\"logical_height:\"){ h=$(i+1) } }}} END {printf(\"%d %d\",w,h)}'", "r"); 
       while (fgets(eventId, sizeof(eventId), fp) != NULL) {
        for(ii=0, token = strtok(eventId," "); token != NULL ; ii++, token = strtok(NULL," ")) {
          int id = atoi(token);
          if ( ii == 0 ) { device_info->ws_width  = id; }
          if ( ii == 1 ) { device_info->ws_height = id; device_info->is_valid_device = true; }
        }
      }
      pclose(fp);
    } else {
      device_info->is_weston_device= false ;
    }
    return 0;
}

void get_fb_device_info (grapic_info_type *device_info)
{
    int fbdev = -1;
    int fbid  = device_info->fb_device_id;
    static struct fb_var_screeninfo vinfo;

    if ( fbid > -1 ) {      
      const char* IARRAYTS = "/dev/fb" ;
      char IARRAY[sizeof(IARRAYTS)+sizeof(int)];
      snprintf(IARRAY,sizeof(IARRAY),"%s%hd",IARRAYTS,fbid);
      // Open the file for reading and writing
      fbdev = open(IARRAY, O_RDWR);
      if(fbdev == -1) {
        perror("Error: cannot open framebuffer device %d ");
        return;
      }
    } else {
      return ;
    }

    // get device screen info 
    if(ioctl(fbdev, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error readin");
        close(fbdev);
        return;
    }
    device_info->fb_width =vinfo.xres;
    device_info->fb_height=vinfo.yres;
    device_info->fb_bit_per_pixel=vinfo.bits_per_pixel;
    device_info->is_valid_device=true;
    close(fbdev);
}

void get_device_info() 
{
 /* DRM devices not handled yet */
 
 info_display_devices[0].fb_device_id   = search_fb_device( HDMI_FB_DEVICE );
 if ( info_display_devices[0].fb_device_id > -1 ) { info_display_devices[0].is_primary_device = true; }
 get_fb_device_info ( &info_display_devices[0] );       
 check_wayland_setting( &info_display_devices[0] ) ; /* we will assign wayland to the primary device by default by guessing for the moment */
 
 info_display_devices[1].fb_device_id = search_fb_device( ILI_FB_DEVICE );
 get_fb_device_info (&info_display_devices[1]);

}

void auto_exec ( int argc, char *argv[], char vchar_cmd, uint32_t display_data_set ) {
    /* check if version support the framebuffer format */
    int bit_per_pixel = info_display_devices[display_data_set].fb_bit_per_pixel ; /* We will take the frambuffer setting as basis as long as the DRM read functions are not implemented */
    char fchar = 'F' ;
    char vchar = 'S' ;
 
    if  ( info_display_devices[display_data_set].is_primary_device == true ) {
       vchar = 'P' ;
    }   
    if  ( info_display_devices[display_data_set].is_weston_device == true ) {
       fchar = 'W' ;
       vchar = 'P' ;
    }
 
    if (LV_COLOR_DEPTH != bit_per_pixel || ( fchar != FCHAR  ) || ( vchar != VCHAR && vchar_cmd == ' ' )  ||  ( vchar_cmd != VCHAR && vchar_cmd != ' ' )) {
      char cbuff[255] ;
      size_t len = strlen(argv[0]) ;
      char *extposptr = NULL ;
      
      strncpy(cbuff,argv[0],len);
      extposptr = rindex(cbuff,'_');
      if ( extposptr ) {
        *extposptr = '\0' ;
        len = strlen(cbuff) ;
      }
      if  ( vchar_cmd != VCHAR && vchar_cmd != ' ' ) {
        vchar = vchar_cmd ;
      }
      if ( fchar != 'W' ) {
        snprintf(&cbuff[len], sizeof(cbuff)-len-1, "_%d%c%c",bit_per_pixel,fchar,vchar);      
      } else {
        snprintf(&cbuff[len], sizeof(cbuff)-len-1, "_%d%c",bit_per_pixel,fchar);      
      }
          
      if ( strcmp(cbuff,argv[0]) == 0) {
        printf ("Error: recursive execution detected.\n Abnormal end.\n");
        exit(-2);
      } 

      printf ("Matching program call : %s ==> %s\n\n",argv[0],cbuff);

      argv[0] = cbuff ;
      execvp(cbuff, argv);
      exit(-1) ; /* This line should never been reached */
    }
}

void usage( char * name ) {
	printf("\nusage: %s\n", name);
	printf("   --primary,     -p  run the demo on the primary display connected to LCDC (fbdev or weston)\n");
	printf("   --secondary,   -s  run the demo on SPI connected frame buffer display\n");
	printf("   --window,      -w  run the demo in a window instead of full screen (weston required)\n");
	printf("   --music,       -m  run optional Music-demo \n");
	printf("   --stress,      -t  run optional Stress-demo \n");
	printf("   --benchmark,   -b  run optional Benchmark-demo \n\n");
	printf("   --help,        -h  print usage \n\n");
	exit(0);
}

int main(int argc, char *argv[])
{
    char vchar_cmd = ' ' ;
    bool window_mode = false ;
    int window_dw = 70 ;
    int window_dh = 70 ;
    int demo_music = 0;
    int demo_stress = 0;
    int demo_benchmark = 0;
              
    /* command line option definition */
    struct option longopt[] = {
        {"primary",0,NULL,'p'},
        {"secondary",0,NULL,'s'},
        {"window",0,NULL,'w'},
        {"music",0,NULL,'m'},
        {"stress",0,NULL,'t'},
        {"benchmark",0,NULL,'b'},                   
        {0,0,0,0}
    };
        
    /* command line parser */
    int iChar ;
    while ((iChar=getopt_long(argc,argv,"pswmtbh",longopt,NULL)) != -1)
    {
        switch ( iChar )
        {
            case 'p':
                vchar_cmd = 'P' ;
                break;
            case 's':
                vchar_cmd = 'S' ;
                break;
            case 'w':
                window_mode = true ;
                break;
            case 'm':
                demo_music = true ;
                demo_stress = false ;
                demo_benchmark = false ;
                break;                
            case 't':
                demo_music = false ;
                demo_stress = true ;
                demo_benchmark = false ;
                break;       
            case 'b':
                demo_music = false ;
                demo_stress = false ;
                demo_benchmark = true ;
                break;                                      
            case 'h':
                usage(argv[0]);
                break;
                                               
            default:
                printf("bad argument <%c> \n",iChar);
                usage(argv[0]);
                break ;
        }
    }

    uint32_t x_res=0, y_res=0, dpi_res=0, bit_per_pixel=0 ;
    uint32_t display_data_set = -1 ;

    /* relaxed device probing */
 
    int wayland_status         = check_wayland_service_status() ; // 0 - active 
              
    get_device_info();

    for (int i = 0 ; i<INFO_DISPLAY_DEVICES_SIZE ; i++ ){
          if ( ((vchar_cmd == 'S') || ((VCHAR == 'S') && (vchar_cmd == ' '))) && ( info_display_devices[i].is_primary_device == false ) && ( info_display_devices[i].is_valid_device == true ))
             display_data_set = i ;
          if ( ((vchar_cmd == 'P') || ((VCHAR == 'P') && (vchar_cmd == ' '))) && ( info_display_devices[i].is_primary_device == true ) && ( info_display_devices[i].is_valid_device == true ))
             display_data_set = i ;
    }
    if ( display_data_set == -1 ) {
       for (int i = 0 ; i<INFO_DISPLAY_DEVICES_SIZE ; i++ ){
          if ( (vchar_cmd == ' ') && ( info_display_devices[i].is_valid_device == true ) ) {
             display_data_set = i ; 
             break ;
          }
       }    
    }
    
    if (display_data_set == -1) {
          printf ("EXIT: no graphic device found.\n");
          exit(-1);
    }
    auto_exec (argc, argv, vchar_cmd, display_data_set) ;
        
    /* executable depending choice */    
    display_data_set = -1 ;
 
    #if !USE_WAYLAND      
      #if USE_EVDEV
        for (int i = 0 ; i<INFO_DISPLAY_DEVICES_SIZE ; i++ ){
          if (( info_display_devices[i].is_primary_device == false ) && ( info_display_devices[i].is_valid_device == true ) && (info_display_devices[i].is_weston_device == false))
             display_data_set = i ;
        }
        if (display_data_set == -1) {
          printf ("EXIT: secondary framebuffer device [spi] not found.\n");
          exit(-1);
        }

      #endif

      #if USE_LIBINPUT
        for (int i = 0 ; i<INFO_DISPLAY_DEVICES_SIZE ; i++ ){
          if (( info_display_devices[i].is_primary_device == true ) && ( info_display_devices[i].is_valid_device == true )&& (info_display_devices[i].is_weston_device == false))
             display_data_set = i ;
        }
        if (display_data_set == -1) {
          printf ("EXIT: primary framebuffer device [hdmi] not found.\n");
          exit(-1);
        }

      #endif   
    #else
      for (int i = 0 ; i<INFO_DISPLAY_DEVICES_SIZE ; i++ ){
         if (( info_display_devices[i].is_primary_device == true ) && ( info_display_devices[i].is_valid_device == true ) && ( info_display_devices[i].is_valid_device == true ) && (info_display_devices[i].is_weston_device == true))
             display_data_set = i ;
      }
      if (display_data_set == -1) {
          printf ("EXIT: device for Weston [hdmi] not found.\n");
          exit(-1);
      }      
      printf ("Weston resolution     : %d x %d \n", info_display_devices[display_data_set].ws_width, info_display_devices[display_data_set].ws_height);                   
    #endif
    
    #if !USE_WAYLAND    
      /* disable console output */
      int fdconsole = open("/dev/tty0",O_RDWR) ;
      ioctl(fdconsole, KDSETMODE, KD_GRAPHICS ) ;

      /* Linux frame buffer device init */
      fbdev_set_device(info_display_devices[display_data_set].fb_device_id) ;
  
      /* The secondary ILI based display does not support the FBIOBLANK ioctl */    
      if ( info_display_devices[display_data_set].is_primary_device == false ) 
         fbdev_disable_fbioblank() ;
        
      fbdev_init();
      fbdev_get_bitperpixel(&bit_per_pixel);
      fbdev_get_sizes(&x_res, &y_res, &dpi_res);
    #endif
    
    
    /*LittlevGL init*/
    lv_init();

    #if !USE_WAYLAND
      /*A small buffer for LittlevGL to draw the screen's content*/
      static lv_color_t buf[DISP_BUF_SIZE];

      /*Initialize a descriptor for the buffer*/
      static lv_disp_draw_buf_t disp_buf;
      lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);

      /*Initialize and register a display driver*/
      static lv_disp_drv_t disp_drv; 
      lv_disp_drv_init(&disp_drv);
      disp_drv.draw_buf   = &disp_buf;
      disp_drv.flush_cb   = fbdev_flush;
      if ( &x_res != 0  && y_res != 0 ) {
        printf ("Use device resolution : %d x %d \n", x_res, y_res);
        disp_drv.hor_res    = x_res ;
        disp_drv.ver_res    = y_res ;
        disp_drv.physical_hor_res    = x_res ;
        disp_drv.physical_ver_res    = y_res ;
      } else {
        disp_drv.hor_res    = 320;
        disp_drv.ver_res    = 240;
      }
      lv_disp_drv_register(&disp_drv);

      #if USE_EVDEV
        evdev_init();
      #endif        
      #if USE_LIBINPUT
        libinput_init();
      #endif
       
      static lv_indev_drv_t indev_drv_1;
      lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
      indev_drv_1.type = LV_INDEV_TYPE_POINTER;

      /*This function will be called periodically (by the library) to get the mouse position and state*/

      #if USE_EVDEV
        indev_drv_1.read_cb = evdev_read;
      #endif    
      #if USE_LIBINPUT
        indev_drv_1.read_cb = libinput_read;
      #endif    

      lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

      /*Set a cursor for the mouse*/
      LV_IMG_DECLARE(mouse_cursor_icon)
      lv_obj_t * cursor_obj = lv_img_create(lv_scr_act()); /*Create an image object for the cursor */
      lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
      lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
      
    #else // USE_WAYLAND
      lv_wayland_init();
      
      struct pollfd pfd;
      uint32_t time_till_next;
      int sleep;     
      
      if ( window_mode == false ) {
        window_dw = 0 ;
        window_dh = 0 ;
      } else {
        printf("window mode           : %d \n",window_mode);    
        printf("window size           : %d x %d\n",info_display_devices[display_data_set].ws_width-window_dw,info_display_devices[display_data_set].ws_height-window_dh);    
      }    
      /* Create a display */
 
      lv_disp_t * disp = lv_wayland_create_window(info_display_devices[display_data_set].ws_width-window_dw, 
                                                  info_display_devices[display_data_set].ws_height-window_dh, 
                                                  "Widget Window Demo", NULL);
      lv_wayland_window_set_fullscreen(disp, true-window_mode);
      
      pfd.fd = lv_wayland_get_fd();
      pfd.events = POLLIN;   
    #endif

    /*Create a Demo*/
    
    if ( !demo_music && !demo_stress && !demo_benchmark )
      lv_demo_widgets() ;

    if ( demo_music )
      lv_demo_music() ;
       
    if ( demo_stress )
      lv_demo_stress() ;
        
    if ( demo_benchmark )    
      lv_demo_benchmark() ;

    /*Handle LitlevGL tasks (tickless mode)*/
    #if !USE_WAYLAND
      while(1) {
           lv_timer_handler();
           usleep(5000);
      }
      
      /* restore the curosr in the console */
      ioctl(fdconsole, KDSETMODE, KD_TEXT ) ;
      close(fdconsole) ;
      
    #else //USE_WAYLAND  
    
      while(1) {
           /* Handle any Wayland/LVGL timers/events */
           time_till_next = lv_wayland_timer_handler();

           /* Run until the last window closes */
          if (!lv_wayland_window_is_open(NULL)) {
             break;
          }

          /* Wait for something interesting to happen */
          if (time_till_next == LV_NO_TIMER_READY) {
            sleep = -1;
          } else if (time_till_next > INT_MAX) {
            sleep = INT_MAX;
          } else {
            sleep = time_till_next;
          }

          while ((poll(&pfd, 1, sleep) < 0) && (errno == EINTR));
      }
      
      lv_deinit () ;
      lv_wayland_deinit() ;
      
    #endif
       
    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if(start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}

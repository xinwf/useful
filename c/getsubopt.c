/*
Aug 27, 2017
*/

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


enum
{
  T, TH , TV ,THV, RT ,RTH ,RTV ,RTHV  ,FLIP_IMAGES  , BUTT
};


enum
{
    FD , FH , FV , RFD , RFH  , RFV , BUTT2
};

// leading r is for resize

char *tile_opts[] =
{
  [T] = "n",
  [TH] = "h",
  [TV] = "v",
  [THV] = "hv",
  [RT] = "rt",
  [RTH] = "rh",
  [RTV] = "rv",
  [RTHV] ="rhv",
  //[FLIP_IMAGES] = "fi",
  [BUTT] = NULL
};

char *flip_opts [] =
{

        [FD] = "d",
        [FH] = "h",
        [FV] = "v",
        [RFD] = "rd",
        [RFH] = "rh",
        [RFV] = "rv",
        [BUTT2] = NULL
};


void mh_parse_options_array(int argc, char **argv)
{
    int oc = 0;
    int option_index = 0;
    char *subopts;

    char *value;
    extern char *optarg;
    extern int optind;


    static char string_options [] = "FfCc:t:s:d:a:";
        //  no_argument  0
        // required_argument 1   (‘:’) to indicate that it takes a required argument
        // optional_argument 2  (‘::’), its argument is optional
    static struct option long_options[] = {
 // a b c d e f g h i j k l m n o p q r s t u v w x y z
        {"fullscreen", 0,  0,  'f'},
        {"fill",  0 ,  0, 'F'},
        {"center", 0 ,0,'C'},
         {"resize-center", 1, 0, 'c'},
         {"solid", 1,0,'s'},
         {"distance",1,0,'d'},
         {"angle",1,0,'a'},
             {"tile",1, 0, 't'},
        {"add",1,0,200},
         {"rf",0,0,201}, // random files
         {"fi",1,0,202}, // flip Image fi
         {0,0,0,0}

    }; // end options

    while (( oc = getopt_long_only(argc, argv, string_options, long_options,&option_index) ) != -1)

        switch (oc)
        {
            case 'f':
                printf("Full screen\n");
                break;
            case 'F':
                printf("Fill screen\n");
                break;
            case 'C':
                    printf("Center Screen\n");
                break;
            case 'c':
                printf("resize center screen: Size %s\n", optarg);
                break;
                   case 'd':
                        printf("distance %s\n", optarg);
                break;
            case 'a':
                printf("angle %s\n", optarg);

                break;
            case 's':
                printf("solid: color %s \n", optarg);

                break;
            case 200:
               printf("add (2) colors C = %s\n", optarg);

                break;
            case 201:
                printf("Random files\n");
                break;
        case '?':
                printf("What did you forget?  Think about it.\n");
                exit(1);
                break;

            case 't': // sub opts one
                printf("in tile\n");
                subopts = optarg;

                while (*subopts != '\0')
                    switch (getsubopt (&subopts, tile_opts, &value))
                    {
                        case T:

                            printf("Tile subopts mode\n");
                            break;
                        case TH:

                            printf("tile hor subopts mode\n");
                            break;
                        case TV:

                            printf("tile vert subopts mode \n");
                            break;
                        case THV:

                            printf("Tile Hor vert subopt mode\n");
                            break;
                        case RT:
                                printf("RTILE: image_size %s\n",value);
                                break;
                            case RTH:
                                    printf("Resize tile Hor: image_size %s\n", value);

                              break;
                        case RTV:
                                printf(" Resize TIle Vert\n");

                            break;
                        case RTHV:
                                printf("resize tile hor %s value\n", value);
                                 break;
                      default: // UNCOMMENTED THIS DEFAULT BREAK
                        printf("default setopts one\n");
                            break;
                    } // end first sub opts.
                    break; // ADDED BREAK HERE
              case 202: // taken from main switch long opts
                         // second subopts fi
                       printf("Case FI %s\n",optarg);
                         subopts = optarg;
                    while (*subopts != '\0')
                       switch (getsubopt (&subopts, flip_opts, &value))
                       {
                        case FD:
                                printf("flipD\n");
                            break;
                         case FH:
                            printf("flipH\n");
                            break;
                        case FV:
                            printf("flipV \n");
                            break;
                        case RFD:
                            if (value == NULL)
                            {
                                printf("bad value %s\n", value);
                                exit(1);
                            }
                            else
                            {
                                printf("resize flipsd %s\n", value);
                            }
                            break;
                        case RFH:
                            if(value == NULL)
                            {
                                printf("bad value %s\n", value);
                                exit(1);
                            }
                            else
                            {
                                printf("resize flipH %s\n",value);
                            }
                            break;
                        case RFV:
                            if(value == NULL)
                            {
                                printf("bad value %s\n", value);
                                exit(1);
                            }
                            else
                            {
                                printf("resizeflipd V %s\n",value);
                            }
                            break;

                        default:
                                //Second suboption.
                            printf ("Unknown suboption `%s'\n", value);
                        break;

                      } // end second switch subopts
                    break; // ADDED BREAK HERE

            default:
                printf("Default main switch\n");
                break;

        } // end main switch


//printf("optind %d, argc %d\n", optind, argc);

    if(optind == argc)
    {
        printf("if(optind == argc)%s \n", argv[optind]);
    }

    if (optind < argc)
    {
        printf( " loading image path if ( optind < argc) %s argv[argc]\n", argv[optind]);

        for(; optind < argc ; optind++)
        {
            printf("getting files\n");
        }

    optind = 0;
    }

} //end function

void check_options(void)
{

  printf("check_options\n");


}


int main (int argc, char **argv )
{

mh_parse_options_array(argc,  argv);


return 0;
}

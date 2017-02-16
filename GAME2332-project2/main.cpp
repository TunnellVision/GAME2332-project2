// main.cpp
//
// second commit

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_ttf.h>


const int  DISPLAY_WIDTH = 800;
const int  DISPLAY_HEIGHT = 600;
const float FPS = 60.0;


ALLEGRO_DISPLAY *game_display = NULL;	// create an Allegro display; all graphical operations will
										// be eventually sent to this window.
ALLEGRO_FONT *game_font = NULL;	// the game font
ALLEGRO_TIMER *game_timer = NULL;	// game timer
ALLEGRO_EVENT game_event;						// game event removed from the game event queue
ALLEGRO_EVENT_QUEUE *game_event_queue = NULL;	// game event queue

ALLEGRO_COLOR pixel_color;

void init();
void deinit();


int main(){
    bool done = false;			// indicates whether or not to quit the program
	bool draw = false;


	init();

	// set window title
	al_set_window_title(game_display, "Project 2 Tetris");

	// set rectangle color
	pixel_color = al_map_rgb(50,0,100);


	while (!done)
	{

        al_wait_for_event(game_event_queue, &game_event);
        if (game_event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (game_event.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE: // escape key pressed
				done = true;
			}
		}

		if (game_event.type == ALLEGRO_EVENT_TIMER) // check if event type is a timer event
		{
			draw = true;
		}

		if(draw){

            al_set_target_backbuffer(game_display);
            al_draw_filled_rectangle(50,50, 100, 100, pixel_color);
            al_flip_display();
		}

    }

    deinit();
    return 0;
}


void init()
{
	// before we can use Allegro 5 we must first initialize the Allegro 5 environment
	if (!al_init())
	{ // display a pop-up box if an error occurs
		al_show_native_message_box(NULL, "Allegro 5 Error", "Fatal error encountered.", "Could not initialize Allegro 5!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	// set some display flags
	al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

	// create the display
	game_display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

	// check if display was successfully created
	if (!game_display)
	{ // display a pop-up box if an error occurs
		al_show_native_message_box(NULL, "Allegro 5 Error", "Fatal error encountered.", "Cannot create Allegro 5 display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}
	// set window position on screen
	al_set_window_position(game_display, 200, 0);

	// initialize the image addon required for loading bitmap files
	al_init_image_addon();

	// initialize the primitives addon for drawing geometric shapes
	al_init_primitives_addon();

	// initialize font addon
	al_init_font_addon();

	// initialize true type font addon
	al_init_ttf_addon();

	//game_font = al_load_font("verdana.ttf", 11, NULL);
	//game_font = al_load_font("courierNewBold.ttf", 11, 0);
	game_font = al_create_builtin_font();
	// check if font was successfully loaded
	if (!game_font)
	{ // display a pop-up box if an error occurs
		al_show_native_message_box(NULL, "Allegro 5 Error", "Fatal error encountered.", "Cannot create or load the game font!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(1);
	}

	// install a keyboard driver. Returns true if successful.
	al_install_keyboard();

	//create the game timer
	game_timer = al_create_timer(1.0 / FPS);

	// create an Allegro 5 event queue
	game_event_queue = al_create_event_queue();

	// register keyboard events so that they can be detected and processed
	al_register_event_source(game_event_queue, al_get_keyboard_event_source());
	// register timer events so that they can be detected and processed
	al_register_event_source(game_event_queue, al_get_timer_event_source(game_timer));

	// start the timer
	al_start_timer(game_timer);
}

void deinit()
{
	// free the allocated memory used by the display
	al_destroy_display(game_display);

	// free the allocated memory used by the font
	al_destroy_font(game_font);

	// free the allocated memory used by the event queue
	al_destroy_event_queue(game_event_queue);

	// free allocated memory by the the timer
	al_destroy_timer(game_timer);
}


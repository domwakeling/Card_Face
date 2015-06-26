#include <pebble.h>

#define WINDOW_WIDTH 144
#define WINDOW_HEIGHT 168
#define M_VERT 8
#define M_HORZ 8
#define P_VERT 2	// must be an even number
#define P_HORZ 2  // must be an even number

Window *main_window;
Layer *background_layer;

void background_update_proc(Layer *l, GContext *ctx) { 
	
	// set fill to black and fill entire background
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, GRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT), 0, GCornerNone);
	
	// *** ACTION 1 - DELETE FROM HERE DOWN TO THE END OF THE FUNCTION
	
	// *** TEMPORARY ***
	
	int size_x = ( WINDOW_WIDTH - 2 * M_HORZ - P_HORZ ) / 2;
	int size_y = ( WINDOW_HEIGHT - 2 * M_VERT - P_VERT ) / 2;
	
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_rect(ctx, GRect(M_HORZ, M_VERT, size_x, size_y), 2, GCornersAll);
	// *** ACTION 1 - THIS IS THE END OF THE FUNCTION!
}

static void main_window_load(Window *window) {
	// get handle for the window layer
	Layer *w = window_get_root_layer(main_window);
	
	// create the layers
	background_layer = layer_create(GRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT));
	
	// set the update procs
	layer_set_update_proc(background_layer, background_update_proc);
	
	// add layers to window
	layer_add_child(w, background_layer);
}

static void main_window_unload(Window *window) {
	layer_destroy(background_layer);
}

static void init() {
	// Create main Window element and assign to pointer
	main_window = window_create();
	
	// Set handlers to manage the elements inside the Window
	window_set_window_handlers(main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});	
	
	// Show the Window on the watch, with animated = true
	window_stack_push(main_window, true);
}

static void deinit() {
	// Destroy Window
	window_destroy(main_window);	
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
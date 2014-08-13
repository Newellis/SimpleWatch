#include <pebble.h>

Window *window;
TextLayer *time_layer, *month_layer, *day_layer;
InverterLayer *inv_layer;
GBitmap *bat_bitmap, *bat_10_bitmap, *bat_90_bitmap, *bat_empty_bitmap, *bat_empty_90_bitmap;
BitmapLayer *bat_10_layer, *bat_20_layer, *bat_30_layer, *bat_40_layer, *bat_50_layer, *bat_60_layer, *bat_70_layer, *bat_80_layer, *bat_90_layer;


char *chngChar(char *str, char oldChar, char newChar) {
    char *strPtr = str;
    while ((strPtr = strchr (strPtr, oldChar)) != NULL)
        *strPtr++ = newChar;
    return str;
}
void handle_timetick(struct tm *tick_time, TimeUnits units_changed){
  static char time_buffer[10];
  static char month_buffer[20];
  static char day_buffer[20];

  //if time changed
  if(units_changed & MINUTE_UNIT) {
  //set time buffer
    //check the 24 hr time pebble setting and get correct time format
    if (clock_is_24h_style()) { 
      strftime(time_buffer, sizeof(time_buffer), "%H:%M", tick_time);
    } else {
      strftime(time_buffer, sizeof(time_buffer), "%I:%M", tick_time);
    }
    char *time_ptr = time_buffer;
    if (time_buffer[0] == '0') { //remove preceding 0 on hour
      time_ptr++;
    }
    chngChar(time_ptr, '0', 'o'); //compensate for fonts zero being bad
    //set text layers to display time buffer
    text_layer_set_text(time_layer, time_ptr);
  } 
  //if day changed
  if(units_changed & DAY_UNIT) {
  //set date buffers
    strftime(month_buffer, sizeof(month_buffer), "%b", tick_time);
    strftime(day_buffer, sizeof(day_buffer), "%e", tick_time);
    if (day_buffer[0] == ' ') { //remove preceding 0 on day
      strftime(day_buffer, sizeof(day_buffer), "%e", tick_time);
    } else {
      strftime(day_buffer, sizeof(day_buffer), " %e", tick_time);
    }
    chngChar(day_buffer, '0', 'o'); //compensate for fonts zero being bad
    //set text layers to display date buffers
    text_layer_set_text(month_layer, month_buffer);
    text_layer_set_text(day_layer, day_buffer);
  }
}

void handle_battery(BatteryChargeState charge) {      
  //change battery bitmaps if charging
  if (charge.is_charging) {
    bat_empty_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_CHARGEING);
    bat_empty_90_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_CHARGEING_90);
  } else {
    bat_empty_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_EMPTY);
    bat_empty_90_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_EMPTY);
  }
  
  //change battery bitmap and bitmap layers based on battery percent
  int battery_percent = charge.charge_percent;
  if (battery_percent >= 100){
    bat_10_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHARGED_ICON_10);
    bat_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHARGED_ICON);
    bat_90_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHARGED_ICON_90);
  } else {
    bat_10_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_10);
    bat_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON);
    bat_90_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_90);
  }
  bitmap_layer_set_bitmap(bat_10_layer, bat_10_bitmap);
  
  if(battery_percent >= 20) {
    bitmap_layer_set_bitmap(bat_20_layer, bat_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_20_layer, bat_empty_bitmap);
  }
  if(battery_percent >= 30) {
    bitmap_layer_set_bitmap(bat_30_layer, bat_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_30_layer, bat_empty_bitmap);
  }
  if(battery_percent >= 40) {
    bitmap_layer_set_bitmap(bat_40_layer, bat_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_40_layer, bat_empty_bitmap);
  }
  if(battery_percent >= 50) {
    bitmap_layer_set_bitmap(bat_50_layer, bat_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_50_layer, bat_empty_bitmap);
  }
  if(battery_percent >= 60) {
    bitmap_layer_set_bitmap(bat_60_layer, bat_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_60_layer, bat_empty_bitmap);
  }
  if(battery_percent >= 70) {
    bitmap_layer_set_bitmap(bat_70_layer, bat_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_70_layer, bat_empty_bitmap);
  }
  if(battery_percent >= 80) {
    bitmap_layer_set_bitmap(bat_80_layer, bat_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_80_layer, bat_empty_bitmap);
  }
  if(battery_percent >= 90) {
    bitmap_layer_set_bitmap(bat_90_layer, bat_90_bitmap);
  } else {
    bitmap_layer_set_bitmap(bat_90_layer, bat_empty_90_bitmap);
  }
}

void handle_init(void) {
  //Create a Window and values
  window = window_create();
  time_layer = text_layer_create(GRect(0,50,144,118));
  month_layer = text_layer_create(GRect(0,148,79,20));
  day_layer = text_layer_create(GRect(74,148,63,20));
  bat_10_layer = bitmap_layer_create(GRect(0, 0, 16, 9));
  bat_20_layer = bitmap_layer_create(GRect(16, 0, 16, 9));
  bat_30_layer = bitmap_layer_create(GRect(32, 0, 16, 9));
  bat_40_layer = bitmap_layer_create(GRect(48, 0, 16, 9));
  bat_50_layer = bitmap_layer_create(GRect(64, 0, 16, 9));
  bat_60_layer = bitmap_layer_create(GRect(80, 0, 16, 9));
  bat_70_layer = bitmap_layer_create(GRect(96, 0, 16, 9));
  bat_80_layer = bitmap_layer_create(GRect(112, 0, 16, 9));
  bat_90_layer = bitmap_layer_create(GRect(128, 0, 16, 9));

  bat_10_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_10);
  bat_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON);
  bat_90_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_90);
  bat_empty_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_EMPTY);
  bat_empty_90_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BAT_ICON_EMPTY);
  bitmap_layer_set_bitmap(bat_10_layer, bat_10_bitmap);
  
  //Track time and battery
  tick_timer_service_subscribe(MINUTE_UNIT | DAY_UNIT, handle_timetick);
  battery_state_service_subscribe(handle_battery);
  
  //Load Fonts
  ResHandle time_font_handle = resource_get_handle(RESOURCE_ID_KARNIVORE_49);
  ResHandle date_font_handle = resource_get_handle(RESOURCE_ID_AKASHI_16);
  ResHandle day_font_handle = resource_get_handle(RESOURCE_ID_KARNIVORE_16);
  
  //Set font and alingment
  text_layer_set_font(time_layer, fonts_load_custom_font(time_font_handle));
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  text_layer_set_font(month_layer, fonts_load_custom_font(date_font_handle));
  text_layer_set_text_alignment(month_layer, GTextAlignmentRight);
  text_layer_set_font(day_layer, fonts_load_custom_font(day_font_handle));
  text_layer_set_text_alignment(day_layer, GTextAlignmentLeft);
  
  //set time and date to current value
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  handle_timetick(current_time, MINUTE_UNIT);
  handle_timetick(current_time, DAY_UNIT);
  
  //set Battery bar to correct value
  BatteryChargeState charge_state = battery_state_service_peek();
  handle_battery(charge_state);
  
  //add layers to the window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(day_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(month_layer));
  
  //Add battery bars to window
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_10_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_20_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_30_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_40_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_50_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_60_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_70_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_80_layer));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(bat_90_layer));
  
  //Inverter layer
  inv_layer = inverter_layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
  
  //push the Window
  window_stack_push(window, true);
}

void handle_deinit(void) {
  //unubscribe from time and battery updates
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  
  //end bitmap refernces
  gbitmap_destroy(bat_bitmap);
  gbitmap_destroy(bat_10_bitmap);
  gbitmap_destroy(bat_90_bitmap);
  gbitmap_destroy(bat_empty_bitmap);
  gbitmap_destroy(bat_empty_90_bitmap);

  //end bitmap layers
  bitmap_layer_destroy(bat_10_layer);
  bitmap_layer_destroy(bat_20_layer);
  bitmap_layer_destroy(bat_30_layer);
  bitmap_layer_destroy(bat_40_layer);
  bitmap_layer_destroy(bat_50_layer);
  bitmap_layer_destroy(bat_60_layer);
  bitmap_layer_destroy(bat_70_layer);
  bitmap_layer_destroy(bat_80_layer);
  bitmap_layer_destroy(bat_90_layer);
  
  //end text layers and window
  text_layer_destroy(time_layer);
  text_layer_destroy(month_layer);
  text_layer_destroy(day_layer);
  inverter_layer_destroy(inv_layer);
  window_destroy(window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}

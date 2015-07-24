//
// pg_gui_lock.h
//

#ifndef _PG_GUI_LOCK_H_
#define _PG_GUI_LOCK_H_


typedef struct
{
    char user[63];
    time_t time;

} gui_lock_data;



extern void display_gui_locked_page(gui_lock_data* data);
extern void display_gui_lock_page();

// read gui lock data for file
extern int getLockData(gui_lock_data* data);


#endif

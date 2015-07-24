#include <qDecoder.h>
#include <strl.h>
#include <version_util.h>

#include "defines.h"
#include "util.h"
#include "pg_gui_lock.h"


#define SUBMIT_GUI_LOCK_VNAME   "SubmitGuiLock"
#define GUI_LOCK_FILE           "/var/lock/gui.lock"
#define GUI_LOCK_DURATION       5*60



int getLockData(gui_lock_data* data)
{
    FILE *fp = fopen(GUI_LOCK_FILE, "r");

    if (fp && fscanf(fp, "%s %lu", &data->user[0], &data->time))
        return 1;
    else
        return 0;
}




// ---------------------------------------------------------------------------
//
//                             Local Helper functions
//
// ---------------------------------------------------------------------------


static void createGuiLock(gui_lock_data* data)
{
    char buf[255];
    snprintf(buf, sizeof(buf), "%s %lu\n", data->user, data->time);
    qSaveStr(buf, strlen(buf), GUI_LOCK_FILE, "w+");
}



static void removeGuiLock()
{
    unlink(GUI_LOCK_FILE);
}


static int getMinutesLeft(time_t tm)
{

    int timeLeft = difftime(tm,time(NULL));
    if (timeLeft > 0)
        return (timeLeft/60 + ((timeLeft % 60)>0? 1:0));
    else
        return 0;
}



static void print_value_row_string(char* label, char* value)
{
    printf("<tr><td>%s</td> <td>%s</td></tr>\n", label, value);
}



static void print_value_row_int(char* label, int value, char* unit)
{
    printf("<tr><td>%s</td> <td>%d %s</td></tr>\n", label, value, unit);
}




// ---------------------------------------------------------------------------
//
//                              GUI is locked page
//
// ---------------------------------------------------------------------------

void display_gui_locked_page(gui_lock_data * data)
{
    char buff[255];
    char* buildDate;

    print_page_header_start("header");
    printf("<link rel='stylesheet' type='text/css' href='/img/single-page.css'>\n");
    print_page_header_end();


    printf ("<body>\n");

    // Header
    printf("<div id='header'>\n");
    printf ("<a href='http://www.edgewaternetworks.com'>"
            "<img alt='Edgewater Networks Inc.' src='/img/EdgewaterLogo.gif' border=0>"
            "</a>\n");
    printf("</div>\n");

    // Content
    printf("<div id='content'>\n");
    printf("<table style='margin-top:25px'>\n");
    printf("<col width=300px>\n");
    print_value_row_string("This System is locked by user:", data->user);
    print_value_row_int("Try again in:", getMinutesLeft(data->time), "minutes");
    print_value_row_string("<h3>System Information:</h3>","");
    print_value_row_string("Model:", modelString());

    gethostname(buff, sizeof(buff));
    print_value_row_string("Hostname:", buff);

    getSoftwareVersion(buff, sizeof(buff));
    buildDate = strchr(buff, '-');
    if (buildDate)
    {
        *buildDate = 0;
        buildDate+=2;
    }
    print_value_row_string("Version:", buff);
    print_value_row_string("Build date:", buildDate);

    printf("</table>\n");
    printf("</div>\n");


    // Footer
    printf("<div id='footer'>\n");
    display_page_footer_content();
    printf("</div>\n");


    printf ("</body>\n");
    printf ("</html>\n");
}


// ---------------------------------------------------------------------------
//
//                              Lock GUI is page
//
// ---------------------------------------------------------------------------

void display_gui_lock_page(void)
{
    int guiLocked = FALSE;
    gui_lock_data data;
    char *submitAction = qValue(SUBMIT_GUI_LOCK_VNAME);
    char buff[30];


    if (getLockData(&data) && data.time > time(NULL))
        guiLocked = TRUE;

    if (submitAction)
    {
        if (strcmp(submitAction, "Unlock")==0 && guiLocked)
        {
            removeGuiLock();
            guiLocked = FALSE;
        }
        else if (strcmp(submitAction, "Lock")==0 && !guiLocked)
        {
            strlcpy(data.user, remote_user, sizeof(data.user));
            data.time=time(NULL)+GUI_LOCK_DURATION;
            createGuiLock(&data);
            guiLocked = TRUE;
        }
    }

    print_common_header(LOCK_GUI_PG_NUM, "Lock GUI", NULL, "GuiLockForm");

    print_text("<hr>");
    print_text("&nbsp;");

    if (guiLocked)
    {
        print_text_ex("alert-text",  "GUI is currently locked");
        print_value_row_int("The lock will expire in:", getMinutesLeft(data.time), "minutes");
        strlcpy (buff, "Unlock", sizeof(buff));

    }
    else
    {
        print_text_ex("alert-text",
                      "Locking the GUI will disable GUI access for all other users of this system");
        strlcpy (buff, "Lock", sizeof(buff));
    }

    print_text("&nbsp;");
    print_text("<hr>");

    print_page_footer();
    print_table_end();

    print_submit_button(SUBMIT_GUI_LOCK_VNAME, buff, NULL);
    print_form_end();
}

#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#include <gtk/gtk.h>
#include "commandline.h"

static void open_graphfile(GtkButton* button, gpointer user_data)
{
    GtkWidget *image = GTK_WIDGET(user_data);
    GtkWidget *toplevel = gtk_widget_get_toplevel(image);
    GtkFileFilter *filter = gtk_file_filter_new();
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Open graphlayout file",
        GTK_WINDOW(toplevel),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        GTK_STOCK_OK, GTK_RESPONSE_ACCEPT,
        GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
        NULL
    );

    gtk_file_filter_add_pattern(filter, "*.grp");
    gtk_file_filter_set_name(filter, "graphlayout file");
    //gtk_file_filter_add_pixbuf_formats(filter);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    switch (gtk_dialog_run(GTK_DIALOG(dialog))) {
        case GTK_RESPONSE_ACCEPT: {
            /*
            gchar *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
            gtk_image_set_from_file(GTK_IMAGE(image), filename);
            break;
            */
            break;
        }
        default:
            break;
    }
    gtk_widget_destroy(dialog);
}

static GtkWidget *create_window_main()
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *image;
    GtkWidget *box;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "graphlayout viewer");
    gtk_widget_set_size_request(GTK_WIDGET(window), 800, 600);

    box    = gtk_vbox_new(FALSE, 0);
    button = gtk_button_new_with_label("Open graphlayout file");
    image  = gtk_image_new_from_file("bg.jpg");
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 0);
    gtk_container_add (GTK_CONTAINER(window), box);

    g_signal_connect(button, "clicked", G_CALLBACK(open_graphfile), image);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    return window;
}

int main (int argc, char *argv[])
{
    command_line_option *option = command_line_option_constructor(argc, argv);

    printf("verbose: %d\n", option->use_verbose);
    printf("version: %d\n", option->use_version);

    GtkWidget *window;
    gtk_init(&argc, &argv);

    window = create_window_main();

    gtk_widget_show_all(window);
    gtk_main();

    command_line_option_destruction(option);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#include <gtk/gtk.h>
#include <cairo.h>
#include "commandline.h"
#include "graph.h"
#include "document.h"

static layout_document *document = 0;
GtkWidget *render_image;
GtkToolItem *select_graph;
GtkWidget *window;
graph_object *graph = NULL;

static gboolean on_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
    cairo_t *cr;
    cairo_text_extents_t extents;

    cr = gdk_cairo_create(render_image->window);

    const char *utf8 = "graph drawing";
    double x, y;

    cairo_select_font_face(
        cr,
        "Sans",
        CAIRO_FONT_SLANT_NORMAL,
        CAIRO_FONT_WEIGHT_NORMAL
    );

    cairo_set_font_size (cr, 100.0);
    cairo_text_extents (cr, utf8, &extents);

    x = 25.0;
    y = 150.0;

    cairo_move_to(cr, x, y);
    cairo_show_text(cr, utf8);

    cairo_destroy(cr);
    return FALSE;
}

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
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

    switch (gtk_dialog_run(GTK_DIALOG(dialog))) {
        case GTK_RESPONSE_ACCEPT: {
            char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

            if (document) {
                layout_document_destructor(document);
            }

            document = layout_document_constructor();
            layout_document_read_file(document, filename);
            gtk_widget_set_sensitive(select_graph, TRUE);
            graph = document->graph_list->graph_object_list_head;

            if (graph) {

            }

            break;
        }
        default:
            break;
    }

    gtk_widget_destroy(dialog);
}

static void select_graph_from_document(GtkButton* button, gpointer user_data)
{
    if (graph == NULL) {
        GtkWidget *dialog;
        dialog = gtk_message_dialog_new(
            GTK_WINDOW(window),
            GTK_DIALOG_DESTROY_WITH_PARENT,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "You have to choose a graphlayout file first",
            "Error"
        );
        gtk_window_set_title(GTK_WINDOW(dialog), "Error");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
}

void create_window_toolbar(GtkWidget *box)
{
    GtkWidget *toolbar;
    GtkToolItem *open, *save, *new, *sep, *exit, *select;

    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width(GTK_CONTAINER(toolbar), 2);

    new = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new, -1);

    open = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open, -1);
    g_signal_connect(open, "clicked", G_CALLBACK(open_graphfile), NULL);

    save = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save, -1);

    select = gtk_tool_button_new_from_stock(GTK_STOCK_PREFERENCES);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), select, -1);
    gtk_widget_set_sensitive(select, FALSE);
    select_graph = select;
    g_signal_connect(G_OBJECT(select), "clicked", G_CALLBACK(select_graph_from_document), NULL);

    sep = gtk_separator_tool_item_new();
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

    exit = gtk_tool_button_new_from_stock(GTK_STOCK_QUIT);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), exit, -1);
    g_signal_connect(G_OBJECT(exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);

    gtk_box_pack_start(GTK_BOX(box), toolbar, FALSE, FALSE, 5);
}

static GtkWidget *create_window_main()
{
    GtkWidget *window;
    GtkWidget *toolbar;
    GtkToolItem *open, *save, *new, *sep, *exit;
    GtkWidget *button;
    GtkWidget *image;
    GtkWidget *box;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "graphlayout viewer");

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_vbox_new(FALSE, 0);
    create_window_toolbar(box);

    image  = gtk_image_new();
    gtk_widget_set_size_request(GTK_WIDGET(image), 800, 600);
    gtk_box_pack_start(GTK_BOX(box), image, TRUE, TRUE, 0);

    g_signal_connect(image, "expose-event", G_CALLBACK(on_expose_event), NULL);

    gtk_container_add (GTK_CONTAINER(window), box);

    render_image = image;
    return window;
}

int main (int argc, char *argv[])
{
    command_line_option *option = command_line_option_constructor(argc, argv);

    printf("verbose: %d\n", option->use_verbose);
    printf("version: %d\n", option->use_version);

    gtk_init(&argc, &argv);

    window = create_window_main();

    gtk_widget_show_all(window);
    gtk_main();

    layout_document_destructor(document);
    command_line_option_destruction(option);
    return 0;
}

#include <gtk/gtk.h>


/* ────────────────────────────────────────────────
   Main Window Activate Callback
   ──────────────────────────────────────────────── */
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *paned;
    GtkWidget *stack;
    GtkWidget *sidebar;
    GtkCssProvider *provider;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Welcome to Windlite Linux");
    gtk_window_set_default_size(GTK_WINDOW(window), 1000, 500);


    GtkIconTheme *theme = gtk_icon_theme_get_for_display(gdk_display_get_default());
    gtk_icon_theme_add_resource_path(theme, "/com/windlitelinux/images");
    gtk_window_set_icon_name(GTK_WINDOW(window), "app-icon");

    provider = gtk_css_provider_new();
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), main_box);

    paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_box_append(GTK_BOX(main_box), paned);

    GtkWidget *sidebar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_paned_set_start_child(GTK_PANED(paned), sidebar_box);
    gtk_widget_set_vexpand(sidebar_box, TRUE);

    stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 250);

    sidebar = gtk_stack_sidebar_new();
    gtk_stack_sidebar_set_stack(GTK_STACK_SIDEBAR(sidebar), GTK_STACK(stack));

    gtk_box_append(GTK_BOX(sidebar_box), sidebar);
    gtk_widget_set_size_request(sidebar, 150, -1);
    gtk_widget_set_vexpand(sidebar, TRUE);

    gtk_paned_set_end_child(GTK_PANED(paned), stack);

    GtkWidget *welcome_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(welcome_box, 20);
    gtk_widget_set_margin_start(welcome_box, 20);
    gtk_widget_set_margin_end(welcome_box, 20);

    GtkWidget *image = gtk_image_new_from_resource("/com/windlitelinux/images/windlite-welcome.png");
    gtk_image_set_pixel_size(GTK_IMAGE(image), 200);
    gtk_widget_set_halign(image, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(image, GTK_ALIGN_START);
    gtk_box_append(GTK_BOX(welcome_box), image);

    g_object_set_data(G_OBJECT(window), "welcome_image", image);

    GtkWidget *welcome_label = gtk_label_new(
        "Welcome to Windlite Linux!\n\n"
        "This tool explains the basics of your new system and environment.\n"
        "Use the menu on the left to explore the topics."
    );
    gtk_label_set_wrap(GTK_LABEL(welcome_label), TRUE);
    gtk_label_set_justify(GTK_LABEL(welcome_label), GTK_JUSTIFY_CENTER);
    gtk_widget_set_halign(welcome_label, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(welcome_box), welcome_label);

    gtk_stack_add_titled(GTK_STACK(stack), welcome_box, "welcome", "Welcome");

    
#   define ADD_TEXT_TAB(id, title, text) do { \
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); \
        gtk_widget_set_margin_top(box, 30); \
        gtk_widget_set_margin_start(box, 30); \
        gtk_widget_set_margin_end(box, 30); \
        GtkWidget *label = gtk_label_new(text); \
        gtk_label_set_wrap(GTK_LABEL(label), TRUE); \
        gtk_box_append(GTK_BOX(box), label); \
        gtk_stack_add_titled(GTK_STACK(stack), box, id, title); \
    } while(0)

    ADD_TEXT_TAB("keys", "Hyprland",
        "Keybinds\n"
        "To modify feel free to use hyprviz or edit `~/.config/hypr/hyprland.conf`\n\n"
        "• SUPER + R → App launcher (w/ wofi)\n"
        "• SUPER + T → Open Terminal (w/ ghostty)\n"
        "• SUPER + E → File manager (w/ dolphin)\n"
        "• SUPER + Q → Close window\n"
        "• SUPER + V → Toggle floating window\n"
        "• SUPER + S → Open Settings (w/ kando)\n"
        "• SUPER + M → Logout Menu (wlogout)\n"
        "• SUPER + A → Maximize Window\n"
        "• SUPER + F → Fullscreen Window\n"
        "• SUPER + [1-0] → Switch workspace\n"
        "• SUPER + SHIFT + [1-0] → Move window to workspace\n"
        "• SUPER + [Any Arrow Key] → Move focus to adjacent window\n"
        "• SUPER + Drag Left → Move window\n"
        "• SUPER + Drag Right → Resize window\n"
        "• PRINT → Screenshot\n"
        "\nConfig files:\n"
        "~/.config/hypr/hyprland.conf\n"
        "\nScroll with SUPER to switch workspaces.\n"
    );

    ADD_TEXT_TAB("kando", "Settings",
        "Settings Menu\n"
        "Our Settings are powered by lots of apps and tools for your convenience.\n"
        "Kando is just the frontend to access them all easily.\n\n"
        "To open Kando use the Shortcut: SUPER + S\n\n"
        "This menu quick access to:\n\n"
        "• Sound (w/ pavucontrol)\n"
        "• Network (w/ nm-connection-editor)\n"
        "• Disks (w/ gparted)\n"
        "• Hardware Info (w/ hardinfo2)\n"
        "• Waybar Configurator GUI\n"
        "• Hyprland Configuration (w/ hyprviz)\n"
    );

    ADD_TEXT_TAB("waybar", "Waybar",
        "Waybar (Top Bar)\n\n"
        "Waybar shows your system status:\n"
        "• Time & Date\n"
        "• Workspaces\n"
        "• Audio volume\n"
        "• Network status\n"
        "• Battery\n"
        "• Custom modules\n"
        "\nConfig files:\n"
        "~/.config/waybar/config.jsonc\n"
        "~/.config/waybar/style.css\n"
    );

    GtkWidget *finish_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_top(finish_box, 40);
    gtk_widget_set_margin_start(finish_box, 20);

    GtkWidget *finish_label = gtk_label_new(
        "You are ready!\n"
        "Click the button below to close this guide.\n\n\nmeow.\n"
    );
    gtk_label_set_wrap(GTK_LABEL(finish_label), TRUE);
    gtk_box_append(GTK_BOX(finish_box), finish_label);

    GtkWidget *close_button = gtk_button_new_with_label("Close");
    gtk_box_append(GTK_BOX(finish_box), close_button);

    g_signal_connect_swapped(close_button, "clicked",
        G_CALLBACK(gtk_window_destroy), window);

    gtk_stack_add_titled(GTK_STACK(stack), finish_box, "finish", "Finish");

    gtk_window_present(GTK_WINDOW(window));
}

extern GResource *resources_get_resource(void);

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;

    g_resources_register(resources_get_resource());
    
    app = gtk_application_new("com.windlite.welcome", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

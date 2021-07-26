#include "lubadh_interface.h"

ChannelUI::ChannelUI() {
    /* BUTTON OPTIONS */
    button_option.border = false;

    /* FILE MENU INIT */
    fileselected = 0;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("./audio")) != NULL) {
    /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            std::string s = ent->d_name;
            std::wstring filename(s.begin(), s.end());

            if(s != "." && s!= "..")
                filenames.push_back(filename);
        }
        closedir (dir);
    } 
    else {
        /* could not open directory */
        perror ("");
    }
    std::sort(filenames.begin(), filenames.end());

    filemenu = Radiobox(&filenames, &fileselected);

    /* SLIDER INIT */
    speed=0;
    length=0;
    start_pos=0;
    time=0;

    speed_slider = Slider(L"Speed         :", &speed, 0, 4096, 1);
    length_slider =Slider(L"Length        :", &length, 0, 4096, 1);
    start_pos_slider = Slider(L"Start Position:", &start_pos, 0, 4096, 1);
    time_slider =  Slider(L"Time          :", &time, 0, 4096, 1);

    /* BUTTON INIT */
    record_button = Button(L"[RECORD]", [this] {}, &button_option);
    erase_button = Button(L"[ERASE]", [this] {}, &button_option);
    retrig_button = Button(L"[RETRIG]", [this] {}, &button_option);
    save_button = Button(L"[SAVE]", [this] {}, &button_option);
    load_button = Button(L"[LOAD]", [this] {}, &button_option);
    export_button = Button(L"[USB EXPORT]", [this] {}, &button_option);
    import_button = Button(L"[USB IMPORT]", [this] {}, &button_option);

    /* TOGGLE INIT */
    monitoring_mode_selected = 0;
    time_mode_selected = 0;
    play_mode_selected = 0; 
    record_mode_selected = 0; 
    punch_in_mode_selected = 0;

    monitoring_mode_options = {L"on", L"arm", L"off"};
    time_mode_options = {L"clk div", L"tape decay", L"windowing"};
    play_mode_options = {L"looping", L"one-shot"};
    record_mode_options = {L"looping", L"one-shot"};
    punch_in_mode_options = {L"on", L"off"};

    monitoring_mode_toggle = Toggle(&monitoring_mode_options, &monitoring_mode_selected);
    time_mode_toggle = Toggle(&time_mode_options, &time_mode_selected);
    play_mode_toggle = Toggle(&play_mode_options, &play_mode_selected);
    record_mode_toggle = Toggle(&record_mode_options, &record_mode_selected);
    punch_in_mode_toggle = Toggle(&punch_in_mode_options, &punch_in_mode_selected);

    /* CHANNEL CONTAINER AND RENDERER */
    channelContainer = channelContainer = Container::Vertical({
        /* Sliders */
        speed_slider,
        length_slider,
        start_pos_slider,
        time_slider,
        /* Buttons and menu */
        Container::Horizontal({
            /* Buttons */
            Container::Vertical({
                record_button,
                erase_button,
                retrig_button,
                save_button,
                load_button,
                export_button,
                import_button,
            }),
            /* Menu */
            filemenu,
        }),
        /* Toggles */
        monitoring_mode_toggle,
        time_mode_toggle,
        play_mode_toggle,
        record_mode_toggle,
        punch_in_mode_toggle,
    });

    channelRenderer = Renderer(channelContainer, [this] {
        /* Loop display constants */
        float start_fl = start_pos/4096.f;
        float end_fl = ((start_pos + length)%4096)/4096.f;

        /* Slider box */
        Element sliderbox = vbox({
            hbox({                
                speed_slider->Render(),
                text(std::to_wstring(speed)),
            }) | xflex,
            hbox({                
                length_slider->Render(),
                text(std::to_wstring(length)),
            }) | xflex,
            hbox({                
                start_pos_slider->Render(),
                text(std::to_wstring(start_pos)),
            }) | xflex,
            hbox({                
                time_slider->Render(),
                text(std::to_wstring(time)),
            }) | xflex,
        });

        Element buttonbox = hbox({
            vbox({ 
                record_button->Render(),
                erase_button->Render(),
                retrig_button->Render(),
                save_button->Render(),
                load_button->Render(),
                export_button->Render(),
                import_button->Render(),
            }) | xflex | border,
            filemenu->Render() | xflex | border,
        });

        Element togglebox = vbox({
            hbox({
                text(L"Monitoring Mode: "),
                monitoring_mode_toggle->Render(),
            }),
            hbox({
                text(L"Time Mode:       "),
                time_mode_toggle->Render(),
            }),
            hbox({
                text(L"Play Mode:       "),
                play_mode_toggle->Render(),
            }),
            hbox({
                text(L"Record Mode:     "),
                record_mode_toggle->Render(),
            }),
            hbox({
                text(L"Punch In Mode:   "),
                punch_in_mode_toggle->Render(),
            }),
        });

        Element runtimeinfobox = vbox({
            text(L"Runtime info: "),
        });

        return vbox({
                window(text(L"Sliders"), sliderbox),
                window(text(L"Buttons"), buttonbox),
                window(text(L"Toggles"), togglebox),
                window(text(L"Runtime Info"), runtimeinfobox),
                // loopdisplay(0.5, start_fl, end_fl),
                std::make_shared<LoopDisplay>(0.5, start_fl, end_fl),
            })  | border | bold;
        });
}

MainDisplay::MainDisplay() {
    left = ChannelUI();
    right = ChannelUI();
    tab_index = 0;
    tab_entries = {L"Left", L"Right",};
    tab_selection = Toggle(&tab_entries, &tab_index);
    tab_content = Container::Tab({
        left.getRenderer(),
        right.getRenderer(),
    }, &tab_index);

    main_container = Container::Vertical({
        tab_selection,
        tab_content,
    });

    main_renderer = Renderer(main_container, [&] {
        Element box = vbox({
            tab_selection->Render() | hcenter,
            tab_content->Render() | flex,
        });
        return window(text(L"Lubadh"), box);
    });
}

void MainDisplay::start() {
    
    screen.Loop(main_renderer);
}
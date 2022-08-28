#include "main.h"

int main(int argc, char **argv) {
	std::filesystem::path path;
    auto argc1 = 1;
	auto app = Gtk::Application::create(argc1, argv, "org.gtk-hooya-viewer");
	gflags::SetUsageMessage("hooya-viewer <file or directory>");
	gflags::SetVersionString("hyperalpha");
	gflags::ParseCommandLineNonHelpFlags(&argc, &argv, true);

	if (FLAGS_help || (argc > 1 && !strcmp(argv[1], "help"))) {
		FLAGS_help = false;
		FLAGS_helpshort = true;
	}

	gflags::HandleCommandLineHelpFlags();

    if (argc <= 1) {
        std::cerr  << gflags::ProgramUsage() << std::endl;
        return EXIT_FAILURE;
    }

	path = argv[1];
    if (std::filesystem::is_directory(path)) {
        printf("%s\n", path.string().c_str());
	    MainWindow main(path);
        return app->run(main);
    } else if (std::filesystem::is_regular_file(path)) {
        Glib::RefPtr<Gdk::Pixbuf> src;

        try {
            src = Gdk::Pixbuf::create_from_file(path);
        } catch (Gdk::PixbufError &e) {
            switch(e.code()) {
            case Gdk::PixbufError::CORRUPT_IMAGE:
            case Gdk::PixbufError::INSUFFICIENT_MEMORY:
            case Gdk::PixbufError::BAD_OPTION:
            case Gdk::PixbufError::UNKNOWN_TYPE:
            case Gdk::PixbufError::UNSUPPORTED_OPERATION:
            case Gdk::PixbufError::FAILED:
            case Gdk::PixbufError::INCOMPLETE_ANIMATION:
                return EXIT_FAILURE;
            }
        }

        SingleImageWindow single(src);
        return app->run(single);
    }

    std::cerr << gflags::ProgramUsage() << std::endl;
    return EXIT_FAILURE;
}

#include "main.h"

int main(int argc, char **argv) {
	int argc1;
	std::filesystem::path dir;

	if (argc > 1) {
		dir = argv[1];
		if (!std::filesystem::exists(dir)) {
			std::cerr << "Directory does not exist!" << std::endl;
			return 1;
		}
	} else {
		std::cerr << "Must provide a directory path!" << std::endl;
		return 1;
	}

	argc1 = 1;
	auto app = Gtk::Application::create(argc1, argv, "org.gtk-hooya-viewer");

	MainWindow main(dir);

	return app->run(main);
}

#include "./Typedefs.hpp"
#include "./Application.hpp"

#include <cstdio>

int main(int argc, char** argv) {
	try {
		Application* application = new Application();
		application->Run();
		delete application;
	} catch (const char* error) {
		printf("%s\n", error); // TODO: Find some other way to do this. This is terrible
		return -1;
	}

	return 0;
}

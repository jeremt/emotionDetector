
#include "utils/Log.hpp"
#include "Application.hpp"

int main() {
  LOG_LEVEL(utils::Log::kDebug);
	Application app;
	app.run();
	return 0;
}

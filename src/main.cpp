
#include "utils/Log.hpp"
#include "Application.hpp"

int main(int argc, char **argv) {

  LOG_LEVEL(utils::Log::kDebug);

  try {

    utils::Command command;
    command
        .setSynopsis("[options]")
        .setDescription("This application detect people emotions. You can "
                        "choose the input data set to use for the detection. "
                        "Finally, you can automaticaly update data set json "
                        " and picture using the application.")
        .addOpt("path", "data.json", "the path to the dataset's config file");

    if (command.parse(argc, argv) == false)
      return 1;
    LOG_INFO << "ok" << LOG_ENDL;
    Application app;
    app.run(command);

  } catch (std::exception const &e) {
    LOG_ERR << "exception thrown \"" << e.what() << "\"" << LOG_ENDL;
  }

	return 0;
}


#include "utils/Log.hpp"
#include "Application.hpp"

int main(int argc, char **argv) {

  try {

    // Initialize command-line settings
    utils::Command command;
    command
        .setSynopsis("[options]")
        .setDescription("This application detect people emotions. You can "
                        "choose the input data set to use for the detection. "
                        "Finally, you can automaticaly update data set json "
                        " and picture using the application.")
        .addOpt("path", "data.json", "the path to the dataset's config file")
        .addOpt("log", "debug", "the log-level (debug, info, warning, error)");

    if (command.parse(argc, argv) == false)
      return 1;

    // Set the current log-level
    if (command.getOpt<std::string>("log") == "debug")
      LOG_LEVEL(utils::Log::kDebug);
    else if (command.getOpt<std::string>("log") == "info")
      LOG_LEVEL(utils::Log::kInfo);
    else if (command.getOpt<std::string>("log") == "warning")
      LOG_LEVEL(utils::Log::kWarning);
    else if (command.getOpt<std::string>("log") == "error")
      LOG_LEVEL(utils::Log::kError);

    // Start the application
    Application app;
    app.run(command);

  } catch (std::exception const &e) {
    LOG_ERR << "exception thrown \"" << e.what() << "\"" << LOG_ENDL;
  }

	return 0;
}

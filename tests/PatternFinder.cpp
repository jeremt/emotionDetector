
#include <highgui.h>
#include "brain/PatternFinder.hpp"
#include "testy.hpp"
#include "utils/Log.hpp"

Suite("PatternFinder", {

  LOG_LEVEL(utils::Log::kError);

  brain::PatternFinder finder;

  describe("Detection of happy and sad emotions",

    it("Should detect emotions from famous politics",
      finder.loadFromJson("data.json");
      test(finder.find(cvLoadImage("tests/obama_sad.jpg")) == "sad");
      test(finder.find(cvLoadImage("tests/obama_happy.jpg")) == "happy");
      test(finder.find(cvLoadImage("tests/hollande_sad.jpg")) == "sad");
      test(finder.find(cvLoadImage("tests/hollande_happy.jpg")) == "happy");
    ),

    it("Should detect emotions from facebook friends' photos",
      test(true);
    ),

    it("Should detect emotions from actors and singers",

    )

  )

})

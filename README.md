emotionDetector
===============

Simple machine learning program to detect people emotions.

Usage
-----

The project provide a cmake compilation. On window, the cmake application will generate a solution for unit tests and for the training/test program. On linux you can simply use `run.sh` program:

```
./run.sh help
```

Create a dataset
----------------

A dataset is composed by a json file which contains set's meta-data, and a folder which contains the actual data.

The json meta-data file is formated like this:

```json
{
  "dataDir": "~/Projects/Epitech/emotionDetector/data",
  "patterns": {
    "happy": ["happy_0.png", "happy_1.png"],
    "sad": ["sad_0.png", "sad_1.png"]
  }
}
```

The data folder contains:

- __haarcascade_frontalface_default.xml__ - used for face detection using OpenCV
- __patternName_num.png__ - files which are the images for each different patterns.


Description
-----------

### CvWrapper

Simple wrapper of OpenCV library.

### Brain

This module will do the "magic stuff", indeed it will learn and detects emotions from other images.

### Utils

Provide some C++ utilities.

TODO
----

- Update GUI
- Finish DataGenerator
- Find why is it so slow...
- Try to detect more emotions (Ekman emotions: anger, disgust, fear, happiness, sadness and surprise)
- Try to create a plugin
- Try to use neuronal network library (FAAN?)

License
-------

The MIT License (MIT)

Copyright (c) 2013 taboada.jeremie@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

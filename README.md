# qt_light
mqtt controlled light GUI implimented with QT

hardcode to use `localhost` and `port 1883` for now

tested with mosquetto broker

uses mosquetto library

# Steps to use
* open __config__ to set _subcribe topics_
  * __Room name:__ location of the light (only switches in this room can control this light)
  * __Primary Switch name:__ must be unique (entrance, master, readingLight, ...)
  * __Secondary Switch name:__ optional, double pole, room master
  * automatically subscribes to switch level if switch supports it but only from Primary
* __connect__ to mosquetto broker
  * light will monitor subscribed topics and act on them
* __disconnect__


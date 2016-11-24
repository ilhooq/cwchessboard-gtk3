# Cwchessboard GTK3+ widget

This is the GTK3+ portage from the original [cwchessboard](http://carlowood.github.io/cwchessboard/) project written for GTK2+

## Build dependencies

Required packages : autoconf automake libgtk-3-dev libgtkmm-3.0-dev libcppunit-dev libboost-dev

Optional packages : libcwd

## Build instructions

```bash
$ CWAUTOMACROSPREFIX=/some/writeable/directory ./autogen.sh
$ ./configure
$ make
```

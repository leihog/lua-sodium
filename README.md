lua-sodium
==========

A simple Lua extension providing bindings for
[libsodium](https://github.com/jedisct1/libsodium).


Installation
============

edit Makefile to match your environment then:

    make && sudo make install

Notes
=====

lua-sodium is a work in progress, feedback, bug reports and patches are always welcome.

There's plenty left to do, so far I've only implemented digital signature functions.

Although I'm using (and testing) this on Debian 64bit with Lua 5.1 the ambition
is that lua-sodium (eventually) work with any Lua environment.

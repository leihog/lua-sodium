lua-sodium
==========

A simple Lua extension providing bindings for
[libsodium](https://github.com/jedisct1/libsodium).


Installation
============

edit Makefile to match your environment then:

    make && sudo make install


Example usage
=============

 
	local sodium = require("sodium");
	local secret, public = sodium.sign_keypair();
	local signed, err = sodium.sign(str, secret);
	if not signed then
        print(err);
        return;
	end

	local msg, err = sodium.sign_open(signed, public);
	if not msg then
        print("verification failed");
        return;
	else
        print("signature verified");
	end

Notes
=====

lua-sodium is a work in progress, feedback, bug reports and patches are always welcome.

There's plenty left to do, so far I've only implemented digital signature functions.

Although I'm using (and testing) this on Debian 64bit with Lua 5.1 the ambition
is that lua-sodium (eventually) work with any Lua environment.

local sodium = require("sodium");

local str = "Börna Börje";
local secret, public = sodium.sign_keypair();
local signed, err = sodium.sign(str, secret);
if not signed then
	print(err);
	return;
end

local msg, err = sodium.sign_open(signed, public);
if not msg then
	print(err);
	return;
else
	print(msg);
end

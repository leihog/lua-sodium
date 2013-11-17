/*
 * lua-sodium
 */
#include "lua.h"
#include "lauxlib.h"

#include "sodium.h"

static int sodium_version(lua_State *L) {
	lua_pushstring(L, sodium_version_string());
	return 1;
}

static int sign_keypair(lua_State *L) {

	unsigned char sk[crypto_sign_SECRETKEYBYTES];
	unsigned char pk[crypto_sign_PUBLICKEYBYTES];
	if (crypto_sign_keypair(pk, sk)) {
		lua_pushnil(L);
		lua_pushstring(L, "Failed to create keys.");
		return 2;
	}

	lua_pushlstring(L, (char*)sk, crypto_sign_SECRETKEYBYTES);
	lua_pushlstring(L, (char*)pk, crypto_sign_PUBLICKEYBYTES);
	return 2;
}

static int sign(lua_State *L) {
	size_t mlen;
	unsigned char *msg = NULL;
	msg = (unsigned char *)lua_tolstring(L, 1, &mlen);

	size_t keylen;
	const unsigned char *key = NULL;
	key = (unsigned char*)lua_tolstring(L, 2, &keylen);

	// @todo validate key by checking it's length?

	unsigned long long slen;
	unsigned char sig[mlen + crypto_sign_BYTES];

	if (crypto_sign(sig, &slen, msg, mlen, key) != 0) {
		lua_pushnil(L);
		lua_pushstring(L, "Failed to sign msg");
		return 2;
	}

	lua_pushlstring(L, (char *)sig, slen);
	return 1;
}

static int sign_open(lua_State *L) {
	size_t slen;
	unsigned long long mlen;
	unsigned char *smsg = NULL;

	smsg = (unsigned char *)lua_tolstring(L, 1, &slen);
	unsigned char msg[slen];

	size_t klen;
	unsigned char *key;
	key = (unsigned char *)lua_tolstring(L, 2, &klen);
	if (klen != crypto_sign_PUBLICKEYBYTES) {
		lua_pushnil(L);
		lua_pushstring(L, "Invalid sign key");
		return 2;
	}

	if (crypto_sign_open(msg, &mlen, smsg, slen, key) != 0) {
		lua_pushnil(L);
		lua_pushstring(L, "Verification failed");
		return 2;
	}

	lua_pushlstring(L, (char *)msg, mlen);
	return 1;
}

static const luaL_reg sodiumlib[] = {
	{"version",         sodium_version},
	{"sign_keypair",    sign_keypair},
	{"sign",            sign},
	{"sign_open",       sign_open},
	{NULL, NULL}
};

#if !defined LUA_VERSION_NUM || LUA_VERSION_NUM == 501
/*
 * http://lua-users.org/wiki/CompatibilityWithLuaFive
 */
static void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup) {
	luaL_checkstack(L, nup, "too many upvalues");
	for (; l->name != NULL; l++) {  /* fill the table with given functions */
		int i;
		for (i = 0; i < nup; i++)  /* copy upvalues to the top */
			lua_pushvalue(L, -nup);
		lua_pushstring(L, l->name);
		lua_pushcclosure(L, l->func, nup);  /* closure with those upvalues */
		lua_settable(L, -(nup + 3));
	}
	lua_pop(L, nup);  /* remove upvalues */
}
#endif

LUALIB_API int luaopen_sodium (lua_State *L) {
	if (sodium_init() != 0) {
		lua_pushstring(L, "Failed to initialize libsodium.");
		return lua_error(L);
	}

	lua_newtable(L);
	luaL_setfuncs(L, sodiumlib, 0);
	return 1;
}

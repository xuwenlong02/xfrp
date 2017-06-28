#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include <syslog.h>
#include <sys/utsname.h>

#include "ini.h"
#include "uthash.h"
#include "config.h"
#include "client.h"
#include "debug.h"
#include "msg.h"
#include "version.h"
#include "login.h"

static struct login 		*c_login;

char *get_run_id()
{
	return c_login->run_id;
}

struct login *get_common_login_config()
{
	return c_login;
}

int is_logged()
{
	return c_login->logged;
}

void init_login()
{
	if (! c_login) 
		c_login = calloc(sizeof(struct login), 1);
	assert(c_login);

	struct common_conf *c_conf = get_common_config();
	assert(c_conf);
	
	struct utsname uname_buf;
	if (uname(&uname_buf)) {
		return;
	}

	c_login->version 		= strdup(PROTOCOL_VERESION);
	c_login->hostname 		= NULL;
	c_login->os 				= strdup(uname_buf.sysname);
	c_login->arch 			= strdup(uname_buf.machine);
	c_login->user 			= NULL;

	c_login->timestamp 		= 0;
	c_login->run_id 		= NULL;
	c_login->pool_count 	= 1;//TODO
	c_login->privilege_key 	= NULL; //TODO
	c_login->user			= c_conf->user;

	c_login->logged 		= 0;
}
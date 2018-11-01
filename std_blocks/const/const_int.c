/*
 * An constant value interaction.
 */

/* #define DEBUG 1 */

#include <stdio.h>
#include <stdlib.h>

/* #define DEBUG 1 */
#include "ubx.h"

/* mongoose is GPLv2, thus the block is too */
UBX_MODULE_LICENSE_SPDX(GPL-2.0)

char const_int_meta[] =
	"{ doc='const int interaction',"
	"  realtime=false,"
	"}";

ubx_config_t const_int_config[] = {
	{ .name="value", .type_name = "int" },
	{ NULL },
};

struct blk_inf {
	ubx_type_t *type;
	int* value;
};


static int const_int_init(ubx_block_t *i)
{
	DBG("");
	int ret = -1;
	struct blk_inf *inf;

	if((i->private_data = calloc(1, sizeof(struct blk_inf)))==NULL) {
		ERR("failed to alloc blk_info");
		ret = EOUTOFMEM;
		goto out;
	}


	inf = (struct blk_inf*) i->private_data;

	inf->type = ubx_type_get(i->ni, "int");

	if(inf->type == NULL) {
		ERR("failed to lookup type int");
		ret = EINVALID_CONFIG;
		goto out;
	}
	ret = 0;
out:
	return ret;
}

static int const_int_start(ubx_block_t *i)
{
	DBG("");
	unsigned int len;
	struct blk_inf *inf;
	inf = (struct blk_inf*) i->private_data;
	inf->value = (int*) ubx_config_get_data_ptr(i, "value", &len);
	return 0;
}

static void const_int_cleanup(ubx_block_t *i)
{
	free(i->private_data);
}

static int const_int_read(ubx_block_t *i, ubx_data_t* data)
{
	DBG("");
	int ret = 0;
	struct blk_inf *inf;
	inf = (struct blk_inf*) i->private_data;

	if(inf->type != data->type) {
		ERR("%s: invalid read target type %s (should be int)",
		    i->name, data->type->name);
		goto out;
	}

	assert(sizeof(int) == data_size(data));
	memcpy(data->data, inf->value, sizeof(int));
	ret = 1;
out:
	return ret;
}


/* put everything together */
ubx_block_t const_int_comp = {
	.name = "consts/const_int",
	.type = BLOCK_TYPE_INTERACTION,
	.meta_data = const_int_meta,
	.configs = const_int_config,

	/* ops */
	.init = const_int_init,
	.start = const_int_start,
	.cleanup = const_int_cleanup,
	.read = const_int_read,
};

static int const_int_mod_init(ubx_node_info_t* ni)
{
	DBG(" ");
	return ubx_block_register(ni, &const_int_comp);
}

static void const_int_mod_cleanup(ubx_node_info_t *ni)
{
	DBG(" ");
	ubx_block_unregister(ni, "const_int/const_int");
}

UBX_MODULE_INIT(const_int_mod_init)
UBX_MODULE_CLEANUP(const_int_mod_cleanup)

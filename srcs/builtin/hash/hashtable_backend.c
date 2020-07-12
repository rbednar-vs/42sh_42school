#include "shell42.h"
#include "hash.h"

char			*hashtable_add(char *key, void **hashtable,
					int hashtable_size, int *index)
{
	char		*path;
	int			i;
	int			hashtable_filled;

	printf("path_search\n");
	path = path_search(key);
	if (!path)
		return (path);
	hashtable_filled = get_hashtable_filled();
	if (hashtable_filled / (hashtable_size - 1) == 1) //change
	{
		// hashtable = ft_realloc_array(&hashtable, hashtable_size, //функция для реаллока void**
		// 	(hashtable_size - 1) * 2 + 1);
		// hashtable_size = (hashtable_size - 1) * 2 + 1;
		change_hastable_value(hashtable, hashtable_size);
	}
	i = 0;
	while (i < hashtable_size)
	{
		if (hashtable[i] == NULL)
		{
			hashtable[i] = init_hash_cell(key, path);
			*index = i;
			return (path);
		}
		i++;
	}

	// i = hashfunction(key);
	// if (hashtable[i] != NULL)
	// 	i = collision_hashtable_add(key);
	// hashtable[i] = init_hash_cell(key, path);
	// *index = i;
	return (path);
}

int				hashtable_delete(char *key, void **hashtable,
					int hashtable_size, int hashtable_filled)
{
	int			index;

	printf("deleting an element\n");
	if (hashtable_filled == 0)
		return (HASHTABLE_NF);
	index = hashtable_find(key, hashtable, hashtable_size);
	if (hashtable_delete_invalid(&index, key, hashtable) == HASHTABLE_NF)
		return (HASHTABLE_NF);
	clear_hash_cell(index, hashtable, SLOT_FILLED_HASH);
	return (0);
}

int				hashtable_delete_invalid(int *index, char *key,
					void **hashtable)
{
	t_hashcmd	*slot_ptr;
	int			collision_index;
	
	printf("check if deleting an element is valid\n");
	if (*index == HASHTABLE_NF || hashtable[*index] == NULL)
		return (HASHTABLE_NF);
	slot_ptr = (t_hashcmd*)hashtable[*index];
	if (ft_strcmp(key, slot_ptr->cmd_name) == 0 &&
			slot_ptr->slot_state == SLOT_DELETED_HASH)
		return (HASHTABLE_NF);
	else if (ft_strcmp(key, slot_ptr->cmd_name))
	{
		collision_index = collision_hashtable_find(*index, key);
		if (collision_index == HASHTABLE_NF ||
				hashtable[collision_index] == NULL)
			return (HASHTABLE_NF);
		slot_ptr = (t_hashcmd*)hashtable[collision_index];
		if (ft_strcmp(key, slot_ptr->cmd_name) == 0 &&
			slot_ptr->slot_state == SLOT_DELETED_HASH)
		return (HASHTABLE_NF);
		*index = collision_index;
	}
	return (0);
}

int				hashtable_clean(void **hashtable,
					int hashtable_size)
{
	int				i;
	t_hashcmd		*hash_cell_ptr;

	i = 0;
	printf("cleaning the table\n");	
	while (i < hashtable_size)
	{
		if (hashtable[i] != NULL)
		{
			hash_cell_ptr = (t_hashcmd*)hashtable[i];
			clear_hash_cell(i, hashtable, 0);
		}
		i++;
	}
	change_hashtable_filled_value(0);
	return (0);
}
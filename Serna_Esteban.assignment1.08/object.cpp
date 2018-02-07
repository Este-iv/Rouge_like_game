#include <stdlib.h>
#include <string>

#include "utils.h"
#include "object.h"
#include "dungeon.h"
#include "descriptions.h"




void del_obj(object *n)
{
  if (n) {
    free(n);
  }
}

void object_gn(dungeon_t *d)
{
  uint32_t i;
  object *o;
  uint32_t room;
  pair_t p;

  for (i = 0; i < 20; i++) {
     o = new object;
    memset(o, 0, sizeof (*o));

    do {
      room = rand_range(1, d->num_rooms - 1);
      p[dim_y] = rand_range(d->rooms[room].position[dim_y],
                            (d->rooms[room].position[dim_y] +
                             d->rooms[room].size[dim_y] - 1));
      p[dim_x] = rand_range(d->rooms[room].position[dim_x],
                            (d->rooms[room].position[dim_x] +
                             d->rooms[room].size[dim_x] - 1));
    } while (d->character_map[p[dim_y]][p[dim_x]]);
    int q;
    q = rand() % d->object_descriptions.size();
    o->position[dim_y] = p[dim_y];
    o->position[dim_x] = p[dim_x];
    d->object_map[p[dim_y]][p[dim_x]] = o;
    o->speed = d->object_descriptions[q].speed.roll();
    o->color = d->object_descriptions[q].get_color();

    o->descriptions = &d->object_descriptions[q].get_description();
    o->name = &d->object_descriptions[q].name;
    o->hit = d->object_descriptions[q].hit.roll();
    o->damage = d->object_descriptions[q].damage;
    o->dodge = d->object_descriptions[q].dodge.roll();
    o->defence = d->object_descriptions[q].defence.roll();
    o->weight = d->object_descriptions[q].weight.roll();
    o->attribute = d->object_descriptions[q].attribute.roll();
    o->value = d->object_descriptions[q].value.roll();
    o->symbol = object_symbol[d->object_descriptions[q].type];
    o->io = 0;
    d->object_map[p[dim_y]][p[dim_x]] = o;

  }
}
int16_t *obj_pos(object *o){return o->position;}

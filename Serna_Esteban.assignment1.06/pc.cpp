#include <stdlib.h>
#include <iostream>

#include "string.h"

#include "character.h"
#include "dungeon.h"
#include "pc.h"
#include "utils.h"
#include "move.h"
#include "path.h"
#include "io.h"
/*
C++ code goes here
*/




void pc_delete(pc_t *pc)
{
  if (pc) {
    free(pc);
  }
}

uint32_t pc_is_alive(dungeon_t *d)
{
  return d->pc->alive;
}

void place_pc(dungeon_t *d)
{
  set_y(d->pc, rand_range(d->rooms->position[dim_y],
                                     (d->rooms->position[dim_y] +
                                      d->rooms->size[dim_y] - 1)));
  set_x(d->pc, rand_range(d->rooms->position[dim_x],
                                     (d->rooms->position[dim_x] +
                                      d->rooms->size[dim_x] - 1)));
}

void config_pc(dungeon_t *d)
{

    memset(&d->pc, 0, sizeof (d->pc));
    d->pc = new character_t;
  d->pc->symbol = '@';

  place_pc(d);

  d->pc->speed = PC_SPEED;
  d->pc->alive = 1;
  d->pc->sequence_number = 0;
  // d->pc = calloc(1, sizeof (*d->pc));
  // d->npc_t = NULL;
  // d->pc->kills[kill_direct] = d->pc->kills[kill_avenged] = 0;

  d->character[get_y(d->pc)][get_x(d->pc)] = d->pc;

  dijkstra(d);
  dijkstra_tunnel(d);

  io_calculate_offset(d);
}

uint32_t pc_next_pos(dungeon_t *d, pair_t dir)
{
  static uint32_t have_seen_corner = 0;
  static uint32_t count = 0;

  dir[dim_y] = dir[dim_x] = 0;

  if (in_corner(d, d->pc)) {
    if (!count) {
      count = 1;
    }
    have_seen_corner = 1;
  }

  /* First, eat anybody standing next to us. */
  if (charxy(get_x(d->pc) - 1, get_y(d->pc) - 1)) {
    dir[dim_y] = -1;
    dir[dim_x] = -1;
  } else if (charxy(get_x(d->pc), get_y(d->pc) - 1)) {
    dir[dim_y] = -1;
  } else if (charxy(get_x(d->pc) + 1, get_y(d->pc) - 1)) {
    dir[dim_y] = -1;
    dir[dim_x] = 1;
  } else if (charxy(get_x(d->pc) - 1, get_y(d->pc))) {
    dir[dim_x] = -1;
  } else if (charxy(get_x(d->pc)+ 1, get_y(d->pc))) {
    dir[dim_x] = 1;
  } else if (charxy(get_x(d->pc) - 1, get_y(d->pc) + 1)) {
    dir[dim_y] = 1;
    dir[dim_x] = -1;
  } else if (charxy(get_x(d->pc), get_y(d->pc)+ 1)) {
    dir[dim_y] = 1;
  } else if (charxy(get_x(d->pc) + 1,get_y(d->pc) + 1)) {
    dir[dim_y] = 1;
    dir[dim_x] = 1;
  } else if (!have_seen_corner || count < 250) {
    /* Head to a corner and let most of the NPCs kill each other off */
    if (count) {
      count++;
    }
    if (!against_wall(d, d->pc) && ((rand() & 0x111) == 0x111)) {
      dir[dim_x] = (rand() % 3) - 1;
      dir[dim_y] = (rand() % 3) - 1;
    } else {
      dir_nearest_wall(d, d->pc, dir);
    }
  }else {
    /* And after we've been there, let's head toward the center of the map. */
    if (!against_wall(d, d->pc) && ((rand() & 0x111) == 0x111)) {
      dir[dim_x] = (rand() % 3) - 1;
      dir[dim_y] = (rand() % 3) - 1;
    } else {
      dir[dim_x] = ((get_x(d->pc) > DUNGEON_X / 2) ? -1 : 1);
      dir[dim_y] = ((get_y(d->pc) > DUNGEON_Y / 2) ? -1 : 1);
    }
  }

  /* Don't move to an unoccupied location if that places us next to a monster */
  if (!charxy(get_x(d->pc) + dir[dim_x],
              get_y(d->pc) + dir[dim_y]) &&
      ((charxy(get_x(d->pc)+ dir[dim_x] - 1,
               get_y(d->pc) + dir[dim_y] - 1) &&
        (charxy(get_x(d->pc) + dir[dim_x] - 1,
                get_y(d->pc)+ dir[dim_y] - 1) != d->pc)) ||
       (charxy(get_x(d->pc) + dir[dim_x] - 1,
               get_y(d->pc) + dir[dim_y]) &&
        (charxy(get_x(d->pc) + dir[dim_x] - 1,
                get_y(d->pc) + dir[dim_y]) != d->pc)) ||
       (charxy(get_x(d->pc)+ dir[dim_x] - 1,
               get_y(d->pc) + dir[dim_y] + 1) &&
        (charxy(get_x(d->pc) + dir[dim_x] - 1,
                get_y(d->pc) + dir[dim_y] + 1) != d->pc)) ||
       (charxy(get_x(d->pc) + dir[dim_x],
               get_y(d->pc) + dir[dim_y] - 1) &&
        (charxy(get_x(d->pc) + dir[dim_x],
                get_y(d->pc) + dir[dim_y] - 1) != d->pc)) ||
       (charxy(get_x(d->pc) + dir[dim_x],
               get_y(d->pc) + dir[dim_y] + 1) &&
        (charxy(get_x(d->pc) + dir[dim_x],
                get_y(d->pc) + dir[dim_y] + 1) != d->pc)) ||
       (charxy(get_x(d->pc) + dir[dim_x] + 1,
               get_y(d->pc) + dir[dim_y] - 1) &&
        (charxy(get_x(d->pc) + dir[dim_x] + 1,
                get_y(d->pc) + dir[dim_y] - 1) != d->pc)) ||
       (charxy(get_x(d->pc) + dir[dim_x] + 1,
               get_y(d->pc) + dir[dim_y]) &&
        (charxy(get_x(d->pc) + dir[dim_x] + 1,
                get_y(d->pc) + dir[dim_y]) != d->pc)) ||
       (charxy(get_x(d->pc) + dir[dim_x] + 1,
               get_y(d->pc)+ dir[dim_y] + 1) &&
        (charxy(get_x(d->pc) + dir[dim_x] + 1,
                get_y(d->pc) + dir[dim_y] + 1) != d->pc)))) {
    dir[dim_x] = dir[dim_y] = 0;
  }

  return 0;
}

uint32_t pc_in_room(dungeon_t *d, uint32_t room)
{
  if ((room < d->num_rooms)                                     &&
      (get_x(d->pc) >= d->rooms[room].position[dim_x]) &&
      (get_x(d->pc) < (d->rooms[room].position[dim_x] +
                                d->rooms[room].size[dim_x]))    &&
      (get_y(d->pc) >= d->rooms[room].position[dim_y]) &&
      (get_y(d->pc) < (d->rooms[room].position[dim_y] +
                                d->rooms[room].size[dim_y]))) {
    return 1;
  }

  return 0;
}

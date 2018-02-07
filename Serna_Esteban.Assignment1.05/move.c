#include "move.h"
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "dungeon.h"
#include "heap.h"
#include "move.h"
#include "npc.h"
#include "pc.h"
#include "character.h"
#include "utils.h"
#include "path.h"
#include "event.h"

void do_combat(dungeon_t *d, character_t *atk, character_t *def)
{
  if (def->alive) {
    def->alive = 0;
    if (def != &d->pc) {
      d->num_monsters--;
    }
    atk->kills[kill_direct]++;
    atk->kills[kill_avenged] += (def->kills[kill_direct] +
                                  def->kills[kill_avenged]);
  }
}

void move_character(dungeon_t *d, character_t *c, pair_t next)
{
  if (charpair(next) &&
      ((next[dim_y] != c->position[dim_y]) ||
       (next[dim_x] != c->position[dim_x]))) {
    do_combat(d, c, charpair(next));
  } else {
    /* No character in new position. */

    d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
    c->position[dim_y] = next[dim_y];
    c->position[dim_x] = next[dim_x];
    d->character[c->position[dim_y]][c->position[dim_x]] = c;
  }
}



uint32_t move_pc(dungeon_t *d, pair_t dir) {

    switch (d->getchar) {
        /* upper left*/
        case 121:
            if ((d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] - 1 < 105)) {
                if ((d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] - 1]) < ter_wall) {
                    dir[dim_y] = d->pc.position[dim_y] - 1;
                    dir[dim_x] = d->pc.position[dim_x] - 1;
                }
            }
            break;
        case 55:
            if ((d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] - 1 < 105)) {
                if ((d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] - 1]) < ter_wall) {
                    dir[dim_y] = d->pc.position[dim_y] - 1;
                    dir[dim_x] = d->pc.position[dim_x] - 1;
                }
                break;
            }
                /* up*/
                case 107:
                    if ((d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] < 105)) {
                        if ((d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x]]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] - 1;
                            dir[dim_x] = d->pc.position[dim_x];
                        }
                    }
                break;
                case 56:
                    if ((d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] < 105)) {
                        if ((d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x]]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] - 1;
                            dir[dim_x] = d->pc.position[dim_x];
                        }
                    }
                break;

                /*Upper Right*/
                case 117:
                    if ((d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] + 1 < 105)) {
                        if ((d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] + 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] - 1;
                            dir[dim_x] = d->pc.position[dim_x] + 1;
                        }
                    }
                break;
                case 57:
                    if ((d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] + 1 < 105)) {
                        if ((d->map[d->pc.position[dim_y] - 1][d->pc.position[dim_x] + 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] - 1;
                            dir[dim_x] = d->pc.position[dim_x] + 1;
                        }
                    }
                break;

                /*right*/
                case 54:
                    if ((d->pc.position[dim_y] > 0 && d->pc.position[dim_x] + 1 < 105)) {
                        if ((d->map[d->pc.position[dim_y]][d->pc.position[dim_x] + 1])) {
                            dir[dim_y] = d->pc.position[dim_y];
                            dir[dim_x] = d->pc.position[dim_x] + 1;
                        }
                    }
                break;
                case 108:
                    if ((d->pc.position[dim_y] > 0 && d->pc.position[dim_x] + 1 < 105)) {
                        if ((d->map[d->pc.position[dim_y]][d->pc.position[dim_x] + 1])) {
                            dir[dim_y] = d->pc.position[dim_y];
                            dir[dim_x] = d->pc.position[dim_x] + 1;
                        }
                    }
                break;

                /*lower right*/
                case 110:
                    if ((d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] + 1 < 105)) {
                        if ((d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] + 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] + 1;
                            dir[dim_x] = d->pc.position[dim_x] + 1;
                        }
                    }
                break;
                case 51:
                    if ((d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] + 1 < 105)) {
                        if ((d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] + 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] + 1;
                            dir[dim_x] = d->pc.position[dim_x] + 1;
                        }
                    }
                break;

                /*down*/
                case 106:
                    if ((d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] < 105)) {
                        dir[dim_y] = d->pc.position[dim_y] + 1;
                        dir[dim_x] = d->pc.position[dim_x];
                        if (d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x]] < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] + 1;
                            dir[dim_x] = d->pc.position[dim_x];
                        }
                    }
                break;
                case 50:
                    if ((d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] < 105)) {
                        if ((d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x]]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] + 1;
                            dir[dim_x] = d->pc.position[dim_x];
                        }
                    }
                break;

                /*lower left*/
                case 98:
                    if (d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] - 1 < 105) {
                        if ((d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] - 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] + 1;
                            dir[dim_x] = d->pc.position[dim_x] - 1;
                        }
                    }
                break;
                case 49:
                    if (d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] - 1 < 105) {
                        if ((d->map[d->pc.position[dim_y] + 1][d->pc.position[dim_x] - 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y] + 1;
                            dir[dim_x] = d->pc.position[dim_x] - 1;
                        }
                    }
                break;

                /*left*/
                case 104:
                    if (d->pc.position[dim_y] > 0 && d->pc.position[dim_x] - 1 < 105) {
                        if ((d->map[d->pc.position[dim_y]][d->pc.position[dim_x] - 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y];
                            dir[dim_x] = d->pc.position[dim_x] - 1;
                        }
                    }
                break;
                case 52:
                    if (d->pc.position[dim_y] > 0 && d->pc.position[dim_x] - 1 < 105) {
                        if ((d->map[d->pc.position[dim_y]][d->pc.position[dim_x] - 1]) < ter_wall) {
                            dir[dim_y] = d->pc.position[dim_y];
                            dir[dim_x] = d->pc.position[dim_x] - 1;
                        }
                    }
                break;

                /* space and #5*/
                case 53:
                case 32:
                    break;
                /* Case for the Stairs*/
                case 62:
                case 60:
                    if(d->map[d->pc.position[dim_y]][d->pc.position[dim_x]] == d->stairs->position) {

                        delete_dungeon(d);
                        init_dungeon(d);
                        gen_dungeon(d);
                        config_pc(d);
                        gen_monsters(d);
                        nrender(d);
                    } else
                break;
                /*Case for look mode*/
                case 76:
                    break;
                /*Escapes the Look mode*/
                case 27:
                    break;
                /*Quits the Game.*/
                case 81:
                    break;
            }

//            refresh();
            return 0;

    }



void do_moves(dungeon_t *d) {
    pair_t next;
    character_t *c;
    event_t *e;
    /* Remove the PC when it is PC turn.  Replace on next call.  This allows *
     * use to completely uninit the heap when generating a new level without *
     * worrying about deleting the PC.                                       */

    if (pc_is_alive(d)) {
        /* The PC always goes first one a tie, so we don't use new_event().  *
         * We generate one manually so that we can set the PC sequence       *
         * number to zero.                                                   */
        e = malloc(sizeof(*e));
        e->type = event_character_turn;
        /* The next line is buggy.  Monsters get first turn before PC.  *
         * Monster gen code always leaves PC in a monster-free room, so *
         * not a big issue, but it needs a better solution.             */
        e->time = d->time + (1000 / d->pc.speed);
        e->sequence = 0;
        e->c = &d->pc;
        heap_insert(&d->events, e);
    }

    while (pc_is_alive(d) &&
           (e = heap_remove_min(&d->events)) &&
           ((e->type != event_character_turn) || (e->c != &d->pc))) {
        d->time = e->time;
        if (e->type == event_character_turn) {
            c = e->c;
        }
        if (!c->alive) {
            if (d->character[c->position[dim_y]][c->position[dim_x]] == c) {
                d->character[c->position[dim_y]][c->position[dim_x]] = NULL;
            }
            if (c != &d->pc) {
                event_delete(e);
            }
            continue;
        }

        npc_next_pos(d, c, next);
        move_character(d, c, next);

        heap_insert(&d->events, update_event(d, e, 1000 / c->speed));
    }

    if (pc_is_alive(d) && e->c == &d->pc) {
        c = e->c;
        d->time = e->time;
        /* Kind of kludgey, but because the PC is never in the queue when   *
         * we are outside of this function, the PC event has to get deleted *
         * and recreated every time we leave and re-enter this function.    */
        e->c = NULL;
        event_delete(e);

        int can_mv = 1;
        int quit = 0;

        while (can_mv == 1) {
            move_pc(d, next);

            if (mappair(next) > ter_floor) {
                move_character(d, c, next);
                can_mv = 0;
            }


            dijkstra(d);
            dijkstra_tunnel(d);
        }

    }
}
    void dir_nearest_wall(dungeon_t *d, character_t *c, pair_t dir) {
        dir[dim_x] = dir[dim_y] = 0;

        if (c->position[dim_x] != 1 && c->position[dim_x] != DUNGEON_X - 2) {
            dir[dim_x] = (c->position[dim_x] > DUNGEON_X - c->position[dim_x] ? 1 : -1);
        }
        if (c->position[dim_y] != 1 && c->position[dim_y] != DUNGEON_Y - 2) {
            dir[dim_y] = (c->position[dim_y] > DUNGEON_Y - c->position[dim_y] ? 1 : -1);
        }
    }

    uint32_t against_wall(dungeon_t *d, character_t *c) {
        return ((mapxy(c->position[dim_x] - 1,
                       c->position[dim_y]) == ter_wall_immutable) ||
                (mapxy(c->position[dim_x] + 1,
                       c->position[dim_y]) == ter_wall_immutable) ||
                (mapxy(c->position[dim_x],
                       c->position[dim_y] - 1) == ter_wall_immutable) ||
                (mapxy(c->position[dim_x],
                       c->position[dim_y] + 1) == ter_wall_immutable));
    }

    uint32_t in_corner(dungeon_t *d, character_t *c) {
        uint32_t num_immutable;

        num_immutable = 0;

        num_immutable += (mapxy(c->position[dim_x] - 1,
                                c->position[dim_y]) == ter_wall_immutable);
        num_immutable += (mapxy(c->position[dim_x] + 1,
                                c->position[dim_y]) == ter_wall_immutable);
        num_immutable += (mapxy(c->position[dim_x],
                                c->position[dim_y] - 1) == ter_wall_immutable);
        num_immutable += (mapxy(c->position[dim_x],
                                c->position[dim_y] + 1) == ter_wall_immutable);

        return num_immutable > 1;
    }





//    //checks the input fro getch() and moves the pc.
//    uint32_t move_pc(dungeon_t *d, pair_t dir) {
//
//        switch (d->getchar) {
//            /* upper left*/
//            case 121:
//            case 55:
//                if (d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] - 1 < 105) {
//                    dir[dim_y] = d->pc.position[dim_y] - 1;
//                    dir[dim_x] = d->pc.position[dim_x] - 1;
//                }
//                break;
//                /* up*/
//            case 107:
//            case 56:
//                if (d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] < 105) {
//                    dir[dim_y] = d->pc.position[dim_y] - 1;
//                    dir[dim_x] = d->pc.position[dim_x];
//                }
//                break;
//                /*Upper Right*/
//            case 117:
//            case 57:
//                if (d->pc.position[dim_y] - 1 > 0 && d->pc.position[dim_x] + 1 < 105) {
//                    dir[dim_y] = d->pc.position[dim_y] - 1;
//                    dir[dim_x] = d->pc.position[dim_x] + 1;
//                }
//
//
//                break;
//                /*right*/
//            case 54:
//            case 108:
//                if (d->pc.position[dim_y] > 0 && d->pc.position[dim_x] + 1 < 105) {
//                    dir[dim_y] = d->pc.position[dim_y];
//                    dir[dim_x] = d->pc.position[dim_x] + 1;
//                }
//                break;
//                /*lower right*/
//            case 110:
//            case 51:
//                if (d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] - 1 < 105) {
//                    dir[dim_y] = d->pc.position[dim_y] + 1;
//                    dir[dim_x] = d->pc.position[dim_x] - 1;
//                }
//                break;
//
//                /*down*/
//            case 106:
//            case 50:
//                if (d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] < 105) {
//                    dir[dim_y] = d->pc.position[dim_y] + 1;
//                    dir[dim_x] = d->pc.position[dim_x];
//                }
//                break;
//
//                /*lower left*/
//            case 98:
//            case 49:
//                if (d->pc.position[dim_y] + 1 > 0 && d->pc.position[dim_x] + 1 < 105) {
//                    dir[dim_y] = d->pc.position[dim_y] + 1;
//                    dir[dim_x] = d->pc.position[dim_x] + 1;
//                }
//                break;
//
//                /*left*/
//            case 104:
//            case 52:
//                if (d->pc.position[dim_y] > 0 && d->pc.position[dim_x] - 1 < 105) {
//                    dir[dim_y] = d->pc.position[dim_y];
//                    dir[dim_x] = d->pc.position[dim_x] - 1;
//                }
//                break;
//
//                /* space and #5*/
//            case 5:
//            case 32:
//                break;
//                /* Case for the Stairs*/
//            case 62:
//            case 60:
//
//                delete_dungeon(d);
//                init_dungeon(d);
//                gen_dungeon(d);
//                config_pc(d);
//                gen_monsters(d);
//
//                break;
//                /*Case for look mode*/
//            case 76:
//                break;
//                /*Escapes the Look mode*/
//            case 27:
//                break;
//                /*Quits the Game.*/
//            case 81:
//                break;
//        }
//
//
//        return 1;
//    }
//}
//

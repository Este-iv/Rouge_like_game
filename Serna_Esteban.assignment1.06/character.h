#ifndef CHARACTER_H
# define CHARACTER_H

# include <stdint.h>

# include "dims.h"

typedef enum kill_type {
  kill_direct,
  kill_avenged,
  num_kill_types
} kill_type_t;

# ifdef __cplusplus
class character_t {
public:
  char symbol;
  pair_t position;
  int32_t speed;
  uint32_t alive;
  /* Characters use to have a next_turn for the move queue.  Now that it is *
   * an event queue, there's no need for that here.  Instead it's in the    *
   * event.  Similarly, sequence_number was introduced in order to ensure   *
   * that the queue remains stable.  Also no longer necessary here, but in  *
   * this case, we'll keep it, because it provides a bit of interesting     *
   * metadata: locally, how old is this character; and globally, how many   *
   * characters have been created by the game.                              */
  uint32_t sequence_number;
  uint32_t kills[num_kill_types];
};

#else
typedef void character_t;
# endif
# ifdef __cplusplus
extern "C"{

  #endif
  #include "character.h"
  #include "heap.h"
  #include "npc.h"
  #include "pc.h"
  #include "dungeon.h"



typedef struct dungeon dungeon_t;
int32_t compare_characters_by_next_turn(const void *character1,
                                        const void *character2);
uint32_t can_see(dungeon_t *d, character_t *voyeur, character_t *exhibitionist);
void character_delete(void *c);

int16_t *char_get_pos(character_t *c);
int8_t get_x(const character_t *c);
int8_t get_y(const character_t *c);

void set_x(character_t *c,int8_t x);
void set_y(character_t *c, int8_t y);

uint32_t get_next_turn(const character_t *c);
 void set_life(character_t *c,uint32_t l);
 uint8_t get_life(const character_t *c);
// void next_turn(character_t *c);
// void reset(character_t *c);
char get_symbol(const character_t *c);
void set_symbol(character_t *c, char s);
uint32_t get_speed( const character_t *c);
void set_speed(character_t *c,int32_t s);

uint32_t get_sequence_num(const character_t *c);
void set_sequence_num(character_t *c, uint32_t s);
  # ifdef __cplusplus
}
#endif
#endif

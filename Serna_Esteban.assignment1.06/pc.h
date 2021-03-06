#ifndef PC_H
# define PC_H

# include <stdint.h>

# include "dims.h"
#include "dungeon.h"

typedef struct dungeon dungeon_t;
# ifdef __cplusplus
class pc_t {
public:
  terrain_type_t map[105][160];
} ;
# else
typedef void pc_t;
#endif

# ifdef __cplusplus
extern "C"{

  #endif
  #include "character.h"
  #include "dungeon.h"
  #include "pc.h"
  #include "utils.h"
  #include "move.h"
  #include "path.h"
  #include "io.h"

  void pc_delete(pc_t *pc);
  uint32_t pc_is_alive(dungeon_t *d);
  void config_pc(dungeon_t *d);
  uint32_t pc_next_pos(dungeon_t *d, pair_t dir);
  void place_pc(dungeon_t *d);
  uint32_t pc_in_room(dungeon_t *d, uint32_t room);


  # ifdef __cplusplus
}
#endif
#endif

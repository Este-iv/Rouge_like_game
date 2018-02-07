#ifndef OBJECT_H
#define OBJECT_H

# include <stdint.h>
# include <string>

# include "descriptions.h"
# include "dims.h"
# include "dice.h"
# include "character.h"
// # include "dungeon.h"


class object{
public:
  char symbol;
  std::string *name;
  std::string const *descriptions;
  std::uint32_t color;
  std::int32_t hit;
  dice damage;
  std::int32_t defence;
  std::int32_t weight;
  std::int32_t speed;
  std::int32_t attribute;
  std::int32_t value;
  std::int32_t dodge;

  pair_t position;
  int io ;
};
typedef struct dungeon dungeon_t;
void object_gn(dungeon_t *d);
void del_obj(object *o);
int16_t *obj_pos(object *o);

#endif

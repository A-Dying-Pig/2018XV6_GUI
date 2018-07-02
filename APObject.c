#include "APObject.h"

struct Pos get_view_pos(struct APPos item, struct APPos window)
{
    struct Pos view_pos;
    view_pos.x = item.scene.x - window.scene.x;
    view_pos.y = item.scene.y - window.scene.y;
}

#include "scm.h"

World_t world_g;


SCM scm_von_neumann_neighbors(SCM x_in, SCM y_in, SCM state_in)
{
    int x = scm_to_int(x_in);
    int y = scm_to_int(y_in);
    unsigned char state = scm_to_uchar(state_in);
    return scm_from_int(
        board_count_von_neumann_neighbors(world_g.board, x, y, state));
}

SCM scm_moore_neighbors(SCM x_in, SCM y_in, SCM state_in)
{
    int x = scm_to_int(x_in);
    int y = scm_to_int(y_in);
    unsigned char state = scm_to_uchar(state_in);
    return scm_from_int(
        board_count_moore_neighbors(world_g.board, x, y, state));
}

SCM scm_get_cell(SCM x, SCM y)
{
    return scm_from_uchar(
        board_get_cell(world_g.board, scm_to_int(x), scm_to_int(y)));
}

void *register_scm_functions(void* data)
{
    scm_c_define_gsubr("board-von-neumann-neighbors", 3, 0, 0, &scm_von_neumann_neighbors);
    scm_c_define_gsubr("board-moore-neighbors", 3, 0, 0, &scm_moore_neighbors);
    scm_c_define_gsubr("board-get-cell", 2, 0, 0, &scm_get_cell);
    return NULL;
}

void scm_generate(World_t* world)
{
    unsigned char result_cell;
    SCM func = world->rule->scm_cell_func;

    for (int y = 0; y < world->board->height; y++) {
        for (int x = 0; x < world->board->width; x++) {
            result_cell = scm_to_uchar(scm_call_2(
                func, scm_from_int(x), scm_from_int(y)));
            board_set_cell(world->next_board, x, y, result_cell);
        }
    }
}
#define MOVE_CURSOR(foucused_position,direction_operator,higher_lower_operator,end_of_field) { foucused_position direction_operator; foucused_position = (foucused_position higher_lower_operator end_of_field) ? end_of_field : foucused_position; }
#define ARRAY_LEN(x) (sizeof(x) / sizeof((x)[0]))

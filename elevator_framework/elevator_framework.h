#ifndef ELEVATORS_FRAMEWORK
#define ELEVATORS_FRAMEWORK
#include <stdbool.h>

#define ELEVATORS_QUANTITY 3 
#define BUTTONS_NUMBER 9

typedef struct elevator_status{
    int id;
    int current_floor;
    int target_floor;
    bool buttons[BUTTONS_NUMBER];
    bool door_open;
    int btn_floor_offset;

} elevator_status;


struct request_orders{
    unsigned int current_max;
    unsigned int orders[BUTTONS_NUMBER];
};

typedef struct elevators_section{
    elevator_status elevators[ELEVATORS_QUANTITY];
    int elevators_quantity;
    struct request_orders reqs;
} elevators_section;

elevator_status elevator_init(int id);
elevators_section elevator_section_init();

int press_button(elevator_status * elevator, int num);
void simulation_one_step(elevators_section * ele_sec);
void print_whole_section_manual(elevators_section * ele_sec);
int add_request(elevators_section * ele_sec, int from_floor);
void print_whole_section(elevators_section * ele_sec);


#endif
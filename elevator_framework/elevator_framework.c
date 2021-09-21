#include "elevator_framework.h"
#include <stdio.h>
#include <stdlib.h>




elevator_status elevator_init(int id){
    elevator_status elevator;
    elevator.current_floor = 0;
    elevator.target_floor = 0;
    elevator.id = id;
    elevator.btn_floor_offset = 0;
    elevator.door_open = false;
    for(int i = 0; i < BUTTONS_NUMBER; i++){
        elevator.buttons[i] = false;
    }


    return elevator;

}


elevators_section elevator_section_init(){ // init with pointer or not?
    elevators_section ele_sec;
    ele_sec.elevators_quantity = ELEVATORS_QUANTITY;
    for(int i = 0; i < ele_sec.elevators_quantity; i++){
        ele_sec.elevators[i] = elevator_init(i);
    }
    for(int i = 0; i < BUTTONS_NUMBER; i++){
        ele_sec.reqs.orders[i] = 0;
    }
    ele_sec.reqs.current_max = 0;

    return ele_sec;
}


int press_button(elevator_status * elevator, int num){
    elevator->buttons[num] = true;
}

void find_new_target_floor(elevator_status * elevator){
    // not implemented TODO
    // raise;
    bool edge_cnt_up = false;
    bool edge_cnt_down = false;
    for(int step = 1; step < BUTTONS_NUMBER; step++){
        int c_floor = elevator->current_floor;
        int btn_id;
        btn_id = c_floor+step-elevator->btn_floor_offset;
        if(btn_id < BUTTONS_NUMBER){
            if(elevator->buttons[btn_id] == true){
                elevator->target_floor= btn_id+elevator->btn_floor_offset;
                break;
            }
        }else{
            edge_cnt_up=true;
        }
        btn_id = c_floor-step-elevator->btn_floor_offset;
        if(btn_id >= 0){
            if(elevator->buttons[btn_id] == true){
                elevator->target_floor= btn_id+elevator->btn_floor_offset;
                break;
            }            
        }else{
            edge_cnt_down=false;
        }

        if(edge_cnt_down && edge_cnt_up){
            break;
        }
    }
}

int find_min(int *arr, int size, unsigned int current_max){
    unsigned int current_min = current_max;
    int current_idx = -1;
    for(int i = 0; i < size; i++){
        if(arr[i] <= current_min && arr[i] > 0){
            current_min = arr[i];
            current_idx = i;
        }
    }
    return current_idx;
}

void calc_new_states(elevators_section * ele_sec){
    // close all doors
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        ele_sec->elevators[i].door_open = false;
    }

    // TODO implement offset
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        int current_floor = ele_sec->elevators[i].current_floor;

        if(ele_sec->elevators[i].buttons[current_floor] == true){
                ele_sec->elevators[i].door_open = true;
                ele_sec->elevators[i].buttons[ele_sec->elevators[i].current_floor] = false;
        }
        if(ele_sec->reqs.orders[current_floor] > 0){
            ele_sec->reqs.orders[current_floor] = 0;
            ele_sec->elevators[i].door_open = true;
        }
    }




    // open doors
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        if(ele_sec->elevators[i].current_floor == ele_sec->elevators[i].target_floor){
            ele_sec->elevators[i].door_open = true;

            find_new_target_floor(&(ele_sec->elevators[i]));
        }
    }


    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        if(ele_sec->elevators[i].target_floor == ele_sec->elevators[i].current_floor){

            int found_floor  = find_min(ele_sec->reqs.orders, BUTTONS_NUMBER ,ele_sec->reqs.current_max);
            
            if(found_floor == -1) break;
            
            ele_sec->reqs.orders[found_floor] = 0;
            ele_sec->elevators[i].target_floor = found_floor;
            
        }
    }
    

}

void move_all_elevators(elevators_section * ele_sec){
    
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        if(ele_sec->elevators[i].door_open == false){
            if(ele_sec->elevators[i].target_floor > ele_sec->elevators[i].current_floor){
                ele_sec->elevators[i].current_floor++;
            }else if(ele_sec->elevators[i].target_floor < ele_sec->elevators[i].current_floor){
                ele_sec->elevators[i].current_floor--;
            }
        }
    }

}

void simulation_one_step(elevators_section * ele_sec){

    // buttons, request etc TODO

    calc_new_states(ele_sec);

    move_all_elevators(ele_sec);

    // print_whole_section(ele_sec);

    // print state
}
void print_elevator(elevator_status * elevator){

    printf("%d,%d,%d,%d,", elevator->id, elevator->door_open, elevator->current_floor, elevator->target_floor);
    for(int i = 0; i < BUTTONS_NUMBER-1; i++){
        printf("%d,", elevator->buttons[i]);
    }
    printf("%d\n", elevator->buttons[BUTTONS_NUMBER-1]);

}
void print_arr(unsigned int arr[], int size){
    for(int i = 0; i < size-1; i++){
        printf("%d,", arr[i]);
    }
    printf("%d\n", arr[size-1]);

}
void print_elevator_manual(elevator_status * elevator){

    printf("id:%d, door:%d, current_floor:%d, target_floor:%d, buttons:", elevator->id, elevator->door_open, elevator->current_floor, elevator->target_floor);
    for(int i = 0; i < BUTTONS_NUMBER-1; i++){
        printf("%d,", elevator->buttons[i]);
    }
    printf("%d\n", elevator->buttons[BUTTONS_NUMBER-1]);

}

void print_whole_section(elevators_section * ele_sec){
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        print_elevator(&(ele_sec->elevators[i]));
    }
    print_arr((ele_sec->reqs.orders), BUTTONS_NUMBER);
    printf("\n");
}



void print_whole_section_manual(elevators_section * ele_sec){
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        print_elevator_manual(&(ele_sec->elevators[i]));
    }

    print_arr((ele_sec->reqs.orders), BUTTONS_NUMBER);
    printf("\n");
}

void add_request(elevators_section * ele_sec, int from_floor){
    ele_sec->reqs.current_max++;
    ele_sec->reqs.orders[from_floor] = ele_sec->reqs.current_max;
}
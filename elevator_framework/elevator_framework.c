#include "elevator_framework.h"
#include "request_queue/request_queue.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define ELEVATORS_QUANTITY 3 // TODO dynamic or static make on
#define BUTTONS_NUMBER 16

typedef struct elevator_status{
    int id;
    int current_floor;
    int target_floor;
    bool buttons[BUTTONS_NUMBER];
    bool door_open;
    int btn_floor_offset;

} elevator_status;


typedef struct elevators_section{
    elevator_status elevators[ELEVATORS_QUANTITY];
    int elevators_quantity;
    struct RequestQueue request_queue;
    int request
} elevators_section;



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


elevators_section elevator_section_init(int quantity){ // init with pointer or not?
    elevators_section ele_sec;
    ele_sec.elevators_quantity = ELEVATORS_QUANTITY;
    for(int i = 0; i < ele_sec.elevators_quantity; i++){
        ele_sec.elevators[i] = elevator_init(i);
    }
    initQueue(&ele_sec.request_queue);
    return ele_sec;
}

// int add_request(struct elevator_state * elevator, request *req){
//     enqueue(&elevator->queue, req);
// }
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

void calc_new_states(elevators_section * ele_sec){
    // close all doors
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        ele_sec->elevators[i].door_open = false;
    }

    // TODO implement offset
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        if(ele_sec->elevators[i].buttons[ele_sec->elevators[i].current_floor] == true){
                ele_sec->elevators[i].door_open = true;
                ele_sec->elevators[i].buttons[ele_sec->elevators[i].current_floor] = false;
        }
    }

    // TODO implement offset
    for(int i = 0; i < ele_sec->request_queue.capacity; i++){
        if(ele_sec->elevators[i].current_floor == ele_sec->request_queue.array[]){
                ele_sec->elevators[i].door_open = true;
                ele_sec->elevators[i].buttons[ele_sec->elevators[i].current_floor] = false;
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
            if(!isEmpty(&(ele_sec->request_queue))){
                request req = dequeue(&(ele_sec->request_queue));
                ele_sec->elevators[i].target_floor = req.from_floor;
            }
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
    print_queue(&(ele_sec->request_queue));
    printf("\n");
}
void print_whole_section_manual(elevators_section * ele_sec){
    for(int i = 0; i < ele_sec->elevators_quantity; i++){
        print_elevator_manual(&(ele_sec->elevators[i]));
    }
    print_queue(&(ele_sec->request_queue));
    printf("\n");
}
// void calc_next_move(struct elevator_state * elevator){
//     int current = elevator->status.current_floor;
//     int target = elevator->status.target_floor;
//     bool* buttons = elevator->status.desired_floors;
//     if(elevator->status.door_open == true){
//         elevator->status.door_open = false;
//     }
//     if(true || current == target){
//         int nearest_floor = current;
//         int nearest_distance = INT_MAX;
//         for(int i = 0; i < BUTTONS_NUMBER; i++){
//             if(buttons[i] == true){
//                 int distance = abs(i - current);
//                 if(current == i){
//                     buttons[i] = false;
//                     continue;
//                 }
//                 if (distance < nearest_distance)
//                 {
//                     if ((current < target && (i - current > 0)) || (current > target && (i - current < 0)) || (current == target))
//                     {
//                         nearest_distance = distance;
//                         nearest_floor = i;
//                     }
//                 }
//             }
//         }
//         target = nearest_floor;
//     }
//     if(current == target){
//         request req;
//         //TODO when request is handling and someone presses the button request is lost
//         if(!front(&elevator->queue, &req)){
//             target = req.from;
//         }

//         //TO TEST
//         if(current == req.from){
//             dequeue(&elevator->queue, &req);
//         }
        
//     }
//     if(current != target){
//         // check if someone can be picked up

//         //TODO
//     }

//     elevator->status.target_floor = target;    
// }



// void move_one_step(struct elevator_state * elevator){
//     int current = elevator->status.current_floor;
//     int target = elevator->status.target_floor;
//     if(current != target){
//         if(current < target){
//             current++;
//         }else{
//             current--;
//         }
//     }
//     if(current == target){
//         elevator->status.door_open = true;
//     }
    
//     elevator->status.current_floor = current;
// }
// void print_elevator_status(struct elevator_state * elevator, bool queue_too){
//     printf("ELEVATOR id: %d", elevator->status.id);
//     if(elevator->status.door_open) printf("  [door opened]");
//     printf("\r\n");
//     printf("\t current: %d \r\n", elevator->status.current_floor);
//     printf("\t target: %d \r\n", elevator->status.target_floor);
//     printf("PRESSED BUTTONS: ");
//     for(int i = 0; i < BUTTONS_NUMBER; i++){
//         if(elevator->status.desired_floors[i])
//             printf("%d ", i);
//     }
//     printf("\n");
//     printf("QUEUE\n");
//     for(request* req = elevator->queue.front; req != NULL; req = req->next){

//         printf("\t request from:%d to:%d at:%lld \n", req->from, req->to, req->timestamp);
//     }
//     printf("-------------------\r\n");
//     printf("\r\n");

// }

// void _calc_move_print(struct elevator_state * elevator){
//     calc_next_move(elevator);
//     move_one_step(elevator);
//     print_elevator_status(elevator, true);
// } 
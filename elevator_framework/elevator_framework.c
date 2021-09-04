#include "elevator_framework.h"
#include "request_queue/request_queue.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUTTONS_NUMBER 16

typedef struct elevator_status{
    int id;
    int current_floor;
    int target_floor;
    bool desired_floors[BUTTONS_NUMBER];
    bool door_open;

} elevator_status;

typedef struct elevator_state{
    elevator_status status;
    struct request_queue queue;
}elevator_state;

struct elevator_state elevator_init(int id){
    elevator_state elevator;
    elevator.status.current_floor = 0;
    elevator.status.target_floor = 0;
    elevator.status.id = id;
    elevator.status.door_open = false;
    for(int i = 0; i < BUTTONS_NUMBER; i++){
        elevator.status.desired_floors[i] = false;
    }
    createQueue(&elevator.queue);
    return elevator;

}
int add_request(struct elevator_state * elevator, request *req){
    enqueue(&elevator->queue, req);
}
int press_button(struct elevator_state * elevator, int num){
    elevator->status.desired_floors[num] = true;
}
void calc_next_move(struct elevator_state * elevator){
    int current = elevator->status.current_floor;
    int target = elevator->status.target_floor;
    bool* buttons = elevator->status.desired_floors;
    if(elevator->status.door_open == true){
        elevator->status.door_open = false;
    }
    if(true || current == target){
        int nearest_floor = current;
        int nearest_distance = INT_MAX;
        for(int i = 0; i < BUTTONS_NUMBER; i++){
            if(buttons[i] == true){
                int distance = abs(i - current);
                if(current == i){
                    buttons[i] = false;
                    continue;
                }
                if (distance < nearest_distance)
                {
                    if ((current < target && (i - current > 0)) || (current > target && (i - current < 0)) || (current == target))
                    {
                        nearest_distance = distance;
                        nearest_floor = i;
                    }
                }
            }
        }
        target = nearest_floor;
    }
    if(current == target){
        request req;
        //TODO when request is handling and someone presses the button request is lost
        if(!front(&elevator->queue, &req)){
            target = req.from;
        }

        //TO TEST
        if(current == req.from){
            dequeue(&elevator->queue, &req);
        }
        
    }
    if(current != target){
        // check if someone can be picked up

        //TODO
    }

    elevator->status.target_floor = target;    
}

void move_one_step(struct elevator_state * elevator){
    int current = elevator->status.current_floor;
    int target = elevator->status.target_floor;
    if(current != target){
        if(current < target){
            current++;
        }else{
            current--;
        }
    }
    if(current == target){
        elevator->status.door_open = true;
    }
    
    elevator->status.current_floor = current;
}
void print_elevator_status(struct elevator_state * elevator, bool queue_too){
    printf("ELEVATOR id: %d", elevator->status.id);
    if(elevator->status.door_open) printf("  [door opened]");
    printf("\r\n");
    printf("\t current: %d \r\n", elevator->status.current_floor);
    printf("\t target: %d \r\n", elevator->status.target_floor);
    printf("PRESSED BUTTONS: ");
    for(int i = 0; i < BUTTONS_NUMBER; i++){
        if(elevator->status.desired_floors[i])
            printf("%d ", i);
    }
    printf("\n");
    printf("QUEUE\n");
    for(request* req = elevator->queue.front; req != NULL; req = req->next){

        printf("\t request from:%d to:%d at:%lld \n", req->from, req->to, req->timestamp);
    }
    printf("-------------------\r\n");
    printf("\r\n");

}

void _calc_move_print(struct elevator_state * elevator){
    calc_next_move(elevator);
    move_one_step(elevator);
    print_elevator_status(elevator, true);
} 
#include "elevator_framework/elevator_framework.c"
#include <string.h>
#define PRINT_WHITE printf("\e[97m");
#define PRINT_GREEN printf("\e[32m");

void test_case(){
    struct elevator_state elevator1 = elevator_init(0);
    request req;
    req.from = 0;
    req.to = 1;
    enqueue(&elevator1.queue, &req);
    print_elevator_status(&elevator1, true);
    calc_next_move(&elevator1);
    print_elevator_status(&elevator1, true);
    move_one_step(&elevator1);
    print_elevator_status(&elevator1, true);
    press_button(&elevator1, 3);
    print_elevator_status(&elevator1, true);
    _calc_move_print(&elevator1);
    _calc_move_print(&elevator1);
    _calc_move_print(&elevator1);
    _calc_move_print(&elevator1);
}
void parse_input_and_invoke(char* cmd, struct elevator_state *elevator){
    // if(){
    //     printf("no cmd\r\n");
    //     return;
    // }
    if(strlen(cmd) < 2 || cmd[0] == 's'){
        PRINT_GREEN
        calc_next_move(elevator);
        
        print_elevator_status(elevator, true);
        PRINT_WHITE
        move_one_step(elevator);
    }else if(cmd[0] == 'b'){
        int btn;
        sscanf(cmd, "b%d", &btn);
        press_button(elevator, btn);
    }else if(cmd[0] == 'r'){
        request req;
        sscanf(cmd, "rf%dt%d", &req.from, &req.to);
        enqueue(&elevator->queue, &req);
    }
    print_elevator_status(elevator, true);

}
int main(int argc, char** argv){
    struct elevator_state elevator2 = elevator_init(1);
    char cmd[32];
    while(true){
        // scanf("%s", cmd);
        fgets(cmd, 32, stdin);
        parse_input_and_invoke(cmd, &elevator2);
        strcpy(cmd, "");
    }
    return 0;
}
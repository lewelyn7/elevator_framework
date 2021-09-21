#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "elevator_framework/elevator_framework.h"
// #include "elevator_framework/elevator_framework.c"

bool mode_manual = false;


int parse_input_and_invoke(char* cmd, elevators_section *ele_sec){

    if(strlen(cmd) < 2 || cmd[0] == 's'){
        simulation_one_step(ele_sec);
    }else if(cmd[0] == 'b'){
        int btn;
        int elevator_i;
        sscanf(cmd, "b%d,%d", &elevator_i, &btn);
        if(press_button(&(ele_sec->elevators[elevator_i]), btn) != 0){
            printf("error: wrong argument\n\n");
        }
    }else if(cmd[0] == 'r'){
        int from_floor;
        sscanf(cmd, "r%d", &from_floor); // TODO validate max queue
        if(add_request(ele_sec, from_floor) != 0){
            printf("error: wrong argument\n\n");
        }
    }else if(cmd[0] == 'e'){
        return 2;
    }else{
        printf("no such command\n\n");
    }

    if(mode_manual){
        print_whole_section_manual(ele_sec);
    }else{
        print_whole_section(ele_sec);
    }
        
    return 0;


}
int main(int argc, char** argv){
    if(argc >= 2){
        if(argv[1][1] == 'm'){
            mode_manual = true;
        }
    }

    elevators_section ele_sec = elevator_section_init();


    char cmd[32];
    while(true){
        fgets(cmd, 32, stdin);
        if(parse_input_and_invoke(cmd, &ele_sec) == 2){
            return 0;
        }
        strcpy(cmd, "");
    }
    return 0;
}
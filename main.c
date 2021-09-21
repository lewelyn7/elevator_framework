#include "elevator_framework/elevator_framework.c"
#include <string.h>
#define PRINT_WHITE printf("\e[97m");
#define PRINT_GREEN printf("\e[32m");
#define MODE_MANUAL 0


int parse_input_and_invoke(char* cmd, elevators_section *ele_sec){
    // if(){
    //     printf("no cmd\r\n");
    //     return;
    // }
    if(strlen(cmd) < 2 || cmd[0] == 's'){ // TODO validate user input
        // PRINT_GREEN
        simulation_one_step(ele_sec);
        // PRINT_WHITE
    }else if(cmd[0] == 'b'){
        int btn;
        int elevator_i;
        sscanf(cmd, "b%d,%d", &elevator_i, &btn);
        press_button(&(ele_sec->elevators[elevator_i]), btn);
    }else if(cmd[0] == 'r'){
        request req; 
        sscanf(cmd, "r%d", &req.from_floor); // TODO validate max queue
        add_request(ele_sec, req.from_floor);
    }else if(cmd[0] == 'e'){
        return 2;
    }
    if(MODE_MANUAL){
        print_whole_section_manual(ele_sec);
    }else{
        print_whole_section(ele_sec);
    }
        
    return 0;


}
int main(int argc, char** argv){
    elevators_section ele_sec = elevator_section_init(3);
    
    char cmd[32];
    while(true){
        // scanf("%s", cmd);
        fgets(cmd, 32, stdin);
        if(parse_input_and_invoke(cmd, &ele_sec) == 2){
            return 0;
        }
        strcpy(cmd, "");
    }
    return 0;
}
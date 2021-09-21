import subprocess
from pydantic import BaseModel
from typing import List

class Elevator(BaseModel):
    id: int
    door_open: bool
    current_floor: int
    target_floor: int
    buttons: List[bool]



class Move(BaseModel):
    elevators: List[Elevator] = []
    requests: List[int] = []

def parse_output(txt) -> List[Move]:
    moves = []
    txt = txt.split("\n\n")[:-1]
    for move_str in txt:
        elevators_str = move_str.split("\n")
        move = Move()
        for elevator_str in elevators_str[:-1]:
            elevator_list = elevator_str.split(",")
            move.elevators.append(Elevator(
                id=int(elevator_list[0]),
                door_open=bool(int(elevator_list[1])),
                current_floor=int(elevator_list[2]),
                target_floor=int(elevator_list[3]),
                buttons=[bool(int(btn)) for btn in elevator_list[4:]]
            ))

        requests_str = elevators_str[-1].split(',')
        # print(requests_str)
        requests = [int(item) for item in requests_str]
        move.requests = requests

        moves.append(move)
    return moves
        



def test_all_pass():
    assert True


def test_btn_order_cmd():

    input = [
        "b0,1",
        "b0,2",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    print(process.stdout)
    assert moves[-1].elevators[0].buttons[1] == True
    assert moves[-1].elevators[0].buttons[2] == True

    assert moves[-1].elevators[1].buttons[0] == False
    assert moves[-1].elevators[2].buttons[0] == False

def test_add_request_cmd():
    input = [
        "r0",
        "r2",
        "r6",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[-1].requests[0] == 1
    assert moves[-1].requests[2] == 2
    assert moves[-1].requests[6] == 3



def test_btn_cmd():

    input = [
        "b0,1",
        "b0,8",
        "b0,2",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[-1].elevators[0].buttons[1] == True
    assert moves[-1].elevators[0].buttons[8] == True
    assert moves[-1].elevators[0].buttons[2] == True

    assert moves[-1].elevators[1].buttons[1] == False
    assert moves[-1].elevators[1].buttons[8] == False
    assert moves[-1].elevators[1].buttons[2] == False

    assert moves[-1].elevators[2].buttons[1] == False
    assert moves[-1].elevators[2].buttons[8] == False
    assert moves[-1].elevators[2].buttons[2] == False


def test_just_btns():
    input = [
        "b0,1",
        "b1,4",
        "b2,0", # TODO -1
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[4].elevators[0].current_floor == 1
    assert moves[5].elevators[0].door_open == True
    assert moves[4].elevators[1].current_floor == 1
    assert moves[4].elevators[2].current_floor == 0
    assert moves[7].elevators[1].current_floor == 4
    assert moves[8].elevators[1].door_open == True
    assert moves[8].elevators[0].door_open == True
    assert moves[8].elevators[2].door_open == True

def test_between():
    input = [
        "b0,1",
        "b1,3",
        "b1,5", # TODO -1
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[6].elevators[1].current_floor ==  3
    assert moves[7].elevators[1].door_open == True
    assert moves[8].elevators[1].current_floor == 4
    assert moves[8].elevators[1].door_open == False
    assert moves[9].elevators[1].current_floor == 5
    assert moves[10].elevators[1].door_open == True

def test_btn_after_start():
    input = [
        "b1,8",
        "s",
        "s",
        "b1,4"
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[1].elevators[1].current_floor == 0
    assert moves[2].elevators[1].current_floor == 1
    assert moves[3].elevators[1].buttons[4] == True
    assert moves[6].elevators[1].current_floor == 4
    assert moves[7].elevators[1].door_open == True
    assert moves[11].elevators[1].current_floor == 8


def test_requests():
    input = [
        "r5",
        "s",
        "s",
        # "b1,4"
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[1].elevators[0].current_floor == 0
    assert moves[2].elevators[0].current_floor == 1
    assert moves[6].elevators[0].current_floor == 5
    assert moves[7].elevators[0].door_open == True

def test_requests_btn_in_the_mid():
    input = [
        "r5",
        "s",
        "s",
        "b0,4"
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[1].elevators[0].current_floor == 0
    assert moves[2].elevators[0].current_floor == 1

    assert moves[6].elevators[0].current_floor == 4
    assert moves[7].elevators[0].door_open == True
    
    assert moves[8].elevators[0].current_floor == 5
    assert moves[8].elevators[0].door_open == False
    assert moves[9].elevators[0].door_open == True


def test_requests_btn_in_the_mid2():
    # button behind elevator
    input = [
        "r6",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "b0,4"
        "s",
        "s",
        "s",
        "s",
        "s",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    assert moves[1].elevators[0].current_floor == 0
    assert moves[2].elevators[0].current_floor == 1

    # assert moves[6].elevators[0].current_floor == 4
    # assert moves[7].elevators[0].door_open == True
    
    assert moves[8].elevators[0].current_floor == 6
    assert moves[8].elevators[0].door_open == False
    assert moves[9].elevators[0].door_open == True


def test_btn_request_in_the_mid():
    # button behind elevator
    input = [
        "b0,8",
        "b1,8",
        "b2,8",
        "s",
        "s",
        "s",
        "r4",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "s",
        "e"
    ]
    input = "\n".join(input) + "\n"
    process = subprocess.run("./main", input=input, text=True, capture_output=True)
    moves = parse_output(process.stdout)
    # assert moves[6].elevators[0].current_floor == 4
    # assert moves[7].elevators[0].door_open == True
    
    assert moves[3].elevators[0].buttons[8] == True
    assert moves[3].elevators[1].buttons[8] == True
    assert moves[3].elevators[2].buttons[8] == True
    assert moves[7].requests[4] == 1

    assert moves[8].elevators[0].current_floor == 4
    assert moves[9].elevators[0].door_open == True



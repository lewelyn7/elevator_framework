

## Elevator framework
# Example:
![CircleCI](https://circleci.com/gh/lewelyn7/elevator_framework.svg?style=svg)

https://circleci.com/gh/lewelyn7/elevator_framework.svg?style=svg
Simple program to simulate behaviour of elevators

## Usage

First build an application by executing `make`

Then run it by simply calling `./main`

Application takes one optional argument `-m`, which enables output in more human-readable format.

After start application waits for user input. There are several commands possible:
 * `s` - one step of simulation
 * `bN,M` - press button *N* in elevator *M*
 * `rN` - request elevator from floor *N*
 * `e` - exit program

### Output
After each command application prints current status of all elevators, which consists of:
 * rows for each elevator indicating status of buttons, doors and floors
 * one row for request queue

### Sample output in manual mode:
```
s
id:0, door:1, current_floor:0, target_floor:0, buttons:0,0,0,0,0,0,0,0,0
id:1, door:1, current_floor:0, target_floor:0, buttons:0,0,0,0,0,0,0,0,0
id:2, door:1, current_floor:0, target_floor:0, buttons:0,0,0,0,0,0,0,0,0
requests:0,0,0,0,0,0,0,0,0

r2
id:0, door:1, current_floor:0, target_floor:0, buttons:0,0,0,0,0,0,0,0,0
id:1, door:1, current_floor:0, target_floor:0, buttons:0,0,0,0,0,0,0,0,0
id:2, door:1, current_floor:0, target_floor:0, buttons:0,0,0,0,0,0,0,0,0
requests:0,0,1,0,0,0,0,0,0
```

### Sample output in standard mode:
```
s
0,1,0,0,0,0,0,0,0,0,0,0,0
1,1,0,0,0,0,0,0,0,0,0,0,0
2,1,0,0,0,0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0,0

b1,4
0,1,0,0,0,0,0,0,0,0,0,0,0
1,1,0,0,0,0,0,0,1,0,0,0,0
2,1,0,0,0,0,0,0,0,0,0,0,0
0,0,0,0,0,0,0,0,0
```
## Tests
Tests are written in *Python* using *pytest* framework

To execute tests first install all libraries (preferably in virutal environment):

```sh
python -m pip install -r requirements.txt
python -m pip install pytest
```

And call pytest to run the tests
```sh
python -m pytest
```
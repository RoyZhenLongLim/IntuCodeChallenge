<h1><center>Documentation</center></h1>
---

### How to run the program
Run the executable. For input, it should be of the form
```
<num_columns> <character_for_which_side_door_is_on>
<num_rows_in_each_col> (one for each column)
<num_students>
(for each student):
<id> <subject> <exam_number> <exam_length>
```
As an example
```
5 r
5 4 5 5 3
16
1 HMX2 2 180
2 HMX2 1 180
3 HMX2 1 180
4 HMX1 2 150
5 HMX1 2 150
6 HMX1 2 150
7 HMX1 2 150
8 HMX1 2 150
9 HM 2 180
10 HM 1 180
11 HM 1 180
12 HM 1 180
13 HC 2 180
14 HC 2 180
15 HC 2 180
16 HP 2 180
```
- For convenience, the inputs and outputs have been stored already in their corresponding directories.

### Pseudocode
```
class exam:
    string subject
    int exam_number
    int exam_length

class person:
    string name
    exam exam

function main:
    priority_queue students
    map exams
    get num_columns and position_of_door
    get rows[num_columns]
    get num_students
    get student_info[num_students]


```
### Assumptions Made
- The door will be on one of the sides of the room
- There are no two people (or exams) with the same id/name
- No column will have any breaks in the middle of it
- The column sizes are approximately evenly distributed (the algorithm will run if they aren't, though it will likely seat all the students in only a few columns)
    - To counter this, one can use a separate algorithm which snakes through the front of the seats and seats everyone at the front in all the columns - however, it is less easy to guarantee students will be seated so that they can cheat off each other

### Example Data Sets + Allocations

### Data Structures Used
- Classes
    - Students
        - Stores each students:
            - 'Name' (can be id) as string
            - Exam Details object
    - Exam Details
        - Stores subject:
            - Name as string
            - Exam Number as integer
            - Exam Length as integer
- Priority Queue
    - Acts similar to a normal queue, but instead of FIFO, it pops the 'highest valued' object in the queue
    - This algorithm uses a special comparison operator to order students
        - Prioritises, in the following order:
            - Shorter exams
            - The exam having more students
        - From there, it's just alphabetical order of subject, then exam number, then student name (all arbitrarily ordered)
- Map
    - Enables storage which is indexed using values other than integers
        - In this case, we indexed by exams in order to group students by their exam, and prioritise shorter exams first, followed by exams with more students
        - We kept count of the students doing an exam with the map
            - Note: we kept a copy of said map since our comparison operator for the prio queue requires it, and we weren't sure if it would break if our map changed

### Justification of Algorithm
To match the spec, we wanted to ensure that
- shorter exams are placed near the door
- make similar exams near each other 

To do this,
- the algorithm will start off by group by unique exam (e.g. HMX2 Exam 2 is distinct from HMX2 Exam 1)
- the algorithm starts to seat the students with the shortest exam first which ever side the door is
  - if the door is on the top or bottom, then the placement of the shortest exams does not matter since they will be 
    able to walk out if the shortest exams have their own columns
- it will then proceed to fill in the largest column with the group with the largest number of students 
  - this ensures we have the largest number of similar exams in a contiguous manner
- any overflow from this column is treated as another group and re-entered into the queue
  - while there is no guarantee that the algorithm will seat the overflow near the first group, this will generally 
    keep the overflow together

Worst case: `O(max(n log n, m * n))` (roughly)
- `n` is the number of students
- `m` is the number of columns

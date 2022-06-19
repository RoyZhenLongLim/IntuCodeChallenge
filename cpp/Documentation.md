<h1><center>Documentation</center></h1>
---

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
    get num_columns
    get position_of_door
    get rows[num_columns]
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
We wanted to ensure groups of exams were kept together to help keep distribution of exams as easy as possible. As such, we decided to adopt an algorithm of fitting the biggest exams (by number of students) into the biggest column, in order to 
<h1><center>Documentation</center></h1>
---

### How to run the program
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
    rows[num_columns], remaining[num_columns]
    for i from 0 to num_columns step 1:
        get num_rows[i]
    get num_students
    for i from 0 to num_students step 1:
        get student[i]
        update exams with new student doing that subject
    for i from 0 to num_students step 1:
        push student[i] to students
    
    seating[max_rows][num_cols]
    seated[max_rows][num_cols]
    while students is not empty:
        get top of students' subject
        if subject's length is maximum length:
            find column with largest remaining[col] value
            for i from rows[max_col] - remaining[max_col] to rows[max_col] while students doing this subject still remain:
                seating[i][max_col] = students.top
            subtract number of students seated from that subject and column
        else if door is on the left side:
            for i from 0 to cols while students are to be seated doing that exam:
                for j from 0 to rows[i] while students are to be seated doing that exam:
                    if not seated[j][i]:
                        seating[j][i] = student.top
                        seated[j][i] = true
                        subtract 1 from students doing that exam
        else:
            for i from cols to 0 while students are to be seated doing that exam step -1:
                for j from 0 to rows[i] while students are to be seated doing that exam:
                    if not seated[j][i]:
                        seating[j][i] = student.top
                        seated[j][i] = true
                        subtract 1 from students doing that exam
    for i from 0 to max_rows step 1:
        for j from 0 to cols step 1:
            if there is student at this seat:
                print student details
```
### Assumptions Made
- The door will be on one of the sides of the room
- There are no two people (or exams) with the same id/name
- No column will have any breaks in the middle of it
- The column sizes are approximately evenly distributed (the algorithm will run if they aren't, though it will likely seat all the students in only a few columns)
    - To counter this, one can use a separate algorithm which snakes through the front of the seats and seats everyone at the front in all the columns - however, it is less easy to guarantee students will be seated so that they can cheat off each other
- That it is ok to keep separate exam numbers of the same subject separate
    - If that is not the case, it is a very quick fix - simply removing the exam_number from the exam class and instead adding it to the person class

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

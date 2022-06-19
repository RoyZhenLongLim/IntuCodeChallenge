# Explanation of each test
## Input 
```
<num_columns> <character_for_which_side_door_is_on>
<num_rows_in_each_col> (one for each column)
<num_students>
(for each student):
<id> <subject> <exam_number> <exam_length>
```
## Output
The format is `{Student Number} {Subject} {Exam Number}` in each column.
## Test 1
Basic Test Case given in specs

## Test 2
Has a large amount of HMX2 students (a lot of exam 2 and exam 3 and one exam 4)
- Shows how the algorithm allocates similar exams
- The room is very full

## Test 3
Has a large variety of exams.

## Test 4
Awkward number of students (5 per exam when the columns are 4)

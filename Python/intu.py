# Mapping between subjects and their respective numbers
# TODO: This is hard coding and susceptible to changes in topic
subject_map = {
    "HMX2": 0,
    "HM": 1,
    "HC": 2,
    "HP": 3,
    "HE": 4,
    "HB": 5,
    "HMX1": 6,
    "PMX": 7,
    "PMXA": 8,
    "PM": 9,
    "Y10": 10,
    "PC": 11,
    "PP": 12
}

n_to_subject = list(subject_map.keys())


# Contains information about the students name, subject and exam number
class Student:
    def __init__(self, student_n, subject_n, exam_n):
        self.student_n = student_n
        self.subject_n = subject_n
        self.exam_n = exam_n


# Scan in the room, the format is {Number of rows in column A} {Number of rows in column B} ...
# Returns number of columns and the number of rows in each column
def create_layout():
    layout = input().split()
    # TODO: Include error checking
    layout = [int(item) for item in layout]
    return len(layout), layout


# Assuming the format is: {Student Number} {Subject} {Exam Number}
# Takes in all the students and stores their information
def create_student_list():
    student_list = []
    student_info = input()
    while (student_info != ""):
        student_info = student_info.split()
        # Need to include error checking to make sure input is correct
        # Insert student in the list
        student_list.append(Student(
            int(student_info[0]),
            subject_map[student_info[1]],
            int(student_info[2])
        ))
        print(f"Student {student_info[0]} inserted sitting {student_info[1]} Exam {student_info[2]}")
        student_info = input()

    return student_list


col_name = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


# Print the room
def print_room(room_layout, room):
    line = ""
    # Print column names
    for i in range(len(room)):
        line = line + " {:<20}".format(col_name[i])

    max_row = max(room_layout)
    # Print row by row
    for row in range(max_row):
        line = ""
        for col in range(len(room)):
            # If there is not a seat, say so
            if row >= room_layout[col]:
                line = line + "{:<20}".format("No Seat")
            # If there is a seat but no student is seated there, say so
            elif room[col][row] is None:
                line = line + "{:<20}".format("None")
            else:
                student = room[col][row]
                line = line + "{:<20}".format(f"S{student.student_n}-{n_to_subject[student.subject_n]}-E{student.exam_n}")

        print(line)


if __name__ == '__main__':

    # Figure out layout of the room
    # ncol: number of columns
    # room_layout[col] returns the number of rows in column col
    ncol, room_layout = create_layout()

    # Create the list of students
    student_list = create_student_list()

    # Sort the list first by subject number and second by exam number (sorts first by subject, then by exam number)
    # Shortest exams are placed at the end of the list so they can be removed using the pop method
    student_list.sort(key=lambda x: (x.subject_n, x.exam_n))

    # Output the order students will be seated in
    print("")
    print("Order in which students will be seated in")
    for student in student_list.__reversed__():
        print(
            f"Student Number: {student.student_n}, "
            f"Subject: {n_to_subject[student.subject_n]} Number {student.subject_n}, "
            f"Exam Number: {student.exam_n}")

    # At this point, we have an ordered set of students from the exams with the shortest to the longest time in a list
    # Create the room
    # Each element in the room is a list contains everyone in the room
    # It is in the following format: room[col][row]
    room = [[None for _ in range(max(room_layout))] for col in range(ncol)]

    ###################################### Algorithm Implementation ####################################################
    # Assign seats based on the following algorithm
    # Fill starting from the right-most column at the front of the room
    col = ncol - 1
    row = 0
    # Increment, if incr is positive
    # we are going down the column, if it is negative, we are going up the column
    incr = 1
    while len(student_list) > 0:
        # Remove a student from the back of the list and place them in a seat
        student = student_list.pop()
        room[col][row] = student
        print(f"Column:{col}, Row:{row}")
        row = row + incr

        # If we are going down the column and have reached the bottom of the column, move to the next column
        if (incr == 1) and (row > room_layout[col] - 1):
            col = col - 1
            row = room_layout[col] - 1
            incr = -1
        # If we are going up the column and have reached the top, move to the next column
        elif (incr == -1) and (row < 0):
            col = col - 1
            row = 0
            incr = 1

    ##################################### End of Implementation ########################################################

    print("")
    print_room(room_layout, room)

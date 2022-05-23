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

if __name__ == '__main__':

    # Figure out layout of the room
    ncol, room_layout = create_layout()

    # Create the list tof students
    student_list = create_student_list()

    # Sort the list first by subject number and second by exam number (sorts first by subject, then by exam number)
    student_list.sort(key=lambda x: (x.subject_n, x.exam_n), reverse=True)

    # Output the order students will be seated in
    for student in student_list:
        print(f"Student Number: {student.student_n}, Subject: {n_to_subject[student.subject_n]} Number {student.subject_n}, Exam Number: {student.exam_n}")

    # At this point, we have an ordered set of students from the exams with the shortest to the longest time in a list
    # Assign seats based on the following algorithm

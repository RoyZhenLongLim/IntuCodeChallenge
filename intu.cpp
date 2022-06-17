#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <tuple>
#include <cstring>
using namespace std;

typedef tuple<string, int, int> triple;

class person {
	public:
		string name;
		string subject;
		int exam_num;
		int exam_length;
};

// Exams sorted in terms of length of exam (copy is to enable priority queue to work correctly)
map<triple, int> exam_type = {};
map<triple, int> exam_copy = {};

// New operator return true if lhs > rhs i.e. lhs needs to be seated before rhs
// (can ignore safely, just helps with prio queue. Changing this can affect priority of seating plan)
class comp{
	public:
		bool operator()(person lhs, person rhs) {
			if (lhs.exam_length != rhs.exam_length) return lhs.exam_length > rhs.exam_length;
			else if (exam_copy[make_tuple(lhs.subject.c_str(), lhs.exam_num, lhs.exam_length)] != exam_copy[make_tuple(rhs.subject.c_str(), rhs.exam_num, rhs.exam_length)]) return exam_copy[make_tuple(lhs.subject.c_str(), lhs.exam_num, lhs.exam_length)] < exam_copy[make_tuple(rhs.subject.c_str(), rhs.exam_num, rhs.exam_length)];
			else if (strcmp(lhs.subject.c_str(), rhs.subject.c_str()) != 0) return strcmp(lhs.subject.c_str(), rhs.subject.c_str()) > 0;
			else if (lhs.exam_num != rhs.exam_num) return lhs.exam_num > rhs.exam_num;
			else return strcmp(lhs.name.c_str(), rhs.name.c_str()) > 0;
		}
};

int main(){
	// Chooses in what order students are sat
	priority_queue<person, vector<person>, comp> students;
	int cols, stu_num, max_row = -1, max_len = -1;
	char door;
	
	// Scanning in layout of room
	scanf("%d %c", &cols, &door);
	int rows[cols];
	int remaining[cols];
	for (int i = 0; i<cols; i++) {
		scanf("%d", &rows[i]);
		remaining[i] = rows[i];
		if (rows[i] > max_row) max_row = rows[i];
	}
	
	// Scanning in student info
	scanf("%d", &stu_num);
	person stu[stu_num];
	for(int i = 0; i < stu_num; i++) {
		person student;
		scanf("%s", student.name.c_str());
		scanf("%s", student.subject.c_str());
		scanf("%d", &student.exam_num);
		scanf("%d", &student.exam_length);
		exam_type[make_tuple(student.subject.c_str(), student.exam_num, student.exam_length)]++;
		exam_copy[make_tuple(student.subject.c_str(), student.exam_num, student.exam_length)]++;
		stu[i] = student;
		if (student.exam_length > max_len) {
			max_len = student.exam_length;
		}
	}
	
	for (int i = 0 ; i < stu_num; i++) {
		students.push(stu[i]);
	}

	// Arranging students
	person seating[max_row][cols];
	bool seated[max_row][cols] = {0};
	while (!students.empty()) {
		// Current subject to be sat - chooses shorter exams first, and as a second layer, chooses exams with the most students
		triple subj = make_tuple(students.top().subject.c_str(), students.top().exam_num,students.top().exam_length);
		// If the subject does not have priority seating due to being shorter
		if (students.top().exam_length == max_len) {
			int max_col = -1;
			int num = -1;
			// Find the column with the most seats
			for (int j = cols; j-->0;) {
				if (remaining[j] > num) {
					max_col = j;
					num = remaining[j];
				}
			}
			int k = 0;
			// Seats all students doing the current exam who can fit in that column
			for (int i = rows[max_col] - remaining[max_col]; i < rows[max_col] && i - (rows[max_col] - remaining[max_col]) < exam_type[subj]; i++) {
				seating[i][max_col] = students.top();
				students.pop();
				k++;
			}
			// Subtract that many students from the number of students left doing that subject, as well as the number of seats remaining in the column
			exam_type[subj] -= k;
			remaining[max_col] -= k;
		} 
		// If the subject has priority seating and the door is on the left
		else if (door == 'l' || door == 'L') {
			// Seat from the left most column starting at the front
			for (int i = 0; i < cols && !students.empty() && exam_type[subj] > 0; i++) {
				for (int j = 0; j < max_row && !students.empty() && exam_type[subj] > 0; j++) {
					if (rows[i] > j && !seated[j][i]) {
						seating[j][i] = students.top();
						seated[j][i] = true;
						students.pop();
						exam_type[subj]--;
						remaining[i]--;
					}
				}
			}
		} 
		// If the subject has priority seating and the door is on the right, top or bottom
		// (we prioritised seating via columns, so door at top or bottom means students sit on the side and leave from the side. We chose the right side as the default)
		else {
			for (int i = cols; i--> 0 && !students.empty() && exam_type[subj] > 0;) {
				for (int j = 0; j < max_row && !students.empty() && exam_type[subj] > 0; j++) {
					if (rows[i] > j && !seated[j][i]) {
						seating[j][i] = students.top();
						seated[j][i] = true;
						students.pop();
						exam_type[subj]--;
						remaining[i]--;
					}
				}
			}
		}
	}

	// Printing seating arrangement
	// Seats students row by row, starting from the front
	for(int i = 0; i<max_row; i++) {
		for(int j = 0; j<cols; j++) {
			if (rows[j] > i) printf("%4s", seating[i][j].name.c_str());
			else printf("    ");
			printf("\t");
		}
		printf("\n");
	}
	return 0;
}
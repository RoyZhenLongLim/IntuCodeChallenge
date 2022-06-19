#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
using namespace std;

// NOTE: we kept separate exam numbers of the same subject different since it makes it
// Easier to ensure a roughly even distribution of students in columns - if it is desirable
// To keep them together, then exam_num can be removed from most of the cases where
// Subjects are differentiated from each other, and just kept for admin purposes

class exam {
	public:
		string subject;
		int exam_num;
		int exam_length;
};

// New operator for the map (just to 'order' the exams)
// Can safely ignore, no need to change
class comparison {
	public:
		bool operator()(exam lhs, exam rhs) {
			return (strcmp(lhs.subject.c_str(),rhs.subject.c_str()) < 0 || (strcmp(lhs.subject.c_str(),rhs.subject.c_str()) == 0 && lhs.exam_num < rhs.exam_num) || (strcmp(lhs.subject.c_str(),rhs.subject.c_str()) == 0 && lhs.exam_num == rhs.exam_num && lhs.exam_length < rhs.exam_length));
		}
};

class person {
	public:
		string name;
		exam ex;
};

// Exams sorted in terms of length of exam (copy is to enable priority queue to work correctly)
map<exam, int, comparison> exam_type = {};
map<exam, int, comparison> exam_copy = {};

// New operator return true if lhs > rhs i.e. lhs needs to be seated before rhs
// (can ignore safely, just helps with prio queue. Changing this can affect priority of seating plan)
class comp{
	public:
		bool operator()(person lhs, person rhs) {
			if (lhs.ex.exam_length != rhs.ex.exam_length) return lhs.ex.exam_length > rhs.ex.exam_length;
			else if (exam_copy[lhs.ex] != exam_copy[rhs.ex]) return exam_copy[lhs.ex] < exam_copy[rhs.ex];
			else if (strcmp(lhs.ex.subject.c_str(), rhs.ex.subject.c_str()) != 0) return strcmp(lhs.ex.subject.c_str(), rhs.ex.subject.c_str()) > 0;
			else if (lhs.ex.exam_num != rhs.ex.exam_num) return lhs.ex.exam_num > rhs.ex.exam_num;
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
	int rows[cols], remaining[cols];
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
		scanf("%s %s %d %d", student.name.c_str(), student.ex.subject.c_str(), &student.ex.exam_num, &student.ex.exam_length);
		exam_type[student.ex]++;
		exam_copy[student.ex]++;
		stu[i] = student;
		if (student.ex.exam_length > max_len) max_len = student.ex.exam_length;
	}
	
	// Setting up the prio queue
	for (int i = 0 ; i < stu_num; i++) {
		students.push(stu[i]);
	}

	// Arranging students
	person seating[max_row][cols];
	// Room for optimisation - could have a variable with scope outside the loop in order to enable the last seated student's position
	// to persist between loops and save time (which is spent iterating over seats which have already been seated in). However,
	// this makes the code harder to read, so held off on doing it for this demo
	bool seated[max_row][cols] = {0};
	while (!students.empty()) {
		// Current subject to be sat - chooses shorter exams first, and as a second layer, chooses exams with the most students
		exam subj = students.top().ex;
		// If the subject does not have priority seating due to being shorter
		if (subj.exam_length == max_len) {
			int max_col = -1;
			// Find the column with the most seats
			for (int j = cols; j-->0;) {
				// Can remove flip the < at the end into a > if it is desired to keep more students in one column than evenly spread them amongst rows
				if (remaining[j] > remaining[max_col] || (remaining[j] == remaining[max_col] && rows[j] < rows[max_col])) {
					max_col = j;
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
			// Note: could do students.top().ex == subj instead of last condition to save on space, though a bit harder to read in other places so left it out
			for (int i = 0; i < cols && !students.empty() && exam_type[subj] > 0; i++) {
				for (int j = 0; j < rows[i] && !students.empty() && exam_type[subj] > 0; j++) {
					if (!seated[j][i]) {
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
				for (int j = 0; j < rows[i] && !students.empty() && exam_type[subj] > 0; j++) {
					if (!seated[j][i]) {
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
	for(int i = 0; i<max_row; i++) {
		for(int j = 0; j<cols; j++) {
			if (rows[j] > i && strcmp(seating[i][j].name.c_str(),"") != 0) printf("%4s %4s %4d", seating[i][j].name.c_str(), seating[i][j].ex.subject.c_str(), seating[i][j].ex.exam_num);
			else printf("              ");
			printf("|\t");
		}
		printf("\n");
	}
	scanf("%*c%*c");
	return 0;
}
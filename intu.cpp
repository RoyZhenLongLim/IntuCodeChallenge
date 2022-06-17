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

// Exams sorted in terms of length of exam
map<triple, int> exam_type = {};

map<triple, int> exam_copy = {};

// New operator return true if lhs > rhs i.e. lhs needs to be seated before rhs
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
	while (!students.empty()) {
		triple subj = make_tuple(students.top().subject.c_str(), students.top().exam_num,students.top().exam_length);
		if (students.top().exam_length == max_len) {
			int max_col = -1;
			int num = -1;
			for (int j = cols; j-->0;) {
				if (remaining[j] > num) {
					max_col = j;
					num = remaining[j];
				}
			}
			int k = 0;
			for (int i = rows[max_col] - remaining[max_col]; i < rows[max_col] && i - (rows[max_col] - remaining[max_col]) < exam_type[subj]; i++) {
				seating[i][max_col] = students.top();
				students.pop();
				k++;
			}
			exam_type[subj] -= k;
			remaining[max_col] -= k;
		} else if (door == 'l' || door == 'L') {
			for (int i = 0; i < cols && !students.empty() && exam_type[subj] > 0; i++) {
				for (int j = 0; j < max_row && !students.empty() && exam_type[subj] > 0; j++) {
					if (rows[i] > j) {
						seating[j][i] = students.top();
						students.pop();
						exam_type[subj]--;
						remaining[i]--;
					}
				}
			}
		} else {
			for (int i = cols; i--> 0 && !students.empty() && exam_type[subj] > 0;) {
				for (int j = 0; j < max_row && !students.empty() && exam_type[subj] > 0; j++) {
					if (rows[i] > j) {
						seating[j][i] = students.top();
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
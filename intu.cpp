#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

class person {
	public:
		string name;
		string subject;
		int exam_num;
};


const string delimit = " ";
// Exams sorted in terms of length of exam
map<string, int> exam_type = {
	{"HMX2", 0},
	{"HM", 1},
	{"HC", 2},
	{"HP", 3},
	/*{"PMX", 4},
	{"PM", 5},
	{"PC", 6},
	{"PP", 7},
	{"Y10",8},*/
	{"HMX1", 10}
};

// Custom operator to check if the lhs exam is 'less' than the rhs exam
// Sort by subject (in decreasing number) then exam number then individual name when student is added to the queue
class comp{
	public:
		bool operator()(person lhs, person rhs) {
			if (exam_type[lhs.subject.c_str()] != exam_type[rhs.subject.c_str()]) return exam_type[lhs.subject.c_str()] < exam_type[rhs.subject.c_str()];
			else {
				if (lhs.subject.c_str() != rhs.subject.c_str()) return lhs.subject.c_str() < rhs.subject.c_str();
				else {
					if (lhs.exam_num != rhs.exam_num) return lhs.exam_num < rhs.exam_num;
					else return lhs.name.c_str() < rhs.name.c_str();
				}
			}
		}
};


int main(){
	priority_queue<person, vector<person>, comp> students;
	int cols, stu_num, max_row = -1;
	
	// Scanning in layout of room
	scanf("%d", &cols);
	int rows[cols];
	for (int i = 0; i<cols; i++) {
		scanf("%d", &rows[i]);
		if (rows[i] > max_row) max_row = rows[i];
	}
	
	// Scanning in student info
	scanf("%d", &stu_num);
	for(int i = 0; i<stu_num; i++) {
		person student;
		scanf("%s", student.name.c_str());
		scanf("%s", student.subject.c_str());
		scanf("%d", student.exam_num);
		students.push(student);
	}
	
	// Seating students with shorter exams closer to door
	person seating[max_row][cols];
	for(int i = 0; i<max_row; i++) {
		for(int j = cols-1; j>=0; j--) { //i and j value can be altered if corner of door changes
			if (!students.empty() && rows[j] > i) {
				seating[i][j] = students.top();
				students.pop();				
			}
		}
	}
	
	// Printing seating arrangement
	for(int i = 0; i<max_row; i++) {
		for(int j = 0; j<cols; j++) {
			if (rows[j] > i) printf("%4s", seating[i][j].name.c_str());
			else printf("    ");
			printf("\t");
		}
		printf("\n");
	}
	
	// Debugging for printing student details
	//for(;!students.empty();students.pop()){
	//	printf("%s %s %d\n", students.top().name.c_str(), students.top().subject.c_str(), students.top().exam_num);
	//}
	return 0;
}

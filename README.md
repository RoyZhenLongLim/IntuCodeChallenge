# Intu Code Challenge

## Key Information
[my-i Code Challenge](https://www.intuitioneducation.com.au/media/1578/my-i-code-challenge-2022.pdf)

## Tutorial on testing intu.py
Make sure you have installed python 3 on your system

### Running the Code
Run the following in the terminal of current working directory to run a test case

```commandline
python3 intu.py < Input/TestX.in > Output/TestX.out
```

For example,

```commandline
python3 intu.py < Input/Test1.in > Output/Test1.out
```
 
- Input is stored as a text file ending with in
- Output is stored as a text file ending with out

### Creating your own tests

Copy `Test1.in`

1. Modify the name of `TestX.in` 
2. The first line represents the number of rows in each column
   - An input of "1 1" means there are two columns with 1 row each
3. The rest of lines contain information on the student in the following format
   - {Student Number} {Subject} {Exam Number}
4. Make sure the bottom of the file has two empty lines
   - This is just due to implementation :p 


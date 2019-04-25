# LineIntersection
Computational Geometry Assignment 1

# Results
We have given an implementation of the Bentley-Ottmann plane sweep algorithm for line segment intersection.<br>
We randomly generated lines by randomly generating their end points and the ran the algorithm on the lines to find the intersection points.


| Number of Lines | Run Time - Total CPU time(s) |
|:-----:|:-----:|
| 2 | ~0.005 |
| 10 | ~0.005 |
| 50 | 0.011 |
| 100 | 0.023 |
| 500 | 0.110 |
| 1,000 | 0.180 |
| 5,000 | 2.500 |
| 10,000 | 13.400 |
| 20,000 | 61.170 |

The complexity of the Bentley-Ottmann algorithm is given as **O(nlogn + Ilogn)** <br>
where n is the number of line segments and I is the number of intersection points.<br>
The run time observed does not indicate how much the complexity is for each input size, <br>
but instead we can observe the trend of how the time takes rows as a function of the imput size.<br>
The actual time also depends upon the memory allocation and allotment for vector and tree data<br> structures. 

<br>
## Input
![Input Image](linesInput.png "Input through Qt GUI")

<br>
## Output
![Output Image](linesOutput.png "Output displyed using matplotlib")

<br>
<br>
## An example of the line intersection computation:
### Status Tree Generation
Insertion happens at a given Y - Co-ordinate which is 2 for this case.
- (0,0) (0,2)
- (0,0) (2,2)
- (0,0) (2,4)
- (0,0) (2,6)
- (0,0) (2,8)

Generating the tree:

0.000000 0.000000 2.000000 6.000000 4

0.000000 0.000000 0.000000 2.000000 3

0.000000 0.000000 0.000000 2.000000 1

0.000000 0.000000 2.000000 8.000000 2

0.000000 0.000000 2.000000 8.000000 1

0.000000 0.000000 2.000000 6.000000 1

0.000000 0.000000 2.000000 4.000000 2

0.000000 0.000000 2.000000 4.000000 1

0.000000 0.000000 2.000000 2.000000 1

Popping the line (0,0) - (2,6) at Y = 2 yields the tree:

0.000000 0.000000 2.000000 4.000000 4

0.000000 0.000000 0.000000 2.000000 3

0.000000 0.000000 0.000000 2.000000 1

0.000000 0.000000 2.000000 8.000000 2

0.000000 0.000000 2.000000 8.000000 1

0.000000 0.000000 2.000000 2.000000 2

0.000000 0.000000 2.000000 4.000000 1

### Event Queue Generation
Let the event points be (assuming all upper end points to show the value of U stored):

- (1,2)
- (2,3)
- (3,4)
- (3,6)
- (3,5)

Generating the tree:

2.000000 3.000000 3
 U:2.000000 3.000000 3.000000 4.000000

1.000000 2.000000 1
 U:1.000000 2.000000 2.000000 1.000000

3.000000 5.000000 2
 U:3.000000 5.000000 4.000000 3.000000

3.000000 4.000000 1
 U:3.000000 4.000000 2.000000 3.000000

3.000000 6.000000 1
 U:3.000000 6.000000 7.000000 4.000000


 Popping results:

Popping event point 3.000000,6.000000
New Tree:

2.000000 3.000000 3
 U:2.000000 3.000000 3.000000 4.000000

1.000000 2.000000 1
 U:1.000000 2.000000 2.000000 1.000000

3.000000 5.000000 2
 U:3.000000 5.000000 4.000000 3.000000

3.000000 4.000000 1
 U:3.000000 4.000000 2.000000 3.000000

### Main algorithm

For the lines:

- (1,1) - (11,11)
- (1,11) - (11,1)
- (1,11) - (11,11)
- (11,11) - (11,1)
- (11,1) - (1,1)
- (1,1) - (1,11)

Results:

Intersection: 1.000000 11.000000

Intersection: 11.000000 11.000000

Intersection: 6.000000 6.000000

Intersection: 1.000000 1.000000

Intersection: 11.000000 1.000000


Execution complete
Execution time in secinds: 0.191

## Instructions for running the code:
+ Install Qt5 for gui:
+ Install matplotlib for displaying results:
+ compile run.cpp
+ run code:
bash execute.sh
# Polygon Triangulation
Computational Geometry Assignment 2

# Results
The Polygon Triangulation has been implemented in 3 stages:
+ DCEL structure ( made up of vertices, edges and faces ) to store the polygon(s).
+ Convert the polygon into y- Monotone polygon(s).
+ Triangulate the y-monotone polygon(s). 


![CPU Time](table.png "CPU Time")

![CPU Time vs No. of points](chart.png "CPU Time vs No. of points")

## Complexity Analysis
**Converting to y-monotone:**
Constructing the priority queue takes O(nlogn) for n vertices as each is handled after sorting. <br>
Queries and updates on binary trees take O(logn) time. Thus handling all the events takes O(nlogn) time.<br>
The algorithm takes O(n) space.<br>
**Triangulation**
Since, the number of pushes is bounded by O(n), the number of pops from the stack cannot be greater than <br>
that. Thus, the time complexity is O(n) ans space complexity is also O(n).

<br>
## Input:
![Input Image](1.png "Input Polygon through Qt GUI")

<br>
## After converting to y-monotone polygons:
![Output Image1](2.png "converting to y-monotone polygons")

<br>
## After triangulation of y-monotone polygons:
![Output Image2](3.png "triangulation")

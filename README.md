 An assignment for the class advanced programming 1 by etgar and yehuda

# Milestone 2

In this milestone we essentionally made a server and a client. The client connects to the server (using tcl protocol). send the server a vector a distance method and a number in this form:

 x1 x2 x3 ... xn MAN/AUC/CHB/CAN/MIN number
 
and the server returns the distance method to be printed by the client, or invalid arguments.


# Milestone 1B

compile: The program can be compiled using a Makefile.

command line (You need to give three arguments to the run the program): ./a.out int file(path/name) distance(MAN/AUC/CHB/CAN/MIN)  

You can insert a vector input according to the length of the vectors in the input file and get the appropriate labeling, the insertion is done in an infinite loop


intro to program:

The program is a K-Nearest Neighbors (KNN) algorithm implementation in C++.
 The KNN algorithm is a classification algorithm that takes in a labeled dataset and a new unlabeled data point,
 and assigns a label to the new data point based on the labels of the nearest data points in the labeled dataset.

flow of the program:

getVector(our main):

The program takes three command line arguments: a value for k (the number of nearest neighbors to consider), a file containing the labeled training data, and a string indicating the distance metric to use. The getInput() function reads a vector of numbers from the user and verifies that it is valid (i.e. no ".." and at least one number is provided). The getClsVecs() function reads a file containing labeled training data, replaces commas with spaces, and parses the resulting string into a vector of pairs, where each pair contains a vector of doubles and a string. The testK() function checks whether a given string consists only of digits. The main() function parses the command line arguments, verifies their validity, and uses them to run the KNN algorithm in an infinite loop.

select:

implementation of the select function, which is used to select the kth smallest element from a given vector of values.
the function do it in O(n) runtime. The function uses finding a pivot by using the median of the medians.

KNN class:

knn has three members: a vector containing the labeled data, a number k for the desired number of neighbors, and a distance class to calculate according to the desired distance. In addition, the class has several methods, the main of which is the getTag() function, which are designed to return the desired label according to the vector from the user. 

IDistance class: a interface for any distance, so that theres no need to rely on a sigle implementation. holds get distance method that takes two vectors and return a double. knn stores a IDistance class.

Distance factory: takes a string and picks a distance class accordingly and uses it to return the distance, inplements IDistance.

changed the distances into IDistance classes.


# milestone 1A!

get input function: 
function that get a vector from the user and check if the vector is valid.
The return value is a valid vector.
the function get string from the user by getline(), and throw error and exit if in input has "..".
the function insert valid number into the vector by "iStringStream", only valid values are entered.
valid values are numbers from the shape: 

"x", "x.yyyy", ".yyy" - translate to "0.yyyy", "x." - translate to "x.0".

all these shape can get "minus" at the beginning of the number.
If another characters/shapes are inserted, the vector will contain all the valid values until the invalid character that inserted.
if there is no number in the vector, the function throw error and exit.

  If the number is integer, the printout will look like this:
  
    x.0
    
  If the number is not a whole number, the printout will look like this:
  
    x.yyyyyyy, 7 number after the dot.
    

distances  we implemented

Euclidean distance - according to - https://en.wikipedia.org/wiki/Euclidean_distance.

Taxicab geometry distance - according to - https://en.wikipedia.org/wiki/Taxicab_geometry.

Chebyshev distance - according to - https://en.wikipedia.org/wiki/Chebyshev_distance.

Canberra distance - according to - https://en.wikipedia.org/wiki/Canberra_distance.

Canberra distance - according to - https://en.wikipedia.org/wiki/Minkowski_distance.

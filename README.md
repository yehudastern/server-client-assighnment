 An assignment for the class advanced programming 1 by etgar and yehuda

# Milestone 3

in this assignment we made the server use threads for each client, added an interface for a client to get requesets to give train data and get train data classified.
the option are to upload the train and test data, set k and distance method, classify the data, print the results or store them in a file with a chosen path.

compile is the same as previous milestone. the difference is in running, now server.out doesnt get a file in the command line - ./server.out port.

lets go over what we added and changed.

## the server's side:
- cli: cli communicates with the client and starts the commands to do the requests of the client.
- inteface command: the interface to all the different commands, it has a execute method that excecutes the command.
- upload command: gets the data from the client and saves it and process it to vectors.
- setting algorithm command: set k and distance for the knn algorithm, checks that they vaild.
- classified command: classify all the vector from unclassified file, and save thier tag with the approriate vector.
- display command: Sending all the tags of the unclassified vector to client for printing.
- download command: Sending all the tags of the unclassified vector to client for put thier in file.
- DefaultIO: defines an interface for io that the cli uses.
- ManageData: this class stores the data the different commands use. it has the classified vector with the tags and the unclassified vector without the tags, also it has the distance method and the k. it lies in cli.
- server.cpp : runs the server, starts new threads for each client, each thread starts cli of each own.
- server class - mainly the same only now gets a cli socket number to send messages to and get messages from.
- socket io: inherits default io, connects between the socket and some other side. has read, write and close socket.
## the clients's side:
- cli: cli communicates with the server and starts the commands to oprate the server.
- inteface command: the interface to all the different commands, it has a execute method that excecutes the command.
- upload command: used to upload a dataset to the K-nearest neighbors (KNN) algorithm. performance check to the path.
- setting algorithm command: get from the user input for k and distance to knn algorithm, and send them to the server
- classified command: oprate the server to classify all the vector from unclassified file.
- display command: get all the tagged that classified from server and print them to the screen.
- download command: get all the tagged that classified from server and write them to the file.
- DefaultIO: defines an interface for io that the cli uses.
- client.cpp : runs the client, creat a client and connect to server, and strat cli to oprate knn algorithm option.
- client class - mainly the same only now gets a server socket number to send messages to and get messages from.
- socket io: inherits default io, connects between the socket and some other side. has read, write and close socket.

# Milestone 2

In this milestone we essentionally made a server and a client. The client connects to the server (using tcl protocol). Send the server a vector a distance method and a number in this form:

     x1 x2 x3 ... xn MAN/AUC/CHB/CAN/MIN number (vector distance k)
 
And the server returns the distance method to be printed by the client, or invalid arguments.
 - Compile: We provided a Makefile, so use make to create the server and client executables.
 - Command line for the server:
 
     ./server.out file port
     
 - for the client:
 
     ./client.out ip port

Added classes:

Get input: 

- The GetInput class is used to read in data from a dataset and store it in a vector of pairs, where each pair consists of a vector of doubles and a string. The GetInput class also gets the information the client sends and converts it into a vector of doubles, a distance method, and a k (the k closest vectors to check). If the information the user entered is wrong it saves that. It can than be used to fuel the knn class to get the results.

Server class: 

- This code defines a class ServerClass for a server in a client-server network communication. The server can send and receive messages to and from a server, and the class provides methods for connecting to the client, receiving messages, and sending messages. (See below for more details about the main methods)

- The server can be initialized as follows: ServerClass(string fileName, int port), It takes two parameters - fileName: a string containing the name of a file, port: an int representing the port number to bind the server's socket to. The constructor creates a socket and binds it to the specified port using the AF_INET address family and the SOCK_STREAM socket type. It then creates an instance of the GetInput class (see above) and stores it in the m_input member variable. If either the socket creation or binding fails, an error message is printed to stderr and the program exits with a status code of 1.

- The server_accept() method listens for a connection from a client on the server's socket and, if one is received, accepts it and stores the resulting client socket in the m_client_sock member variable. If there is an error listening to or accepting a connection, an error message is printed to stderr.

- The server_recv() method receives data from the client socket stored in m_client_sock. It reads the data into a buffer and if the data is exist then passes it to the setInfo method of the m_input object(for recives organization data). If there was an error receiving data from the client, an error message is printed to stderr and 0 is returned (for close the connect with the client). If the connection was closed by the client, a message is printed to cout and 0 is returned. Otherwise, 1 is returned (for coninue in the loop).

- The server_send() method processes the data received from the client using the Knn class and sends the result back to the client. It first checks the value of the m_input object's getflag method to determine if the data was properly formatted. If it was, the Knn class is used to classify the data and the resulting tag is sent to the client. If the getflag of Knn or GetInput Class returns 0, indicating an error in the input data, an error message is sent to the client instead.

Client class:

- This code defines a class ClientClass for a client in a client-server network communication. The client can send and receive messages to and from a server, and the class provides methods for connecting to the server, sending messages, and receiving messages.

- The class has a constructor that takes an IP address and port number as arguments, and creates a socket for the client. It also has connect() method that attempts to connect the client to the server using the provided IP address and port number.

- The sendMessage() method sends a message to the server, and the receiveMessage() method receives a message from the server. The sendError() method is called when there is an error in the communication, and it sends an error message to the server.

- The checkIp() and checkPort() methods are helper functions that validate the IP address and port number, respectively. If either of them is invalid, the program exits with an error message.

server.cpp and client.cpp run the server and the class using the server class and client class. The server performs several normal checks for the input received in the command line, and runs in a loop to receive a client, when it succeeds in connecting, it remains in another internal loop as long as the transmitted information is correct.

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

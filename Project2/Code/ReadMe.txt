Daniel Louis
Algorithms 
Project 2 : Convex hull

	To run this program, first run cmake using the CMakeLists.txt provided, then with that to call the program type ./ConvexHull followed by two arguments. The first argument is which of the three algorithms would you wish to run G for Graham Scan, J for Jarvis march, Q for quickhull. The second argument is the file that contains the points that the hull will ceround. So to finish type ./ConvexHull G test.txt and this will call the Graham scan to be made with the points in test.txt.

	This program contains three algorithms that will construct a 2 dimensional convex hull around points given in an extra external file provided.

		The first of these three is the Graham scan which will follow though step by step in order to check every point and see what ones should be on the convex hull. 

		The second one is the Jarvis march which will also march through each point in order to create the convex hull.

		The finial algorithm is the quickhull which will continuously cut the points in half until the are no more points that are outside the hull then it will work on the other side so it is close to merge sort without having to merge anything together. 

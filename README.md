# Candidate-Elimination-Learning-Algorithm

This work is an implementation of the candidate elimination algorithm proposed by Tom Mitchell. The dataset consists of various animals and their relevant features. The task is to classify each animal into their groups by applying the algorithm to generate general and specific boundaries. There are 7 different animal classes and the algo tries to generate boundaries and help narrow them down to classify new animals based on their features.

Usage:
------
go to src directory and type "g++ *.cpp". 
Now run the executable file to generate the output.

Output:
-------
Displays whether the concept can be learned or not for the particular class. Also displays the general and specific boundary for each class if concept learning is possible.

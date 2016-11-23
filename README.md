# AmericanOptionTrees

A library to visualize the evolution of American put option prices on a binomial tree, marking also which are the exercise nodes. The numerical work is in C++ and the visualization is in python.

## The Calculator
The calculator is compiled using g++ with `make bin/americancalc`. It allows you to save the computed price tree of a put option in a text file.

The structure of the saved trees are as follows:
 1. each consecutive line is an additional layer of the tree corresponding to a given time,
 2. each line contains a list of the prices separated by commas, 
~~~~
[ ... ], ... , [ ... ]
~~~~
starting from the top-most node,
 3. each bracketed price contains a list of pairs `(price,bool)` separated by commas. The pair contains the price and whether the option was exercised. 
 
 The tree might contain more than one valued option. But the calculator will calculate the tree of only one put option. The first line might thus look like (if time zero has depth 0)
`[(price, bool)]`
the second line will be
`[(price1,bool1)], [(price2,bool2)]`
and so on.

You can also compile with g++ run `make all`. You may then visualize elsewhere, for instance using the python notebook in the folder `python/`.

## Roadmap
The plan is to evolve the library and wrap it under python using for instance pybind11.

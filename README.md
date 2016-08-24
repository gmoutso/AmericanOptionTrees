# AmericanOptionTrees

A library to visualize the evolution of American put option prices on a binomial tree, marking also which are the exercise nodes.

What works so far is... everything but the visualization. You can save the computed tree in a text file and import it in python to graph the colored surface price(time,spot). 

The structure of the saved tree is as follows:
1. Each consecutive line is an additional layer of the tree,
2. Each line contains a list of the prices separated by commas,
~~~~
[ ... ], ... , [ ... ]
~~~~
starting from the top-most node,
3. Each bracketed price contains a list of pairs separated by commas. The pair contains the price and whether the option was exercised. The tree might contain more than valued option.
For instance, if we start with one node at time zero, and one option, the first line will be 
`[(price, bool)]`
the second line will be
`[(price1,bool1), (price1)]`
and so on.

To compile with g++ run `make all`.

To do: wrap a shared library with a python module.


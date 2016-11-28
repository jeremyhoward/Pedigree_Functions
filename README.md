# Pedigree Functions

Usefull C++ code that I use to output a relationship matrix based on pedigree information in row-column-value format for the complete set of animals or a subset of animals.

# Input 
This function takes in as input the name of the pedigree file that contains three columns seperated by a space. The three columns refer to the animal sire and dam and can be in any format (i.e. numeric or alpha-numeric). An animal can't have a value of zero and missing parents have a value of 0.

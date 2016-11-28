# Pedigree_Functions

Usefull function that I used to read in a pedigree file, sort it so parents come before progeny and the output a relationship matrix in row-column-value format.

# Input 
This function takes in as input the name of the pedigree file that contains three columns seperated by a space. The three columns refer to the animal sire and dam and can be in any format (i.e. numeric or alpha-numeric). An animal can't have a value of zero and missing parents have a value of 0.

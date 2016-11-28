# Pedigree Functions
C++ code that I have used to output a relationship matrix based on pedigree information in row-column-value format for the complete set of animals or on a subset of animals.

# Input 
PEDIGREE FILE NAME: This function takes in as input the name of the pedigree file that contains three columns separated by a space. The three columns refer to the animal sire and dam and can be in any format (i.e. numeric or alpha-numeric). An animal can't have a value of zero and missing parents have a value of 0.

OUTPUT SORTED PEDIGREE NAME: Name of file that will be generated that contains a sorted pedigree so parents come before progeny

OUTPUT FULL RELATIONSHIP NAME: Name of file that will be generated that contains the full upper-diagonal of the pedigree based relationship for all animals

SUBSET ANIMAL IDS: A file with IDs for animals that you want relationship information for. The row and column will be in the same order that the IDs are in with the associated file that is gets read in. This is optional and not required to run.

# To Compile
g++ pedigree_functions.cpp -o pedigreefun

# To Run
Only need full relationship: "./pedigreefun smallpedigree.txt pedigreesorted fullrelationship"
Need full and subset relationship: "./pedigreefun smallpedigree.txt pedigreesorted fullrelationship subsetids"

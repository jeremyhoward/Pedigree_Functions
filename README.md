# Pedigree Functions
C++ code that I have used to output a relationship matrix based on pedigree information in row-column-value format for the complete set of animals or on a subset of animals.

# Input 
PEDIGREE FILE NAME: This function takes in as input the name of the pedigree file that contains three columns separated by a space. The three columns refer to the animal sire and dam and can be in any format (i.e. numeric or alpha-numeric). An animal can't have a value of zero and missing parents have a value of 0.

SUBSET ANIMAL IDS: A file with IDs for animals that you want relationship information for. The row and column will be in the same order that the IDs are in with the associated file that is gets read in.

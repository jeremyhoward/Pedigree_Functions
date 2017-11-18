#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
using namespace std;

class Pedigree_Class
{
private:
    string animal;              /* Original Animal ID */
    string sire;                /* Original Sire ID */
    string dam;                 /* Orignal Dam ID */
    int renum_anim;             /* Renumbered ID */
    int generation;             /* Generation Number */
public:
    Pedigree_Class();
    Pedigree_Class(string anim = "", string si = "", string da = "", int reanim = 0, int gen = 1);
    ~Pedigree_Class();
    string getanim(){return animal;}
    string getsire(){return sire;}
    string getdam(){return dam;}
    int getrenumanim(){return renum_anim;}
    int getgener(){return generation;}
    void Update_Generation(int temp);
    void Update_Renum_Anim(int temp);
    friend bool sortByGen(const Pedigree_Class&, const Pedigree_Class&);        /* Used to sort by generation */
};

Pedigree_Class::Pedigree_Class(){animal = ""; sire = ""; dam = ""; renum_anim = 0; generation = 0;}
Pedigree_Class::Pedigree_Class(string anim, string si, string da, int reanim, int gen)
{
    animal = anim; sire = si; dam = da; renum_anim = reanim; generation = gen;
}
// Destructors
Pedigree_Class::~Pedigree_Class(){};
// Functions
void Pedigree_Class::Update_Generation(int temp){generation = temp;}
void Pedigree_Class::Update_Renum_Anim(int temp){renum_anim = temp;}
// Sort objects
bool sortByGen(const Pedigree_Class &lhs, const Pedigree_Class &rhs) {return lhs.generation > rhs.generation;}

/* Status bar for constructing A Matrix */
static inline void loadbar(unsigned int x, unsigned int n, unsigned int w = 50)
{
    if((x != n) && (x % (n/100+1) != 0)) return;
    float ratio_ =  x/(float)n;
    int c = int(ratio_ * w);
    cout << setw(3) << (int)(ratio_*100) << "% [";
    for (int x=0; x<c; x++) cout << "|";
    for (int x=c; x<w; x++) cout << " ";
    cout << "]\r" << flush;
}

int main(int argc, char* argv[])
{
    time_t full_begin_time = time(0);
    cout << endl;
    cout <<"+-----+-----+-----+-----+-----+-----+-----+------+-----+" << endl;
    cout <<"|                                        ///\\\\\\        |" << endl;
    cout <<"|                                       /      \\       |" << endl;
    cout <<"|  Pedigree Relationship Functions     #-/.\\==/.\\      |" << endl;
    cout <<"|  Author: Jeremy T. Howard           (, \\_/ \\\\_/      |" << endl;
    cout <<"|  Updated: Date: 11/18/2017           |    -`  |      |" << endl;
    cout <<"|                                       \\  \\_/ /       |" << endl;
    cout <<"|                                      /`-.__.`        |" << endl;
    cout <<"|                                   .-'`-.___|__       |" << endl;
    cout <<"+-----+-----+-----+-----+-----+-----+-----+------+-----+" << endl;
    cout <<"| This program is free software: you can redistribute  |" << endl;
    cout <<"| it and/or modify it under the terms of the GNU       |" << endl;
    cout <<"| General Public License as published by the Free      |" << endl;
    cout <<"| Software Foundation, either version 3 of the License,|" << endl;
    cout <<"| or (at your option) any later version.               |" << endl;
    cout <<"+-----+-----+-----+-----+-----+-----+-----+------+-----+" <<endl;
    cout << endl;
    if(argc != 4 && argc != 5){cout << "Incorrect Number of parameters specified" << endl; exit (EXIT_FAILURE);}
    /* Pedigree file */
    string pedigree_file = argv[1];
    string pedigree_sorted = argv[2];
    string pedigree_file_out = argv[3];
    string outsubsetrelationship;
    if(argc == 5){outsubsetrelationship = argv[4];}
    cout << "- Pedigree file name is '" << pedigree_file << "'." << endl;
    cout << "   - Assume that: " << endl;
    cout << "       - Column 1 is Animal; Column 2 is Sire; Column 3 is Dam." << endl;
    cout << "       - Missing is either a '.', '0' or '-'." << endl;
    cout << "       - No header in file and is space delimeted." << endl;
    cout << "- The sorted pedigree file will be saved to the following file: '" << pedigree_sorted << "'." << endl;
    cout << "- Relationships matrix will be output to the following file: '" << pedigree_file_out << "'." << endl;
    if(argc == 5){cout << "-The IDs from '" << outsubsetrelationship << "' file will be calculated and put in 3 column format." << endl;}
    cout << endl;
    /* Read in Pedigree file */
    vector <string> numbers;
    string line;
    /* Import file and put each row into a vector then grab chromsome and position */
    ifstream infile;
    infile.open(pedigree_file.c_str());
    while (getline(infile,line)){numbers.push_back(line);}
    cout << "- Pedigree file read in and number of animals is " << numbers.size() << endl << endl;
    vector < Pedigree_Class > pedigree;
    vector < string > Orig_Animal(numbers.size(),"");          /* vector to store original animals id's */
    vector < string > Orig_Sire(numbers.size(),"");             /* vector to store original sire id's */
    vector < string > Orig_Dam(numbers.size(),"");              /* vector to store original dam id's */
    vector < int > Row(numbers.size(),1);
    vector < int > Generation(numbers.size(),1);
    for(int i = 0; i < numbers.size(); i++)
    {
        string temp = numbers[i]; size_t pos = temp.find(" ", 0); string tempanimal = temp.substr(0,pos); temp.erase(0, pos+1);
        pos = temp.find(" ", 0); string tempsire = temp.substr(0,pos); temp.erase(0, pos+1); string tempdam = temp;
        /* if you find one of the possible missing value change it to 0 */
        if(tempsire == "." || tempsire == "-"){tempsire = "0";}
        if(tempdam == "." || tempdam == "-"){tempdam = "0";}
        /* save in class */
        Pedigree_Class pedigreetemp(tempanimal,tempsire,tempdam,1,1);
        pedigree.push_back(pedigreetemp);
    }
    cout << "- Parsed out file into animal, sire and dam." << endl;
    cout << "   - Row 1: - Animal (" << pedigree[0].getanim() << "); Sire (";
    cout << pedigree[0].getsire() << "); Dam (" << pedigree[0].getdam() << ")." << endl;
    cout << "   - Row 1: - Animal (" << pedigree[1].getanim() << "); Sire (";
    cout << pedigree[1].getsire() << "); Dam (" << pedigree[1].getdam() << ")." << endl;
    /* check to make sure all sire and dams are represented as an animal and assume both parents are unknown */
    int uniquesiredam; string kill = "NO";
    while(kill != "YES")
    {
        int i = 0;
        while(i < pedigree.size())
        {
            if(pedigree[i].getsire() != "0")
            {
                int j = 0; string found = "NO";
                /* grab sire and see if it is an animal */
                while(found == "NO")
                {
                    if(pedigree[i].getsire() == pedigree[j].getanim()){found = "YES";}
                    j++;
                    if(j > pedigree.size())
                    {
                        Pedigree_Class pedigreetemp(pedigree[i].getsire(),"0","0",1,1);
                        pedigree.push_back(pedigreetemp);
                        found = "YES";
                    }
                }
            }
            if(pedigree[i].getdam() != "0")
            {
                int j = 0; string found = "NO";
                while(found == "NO")
                {
                    if(pedigree[i].getdam() == pedigree[j].getanim()){found = "YES";}
                    j++;
                    if(j > pedigree.size())
                    {
                        Pedigree_Class pedigreetemp(pedigree[i].getdam(),"0","0",1,1);
                        pedigree.push_back(pedigreetemp);
                        found = "YES";
                    }
                }
            }
            i++;
            //cout << pedigree.size() << endl;
        }
        kill = "YES";
        //for(int i = 0; i < pedigree.size(); i++)
        //{
        //    cout<<pedigree[i].getanim()<<" "<<pedigree[i].getsire()<<" "<<pedigree[i].getdam()<<" "<<pedigree[i].getgener()<<endl;
        //}
        //cout << endl;
    }
    for(int i = 0; i < pedigree.size(); i++)
    {
        if(pedigree[i].getanim() == "0"){cout << endl << "Animal ID can't be 0" << endl; exit (EXIT_FAILURE);}
    }
    cout << "   - Size of pedigree object: " << pedigree.size() << ". " << endl << endl;
    cout << "- Ensure Pedigree is sorted so parents come before progeny." << endl;
    /* Algorithm works by proceeding through the pedigree one animal at a time and all animals begin with generation number = 1. */
    /* Take current generation and increase it by 1 and compare m to the generation number of sire and dam. If it is less than sire */
    /* and dam then change DD to generation 2; This was taken from Dr. Schaeffer's Notes. */
    int orderiteration = 0;
    string done = "NO";
    while(done == "NO")
    {
        orderiteration++; int numberchanged = 0;
        for(int i = 0; i < pedigree.size(); i++)
        {
            if(pedigree[i].getsire() != "0" | pedigree[i].getdam() != "0")
            {
                for(int j = 0; j < pedigree.size(); j++)
                {
                    if(pedigree[i].getsire() == pedigree[j].getanim())
                    {
                        if(pedigree[j].getgener() <= pedigree[i].getgener()){pedigree[j].Update_Generation(pedigree[i].getgener() + 1); numberchanged++;}
                    }
                    if(pedigree[i].getdam() == pedigree[j].getanim())
                    {
                        if(pedigree[j].getgener() <= pedigree[i].getgener()){pedigree[j].Update_Generation(pedigree[i].getgener() + 1); numberchanged++;}
                    }
                }
            }
        }
        if(orderiteration % 1 == 0){cout << "   - " << orderiteration << " (Changed Generation: " << numberchanged << ")" << endl;}
        if(numberchanged == 0){done = "YES";}
    }
    sort(pedigree.begin(), pedigree.end(), sortByGen);
    cout << "   - Took " << orderiteration << " iterations of the algorithm to figure out order." << endl;
    cout << "- Output Sorted Pedigree." << endl;
    fstream checkRela; checkRela.open(pedigree_sorted.c_str(), std::fstream::out | std::fstream::trunc); checkRela.close();
    /* Save as a continuous string and then output */
    stringstream outputstringped(stringstream::out); int outputnumberped = 0;
    for(int i = 0; i < pedigree.size(); i++)
    {
        outputstringped << pedigree[i].getanim()<<" "<<pedigree[i].getsire()<<" "<<pedigree[i].getdam() << endl;
        if(outputnumberped % 1000 == 0)
        {
            /* output pheno pedigree file */
            std::ofstream output10(pedigree_sorted.c_str(), std::ios_base::app | std::ios_base::out);
            output10 << outputstringped.str(); outputstringped.str(""); outputstringped.clear();
        }
        outputnumberped++;
    }
    std::ofstream output10(pedigree_sorted.c_str(), std::ios_base::app | std::ios_base::out);
    output10 << outputstringped.str(); outputstringped.str(""); outputstringped.clear();
    cout << "- Pedigree is sorted so parents come before progeny." << endl;
    //for(int i = 0; i < pedigree.size(); i++)
    //{
    //    cout<<pedigree[i].getanim()<<" "<<pedigree[i].getsire()<<" "<<pedigree[i].getdam()<<" "<<pedigree[i].getgener()<<endl;
    //}
    //cout << endl;
    /* Now set renumber ID */
    for(int i = 0; i < pedigree.size(); i++){pedigree[i].Update_Renum_Anim(i+1);}
    //for(int i = 0; i < pedigree.size(); i++)
    //{
    //    cout<<pedigree[i].getanim()<<" "<<pedigree[i].getsire()<<" "<<pedigree[i].getdam()<<" "<<pedigree[i].getgener()<<" ";
    //    cout<<pedigree[i].getrenumanim()<<endl;
    //}
    //cout << endl;
    /* Now Create Relationship Matrix, but first need to renumber */
    cout << "- Begin constructing Relationship Matrix." << endl;
    time_t A_begin_time = time(0);
    cout << "   - renumber id's so are integer (1:number of animals)." << endl;
    vector < int > renum_animal(pedigree.size(),0);
    vector < int > renum_sire(pedigree.size(),0);
    vector < int > renum_dam(pedigree.size(),0);
    for(int i = 0; i < pedigree.size(); i++)
    {
        renum_animal[i] = pedigree[i].getrenumanim();
        string temp = pedigree[i].getanim();
        for(int j = 0; j < pedigree.size(); j++)
        {
            /* change it if sire or dam */
            if(temp == pedigree[j].getsire()){renum_sire[j] = pedigree[i].getrenumanim();}
            if(temp == pedigree[j].getdam()){renum_dam[j] = pedigree[i].getrenumanim();}
        }
    }
    //for(int i = 0; i < pedigree.size(); i++)
    //for(int i = 0; i < 25; i++)
    //{
    //    cout<<renum_animal[i]<<" "<<renum_sire[i]<<" "<<renum_dam[i]<<endl;
    //}
    //cout << endl;
    cout << "   - Constructing A matrix." << endl;
    /* initialzie 2-D vector to 0 */
    vector< vector < double >> Amatrix;
    for(int i = 0; i < pedigree.size(); i++)
    {
        vector < double > row(pedigree.size(),0); Amatrix.push_back(row);
    }
    /* Construct Full A Matrix */
    for(int i = 0; i < renum_animal.size(); i++)
    {
        if (renum_sire[i] != 0 && renum_dam[i] != 0)
        {
            for (int j = 0; j < i; j++)
            {
                Amatrix[j][i] = Amatrix[i][j] = 0.5 * (Amatrix[j][(renum_sire[i]-1)] + Amatrix[j][(renum_dam[i]-1)]);
            }
            Amatrix[(renum_animal[i]-1)][(renum_animal[i]-1)] = 1 + 0.5 * Amatrix[(renum_sire[i]-1)][(renum_dam[i]-1)];
        }
        if (renum_sire[i] != 0 && renum_dam[i] == 0)
        {
            for (int j = 0; j < i; j++)
            {
                Amatrix[j][i] = Amatrix[i][j] = 0.5 * (Amatrix[j][(renum_sire[i]-1)]);
            }
            Amatrix[(renum_animal[i]-1)][(renum_animal[i]-1)] = 1;
        }
        if (renum_sire[i] == 0 && renum_dam[i] != 0)
        {
            for (int j = 0; j < i; j++)
            {
                Amatrix[j][i] = Amatrix[i][j] = 0.5 * (Amatrix[j][(renum_dam[i]-1)]);
            }
            Amatrix[(renum_animal[i]-1)][(renum_animal[i]-1)] = 1;
        }
        if (renum_sire[i] == 0 && renum_dam[i] == 0)
        {
            Amatrix[(renum_animal[i]-1)][(renum_animal[i]-1)] = 1;
        }
        //loadbar(i+1,pedigree.size());
    }
    time_t A_end_time = time(0);
    cout << "- Finished Constructing A Matrix (Took: ";
    cout << difftime(A_end_time,A_begin_time) << " seconds)" << endl << endl;
    cout << "- Output file to " << pedigree_file_out << "." << endl;
    fstream checkRel; checkRel.open(pedigree_file_out.c_str(), std::fstream::out | std::fstream::trunc); checkRel.close();
    /* Save as a continuous string and then output */
    stringstream outputstring(stringstream::out); int outputnumber = 0;
    /* output relationship matrix */
    for(int ind1 = 0; ind1 < pedigree.size(); ind1++)
    {
        for(int ind2 = 0; ind2 < pedigree.size(); ind2++)
        {
            if(ind2 >= ind1)
            {
                outputstring << pedigree[ind1].getanim() << " "<<pedigree[ind2].getanim()<<" ";
                outputstring << Amatrix[ind1][ind2] << endl;
                if(outputnumber % 1000 == 0)
                {
                    /* output pheno pedigree file */
                    std::ofstream output9(pedigree_file_out.c_str(), std::ios_base::app | std::ios_base::out);
                    output9 << outputstring.str(); outputstring.str(""); outputstring.clear();
                }
                outputnumber++;
            }
        } /* Finish loop across ind2 */
        loadbar(ind1+1,pedigree.size());
    } /* Finish loop across ind1 */
    cout << endl;
    /* output rest of them */
    std::ofstream output9(pedigree_file_out.c_str(), std::ios_base::app | std::ios_base::out);
    output9 << outputstring.str(); outputstring.str(""); outputstring.clear();
    if(argc == 5)
    {
        cout << "- Begin to construct and output a portion of the relationships" << endl;
        time_t sub_begin_time = time(0);
        vector < string > subsetids;
        vector < int > rowbigA;             /* used to index which row/col the animal is on */
        string line;
        /* Import file and put each row into a vector then grab chromsome and position */
        ifstream infile;
        infile.open(outsubsetrelationship.c_str());
        while (getline(infile,line)){subsetids.push_back(line); rowbigA.push_back(-5);}
        cout << "   - Pedigree file read in and number of animals is " << subsetids.size() << endl;
        cout << "   - Figure out where animals are located in the full A Matrix." << endl;
        for(int i = 0; i < subsetids.size(); i++)
        {
            int j = 0; string found = "NO";
            while(found == "NO")
            {
                if(pedigree[j].getanim() == subsetids[i]){rowbigA[i] = pedigree[j].getrenumanim() - 1; found = "YES";}
                if(pedigree[j].getanim() != subsetids[i]){j++;}
                if(j >= pedigree.size()){cout << "Couldn't Find Animal!!" << endl; exit (EXIT_FAILURE);}
            }
        }
        /* Build SubA */
        cout << "   - Fill A Matrix for desired animals." << endl;
        vector< vector < double >> SubAmatrix;
        for(int i = 0; i < subsetids.size(); i++)
        {
            vector < double > row(subsetids.size(),0); SubAmatrix.push_back(row);
        }
        for(int i = 0; i < subsetids.size(); i++)
        {
            for(int j = i; j < subsetids.size(); j++)
            {
                SubAmatrix[i][j] = Amatrix[rowbigA[i]][rowbigA[j]];
                if(i != j){SubAmatrix[i][j] = SubAmatrix[j][i] = Amatrix[rowbigA[i]][rowbigA[j]];}
            }
        }
        string subsetoutputfile = "sub_" + pedigree_file_out;
        cout << "- Output file to " << subsetoutputfile << "." << endl;
        fstream checkRela; checkRela.open(subsetoutputfile.c_str(), std::fstream::out | std::fstream::trunc); checkRela.close();
        /* Save as a continuous string and then output */
        stringstream outputstringa(stringstream::out); int outputnumber = 0;
        /* output relationship matrix */
        for(int ind1 = 0; ind1 < subsetids.size(); ind1++)
        {
            for(int ind2 = 0; ind2 < subsetids.size(); ind2++)
            {
                if(ind2 >= ind1)
                {
                    outputstringa << subsetids[ind1] << " "<< subsetids[ind2] <<" ";
                    outputstringa << SubAmatrix[ind1][ind2] << endl;
                    if(outputnumber % 1000 == 0)
                    {
                        /* output pheno pedigree file */
                        std::ofstream output10(subsetoutputfile.c_str(), std::ios_base::app | std::ios_base::out);
                        output10 << outputstringa.str(); outputstringa.str(""); outputstringa.clear();
                    }
                    outputnumber++;
                }
            } /* Finish loop across ind2 */
        } /* Finish loop across ind1 */
        /* output rest of them */
        std::ofstream output10(subsetoutputfile.c_str(), std::ios_base::app | std::ios_base::out);
        output10 << outputstringa.str(); outputstringa.str(""); outputstringa.clear();
        time_t sub_end_time = time(0);
        cout << "- Finished Constructing Subset A Matrix (Took: ";
        cout << difftime(sub_end_time,sub_begin_time) << " seconds)" << endl << endl;
    }
    time_t full_end_time = time(0);
    cout << "- Finished Program (Took: " << difftime(full_end_time,full_begin_time) << " seconds)" << endl << endl;
}



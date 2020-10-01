#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iterator>
#include <set>
#include <string>
#include <vector>

/* This program
 * "assigns" too lists of names of the same size
 * to each "randomly"
 */

int main(int argc, char ** argv)
{
	if(argc < 3)
	{
		fprintf(stdout, "usage: tassign [names 1 file] [names 2 files]\n");
		exit(0);
	}

	else
	{
		FILE * fn1 = fopen(argv[1], "r"); 
		FILE * fn2 = fopen(argv[2], "r");

		char ct = '\0';

		std::vector<std::string> nvec1;
		std::vector<std::string> nvec2;

		std::string nextname;
		while((ct = fgetc(fn1)) != EOF)
		{
			if(ct == '\n')
			{
				nvec1.push_back(nextname);
				nextname = "";
			}
			else
			{
				nextname += ct;
			}
		}
		fclose(fn1);

		
		while((ct = fgetc(fn2)) != EOF)
		{
			if(ct == '\n')
			{
				nvec2.push_back(nextname);
				nextname = "";
			}
			else
			{
				nextname += ct;
			}
		}

		fclose(fn2);

		// Read in names
		if(nvec1.size() != nvec2.size())
		{
			fprintf(stderr, "[error]: sizes of both name lists should be the same.\n");
			exit(2);
		}


		int count = nvec1.size();

		if(count == 0)
		{
			fprintf(stderr, "[error]: count should be > 0\n");
			exit(1);
		}

		srand(time(nullptr));

		int val;

		std::set<int> sind;
		
		int r = 1;
		
		// Copy each name into a new vector
		std::vector<int> names_v;
		while(sind.size() < count)
		{
			val = rand() % count;
			if(sind.find(val) == sind.end()) 
			{
				// strips duplicates
				if(sind.find(val) == sind.end()) 
				{
					sind.insert(val);
					names_v.push_back(val);
					++r;
				}
			}
		}


		// Assign left to right,  based on index

		fprintf(stdout, "-ASSIGNMENT-\n");
		for(int it = 0; it < count; ++it)
		{
			fprintf(stdout, "%s : %s\n", nvec1[it].c_str(), nvec2[names_v[it]].c_str());
		}

		return 0;
	}
}

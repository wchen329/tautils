#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

typedef std::vector<std::string> Vec_str;
typedef Vec_str::iterator Vec_str_it;

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		fprintf(stdout, "Usage: grouper [list of names] [number of groups]\n");
		exit(0);
	}

	int gp = atoi(argv[2]);
	if(gp == 0)
	{
		fprintf(stdout, "[error] group count is invalid (must be > 0)");
		exit(0);
	}

	Vec_str nvec1;

	FILE * fn1 = fopen(argv[1], "r"); 
	std::string nextname;
	char ct;
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

	std::random_shuffle<Vec_str_it>(nvec1.begin(), nvec1.end());

	int count = 0;
	int group = 1;

	// Do iterated print
	for(size_t bb = 0; bb < nvec1.size(); ++bb)
	{
		count = bb % gp;
		group = (bb / gp) + 1;

		if(count == 0)
		{
			fprintf(stdout, "--GROUP No. %d--\n", group);
		}

		fprintf(stdout, "%s\n", nvec1[bb].c_str());
	}

	return 0;
}

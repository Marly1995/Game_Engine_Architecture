#include "c:\Users\Marlon\Documents\GitHub\Game_Engine_Architecture\includes.h"
#include "Heatmap.h"
#include "Histogram.h"
#include "Trajectory.h"

using namespace std;

class DataManager
{
public:
	vector<Heatmap> heatmaps;
	vector<Histogram> histograms;
	vector<Trajectory> trajectories;

	DataManager();

	int loadFile(char* fileDirectory);
	void loadPowerFile(char* fileDirectory);
	void loadPositionFile(char* fileDirectory);
};
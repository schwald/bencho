#ifndef PLOTTERGNUPLOT_H
#define PLOTTERGNUPLOT_H

#define TERMINAL "ps"
#define PS2PDF true

#include <stdio.h>

#include <vector>
#include <string>

#include "AbstractPlotter.h"

class PlotterGnuplot : public AbstractPlotter
{
private:
	string _terminal;

	void callPlot(string resultDir, string plotterScript, string systemScript, string benchName, string benchId);
	string createFinalScript(string resultFile, string baseScript, string systemScript);

	void mergeSystemScript(string baseScript, string systemScript, string mergedScript);
	void replaceTerminals(string baseScript, string resultFile);
	void setPerfCounters(string baseScript, string resultFile);
	void setPlotCommands(string baseScript);

	void bufferSearchReplace(string replaceFile, string search, string replace);

	vector<string> getCounters(string baseScript);
	int getCounterPosition(string counter, string resultFile);
};


#endif //PLOTTERGNUPLOT_H
#ifndef PLOTTERPYTHON_H
#define PLOTTERPYTHON_H


#include "AbstractPlotter.h"

class PlotterPython : public AbstractPlotter
{
public:
	void callPlot(string resultDir, string plotterScriptDir, string benchName, string benchId);
};


#endif //PLOTTERPYTHON_H
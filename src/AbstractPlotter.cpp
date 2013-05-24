#include "AbstractPlotter.h"


AbstractPlotter::AbstractPlotter()
{
	_resultDir = "./results";
	_plotterScriptDir = "./benchmarks";
	_systemScriptDir = "./bencho/plotting";

	_plotterScript = "";
	_systemScript = "";

	_benchName = "";
	_benchId = "";
}

AbstractPlotter::~AbstractPlotter()
{

}


void AbstractPlotter::plot()
{
	string resultFile = getResultFile(getBenchName(), getBenchId(), getResultDir());
	if (fileExists(resultFile))
	{
		callPlot(getResultDir(), getPlotterScript(), getSystemScript(), getBenchName(), getBenchId());
	} else {
		cerr << "No result file of benchmark: " << getBenchName() << ", Id: " << getBenchId() << " available." << endl;
	}
}

void AbstractPlotter::setUp(bool isDefault)
{
	setBenchName(findBenchName(getResultDir()));
	setBenchId(findBenchId(getBenchName(), getResultDir()));

	if(!isDefault)
	{
		string userinput;
		cout << "Name of Benchmark?" << endl << "(default: " << getBenchName() << ")" << endl;
		getline(cin, userinput);
		if(!userinput.empty())
		{
			setBenchName(userinput);
			setBenchId(findBenchId(getBenchName(), getResultDir()));
		}
		cout << "ID?" << endl << "(default: " << getBenchId() << ")" << endl;
		getline(cin, userinput);
		if(!userinput.empty())
		{
			setBenchId(userinput);
		}
	}
}

void AbstractPlotter::setUp(string resultDir, string plotterScriptDir, string systemScriptDir, string plotterScript, string systemScript, string benchName, string benchId)
{
	setResultDir(resultDir);
	setPlotterScriptDir(plotterScriptDir);
	setSystemScriptDir(systemScriptDir);
	setPlotterScript(plotterScript);
	setSystemScript(systemScript);
	setBenchName(benchName);
	setBenchId(benchId);
}

void AbstractPlotter::pdfcropResult()
{
	string resultDir = getResultDir();
	string benchName = getBenchName();
	string benchId = getBenchId();

	struct dirent *de=NULL;
  	DIR *d=NULL;
	string benchmarksResultDir = resultDir + "/" + benchName;
	string resultPrefix = benchName + "_" + benchId + "_";
	d = opendir(benchmarksResultDir.c_str());
	if (d)
	{
		while((de = readdir(d))) {
		if (strncmp(resultPrefix.c_str(), de->d_name, resultPrefix.size()) == 0) {
			pdfCropFile(benchmarksResultDir + "/" + de->d_name);
		}
    }
    closedir(d);
	} else { perror(benchmarksResultDir.c_str()); }
}


string AbstractPlotter::createFinalScript(string resultFile, string baseScript)
{
	// overwrite this in actual plotter
	return baseScript;
}

void AbstractPlotter::callPlot(string resultDir, string plotterScript, string systemScript, string benchName, string benchId)
{
	// overwrite this in actual plotter
}


string AbstractPlotter::getResultDir()
{
	return _resultDir;
}

string AbstractPlotter::getPlotterScriptDir()
{
	return _plotterScriptDir;
}

string AbstractPlotter::getSystemScriptDir()
{
	return _systemScriptDir;
}

string AbstractPlotter::getPlotterScript()
{
	return _plotterScript;
}

string AbstractPlotter::getSystemScript()
{
	return _systemScript;
}

string AbstractPlotter::getBenchName()
{
	return _benchName;
}

string AbstractPlotter::getBenchId()
{
	return _benchId;
}

void AbstractPlotter::setResultDir(string resultDir)
{
	_resultDir = resultDir;
}

void AbstractPlotter::setPlotterScriptDir(string plotterScriptDir)
{
	_plotterScriptDir = plotterScriptDir;
}

void AbstractPlotter::setSystemScriptDir(string systemScriptDir)
{
	_systemScriptDir = systemScriptDir;
}

void AbstractPlotter::setPlotterScript(string plotterScript)
{
	_plotterScript = plotterScript;
}

void AbstractPlotter::setSystemScript(string systemScript)
{
	_systemScript = systemScript;
}

void AbstractPlotter::setBenchName(string benchName)
{
	_benchName = benchName;
}

void AbstractPlotter::setBenchId(string benchId)
{
	_benchId = benchId;
}
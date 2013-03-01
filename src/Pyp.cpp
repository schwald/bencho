#include <Python.h> // need to include this here and not in the .h file to avoid some macro overwriting warnings
#include "Pyp.h"


Pyp::Pyp()
{
	_resultDir = "./results";
	_pyScriptDir = "./benchmarks";

	_benchName = "";
	_id = "";
}

Pyp::~Pyp()
{

}


void Pyp::plot()
{
	Pyp::plot(Pyp::getResultDir(), Pyp::getPyScriptDir(), Pyp::getBenchName(), Pyp::getBenchId());
}

void Pyp::plot(string resultDir, string pyScriptDir, string benchName, string benchId)
{
	string resultFile = getResultFile(benchName, benchId, resultDir);
	string pyScript = pyScriptDir + "/" + benchName + ".py";
	string pyScriptFinal = Pyp::createFinalPyScript(pyScript, resultFile);


	// ToDo: Check first if file exists
	Pyp::callPythonPlot(resultFile, pyScriptFinal);
}

void Pyp::callPythonPlot(string resultFile, string scriptFile)
{
	PyObject *pName, *pModule, *pFunc, *pString, *pArgs;

	// Initialize the Python Interpreter
	Py_Initialize();

	// Build the name object, this case the system.py
	pName = PyString_FromString("system");

	// Load the module object
	pModule = PyImport_Import(pName);

	// pFunc is a borrowed reference, "plot" the function to call
	pFunc = PyObject_GetAttrString(pModule, "plot");

	if (PyCallable_Check(pFunc))
	{
		pArgs = PyTuple_New(2); // plot() should expect 2 arguments
		pString = PyString_FromString(resultFile.c_str());
		if (!pString)
		{
			PyErr_Print();
			return;
		}
		PyTuple_SetItem(pArgs, 0, pString);
		pString = PyString_FromString(scriptFile.c_str());
		if (!pString)
		{
			PyErr_Print();
			return;
		}
		PyTuple_SetItem(pArgs, 0, pString);

		// Actual call of the function
		PyObject_CallObject(pFunc, pArgs);

		 if (pArgs != NULL)
		 	Py_DECREF(pArgs);
	}

	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_DECREF(pFunc);
	Py_DECREF(pString);

	// Finish the Python Interpreter
	Py_Finalize();
}

void Pyp::setUp(bool setDefault)
{
	Pyp::setBenchName(findBenchName(Pyp::getResultDir()));
	Pyp::setBenchId(findBenchId(Pyp::getBenchName(), Pyp::getResultDir()));

	if(!setDefault)
	{
		string userinput;
		cout << "Name of Benchmark?" << endl << "(default: " << Pyp::getBenchName() << ")" << endl;
		getline(cin, userinput);
		if(!userinput.empty())
		{
			Pyp::setBenchName(userinput);
			Pyp::setBenchId(findBenchId(Pyp::getBenchName(), Pyp::getResultDir()));
		}
		cout << "ID?" << endl << "(default: " << Pyp::getBenchId() << ")" << endl;
		getline(cin, userinput);
		if(!userinput.empty())
		{
			Pyp::setBenchId(userinput);
		}
	}
}

string Pyp::createFinalPyScript(string pyScriptBase, string ResultFile)
{
	string pyScriptFinal = pyScriptBase;
	return pyScriptFinal;
}


string Pyp::getResultDir()
{
	return _resultDir;
}

string Pyp::getPyScriptDir()
{
	return _pyScriptDir;
}

string Pyp::getBenchName()
{
	return _benchName;
}

string Pyp::getBenchId()
{
	return _id;
}

void Pyp::setResultDir(string resultDir)
{
	_resultDir = resultDir;
}

void Pyp::setPyScriptDir(string pyScriptDir)
{
	_pyScriptDir = pyScriptDir;
}

void Pyp::setBenchName(string benchName)
{
	_benchName = benchName;
}

void Pyp::setBenchId(string id)
{
	_id = id;
}
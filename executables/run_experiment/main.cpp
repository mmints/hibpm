#include <hibpm/DeclareParser.hpp>
#include <hibpm/DeclareKnowledgeBase.hpp>
#include <filesystem>
#include <string.h>

using namespace hibpm;
namespace fs = std::filesystem;

// Enumeration of all different types of experiment that can be performed
enum ExperimentType {
    NONE, // If the input argument does not mach to the experiment types
    LAZY_EXPAND,
    EGO_EXPAND,         // TODO: This state is not implemented for now
    LAZY_EXPAND_SHRINK  // TODO: This state is not implemented for now
    // TODO: Extant this enumeration with further types/states
};

ExperimentType selectExperimentType(char* &experiment)
{
    if (strcmp(experiment,"--lazy-expand") == 0 || strcmp(experiment,"-le") == 0)
        return LAZY_EXPAND;

    if (strcmp(experiment,"--ego-expand") == 0 || strcmp(experiment, "-ee") == 0)
        return EGO_EXPAND;

    if (strcmp(experiment,"--lazy-expand-shrink") == 0 || strcmp(experiment,"-les") == 0)
        return LAZY_EXPAND_SHRINK;

    // TODO: Insert missing cases

    // Error handling of work argument input
    std::cout << "Experiment option does not exist!" << std::endl;
    return NONE;
}

void printHelp()
{
    std::cout <<

    "Help Page\n" <<
    "\nUse as following:\n" <<
    "\t./run_experiment <OPTION> <INPUT_PATH> <OUTPUT_PATH>\n" <<

    "\nOPTIONS:\n" <<
    "\t[-h, --help] This message. \n" <<
    "\t[-le, --lazy-expand] This message \n" <<
    "\t[-ee, --ego-expand] This message \n" <<
    "\t[-les, --lazy-expand-shrink] This message \n" <<

    "\nINPUT_PATH:\n" <<
    "\tPath to a model in HIBPM format (.txt).\n" <<

    "\nOUTPUT_PATH:\n" <<
    "\tPath to a directory where to save the results of the experiment. \n" <<
    std::endl;
}

void writeResultsToFile(fs::path &input,fs::path &output)
{
    // TODO: Write correct Data into csv file
    // For now, this function is just a template for writing printing functions
    string out = output.string() +"/"+ input.filename().replace_extension("csv").string();
    std::cout <<"Output dir: " << out << std::endl;

    std::ofstream outfile (out);
    outfile << "my text here!" << std::endl;
    outfile.close();
}

int main(int argc, char** argv)
{
    // Welcome Msg
    std::cout <<"HIBPM Experiment Running Environment\n" << std::endl;

    // Check if input is ok
    if (argc == 1 || argc != 4 && (strcmp(argv[1],"-h") != 0 || strcmp(argv[1],"--help") == 0)) {
        std::cout << "Wrong usage of the application! \n"
                  << "Use Like this \n"
                  << "\t ./run_experiment <OPTION> <INPUT_PATH> <OUTPUT_PATH>"
                  << std::endl;
        return -1;
    }

    // Handle helping screen
    if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0) {
        printHelp();
        return 0;
    }

    fs::path inputFile(argv[2]);
    if (!fs::exists(inputFile))
    {
        std::cout << "The file " << inputFile << " does not exist." << std::endl;
        return -1;
    }

    fs::path outputPath(argv[3]);
    if (!fs::exists(outputPath))
    {
        std::cout << "The output path " << inputFile << " does not exist." << std::endl;
        return -1;
    }

    // Check options for the experiment type and execute the experiment
    ExperimentType experimentType = selectExperimentType(argv[1]);
    switch (experimentType)
    {
        case NONE: {
            std::cout << "Exit" << std::endl;
            return 0;
        }
        case LAZY_EXPAND: {
            std::cout << "LAZY_EXPAND" << std::endl;
            break;
        }
        case EGO_EXPAND: {
            std::cout << "TODO: EGO_EXPAND" << std::endl; // TODO: Add experiment
            break;
        }
        case LAZY_EXPAND_SHRINK: {
            std::cout << "TODO: LAZY_EXPAND_SHRINK" << std::endl; // TODO: Add experiment
            break;
        }
    }

    writeResultsToFile(inputFile, outputPath);

    std::cout << "Done.\n Results of the the experiment on model "
    << inputFile.filename().replace_extension("")
    << " where written to " << outputPath.filename()
    << std::endl;
    return 0;
}
